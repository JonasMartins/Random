#!/usr/bin/python3
import sys

def main():
    print('Python version {}.{}.{}'.format(*sys.version_info))
    print(sys.platform)

    # import os

    # print(os.name)
    # # print(os.getenv('PATH'))
    
    # # current directory
    # print(os.getcwd())

    # import urllib.request
    # page = urllib.request.urlopen('http://github.com/')
    # for line in page: print(str(line, encoding = 'utf_8'), end = '')

    

if __name__ == "__main__": main()