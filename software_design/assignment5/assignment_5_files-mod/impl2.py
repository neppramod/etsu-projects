class Singleton(type):
  _instances = {}
  def __call__(cls, *args, **kwargs):
    if cls not in cls._instances:      # instantiate shared class instance on first object instantiation 
      Singleton._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
    else:   # reinvoke __init__ for the lone instance on subsequent instantiations.  remove clause if re-init not desired
      Singleton._instances[cls].__init__(*args, **kwargs) 
    return Singleton._instances[cls]


class FileCabinet(metaclass=Singleton):
    _me = "?? FileCabinet.{}: "
    _fileListCollection = []
    def __init__(self, *args, **kwargs):
      

    def print_files(self):
        for file in FileCabinet._fileListCollection:
            print("{0}".format(file))

fc = FileCabinet(['a', 'b'])

