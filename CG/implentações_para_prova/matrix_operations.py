#!/usr/bin/python
# encoding: utf-8

import sys

class Matrix:    

  def __init__(self,file):
    self.file = file
    self.columns = self.getColumns()
    self.rows = self.getRows()
    self.allocMatrix()
    self.fillMatrix()

  # Percorre a matriz do arquivo e cada item Ã© armazenado na matriz da memÃ³ria
  def fillMatrix(self):
    h = w = 0
    with open(self.file) as m:
       for line in m:
          line = line.split(',')
          line[len(line)-1] = line[len(line)-1].replace("\n","") 
          for i in range(len(line)):
            self.matrix[h][w] = int(line[i])
            w += 1
          h += 1 
          w = 0
          if 'str' in line:
            break
    print('')

  # Retona a dimensão de colunas de uma matriz
  def getColumns(self):
    length = 0
    with open(self.file) as m1:
      s = m1.readline()
      array = s.split(',')
    return len(array) # {\n}

  # Retona a dimensÃ£o de linhas de uma matriz
  def getRows(self):
    with open(self.file) as f:
      return sum(1 for _ in f)

  # Checar a disponibilidade ao se abrir um arquivo
  def checkOpen(self):
    value = False
    try:
      m1 = open(self.file)
      m1.close()
      #print(type(s) is str)
      value = True
    except IOError as e:
      print ("I/O error")
    # except ValueError:
    #   print ("Could not convert data to an integer."
    except:
      print ("Unexpected error:", sys.exc_info()[0])
      raise
    return value

  # # checar possibilidade de multiplicaÃ§Ã£o entre as matrizes
  # def checkTimes():
  #   if(getColumns('matriz1.txt') != getRows('matriz2.txt')):
  #     print('ImpossÃ­vel multiplicar as matrizes dadas')
  #   return

  # alocando a matriz na memoria
  def allocMatrix(self):
    self.matrix = [[0 for x in range(self.rows)] for y in range(self.columns)] 

  def showMatrix(self):
    for i in range(0,self.rows):
      for j in range(0,self.columns):
        sys.stdout.write(str(self.matrix[i][j]))
        sys.stdout.write('-') 
      print('')
    print('=======================')
    return

  def timesMetrix(m1,m2):
    h = len(m1)
    w = len(m2[0])
    y = len(m2)

    m3 = allocMatrix(h,w)

    for i in range(0,h):
      for j in range(0,w):
        for k in range(0,y):
          m3[i][j] += m1[i][k] * m2[k][j]

    return m3

if __name__ == "__main__": main()