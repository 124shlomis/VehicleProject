import matplotlib.pyplot as plt
import numpy as np
data = np.loadtxt('./pathPoints.txt')
x = data[:, 0]
y = data[:, 1]
plt.plot(x, y, 'r.')
data = np.loadtxt('./VehiclePosition.txt')
if data.ndim == 1:
    x = data[0]
    y = data[1]
else:
    x = data[:, 0]
    y = data[:, 1]
plt.plot(x, y, 'b.')
plt.axis('equal')
plt.xlabel('x [m]')
plt.ylabel('y [m]')
plt.title('Vehicle Simulation')
plt.grid()
plt.legend(['Global Path', 'Vehicle Position'])
plt.show()
