#!/usr/bin/python
# encoding: utf-8

import sys

class Matrix:    

  """ ULTRA FLEXIBLE PYTHON CLASS, ACCEPT FILE MATRIXES AND 
  NORMAL DEFINICIONS """
  
  def __init__(self, **kwargs):
    self.variables = kwargs


  def set_variable(self,k,v):
    self.variables[k] = v

  def get_variable(self,k):
    return self.variables.get(k,None)
    
  def setEnvFile(self):
    self.set_variable('columns',self.getColumns())
    self.set_variable('rows',self.getRows())
    self.allocMatrix()

  # Percorre a matriz do arquivo e cada item Ã© armazenado na matriz da memÃ³ria
  def fillMatrix(self):
    h = w = 0
    mm = self.get_variable('matrix')
    with open(self.get_variable('file')) as m:
       for line in m:
          line = line.split(',')
          line[len(line)-1] = line[len(line)-1].replace("\n","") 
          for i in range(len(line)):
            mm[h][w] = int(line[i])
            w += 1
          h += 1 
          w = 0
          if 'str' in line:
            break
    self.set_variable('matrix',mm)

  # Retona a dimensão de colunas de uma matriz
  def getColumns(self):
    length = 0
    with open(self.get_variable('file')) as m1:
      s = m1.readline()
      array = s.split(',')
    return len(array) # {\n}

  # Retona a dimensÃ£o de linhas de uma matriz
  def getRows(self):
    with open(self.get_variable('file')) as f:
      return sum(1 for _ in f)

  # Checar a disponibilidade ao se abrir um arquivo
  def checkOpen(self):
    value = False
    try:
      m1 = open(self.get_variable('file'))
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


  # alocando a matriz na memoria
  def allocMatrix(self): 
    m = [[0 for x in range(self.get_variable('rows'))] for y in range(self.get_variable('columns'))]
    self.set_variable('matrix',m)  

  def showMatrix(self):
    r = self.get_variable('rows')
    c = self.get_variable('columns')
    m = self.get_variable('matrix')
    for i in range(0,r):
      for j in range(0,c):
        sys.stdout.write(str(m[i][j]))
        sys.stdout.write('-') 
      print('')
    print('=======================')
    return


if __name__ == "__main__": main()