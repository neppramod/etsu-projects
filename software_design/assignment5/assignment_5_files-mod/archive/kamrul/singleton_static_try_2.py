class Singleton(type):
    _instances = {}
    
    def __call__(obj, *args, **kwargs):
        object_found = False        
        object_name = args[0]
        
        for key in Singleton._instances.keys():
            if (key == args[0]):  
                object_found = True
                break
        
        #if obj not in Singleton._instances:
        if object_found == False:    
            obj = super(Singleton, MyClass).__call__(*args, **kwargs)
            Singleton._instances[object_name] = obj
        else:
            Singleton._instances[object_name].__init__(*args, **kwargs)
        return Singleton._instances[object_name]


class MyClass(metaclass=Singleton):
    
    def __init__(self, *args):
        if len(args): self.value = args[0]
        
    def get_name(self):
        return self.value


    
a = MyClass('a')
b = MyClass('a')
print(a == b)
c = MyClass('c')
print(b == c)

