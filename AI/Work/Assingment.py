"""

	 INSTALAR A BIBLIOTECA MATPLOT:
	 LINUX: sudo apt-get install python3-matplotlib
	 ALTER: https://matplotlib.org/users/installing.html

	 INSTALAR NUMPY:
	 https://www.scipy.org/scipylib/download.html

"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

X = np.arange(-5, 5, 0.5)
Y = np.arange(-5, 5, 0.5)
X, Y = np.meshgrid(X, Y)
R = np.sqrt(X**2 + Y**2)
Z = np.sin(R)

# sin(raiz de (x^2+y^2))

fig = plt.figure()
ax = Axes3D(fig)
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.viridis)

plt.show()
