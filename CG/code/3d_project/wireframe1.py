#!/bin/bin/python

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

if __name__ == "__main__": main()
