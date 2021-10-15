import RPi.GPIO as GPIO
import time
import matplotlib.pyplot as plot
dac = [26, 19, 13, 6, 5, 11, 9, 10]
leds = [21, 20, 16, 12, 7, 8, 25, 24]
bits = len(dac)
levels = 2**bits
print(dac, bits, levels)
maxVoltage = 3.3
comparator = 4
step_voltage = maxVoltage / levels
period = 0.007
frequency = 1 / period

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(leds,  GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(comparator, GPIO.IN)




def decimal2binary(decimal): 
    return [int(bit) for bit in bin(decimal)[2:].zfill(bits)]
def num2dac(value):             
    signal = decimal2binary(value)
    GPIO.output(dac, signal)
    return signal
def adc():                       
    value = 0
    s = [128,64,32,16,8,4,2,1]
    for i in range(len(s)):
        value += s[i]
        signal = num2dac(value)
        time.sleep(period)
        comporatorValue = GPIO.input(comparator)
        if comporatorValue == 0:
            value-=s[i]
        voltage = value/ levels * maxVoltage
    print("Digital value = {:^3} -> {}, Analog value = {:.2f}".format(value,signal,voltage))
    return value
try:
    GPIO.setup(17, GPIO.OUT, initial = GPIO.HIGH) # началась зарядка конденсатора
    time_of_start = time.time()        # запоминаем время начала зарядки конденсатора                  
    list = []  
    while True:
        value = adc()                        # считываем напряжение с конденсатора
        list.append(value)            # запоминаем значение в лист
        signal = decimal2binary(value)
        GPIO.output(leds, signal)            # подаём цифровой сигнал на светодиоды в области leds макетной платы
        print(value)
        if value >= 253:                   # если конденсатор практически полностью зарядился, то напряжение на конденсатор перестаёт подаваться
            GPIO.output(17, GPIO.LOW)
            break                           # конец зарядки
    
    while True:                                            # началась разрядка конденсатора на резистор
        value = adc()                                           
        list.append(value)                          # запоминаем значения напряжения на конденсаторе в лист 
        signal = decimal2binary(value)             
        GPIO.output(leds,signal)                           # подаём цифровой сигнал на светодиоды
        print (value)
        if value <= 3:                                     # конденсатор практически полностью разрядился
            break                                          # конец разрядки
    
    time_of_finish = time.time()                       # запоминаем время конца разрядки конденсатора 
    time_of_experiment= time_of_finish - time_of_start  # время длительности эксперимента
    print( "Длительность эксперимента ->", time_of_experiment, "Период измерений ->", period, "Частота дискретизации ->", frequency)   # выводим результаты эксперимента
    
    plot.plot(list)                                # строим график
    plot.show()

            
    with open("data.txt", "w") as file_data:                       # записываем данные эксперимента в файлы data.txt и settings.txt
        file_data.write("\n".join([str(item) for item in list]))
    settings = [period, step_voltage]
    with open("settings.txt", "w") as file_settings:
        file_settings.write("\n".join([str(item) for item in settings]))



except KeyboardInterrupt:
    print('\nThe programm was stopped by the keyboard')

finally: # очистка настроек макетной платы
    GPIO.output(leds, GPIO.LOW)
    GPIO.output(dac, GPIO.LOW)
    GPIO.cleanup(dac)
    GPIO.cleanup(leds)
    print("GPIO cleanup completed")
