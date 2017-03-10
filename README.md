# Minesweeper
A simple Minesweeper game implemented with a graphics library EasyX in C.
## Screenshot
![](http://yaochenkun.cn/wp-content/uploads/2016/07/mine2.jpg)

![](http://yaochenkun.cn/wp-content/uploads/2016/07/mine1.png)

## Download and Run
Just dowanload and open [扫雷.exe](https://github.com/yaochenkun/MinesweeperGame/blob/master/扫雷.exe)

## Environment and Configurations
* Download and install VC++6.0.
* Download and install [EasyX库 2012立冬版](http://www.easyx.cn/downloads/View.aspx?id=6). (If you cannot visit the download link, this repository has also provided the installation package, and you can just download from here.)
* Compile the source code file 'xxx.cpp' by VC, and then you can run and play the game.

## Key Points
* Use amounts of identifiers to represent the __status__ (mine or no mine(i.e. 0~8 mines around)) of each cell in map.
* Design __two recursions__ to implement:
 1. the searching process when user clicks a 'no mine' cell;
 2. the automatic opening process of the surrouding cells when the central cell was determined.
 
## For More
If you want more information about 'How to develop this game', you can have a further look at the file [扫雷开发文档.pdf](https://github.com/yaochenkun/MinesweeperGame/blob/master/扫雷开发文档.pdf).
