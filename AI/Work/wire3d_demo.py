'''
=================
3D wireframe plot
=================

A very basic demonstration of a wireframe plot.

source: https://matplotlib.org/mpl_toolkits/mplot3d/tutorial.html

'''

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Grab some test data.
X, Y, Z = axes3d.get_test_data(0.05)

# Plot a basic wireframe.
# rstride is Array row stride and cstride is Array column stride  
ax.plot_wireframe(X, Y, Z, rstride=5, cstride=5)

plt.show()
