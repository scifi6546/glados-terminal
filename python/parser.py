
from terminal import *

def open_file():
    file_string=""
    file=open("text.txt","r",1)
    while(0==0):
        temp_string=file.read(10)
        if(temp_string!=""):
            file_string=file_string + temp_string
        else:
            break
    return file_string
class token:
    type=""
    content=""
    def __init__(self,type,content):
        self.type=type
        self.content=content
    def __str__(self):
        return "TOKEN   type: " + self.type + "    content: " + str(self.content)
class string:
    string=""
    index=0
    def __init__(self,input):
        self.string = input
        self.index=0
    def read_char(self):
        if(self.index==self.get_len()):
            return None
        char = self.string[self.index]
        self.index=self.index+1
        return char
    def get_len(self):
        return len(self.string)
    def peak(self):
        return self.string
    def put_back(self):
        self.index=self.index-1
class parser:
    token_arr=[]
    def __init__(self):
       self.file=string(open_file())
       self.parse_file()

    def parse_file(self):
        while(0==0):
            char = self.file.read_char()
            if(char is None):
                break
            if(char=='#'):
                self.ignore()
            if(char.isalpha()):
                self.file.put_back()
                self.read()
            if(char=='('):
                self.file.put_back()
                self.parenthesis_open()
            if(char==')'):
                self.file.put_back()
                self.parenthesis_closed()
            if(char=='"'):
                self.file.put_back()
                self.quote()
            if(char.isdigit()):
                self.file.put_back()
                self.num()
            if(char==','):
                self.file.put_back()
                self.comma()
            if(char==';'):
                self.file.put_back()
                self.semicolon()
                
            
    def ignore(self):
        while(0==0):
            char = self.file.read_char()
            if(char=='\n'):
                break
        print("ignored")
    def read(self):
        type="name"
        contents=""
        temp_char=""
        while(0==0):
            broke=False#checks if symbol has been found
            temp_char=self.file.read_char()
            if(temp_char=="("):
                self.file.put_back()
                broke=True
                break
            if(temp_char==")"):
                self.file.put_back()
                broke=True
                break
            if(temp_char==","):
                self.file.put_back()
                broke=True
                break
            if(broke==False):
                contents+=temp_char
        token_temp = token(type,contents)
        self.token_arr.append(token_temp)
        print(token_temp)
        
    def quote(self):
        self.file.read_char()
        contents=""
        type="quote"
        while(0==0):
            temp_char=self.file.read_char()
            if(temp_char!='"'):
                contents+=temp_char
            else:
                break
        temp_token=token(type,contents)
        print(temp_token)
        self.token_arr.append(temp_token)
    def parenthesis_open(self):
        contents="("
        type="("
        temp_token=token(type,contents)
        self.token_arr.append(temp_token)
        self.file.read_char()
        print(temp_token)
    def parenthesis_closed(self):
        contents=")"
        type=")"
        temp_token=token(type,contents)
        self.token_arr.append(temp_token)
        self.file.read_char()
        print(temp_token)
    def num(self):
        type="number"
        contents_temp=""
        while(0==0):
            temp_char=self.file.read_char()
            if(temp_char.isdigit()):
                contents_temp+=temp_char
            else:
                self.file.put_back()
                break
        contents=int(contents_temp)
        temp_token=token(type,contents)
        self.token_arr.append(temp_token)
        print(temp_token)
    def comma(self):
        content=","
        type=","
        temp_token=token(type,content)
        self.token_arr.append(temp_token)
        print(temp_token)
        self.file.read_char()
    def semicolon(self):
        content=";"
        type=";"
        temp_token=token(type,content)
        self.token_arr.append(temp_token)
        print(temp_token)
        self.file.read_char()
