class MyClass(object):

    def __init__(self, *args, **kwargs):
        print("Args");

        self.args = args
        self.kwargs = kwargs
        
        for arg in args:
            print(arg)

        

        if kwargs is not None:
            for key in kwargs.keys():
                print("Key: {0}, Value: {1}".format(key, kwargs[key]))

    def __repr__(self):
        return "{}{}".format(self.__class__.__name__, self.args)


