import os

class Singleton(type):

    _instances = {}

    def __call__(cls, *args, **kwargs):

        file_name = args[0]

        if file_name not in cls._instances:
            obj = super(Singleton, cls).__call__(*args, **kwargs)
            Singleton._instances[file_name] = obj
        else:
            Singleton._instances[file_name].__init__(*args, **kwargs)

        return Singleton._instances[file_name]


class TextFile(metaclass=Singleton):

    def __init__(self, filename, position = 0):
        
        self.filename = filename
        self.position = position
        
        try:
            
            self.file_handle = open(self.filename, 'r')            
            self.file_handle.seek(self.position)           

        except IOError as e:
            print("Can't access '{0}': {1}".format(self.filename, e))

    def seek(self, offset):
        self.position = offset
        self.file_handle.seek(self.position)        

    def readline(self):        
        read_str = self.file_handle.readline()
        self.position = self.file_handle.tell()
        return read_str

    def close(self):
        self.file_handle.close()

    
    def __repr__(self):
        return "{}('{}',{})".format(self.__class__.__name__, self.filename, self.position)

class TextFileCollection:
    _me = "?? TextFileCollection.{}: "
    _fileListCollection = []
    _dict = {}

    def __init__(self, *args):
        for arg in args:
            print(arg)

        self._value = args[0]

        rept = []
        fileList = []
        self.ownList = []

        for arg in args:
            if arg in fileList:
                rept.append(arg)
            else:
                fileList.append(arg)

        if len(rept) > 0:
            self.assert_defined("init",rept,"duplicate filename in filespec.{}")
        else:
            for file_obj in fileList:
                if isinstance(file_obj, tuple):
                    file_name = file_obj[0]
                    position = file_obj[1]['position']
                    self.ownList.append(file_name)
                else:
                    file_name = file_obj
                    position = 0
                    self.ownList.append(file_name)

                txtFile = TextFile(file_name, position)

                if txtFile not in TextFileCollection._fileListCollection:                
                    TextFileCollection._fileListCollection.append(txtFile)
                
                if txtFile not in TextFileCollection._dict:
                    TextFileCollection._dict[txtFile] = [self]
                else:
                    TextFileCollection._dict[txtFile].append(self)
                
        
    def set(self, newValue=None):
        self._value = newValue
        
    def unset(self):  del TextFileCollection._value

    def printstate(self):
        print(TextFileCollection._dict)
        print(TextFileCollection._fileListCollection)

    def search(self, filename):
        found_file = None

        for file_object in TextFileCollection._fileListCollection:
            if (file_object.filename == filename):
                found_file = file_object
                break
        return found_file
   
    def __eq__(self, other):
        if not isinstance(other, TextFileCollection): return False
        self.assert_defined('__eq__')
        other.assert_defined('__eq__')
        return True    # both instances will always share _value
      #
      # memento pattern
      #
    #def __repr__(self):
    #    self.assert_defined('__repr__')
    #    return "{}({})".format(self.__class__.__name__, self._value)
      #
      # supporting routintes
      #
      
    def assert_defined(self, routine):
        assert '_value' in dir(TextFileCollection), (TextFileCollection._me + "_value is undefined").format(routine)
   

    def seek(self, filename, offset):
        file_obj = self.search(filename)

        assert file_obj != None, "File not found"
        file_obj.seek(offset)

    def readline(self, filename):
        file_obj = self.search(filename)
        
        assert file_obj != None, "File not found"
        return file_obj.readline()

    def close(self, filename):
        file_obj = self.search(filename)
        
        assert file_obj != None, "File not found"

        # First remove self from list and if the list count is 0 close the file
        TextFileCollection._dict[file_obj].remove(self)        

        if len(TextFileCollection._dict[file_obj]) == 0:
            TextFileCollection._fileListCollection.remove(file_obj)
            del TextFileCollection._dict[file_obj]
            
            file_obj.close()
        
    

#a = TextFile('invictus.txt', 30)
#b = TextFile('invictus.txt')
#print(a == b)
#c = TextFile('no enemies.txt')
#print(a == c)
#print(eval(repr(a)) == a)

desid = "desiderata.txt"
invictus = "invictus.txt"
no_enemies = "no enemies.txt"

#c_fail = TextFileCollection(desid, desid, invictus, invictus, no_enemies)

c0 = TextFileCollection(desid, invictus)
c1 = TextFileCollection((desid, {'position':40}), no_enemies)

c1.printstate()
c0.printstate()
#c0.close('desiderata.txt')
