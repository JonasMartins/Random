#!/usr/bin/python
# encoding: utf-8

from matrix_operations import Matrix

m1 = Matrix(file = 'matriz1.txt')
m2 = Matrix(file = 'matriz2.txt')

m1.setEnvFile();
m2.setEnvFile();

m1.fillMatrix()
m2.fillMatrix()

m1.showMatrix()
m2.showMatrix()
