#!/usr/bin/python
# encoding: utf-8

import sys

class Matrix:    

  """ 
  ULTRA FLEXIBLE PYTHON CLASS, ACEITA 3 TIPOS DE DEFINIÇÕES DE OBJETOS, 
  UMA MATRIZ VINDA DE UM ARQUIVO, PASSADOS APENAS AS LINHAS A COLUNAS, E
  A MATRIZ PASSA EM SÍ, COMO OM VETOR MULTIDIMENCIONAL, O CONSTRUTOR SE ENCARREGA
  DE IDENTIFICAR QUAL TIPO DE OBJETO FOI CIRADO ATRAVÉS DO **kwargs

  """
  
  def __init__(self, **kwargs):
    self.variables = kwargs
    
    # para pegar uma matriz de um arquivo texto
    if(self.variables.has_key('file')):
      self.__setEnvFile()
    
    # para pegar de um vetor escrito no proprio codigo
    if(self.variables.has_key('matrix')):
      # m = 
      self.set_variable('columns',len(self.get_variable('matrix')))
      self.set_variable('rows',len(self.get_variable('matrix')[0]))    

    # para pegar de uma matrix já especificada com rows e columns
    # ela já inicia toda igual a zero 
    else:
      self.__allocMatrix()

  def set_variable(self,k,v):
    self.variables[k] = v

  def get_variable(self,k):
    return self.variables.get(k,None)
    
  # setando o ambiente para matrizes vindas de arquivos texto
  def __setEnvFile(self):

    self.set_variable('columns',self.__getColumns())
    self.set_variable('rows',self.__getRows())
    self.__allocMatrix()

  # apenas printando as dimensões da matriz, com proṕosito de debug 
  def show_dimensions(self):
    print('{0} x {1}'.format(self.get_variable('rows'),self.get_variable('columns')))

  # Percorre a matriz do arquivo e cada item Ã© armazenado na matriz da memÃ³ria
  def fillMatrix(self):
    h = w = 0
    with open(self.get_variable('file')) as m:
       for line in m:
          line = line.split(',')
          line[len(line)-1] = line[len(line)-1].replace("\n","") 
          for i in range(len(line)):
            self.get_variable('matrix')[h][w] = int(line[i])
            w += 1
          h += 1 
          w = 0
          if 'str' in line:
            break

  # Retona a dimensão de colunas de uma matriz
  def __getColumns(self):
    length = 0
    with open(self.get_variable('file')) as m1:
      s = m1.readline()
      array = s.split(',')
    return len(array) # {\n}

  # Retona a dimensÃ£o de linhas de uma matriz
  def __getRows(self):
    with open(self.get_variable('file')) as f:
      return sum(1 for _ in f)

  # Checar a disponibilidade ao se abrir um arquivo
  def __checkOpen(self):
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

  # Transformando a matriz do objeto em uma matriz identidade, caso seja axa
  def generate_identity(self):
    if(self.get_variable('rows') == self.get_variable('columns')):
      for i in range(0,self.get_variable('rows')):
        self.get_variable('matrix')[i][i] = 1

  # alocando a matriz na memoria
  def __allocMatrix(self): 
    m = [[0 for x in range(self.get_variable('rows'))] for y in range(self.get_variable('columns'))]
    self.set_variable('matrix',m)  

  def showMatrix(self):
    print('\n********************')
    for i in range(0,self.get_variable('columns')):
      for j in range(0,self.get_variable('rows')):
        sys.stdout.write(str(self.get_variable('matrix')[i][j]))
        sys.stdout.write('-') 
      print('')
    print('\n********************')
    return


if __name__ == "__main__": main()