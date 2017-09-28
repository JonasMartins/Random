#!/usr/bin/python
# encoding: utf-8
# 
import math

class Transformation:
  
  def __init__(self,alfa,translation,scale,theta):
    
    self.alfa = alfa
    # translação é apenas um vetor comum como uma lista
    self.trans = translation

    # tambem um vetor
    self.scale = scale
    self.theta = float(theta)
    self.sintheta = math.sin(self.theta)
    self.costhetha = math.cos(self.theta)
  
  def minus(self,value):
    return value * (-1)

  def get_matrix(self,argument):
    switcher = {

    # xy na direção x cxy
     0: [ [1,math.tan(self.alfa),0,0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1] ],

    # yz na direção y cyz
     1: [ [1,0,0,0],
            [0,1,math.tan(self.alfa),0],
            [0,0,1,0],
            [0,0,0,1] ],

    # xz na direção x cxz
     2: [ [1,0,math.tan(self.alfa),0],
            [0,1,0,0],
            [0,0,1,0],
            [0,0,0,1] ],

    # zx na direção z czx
     3: [ [1,0,0,0],
            [0,1,0,0],
            [math.tan(self.alfa),0,1,0],
            [0,0,0,1] ],

    # zy na direção z czy
     4: [ [1,0,0,0],
            [0,1,0,0],
            [0,math.tan(self.alfa),1,0],
            [0,0,0,1] ],

    # yx na direção y cyx
     5: [ [1,0,0,0],
            [math.tan(self.alfa),1,0,0],
            [0,0,1,0],
            [0,0,0,1] ],

     # MATRIZ DE TRANSLAÇÃO
     6: [ [1,0,0,self.trans[0]],
          [0,1,0,self.trans[1]],
          [0,0,1,self.trans[2]],
          [0,0,0,1] ],
     
     # MATRIZ DE ESCALA
     7: [ [self.scale[0],0,0,0],
          [0,self.scale[1],0,0],
          [0,0,self.scale[2],0],
          [0,0,0,1] ],

     # MATRIZ DE ROTAÇÃO EIXO X
     8: [ [1,0,0,0],
          [0,self.costhetha,self.minus(self.sintheta),0],
          [0,self.sintheta,self.costhetha,0],
          [0,0,0,1] ],

     # MATRIZ DE ROTAÇÃO EIXO Y
     9: [ [self.costhetha,0,self.sintheta,0],
          [0,1,0,0],
          [self.minus(self.sintheta),0,self.costhetha,0],
          [0,0,0,1] ],

     # MATRIZ DE ROTAÇÃO EIXO Z
     10: [ [self.costhetha,self.minus(self.sintheta),0,0],
          [self.sintheta,self.costhetha,0,0],
          [0,0,self.scale[2],0],
          [0,0,0,1] ],
     
     # ESPELHO XZ
     11: [ [1,0,0,0],
          [0,-1,0,0],
          [0,0,1,0],
          [0,0,0,1] ],
     
     # ESPELHO YZ
     12: [ [-1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ],

     # ESPELHO XY
     13: [ [1,0,0,0],
          [0,1,0,0],
          [0,0,-1,0],
          [0,0,0,1] ],

    }
    return switcher.get(argument, None)
   

  # # checar possibilidade de multipliçãoo entre as matrizes
  # def __checkTimes(self):
  #   if(self.matrix1.get_columns() != self.matrix2.get_rows()):
  #     print('Impossível multiplicar as matrizes dadas')
  #   return

  # def timesMetrix(self):

  #   h = self.matrix1.get_rows()
  #   w = self.matrix2.get_columns()
  #   y = self.matrix2.get_rows()

  #   self.m3 = Matrix(h,w)

  #   for i in range(0,h):
  #     for j in range(0,w):
  #       for k in range(0,y):
  #         m3[i][j] += m1[i][k] * m2[k][j]

  #   return m3

    




# m1 = Matrix(file = 'matriz1.txt')
# m2 = Matrix(file = 'matriz2.txt')


# o length do vetor é o numero de colunas
# a quantidade de cada elemento é o numero de linhas
# v = [[0,0,7,1]]

# m3 = Matrix(rows = 4,columns = 4)


# m1.showMatrix()
# m2.showMatrix()
# m3.generate_identity()
# m3.showMatrix()
# 

# def checkTimes(matrix1,matrix2):
#   if matrix1.get_columns() != matrix2.get_rows():
#     print('Impossível multiplicar as matrizes dadas')
#     sys.exit()
#   return

# def timesMetrix(m1,m2,scalar):
#   m3 = None
#   if scalar is not None:
#     m3 = Matrix(rows = m1.get_rows(),columns = m1.get_columns())
#     for i in range(0,m3.get_variable('columns')):
#       for j in range(0,m3.get_variable('rows')): 
#         m3.get_variable('matrix')[i][j] = m1.get_variable('matrix')[i][j] * scalar

#   else:
#     checkTimes(m1,m2)
    
#     h = m1.get_rows()
#     w = m2.get_columns()
#     y = m2.get_rows()

#     m3 = Matrix(rows = h,columns = w)
#     for i in range(0,w):
#       for j in range(0,h):
#         for k in range(0,y):
#           m3.get_variable('matrix')[i][j] += m1.get_variable('matrix')[i][k] * m2.get_variable('matrix')[k][j]

#   return m3

# def main():
#   m3 = Matrix(file='matriz1.txt')
#   # m4 = Matrix(file='matriz1.txt')
#   m5 = Matrix(matrix = v)
#   # m7 = timesMetrix(m5,None,5)
#   # m7.showMatrix()
#   t = Transformation()
#   t.set_variable('matrix1',m5)

if __name__ == "__main__": main()