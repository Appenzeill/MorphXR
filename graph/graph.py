import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt
import math

arm_length = 50
angle = -90

sine_degrees = math.sin(math.radians(angle))
divider = 1 / sine_degrees
z = arm_length / divider

len_a = arm_length*arm_length
len_b = z*z
y = math.sqrt(len_a - len_b)

# 25
print(round(z))

# 43
print(round(y))


mpl.rcParams['legend.fontsize'] = 10

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_ylim(0,100)
ax.set_xlim(0,100)
ax.set_zlim(0,100)

# Get some 3D data
# X = [50, 50, 50]
# Y = [50, 100, 120]
# Z = [30, 50, 70]

X = [50, 50, 50]
Y = [0, 50, 50 + y]
Z = [50, 50, 50 + z]



# Plot using Axes notation and standard function calls
ax.plot(X, Y, Z)
plt.show()
