from terminal import *

class interperter:
    def __init__(self,tokens):
        self.term = terminal()
        self.tokens=tokens
        parenth=0 #counts number of parenthesis
        temp_method_name = ""
        temp_method_args = []
        for i in range(0,len(tokens)):
            if(tokens[i].type=='('):
                parenth=parenth+1
            if(tokens[i].type==")"):
                parenth=parenth-1
                if(parenth==0):
                    self.run_method(temp_method_name,temp_method_args)
                    temp_method_name=""
                    temp_method_args=[]
            if(tokens[i].type=="name"):
                if(parenth==0):
                    temp_method_name=tokens[i].content
                if(parenth==1):
                    temp_method_args.append(tokens[i].content)
            if(tokens[i].type=="number"):
                if(parenth==1):
                    temp_method_args.append(tokens[i].content)
            if(tokens[i].type=="quote"):
                if(parenth==1):
                    temp_method_args.append(tokens[i].content)
    def run_method(self,method_name,args):
        if(method_name=="split_pane_h" and len(args)==4):
            self.term.split_pane_h(args[0],args[1],args[2],args[3])
            self.term.draw_splits()
        if(method_name=="split_pane_v" and len(args)==4):
            self.term.split_pane_v(args[0],args[1],args[2],args[3])
            self.term.draw_splits()
        if(method_name=="text" and len(args)==3):
            self.term.add_text(args[0],args[1],args[2])
            
        if(method_name=="sleep" and len(args)==1):
            time.sleep(args[0]/1000)
        
            
            
    
        