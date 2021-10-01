import RPi.GPIO as GPIO
import time
dac = [26, 19, 13, 6, 5, 11, 9, 10]
bits = len(dac)
levels = 2**bits
maxVoltage = 3.3
troykaModule = 17
comparator = 4


GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(troykaModule,  GPIO.OUT, initial=GPIO.HIGH)
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
        voltage = value/ levels * maxVoltage
        time.sleep(0.0007)
        comporatorValue = GPIO.input(comparator)
        if comporatorValue == 0:
            value-=s[i]
        print("ADC value = {:^3} -> {}, input  voltage = {:.2f}".format(value,signal,voltage))
        
try:
    while True:
        adc()
except KeyboardInterrupt:
    print('\nThe programm was stopped by the keyboard')
else:
    print("No exceptions")
finally:
    GPIO.output(dac, GPIO.LOW)
    GPIO.cleanup(dac)
    print('GPIO cleanup completed')