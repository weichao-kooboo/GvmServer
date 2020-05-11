try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.cElementTree as ET

import Node as N
import Method as M
import Parameter
import decode

classTag = "class"
className = "name"
methodTag = "method"
methodName = "name"
methodFlow = "prflow"
paramTag = "param"
paramType = "prtype"
paramName = "prname"

tree = ET.ElementTree(file='protocol.xml')
root = tree.getroot()

# 读取所有类
cVector = []
for elem in root:
    if elem.tag == classTag:
        tClass = N.ClassNode(elem.attrib[className])
        for methods in elem:
            if methods.tag == methodTag:
                tMethods = M.Method(methods.attrib[methodName], methods.attrib[methodFlow])
                for params in methods:
                    if params.tag == paramTag:
                        tParam = Parameter.Parameter(params.attrib[paramName], params.attrib[paramType])
                        tMethods.appendPara(tParam)
                tClass.addMethod(tMethods)
        cVector.append(tClass)

print(cVector)
for t in cVector:
    t.display()

for t in cVector:
    dec = decode.Decode(t)
    dec.decode()

