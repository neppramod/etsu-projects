class Singleton(type):
    _instances = {}
    
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            #print("Not in _instances")
            Singleton._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        else:
            Singleton._instances[cls].__init__(*args, **kwargs)
        return Singleton._instances[cls]


class MyClass(metaclass=Singleton):
    def __init__(self, *args):
        if len(args): self.value = args[0]

a = MyClass('a')
b = MyClass('a')
print(a == b)
c = MyClass('c')
print(b == c)

print(id(a))
print(id(b))
print(id(c))
