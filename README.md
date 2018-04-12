# glados-terminal
This recreates the end credits of Portal 1 and 2 in a terminal.

# Introduction
  This program recreates the end sequence of Portal 1 and 2 inside of a terminal Using ncurses.
# Instalalation
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
split_pane_h(Pane1,Pane2,Percantage)\n
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
splate_pane_v(Pane1,Pane2,Percentage);
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
 
