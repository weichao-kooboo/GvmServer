#! /usr/bin/python

# file=open("1.txt",mode='r')

# print("文件名:",file.name)
# print("是否已关闭:",file.closed)
# print("访问模式:",file.mode)

# line=file.readline()
# print("%s" % line)
# line=file.readline()
# print("%s" % line)
# file.close()

strTest = "hi"
Strr = strTest + "hello"
print(Strr)
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.cElementTree as ET

tree = ET.ElementTree(file='test.xml')
root = tree.getroot()
print(root.tag, root.attrib)

for child_in_root in root:
    print(child_in_root.tag, child_in_root.attrib)

# 查询
print('查询:')
for elem in tree.iter():
    print(elem.tag, elem.attrib)
print('==============================')
print('node查询:')
# node查询
for elem in tree.iter(tag='branch'):
    print(elem.tag, elem.attrib)

print('==============================')
print('XPath查询:')
# Xpath查询
for elem in tree.iterfind('branch/sub-branch'):
    print(elem.tag, elem.attrib)

print('==============================')

for elem in tree.iterfind('branch[@name="release01"]'):
    print(elem.tag, elem.attrib)

