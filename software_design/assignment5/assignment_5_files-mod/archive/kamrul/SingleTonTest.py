class Singleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):

        print(Singleton._instances)
        
        file = args[0]
        if file not in cls._instances:      # instantiate shared class instance on first object instantiation 
          Singleton._instances[file] = super(Singleton, cls).__call__(*args, **kwargs)
        else:   # reinvoke __init__ for the lone instance on subsequent instantiations.  remove clause if re-init not desired
          Singleton._instances[file].__init__(*args, **kwargs) 
        return Singleton._instances[file]


class TextFile(metaclass=Singleton):
    def __init__(self, name, position=0): # This is variable *args
        self.name = name
        self.position = position
        
        try:
            self.file_handle = open(name,'r')
            self.file_handle.seek(self.position)
            
        except IOError as e:
            print ("File error")

    def readline(self):
        return self.file_handle.readline()
        
    def close(self):
        self.file_handle.close()
        
    def get_name(self):
        return self.name
    
    def get_position(self):
        return self.position
    
    def seek(self, offset):
        self.file_handle.seek(offset)
        
    def __eq__(self, other):
        return self.name == other.name

class TextFileCollection:
    _me = "?? TextFileCollection.{}: "
    _fileListCollection = []
    _dict = {}

    def __init__(self, *args, **kwargs):
        rept = []
        fileList = []
        self.ownList = []
        for file in args:
            if file in fileList:
                 rept.append(file)
            else:
                fileList.append(file)
                

        if len(rept) > 0:
            self.assert_defined("init",rept,"duplicate filename in filespec.{}")
        else:
            for file in fileList:
                if isinstance(file,tuple):
                    fileName = file[0]
                    position = file[1]['position']
                    self.ownList.append(fileName)
                else:
                    fileName = file
                    position = 0
                    self.ownList.append(fileName)
                    
                print ("Key: {0}, Value: {1}".format(fileName, position))
                TextFileCollection._fileListCollection.append(TextFile(fileName, position))
 
    def readline(self,fileName):
        flag = False
        obj = object
        if fileName in self.ownList:
            for fileObj in TextFileCollection._fileListCollection:
                if fileObj.name == fileName:
                    flag = True
                    obj = fileObj
            if(flag == True):
                print(obj.readline())
        else:
            self.assert_defined('readline',fileName,'handle on {} not held by')
        
        
    def assert_defined(self, routine,fileError,errorMsg):
         assert 'value' in dir(self), (TextFileCollection._me + errorMsg+str(id(self))).format(routine,fileError)        
            


desid="desiderata.txt"
orgin="invictus.txt"
enemie="no_enemies.txt"
fc = TextFileCollection(desid,desid,orgin,enemie,enemie)
fc = TextFileCollection(desid,orgin,enemie)
f = TextFileCollection((desid,{'position':4}),orgin)
fc.readline(enemie)

