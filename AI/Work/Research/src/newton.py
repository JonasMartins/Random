'''
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''
from numpy import *
from line_search import find_step_length

# f a funcao principal
# fd gradiente de f
# fdd hassian matrix
# callback uma funcao para imprimir cada iteracao
def newton(f, fd, fdd, x, max_iterations, precision, callback):
	for i in range(1, max_iterations):
		gradient = fd(x)
		hessian = fdd(x)
		
		# linalg: numpy function
		# linalg.solve: Solve a linear matrix equation, or system of linear scalar equations.
		# Computes the “exact” solution, x, of the well-determined, i.e., full rank, linear matrix equation ax = b.
		direction = -linalg.solve(hessian, gradient)
		
		'''
		Example:
		3 * x0 + x1 = 9 and x0 + 2 * x1 = 8:
		a = np.array([[3,1], [1,2]])
		b = np.array([9,8])
		x = np.linalg.solve(a, b)
		x: array([ 2.,  3.])
		'''
		
		# Metodo tradicional:
		# ainv is the hassian inverse
		# ainv = linalg.inv(hessian)
		

		alpha = find_step_length(f, fd, x, 1.0, direction, c2=0.9)
		x_prev = x
		x = x + alpha*direction
		
		callback(i, direction, alpha, x)
		
		if linalg.norm(x - x_prev) < precision:
		  break
		return x
	
