# Minesweeper
A simple Minesweeper game implemented with a graphics library EasyX in C.
## Screenshot
* Home<br><br>![](http://yaochenkun.cn/wordpress/wp-content/uploads/2016/07/mine2.jpg)
* Playing<br><br>![](http://yaochenkun.cn/wordpress/wp-content/uploads/2016/07/mine1.png)

## Environment and Settings
* Download and install VC++6.0.
* Download and install [EasyX库 2012立冬版](http://www.easyx.cn/downloads/View.aspx?id=6). (If you cannot visit the download link, this repository has also provided the installation package, and you can just download from here.)
* Compile the source code file 'xxx.cpp' by VC, and then you can run and play the game.

## Key Points
* Use amounts of identifiers to represent the statuses (mine or no mine(i.e. 0~8 mines around)) of each cell in map.
* Design two recursions to implement:
 1. the searching process when user clicks a 'no mine' cell;
 2. the automatic opening process of the surrouding cells when the central cell was determined.

