class Parameter:
    def __init__(self, name, pType):
        self.name = name
        self.pType = pType

    def __del__(self):
        del self.name
        del self.pType

    def display(self):
        print(self.name)
        print(self.pType)

    def serialization(self):
        return self.pType + " " + self.name
