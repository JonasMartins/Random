def test_var_args(f_arg, *argv):
    print "first normal arg:", f_arg
    for arg in argv:
        print "another arg through *argv :", arg

test_var_args('yasoob','python','eggs','test')

# first normal arg: yasoob
# another arg through *argv : python
# another arg through *argv : eggs
# another arg through *argv : test

def greet_me(**kwargs):
    if kwargs is not None:
        for key, value in kwargs.iteritems():
            print "%s == %s" %(key,value)

greet_me(name="yasoob")

# name == yasoob