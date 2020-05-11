class Method:
    def __init__(self, name, flow):
        self.name = name
        self.flow = flow
        self.para = []

    def __del__(self):
        del self.name
        del self.flow

    def appendPara(self, para):
        self.para.append(para)

    def showFlow(self):
        return self.flow

    def showName(self):
        return self.name

    def showParam(self):
        return self.para

    def display(self):
        print(self.name)
        print(self.flow)
        for elem in self.para:
            elem.display()
