# glados-terminal
This recreates the end credits of Portal 1 and 2 in a terminal.

# Introduction
  This program recreates the end sequence of Portal 1 and 2 inside of a terminal Using ncurses.
# Install
  run
  ```
      $ make
  ```
# Requirements

  This program requires ncurses.
 
# Config File Syntax

The layout is thought of as different window panes with content inside of it

The first pane will be named "Main"

to split pane horizontally the command is:
```
split_pane_h(Pane_Original,Pane1,Pane2,Percantage);
```
Where panel1 is the name of the first new panel and Panel2 is the name of the second new panel. Percentage is the percentage of the pane used by pane1.
 the result would look like 
 
 ```
 -----------------------------
 |                  |        |
 |  Pane1           | Pane2  |
 |                  |        | 
 | <---Percentage-> |        |
 -----------------------------
 ```
to split a pane vertically the command is:
```
splate_pane_v(Panel_Original,Pane1,Pane2,Percentage);
```
Where panel1 is the name of the first new panel and Panel2 is the name of the second new panel. Percentage is the percentage of the pane used by pane1.
 the result would look like 
 
 ```
 ---------------------
 | Panel1       ^     |
 |         Percentage |
 |              |     |
 |              |     |
 ----------------------
 | Panel2             |
 |                    |
 ----------------------
 ```
 
 To set the background color run
 ```
 background_color(1000,1000,1000);
 ```
 where the numbers are Red,Blue,Green scaled from 0 to 1000
 
 To set the text color run
 ```
 text_color(1000,1000,1000);
 ```
 where the numbers are Red,Blue,Green scaled from 0 to 1000
 
 to print text run 
 ```
 text(pane,100,"text");
 ```
 where Pane is the pane that the text will go in, the first number is the delay between charecters (in milliseconds), and text is the text printed. Inorder to print a new line a \n charecter has to be in "text"
 
 To delete all text in a pane
 
 ```
 delete_text(pane);
 ```
 
 # Example Config File
 
 ```
 background_color(100,200,100);
 text_color(1000,1000,1000);
 split_pane_h(main_pane,Panel1,Panel2,70);
 text(Panel1,100,"hi there, it was a triumph");
 delete_text(pane);
 ```
