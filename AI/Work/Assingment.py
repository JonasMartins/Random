#!usr/bin/python3

"""

	 INSTALL MATPLOT LIB:
	 LINUX: sudo apt-get install python3-matplotlib
	 ALTER: https://matplotlib.org/users/installing.html

	 INSTALL NUMPY:
	 https://www.scipy.org/scipylib/download.html

"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

X = np.arange(0, 3, 0.1)
Y = np.arange(-2.0, 0.5, 0.1)

X, Y = np.meshgrid(X, Y)

# f (x) = (4 − 2.1x^2  + 1/3* x^4)y + x*y − 4(1 − y^2)y^2


# d/dx(f(x)) = y(1.33x^3 - 4.2x)+y 
# d/dy(f(x)) = -2.1x^2 + 0.333 x^4 + x-4(-4y^3+2y)


# R = np.sqrt(X**2 + Y**2)
# Z = np.sin(R)

R = Y * ( (4 - (2.1 * (X**2))) + (1/3) * (X**4))
Z = R + ((X * Y) - (4 * (1 - (Y**2)) * (Y**2)))
# sin(raiz de (x^2+y^2))

fig = plt.figure()
ax = Axes3D(fig)
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.viridis)

plt.show()
