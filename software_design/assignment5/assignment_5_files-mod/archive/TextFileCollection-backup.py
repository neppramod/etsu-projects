class Singleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:      # instantiate shared class instance on first object instantiation 
          Singleton._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        else:   # reinvoke __init__ for the lone instance on subsequent instantiations.  remove clause if re-init not desired
          Singleton._instances[cls].__init__(*args, **kwargs) 
        return Singleton._instances[cls]


class TextFile:
    def __init__(self, name, position):
        self.name = name
        self.position = position
    def get_name(self):
        return self.name
    def get_position(self):
        return self.position
    def set_position(self, position):
        self.position = position
    def __eq__(self, other):
        return self.name == other.name

class TextFileCollection(metaclass=Singleton):
    #_me = "?? TextFileCollection.{}: "
    _fileListCollection = []

    def __init__(self, *args, **kwargs):        
        for key, value in kwargs.items():
            print ("Key: {0}, Value: {1}".format(key, value))
            TextFileCollection._fileListCollection.append(TextFile(key, value))

    def search(self, filename):
        found_file = None
        for fileobj in TextFileCollection._fileListCollection:
            if filename == fileobj.get_name():
                found_file = fileobj
                break
        return found_file
            

    def print_files(self):
        for file in TextFileCollection._fileListCollection:
            print("Name: {0}, Position: {1}".format(file.get_name(), file.get_position()))

    def file_list(self):
        return TextFileCollection._fileListCollection

    def seek(self, filename, position):
        fileobj = self.search(filename)

        print(fileobj)
        
        if (fileobj is not None):
            #print("Name: {0}, Position: {1}".format(fileobj.get_name(), fileobj.get_position()))
            fileobj.set_position(position)

fc = TextFileCollection(a=2, b = 5)

