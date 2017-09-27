#!/usr/bin/python
# encoding: utf-8

from transformations import Transformation
from matrix import Matrix

v_trans = [-1,-1,-1]
v_scale = [2,2,2]

cisalhamento = Transformation(30,None,None,None)

translacao = Transformation(None,v_trans,None,None)

scala = Transformation(None,None,v_scale,None)

rotacao = Transformation(None,None,None,45)