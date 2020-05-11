class ClassNode:
    def __init__(self, name):
        self.name = name
        self.methods = []

    def addMethod(self, method):
        self.methods.append(method)

    def showMethod(self):
        return self.methods

    def display(self):
        print(self.name)
        for t in self.methods:
            t.display()
