#!/bin/bin/python
import math

__version__ = "1.1.0"

class Node:
  def __init__(self, coordinates):
    self.x = coordinates[0]
    self.y = coordinates[1]
    self.z = coordinates[2]

class Edge:
  def __init__(self, start, stop):
    self.start = start
    self.stop = stop

class Wireframe:
  def __init__(self):
    self.nodes = []
    self.edges = []

  def addNodes(self, nodeList):
    for node in nodeList:
      self.nodes.append(Node(node))

  def addEdges(self, edgeList):
    for (start, stop) in edgeList:
      self.edges.append(Edge(self.nodes[start], self.nodes[stop]))

  def outputNodes(self):
    print('--- Nodes ---')
    for i, node in enumerate(self.nodes):
      print(i, node.x, node.y, node.z)

  def outputEdges(self):
    print "\n --- Edges --- "
    for i, edge in enumerate(self.edges):
      print(i, edge.start.x, edge.start.y, edge.start.z)
      print(edge.stop.x, edge.stop.y, edge.stop.z)

  def translate(self, axis, d):
    """ Add constant 'd' to the coordinate 'axis' of each node of a wireframe """
    if axis in ['x', 'y', 'z']:
      for node in self.nodes:
        setattr(node, axis, getattr(node, axis) + d)

  def scale(self, centre, scale):
    """ Scale the wireframe from the centre of the screen """
    for node in self.nodes:
      node.x = centre[0] + scale * (node.x - centre[0])
      node.y = centre[1] + scale * (node.y - centre[1])
      node.z *= scale

  def findCentre(self):
    """ Find the centre of the wireframe. """
    num_nodes = len(self.nodes)
    meanX = sum([node.x for node in self.nodes]) / num_nodes
    meanY = sum([node.y for node in self.nodes]) / num_nodes
    meanZ = sum([node.z for node in self.nodes]) / num_nodes

    return (meanX, meanY, meanZ)

  def rotateX(self, centre, radians):
    for node in self.nodes:
      y      = node.y - centre[1]
      z      = node.z - centre[2]
      d      = math.hypot(y, z)
      theta  = math.atan2(y, z) + radians
      node.z = centre[2] + d * math.cos(theta)
      node.y = centre[1] + d * math.sin(theta)

  def rotateY(self, centre, radians):
    for node in self.nodes:
      x      = node.x - centre[0]
      z      = node.z - centre[1]
      d      = math.hypot(x, z)
      theta  = math.atan2(x, z) + radians
      node.z = centre[2] + d * math.cos(theta)
      node.x = centre[0] + d * math.sin(theta)

  def rotateZ(self, centre, radians):        
    for node in self.nodes:
      x      = node.x - centre[0]
      y      = node.y - centre[1]
      d      = math.hypot(y, x)
      theta  = math.atan2(y, x) + radians
      node.x = centre[0] + d * math.cos(theta)
      node.y = centre[1] + d * math.sin(theta)


if __name__ == "__main__": main()
