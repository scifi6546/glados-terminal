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

        split_x = self.x_y_array[0] +             \
        math.floor((percent/100)*                 \
        (self.x_y_array[2] - self.x_y_array[0]))
        child_one_x_y_array=[]
        child_one_x_y_array[0] = self.x_y_array[0]+1
        child_one_x_y_array[1] = self.x_y_array[1]+1
        child_one_x_y_array[2] = split_x-1
        child_one_x_y_array[3] = self.x_y_array[3]-1

        child_two_x_y_array = []
        child_two_x_y_array[0] = split_x+1
        child_two_x_y_array[1] = self.x_y_array[1]+1
        child_two_x_y_array[2] = self.x_y_array[2]-1
        child_two_x_y_array[3] = self.x_y_array[3]-1

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

        child_one_x_y_array = []
        child_one_x_y_array[0] = self.x_y_array[0]+1
        child_one_x_y_array[1] = self.x_y_array[1]+1
        child_one_x_y_array[2] = self.x_y_array[3]-1
        child_one_x_y_array[3] = split_y-1

        child_two_x_y_array = []
        child_two_x_y_array[0] = self.x_y_array[0]+1
        child_two_x_y_array[1] = split_y+1
        child_two_x_y_array[2] = self.x_y_array[2]-1
        child_two_x_y_array[3] = self.x_y_array[3]-1

        self.child_one = window(name_1,child_one_x_y_array)
        self.child_two = window(name_1,child_two_x_y_array)

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
        self.x=x_y_tuple[1]
        self.y=x_y_tuple[0]
        self.stdscr.keypad(True)
        self.stdscr.clear()
        
     
       # self.set_color(234,246,157)
        #self.clear()

        #self.split_pane_h("temp",50)
        time.sleep(10)
        self.main_pane=window("main_pane",[0,0,self.x,self.y])
        #self.draw_splits()
    def __del__(self):
        curses.nocbreak()
        self.stdscr.keypad(False)
        curses.echo()
        curses.endwin()
    def draw_splits(self):
        #first draw root frame

        # top + bottom bar
        for i in range(0,self.x-1):
            self.stdscr.addstr(0,i,"-")
            self.stdscr.addstr(self.y-1,i,"-")
        
        #sides
        for i in range(1,self.y-1):
            self.stdscr.addstr(i,0,"|")
            self.stdscr.addstr(i,self.x-1,"|")
        self.stdscr.refresh()
        #if(self.main_pane.split is not None):
         #   self.draw_splits_child(self.main_pane)
        #self.stdscr.refresh()

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
    def split_pane_h(self,pane,percent):
        self.stdscr.addstr(0,0,"hello")
        self.stdscr.refresh()
    def set_color(self,red,blue,green):
        print("todo")
        #curses.init_color(1,red,blue,green)
    def clear(self):
        for i in range(0,self.y-1):
            for j in range(0,self.x-1):
                self.stdscr.addstr(" ",curses.color_pair(1))
        self.stdscr.refresh()
