#!/usr/bin/python3

class invlusive_range:

  def __init__(self, *args):
    numargs = len(args)

    if numargs < 1: raise TypeError('requires at least one argument')
    elif numargs == 1:
      # dafault
      self.stop = args[0]
      self.start = 0
      self.step = 1
    elif numargs == 2:
      (self.start, self.stop) = args
      self.step = 1
    elif numargs == 3:
      (self.start, self.stop, self.step) = args

    else: raise TypeError('expected at most 3 arguments, got {} ', format(numargs))
  
  # This function having a yield statement makes this function a generator
  # and a generator makes a iterator object
  def __iter__(self):
    i = self.start
    while i <= self.stop:
      # yield statment makes this class a generator
      # works like return, if return was used here instead, 
      # it will return and the when the next time the iterator was called
      # it would start at begining of the function, when yield is used,
      # the next time the function is called, the executuin picks up
      # right after yield statement 
      yield i
      i += self.step


def main():
    for i in invlusive_range(25): print(i, end = ' ')

if __name__ == "__main__": main()