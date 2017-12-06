from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

'''
def get_test_data(delta=0.05):

    from matplotlib.mlab import  bivariate_normal
    x = y = np.arange(-3.0, 3.0, delta)
    X, Y = np.meshgrid(x, y)

    Z1 = bivariate_normal(X, Y, 1.0, 1.0, 0.0, 0.0)
    Z2 = bivariate_normal(X, Y, 1.5, 0.5, 1, 1)
    Z = Z2 - Z1

    X = X * 10
    Y = Y * 10
    Z = Z * 500
    return X, Y, Z

'''


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

x, y, z = axes3d.get_test_data(0.05)

# print(x)
# print(y)
# print(z)
s = .25
X = np.arange(-2, 2.+s, s) #arange(start,finish,increment), stores resulting vector in X
Y = np.arange(-1, 3.+s, s)

X, Y = np.meshgrid(X, Y)
Z = map(function, X, Y)


print(X)
print(Y)


#ax.plot_wireframe(x,y,z, rstride=1, cstride=1)

#plt.show()