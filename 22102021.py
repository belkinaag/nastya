import matplotlib.pyplot as plt
import numpy as np

with open("/home/gr102/Desktop/Scripts/belkina-repo/settings.txt", "r") as settings:
    tmp=[float(i) for i in settings.read().split("\n")]

data_array = np.loadtxt("/home/gr102/Desktop/Scripts/belkina-repo/data.txt", dtype=int)

fig, ax = plt.subplots(figsize=(16,10), dpi=400)

time_array = []
voltage_array = tmp[0]*data_array
for i in range(len(voltage_array)):
    time_array.append(i*tmp[1])

ax.plot(time_array, voltage_array, "m", linewidth = '1.0', marker = '*', markevery=50, markersize = '12.0')

ax.set_xlim([min(time_array), 1.1*max(time_array)])
ax.set_ylim([min(voltage_array), 1.1*max(voltage_array)])

plt.title("Процесс заряда и разряда конденсатора в RC-цепи", fontstyle = 'italic', horizontalalignment = 'center')
plt.xlabel("Время, с")
plt.ylabel("Напряжение, V")
plt.legend("V(t)")

plt.grid(which='major', color='green', linestyle='-', linewidth = 0.5)
plt.grid(which='minor', color='green', linestyle='--', linewidth = 0.25)

plt.text(20, 1, "Время зарядки = 16.08 с ", fontstyle = 'italic', fontsize = 'small')
plt.text(20, 0.95, "Время разрядки = 9.52 с ", fontstyle = 'italic', fontsize = 'small')

plt.minorticks_on()

fig.savefig("test.svg")


plt.show()


    
    