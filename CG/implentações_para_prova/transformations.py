#!/usr/bin/python
# encoding: utf-8
# 

class Transformation:
  
  def __init__(self,m1,m2):
    self.m1 = m1
    self.m2 = m2
    self.checkTimes()

  # # checar possibilidade de multiplicaÃ§Ã£o entre as matrizes
  def checkTimes(self):
    if(self.getColumns(m1) != self.getRows(m2)):
      print('ImpossÃ­vel multiplicar as matrizes dadas')
    return

  def getRows(self,matrix):
    return len(matrix)

  def getColumns(self,matrix):
    return len(matrix[0]) 

  def timesMetrix(self):

    h = getRows(self.m1)
    w = getColumns(self.m2)
    y = getRows(self.m2)

    m3 = allocMatrix(h,w)

    for i in range(0,h):
      for j in range(0,w):
        for k in range(0,y):
          m3[i][j] += m1[i][k] * m2[k][j]

    return m3

    