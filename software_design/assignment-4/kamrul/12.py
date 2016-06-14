import os
class MyClass(object):
    def __init__(self, rdfile, wrtfile):
        try:
            self.readList = self.getAttributList(rdfile,'r')
            self.writeList= self.getAttributList(wrtfile,'w')
            print("#############ReadList###############")
            print(self.readList)
            print("#############WriteList###############")
            print(self.writeList)

        except:
            print("Exception Part")

    def getAttributList(self, fileToAttributeName, mode):        
        try:
            fileName, fileExtension = os.path.splitext(fileToAttributeName)           
            if(fileExtension == '.txt'):                
                file = open(fileToAttributeName,mode)
                attrList = []
                for line in file:                                        
                    attrList.append(line.split())
                file.close()
                return attrList        
            else:                
                print("File is not text mode")
        except:
             print('error inside try')


    def __getattribute__(self, attr_name):
        return super().__getattribute__(attr_name)

    def __setattr__(self, attr_name):
        return super().__setattr__(attr_name,value)

    def get_v(self, attr_name):
        for x in self.readList:
            print(x)
        return super().getattribute__(attr_name)

    def set_v(self, attr_name):
        return super().__setattr__(attr_name)
    

                
