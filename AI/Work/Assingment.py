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
X = np.arange(-3, 3, 0.1)
Y = np.arange(-2.0, 2.0, 0.1)
X, Y = np.meshgrid(X, Y)
Z = ((4-(2.1*(X**2)))+(1/3)*(X**4))+((X*Y)-(4*(1-(Y**2))*(Y**2)))
fig = plt.figure()
ax = Axes3D(fig)
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.viridis)
plt.show()
