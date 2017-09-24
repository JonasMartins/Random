#!/usr/bin/python

class Animal:
  def talk(self): print('I have something to say')
  def walk(self): print('Hey!, I''m walkin'' here!') 
  def cloths(self): print('I have Nice clothes!')


class Duck(Animal):
    def __init__(self, **kwargs):
        # self._color = kwargs.get('color', 'white')
        self.variables = kwargs
        
    # this walk overrides walk from animal
    def walk(self):
        # if i dont want to override:
        # super().walk()
        print('Walks like a duck.')
    
    def set_color(self, color):
      self.variables['color'] = color

    def get_color(self):
      return self.variables.get('color', None)
    
    def set_variable(self,k,v):
      self.variables[k] = v

    def get_varible(self,k):
      return self.variables.get(k,None)

def main():
    donald = Duck(color = 'blue')
    # donald = Duck(feet = 2)
    print(donald.get_variable('color'))

if __name__ == "__main__": main()