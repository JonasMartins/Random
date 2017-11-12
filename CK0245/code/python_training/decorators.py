#!/usr/bin/python3

class Duck:
    def __init__(self, **kwargs):
        self.properties = kwargs

    def quack(self):
        print('Quaaack!')

    def walk(self):
        print('Walks like a duck.')

    def get_properties(self):
        return self.properties

    def get_property(self, key):
        return self.properties.get(key, None)

    # This @property makes this dunction an accessor
    # for the variable called color
    @property
    def color(self)
        return self.properties.get('color', None)

    @color.setter
    def color(self, c):
        self.properties['color'] = c

    @color.deLeter
    def color(self):
        del self.properties['color']

def main():
    donald = Duck()
    # This new sintax allow us to use:

    donald.color = 'blue'

    print(donald.color)




if __name__ == "__main__": main()