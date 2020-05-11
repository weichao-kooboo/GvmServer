class Decode:
    def __init__(self, node):
        self.node = node
        # 类名
        self.className = node.name
        # 生成的客户端头文件名
        self.class_name_client = "client_" + node.name
        # 生成的服务端头文件名
        self.class_name_server = "server_" + node.name

    def __del__(self):
        del self.node
        if self.header_file_client.closed == "false":
            self.header_file_client.close()
        if self.header_file_server.closed == "false":
            self.header_file_server.close()
        if self.body_file_client.closed == "false":
            self.body_file_client.close()
        if self.body_file_server.closed == "false":
            self.body_file_server.close()


    def decode(self):
        self.__decodeHeader()
        self.__decodeBody()

    def __decodeHeader(self):
        self.header_file_client = open(self.class_name_client + ".h", "w")
        self.header_file_server = open(self.class_name_server + ".h", "w")
        # client
        client_pre_str = self.__writeHeaderStaticString(self.class_name_client)
        server_pre_str = self.__writeHeaderStaticString(self.class_name_server)
        end_str = "};"
        self.header_file_client.write(client_pre_str)
        self.header_file_server.write(server_pre_str)
        # 写入方法

        client_context = []
        server_context = []
        client_methods = self.node.showMethod()
        for method in client_methods:
            context = self.__decodeMethod(method)
            flow = method.showFlow()
            if flow == "p2p":
                client_context.append(context)
                server_context.append(context)
            elif flow == "s2c":
                server_context.append(context)
            elif flow == "c2s":
                client_context.append(context)

        client_context.append("\n" + end_str)
        server_context.append("\n" + end_str)
        self.header_file_client.writelines(client_context)
        self.header_file_server.writelines(server_context)

        self.header_file_client.close()
        self.header_file_server.close()

    def __decodeBody(self):
        self.body_file_client = open(self.class_name_client + ".cpp", "w")
        self.body_file_server = open(self.class_name_server + ".cpp", "w")

        # server
        client_pre_str = self.__writeBodyStaticString(self.class_name_client)
        server_pre_str = self.__writeBodyStaticString(self.class_name_server)

        self.body_file_client.write(client_pre_str)
        self.body_file_server.write(server_pre_str)

        # 写入方法
        client_context = []
        server_context = []
        client_methods = self.node.showMethod()
        for method in client_methods:
            flow = method.showFlow()
            if flow == "p2p":
                client_context.append(self.__decodeCppMethod(self.class_name_client, method))
                server_context.append(self.__decodeCppMethod(self.class_name_server, method))
            elif flow == "s2c":
                server_context.append(self.__decodeCppMethod(self.class_name_server, method))
            elif flow == "c2s":
                client_context.append(self.__decodeCppMethod(self.class_name_client, method))

        self.body_file_client.writelines(client_context)
        self.body_file_server.writelines(server_context)

        self.body_file_client.close()
        self.body_file_server.close()

    def __writeHeaderStaticString(self, classname):
       return "class " + classname + "\n"  \
                      "{\n"                             \
                      "public:\n"                       \
                      + classname + "();\n"        \
                      + "~" + classname + "();\n"

    def __writeBodyStaticString(self, classname):
        return "#include \"" + classname + ".h\"\n\n"           \
                + classname + "::" + classname + "()\n{\n}\n"   \
                + classname + "::~" + classname + "()\n{\n}\n"

    def __decodeMethod(self, method):
        context = "void " + method.showName() + "("
        paramters = method.showParam()
        count = 0
        plen = len(paramters)
        for param in paramters:
            context += param.serialization()
            count = count+1
            if count != plen:
                context += ","
        context += ");"
        return context

    def __decodeCppMethod(self, classname, method):
        context = "void " + classname + "::" + method.showName() + "("
        paramters = method.showParam()
        count = 0
        plen = len(paramters)
        for param in paramters:
            context += param.serialization()
            count = count+1
            if count != plen:
                context += ","
        context += ")\n{\n}\n"
        return context


