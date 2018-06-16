import curses
import time
import math
class window:
    def __init__(self,name,x_y_array):
        self.name=name
        self.x_y_array=x_y_array
        # array is [x_top_left, y_top_left, 
        #  x_bottom_right,y_bottom_right]
        # all info about the window can be found from these points 
        #     *------------
        #     |           |
        #     |           |
        #     |-----------*
        #other two corners do not ned to be explicitly stated
        self.split=None
        self.text_cord=[x_y_array[0],x_y_array[1]]
    def split_h(self,name_1,name_2,percent):
        #     *------------
        #     |           |
        #     |           |
        #     |-----------*
        #children windows do not contain boarders of parent,so
        # outer is parent inner is child
        #     *-----------*
        #     |*---------*|
        #     ||         ||  
        #     |*---------*|
        #     *-----------*

        split_x = self.x_y_array[0] + math.floor((percent/100)*(self.x_y_array[2] - self.x_y_array[0]))
        
        child_one_x_y_array=[self.x_y_array[0]+1,
        self.x_y_array[1]+1,
        split_x-1,
        self.x_y_array[3]-1]



        child_two_x_y_array = [split_x+1,
        self.x_y_array[1]+1,self.x_y_array[2]-1,
        self.x_y_array[3]-1]

        self.child_one = window(name_1,child_one_x_y_array)
        self.child_two = window(name_2,child_two_x_y_array)

        self.percent = percent
        self.split="horizontal"
        self.split_cord=split_x

    def split_v(self,name_1,name_2,percent):
        #     *------------
        #     |           |
        #     |           |
        #     |-----------*
        #children windows do not contain boarders of parent,so
        # outer is parent inner is child
        #     *-----------*
        #     |*---------*|
        #     ||         ||  
        #     |*---------*|
        #     *-----------*
        split_y = self.x_y_array[1] +          \
        math.floor((percent/100)*              \
        (self.x_y_array[3]-self.x_y_array[1]))

        child_one_x_y_array = [self.x_y_array[0]+1,
        self.x_y_array[1]+1,
        self.x_y_array[2]-1,
        split_y-1]
        

        child_two_x_y_array = [self.x_y_array[0]+1,
        split_y+1,
        self.x_y_array[2]-1,
        self.x_y_array[3]-1]
        

        self.child_one = window(name_1,child_one_x_y_array)
        self.child_two = window(name_2,child_two_x_y_array)

        self.percent = percent
        self.split = "vertical"
        self.split_cord=split_y
    def get_name(self):
        return self.name
class terminal:
    def __init__(self):
        self.stdscr=curses.initscr()
        curses.noecho()
        curses.cbreak()
        x_y_tuple=self.stdscr.getmaxyx()
        self.x=curses.COLS-1
        self.y=curses.LINES-1
        self.stdscr.keypad(True)
        self.stdscr.clear()
        self.text_delay=.5
     
       # self.set_color(234,246,157)
        #self.clear()

        #self.split_pane_h("temp",50)
      
        self.main_pane=window("main_pane",[0,0,self.x,self.y])
        #self.draw_splits()
    def __del__(self):
        curses.nocbreak()
        self.stdscr.keypad(False)
        curses.echo()
        curses.endwin()
    def draw_splits(self):
        #first draw root frame
        #print("drawing frame")
        # top + bottom bar
        for i in range(0,self.x-1):
            self.stdscr.addstr(0,i,"-")
            self.stdscr.addstr(self.y-1,i,"-")
        
        #sides
        for i in range(1,self.y-1):
            self.stdscr.addstr(i,0,"|")
            self.stdscr.addstr(i,self.x-1,"|")
        self.stdscr.refresh()
        if(self.main_pane.split is not None):
           self.draw_splits_child(self.main_pane)
        self.stdscr.refresh()

    def draw_splits_child(self,window):
        if(window.split=="horizontal"):
            for i in range(window.x_y_array[1],window.x_y_array[3]):
                self.stdscr.addstr(i,window.split_cord,"|")
        if(window.split=="vertical"):
            for i in range(window.x_y_array[0],window.x_y_array[2]):
                self.stdscr.addstr(window.split_cord,i,"-")
        if(window.split is not None):
            self.draw_splits_child(window.child_one)
            self.draw_splits_child(window.child_two)


    def split_pane_h(self,pane,pane1,pane2,percent):
        if (self.main_pane.name==pane):
            self.main_pane.split_h(pane1,pane2,percent)
        else:
            self.INT_split_pane_h(self.main_pane,pane1,pane2,percent,pane)
    def INT_split_pane_h(self,pane,pane_name1,pane_name2,percent,wanted_pane):
        if(pane.name==wanted_pane):
            pane.split_h(pane_name1,pane_name2,percent)
        else:
            if(pane.split is not None):
                self.INT_split_pane_h(pane.child_one,pane_name1,pane_name2,percent,wanted_pane)
                self.INT_split_pane_h(pane.child_two,pane_name1,pane_name2,percent,wanted_pane)


    def split_pane_v(self,pane,pane1,pane2,percent):
        if (self.main_pane.name==pane):
            self.main_pane.split_v(pane1,pane2,percent)
        else:
            self.INT_split_pane_v(self.main_pane,pane1,pane2,percent,pane)
    def INT_split_pane_v(self,pane,pane_name1,pane_name2,percent,wanted_pane):
        if(pane.name==wanted_pane):
            pane.split_v(pane_name1,pane_name2,percent)
        else:
            if(pane.split is not None):
                self.INT_split_pane_v(pane.child_one,pane_name1,pane_name2,percent,wanted_pane)
                self.INT_split_pane_v(pane.child_two,pane_name1,pane_name2,percent,wanted_pane)
            #else:
                #print("ERROR")

    
    def add_text(self,window,speed,text):
        self.INT_add_text(self.main_pane,speed,text,window)

    def INT_add_text(self,window,speed,text,wanted_window):
        condition = False #checks if metod is on right window
        if(window.split is None):
            if(window.name==wanted_window):
                condition=True
        if(condition==True):
            for i in range(0,len(text)):
                if(text[i]=='\n'):
                    window.text_cord=[window.x_y_array[0],window.text_cord[1]+1]
                    
                else:
                    temp_cord=window.text_cord
                    self.stdscr.addstr(temp_cord[1],temp_cord[0],text[i])
                    self.stdscr.refresh()
                    temp_cord[0] = temp_cord[0]+1
                    window.text_cord=temp_cord
                    time.sleep(speed/1000)
        else:
            if(window.split is not None):
                self.INT_add_text(window.child_one,speed,text,wanted_window)
                self.INT_add_text(window.child_two,speed,text,wanted_window)


    def set_color(self,red,blue,green):
        print("todo")
        #curses.init_color(1,red,blue,green)
    def clear(self):
        for i in range(0,self.y-1):
            for j in range(0,self.x-1):
                self.stdscr.addstr(" ",curses.color_pair(1))
        self.stdscr.refresh()