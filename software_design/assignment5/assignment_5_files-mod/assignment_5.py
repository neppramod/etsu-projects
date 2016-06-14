import os

class Singleton(type):
    _instances = {}
    
    def __call__(obj, *args, **kwargs):
        object_found = False        
        object_name = args[0]
        
        for key in Singleton._instances.keys():
            if (key == args[0]):  
                object_found = True
                break
                
        if object_found == False:    
            obj = super(Singleton, TextFile).__call__(*args, **kwargs)
            Singleton._instances[object_name] = obj
        else:
            Singleton._instances[object_name].__init__(*args, **kwargs)
        return Singleton._instances[object_name]
    

class TextFile(metaclass=Singleton):

    def __init__(self, *args):
        try:
            assert(len(args) == 1 or len(args) == 2), "Length {0} is not expected".format(len(args))

            self.filename = args[0]           
            
            if (len(args) == 2):            
                self.position = args[1]
            else:            
                self.position = 0

            self.file_fd = open(self.filename, 'r')

            if (self.position > 0):
                self.file_fd.seek(self.position)

            print("Filename: {0}, Position: {1}".format(self.filename, self.position))
            
        except Exception as err:
            print("Can't access '{0}': {1}".format(self.filename, err))

    def seek(self, offset):
        self.file_fd.seek(offset)

    def readline(self):
        return self.file_fd.readline()

    def close(self):
        self.file_fd.close()

    def __repr__(self):        
        return "{}('{}',{})".format(self.__class__.__name__, self.filename, self.position)


        
a = TextFile('invictus.txt', 30)
b = TextFile('invictus.txt')
print(a == b)
c = TextFile('no enemies.txt')
print(a == c)
print(eval(repr(a)) == a)
