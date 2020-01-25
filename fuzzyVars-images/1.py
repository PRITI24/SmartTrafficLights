import numpy as np
import skfuzzy as fuzz
import matplotlib.pyplot as plt

# Queue

x = np.arange(0, 14, 1)

vshort = fuzz.trimf(x, [0, 0, 2])
short = fuzz.trapmf(x, [1, 2, 4, 5])
middle = fuzz.trimf(x, [4, 6, 8])
long = fuzz.trapmf(x, [7, 8, 10, 11])
vlong = fuzz.trimf(x, [10, 13, 13])

plt.figure(figsize=(12, 4),dpi=50)

plt.plot(x, vshort, 'b', linewidth=1.5, label='very short')
plt.plot(x, short, 'g', linewidth=1.5, label='short')
plt.plot(x, middle, 'r', linewidth=1.5, label='middle')
plt.plot(x, long, 'y', linewidth=1.5, label='long')
plt.plot(x, vlong, 'purple', linewidth=1.5, label='very long')
plt.plot(x, x*0, 'k') #just to hide all colors at the botton

plt.legend(loc='center left', bbox_to_anchor=(0.87, 0.5))
y = np.arange(0,1.5,1)
plt.xticks(x, x)
plt.yticks(y, y)
plt.show()

# Arrival

x = np.arange(0, 7, 1)

small = fuzz.trimf(x, [0, 0, 2])
average = fuzz.trimf(x, [1, 3, 5])
big = fuzz.trimf(x, [4, 6, 6])

plt.figure(figsize=(12, 4),dpi=50)

plt.plot(x, small, 'b', linewidth=1.5, label='small')
plt.plot(x, average, 'g', linewidth=1.5, label='average')
plt.plot(x, big, 'r', linewidth=1.5, label='big')
plt.plot(x, x*0, 'k')

plt.legend(loc='center left', bbox_to_anchor=(0.87, 0.5))

plt.xticks(x, x)
plt.yticks(y, y)
plt.show()

# Extension

x = np.arange(0, 26, 1)

vsmall = fuzz.trimf(x, [0, 0, 10])
small = fuzz.trapmf(x, [0, 5, 10, 15])
big = fuzz.trapmf(x, [10, 15, 20, 25])
vbig = fuzz.trimf(x, [15, 25, 25])

plt.figure(figsize=(12, 4),dpi=50)

plt.plot(x, vsmall, 'b', linewidth=1.5, label='very small')
plt.plot(x, small, 'g', linewidth=1.5, label='small')
plt.plot(x, big, 'r', linewidth=1.5, label='big')
plt.plot(x, vbig, 'y', linewidth=1.5, label='very big')
plt.plot(x, x*0, 'k')

plt.legend(loc='center left', bbox_to_anchor=(0.87, 0.5))

plt.xticks(x, x)
plt.yticks(y, y)
plt.show()
