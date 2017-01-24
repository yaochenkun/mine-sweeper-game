#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#pragma comment(lib,"winmm.lib")
/***************************************************************************************************************************************/
/*宏定义*/
/***************************************************************************************************************************************/
#define NOMINE 0/*无雷*/
#define MINE 1/*有雷*/
#define UNHIT 2/*未翻*/
#define HIT 3/*已翻*/
#define MARK 4/*红旗*/
#define UNDETERMINE 5/*问号*/
#define STOP 6/*暂停*/
#define KEEPON 7/*继续*/
/***************************************************************************************************************************************/
/*函数声明*/
/***************************************************************************************************************************************/
int  first();/*游戏开场画面*/
void menu();/*菜单栏*/
void move();/*难度方块移动效果*/
void stop();/*暂停图样*/
void keepon();/*继续图样*/
void picture(int x);/*难度方块*/
void cover(int x);/*覆盖难度方块*/
void extend();/*伸展开始*/
void amount9();/*9X9表格*/
void cover9();/*9X9覆盖表格*/
void amount16();/*16X16表格*/
void cover16();/*16X16覆盖表格*/
void clock(time_t t1);/*时间*/
void minenumber();/*剩雷数字*/
void mine(int x,int y);/*雷图样(坐标)*/
void blank(int a,int b);/*光标覆盖(下标)*/
void remove(int a,int b);/*光标还原(下标)*/
void colornumber(int m,int x,int y);/*彩色数字(下标)*/
void sign(int a,int b);/*红旗图样(下标)*/
void remain(int a,int b);/*问号图样(下标)*/
void number9(int n,int a,int b);/*9X9数字方块(下标)*/
void number16(int n,int a,int b);/*16X16数字方块(下标)*/
void judge9(int i,int j);/*9X9搜索(下标)*/
void open9(int i,int j);/*9X9开格(下标)*/
void judge16(int i,int j);/*16X16搜索(下标)*/
void open16(int i,int j);/*16X16开格(下标)*/
void sound9(int i,int j);/*9X9音效*/
void sound16(int i,int j);/*16X16音效*/
/***************************************************************************************************************************************/
/*主函数*/
/***************************************************************************************************************************************/
/*定义全局二维数组*/			/*存储内容*/
int	map1[9][9],map2[16][16];/*MINE/NOMINE*/
int _map1[9][9],_map2[16][16];/*HIT/UNHIT/MARK/UNDETERMINE*/
int sum/*定义全局变量统计已翻方块个数*/,minenum/*计算剩余雷数*/;
time_t t1,t2,t3,t4;/*t1记录最先开始时间,t2刷新当前时间,t3记录暂停按下的时间,t4记录继续按下的时间*/
/***************************************************************************************************************************************/
void main()/*主函数*/
{
	initgraph(640, 480);
	if(first())
	{
		cleardevice();
		menu();/*画菜单*/
		stop();/*初始化"暂停图样"*/ 
		MOUSEMSG m; /*定义鼠标变量*/
		while(true)/*"一重永真循环"用以捕获对"菜单栏"的鼠标信息*/
		{     
			m=GetMouseMsg();
			if(m.uMsg==WM_LBUTTONDOWN)/*按下左键*/
				if((m.x>20&&m.x<140)&&(m.y>30&&m.y<80))/*识别玩家"最先"点击"难度"信息*/
				{
					printf("\a");
					move();/*调用"难度方块移动效果"函数*/
					extend();/*调用"伸展开始"函数*/
				}
				else if((m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*识别玩家"最先"点击"退出"信息*/
				{	
					printf("\a");
					closegraph();
					exit(0);/*关闭窗口并退出操作系统*/
				}
		}
	}
}
/***************************************************************************************************************************************/
/*函数定义*/
/***************************************************************************************************************************************/
int  first()/*游戏开场画面*/
{	
	int points1[6],points2[6];/*存两个正三角形的点坐标*/
	int points3[6],points4[6];
	points1[0]=260;points1[1]=140;points1[2]=(int)(260+50*0.866);points1[3]=(int)(140+50*1.5);points1[4]=(int)(260-50*0.866);points1[5]=(int)(140+50*1.5);
	points2[0]=260;points2[1]=(int)(140+50*2);points2[2]=(int)(260-50*0.866);points2[3]=(int)(140+50*0.5);points2[4]=(int)(260+50*0.866);points2[5]=(int)(140+50*0.5);
	points3[0]=370;points3[1]=140;points3[2]=(int)(370+50*0.866);points3[3]=(int)(140+50*1.5);points3[4]=(int)(370-50*0.866);points3[5]=(int)(140+50*1.5);
	points4[0]=370;points4[1]=(int)(140+50*2);points4[2]=(int)(370-50*0.866);points4[3]=(int)(140+50*0.5);points4[4]=(int)(370+50*0.866);points4[5]=(int)(140+50*0.5);
	setfillstyle(WHITE);/*"扫雷"封面*/
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);fillpolygon(3,points3);fillpolygon(3,points4);
	setfillstyle(BLACK);
	fillcircle(260,190,25);fillcircle(370,190,25);
	setcolor(WHITE);
	outtextxy(253,181,"扫");outtextxy(363,181,"雷");/*"扫雷"字样*/
	outtextxy(279,250,"By Chicken");/*"125代表队"字样*/
	
	IMAGE tmp;
	getimage(&tmp,0,0,textwidth("按任意键进入"),textheight("按任意键进入"));/*保存当前图像*/
	while(true)/*如果不按任意键就一直移动*/
	{
		for(int i=0;i<510;i++)/*字样在横坐标0-510范围移动*/
		{
			outtextxy(i,450,"按任意键进入");/*"按任意键进入"字样*/
			Sleep(20);/*延时*/
			putimage(i,450,&tmp);/*打印当前图像*/
			if(kbhit())/*按键信息*/
			{
				printf("\a");
				return 1;/*按键返回1*/
			}
		}
		for(;i>0;i--)/*循环移动*/
		{
			outtextxy(i,450,"按任意键进入");
			Sleep(20); 
			putimage(i,450,&tmp);
			if(kbhit())
			{
				printf("\a");
				return 1;
			}
		}
	}
}
/***************************************************************************************************************************************/
void menu()/*菜单栏*/
{
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	setbkmode(DARKGRAY);
	bar(20,30,140,80);/*难度框*/
	rectangle(20,30,140,80);/*加边框*/
	bar(20,130,140,180);/*重来框*/
	rectangle(20,130,140,180);
	bar(20,230,140,280);/*退出框*/
	rectangle(20,230,140,280);
	outtextxy(65,48,"难度");/*"难度"字样*/
	outtextxy(65,148,"重来");/*"重来"字样*/
	outtextxy(65,248,"退出");/*"退出"字样*/
	int points1[6],points2[6];/*剩雷图样*/
	points1[0]=50;points1[1]=400;points1[2]=(int)(50+25*0.866);points1[3]=(int)(400+25*1.5);points1[4]=(int)(50-25*0.866);points1[5]=(int)(400+25*1.5);
	points2[0]=50;points2[1]=(int)(400+25*2);points2[2]=(int)(50-25*0.866);points2[3]=(int)(400+25*0.5);points2[4]=(int)(50+25*0.866);points2[5]=(int)(400+25*0.5);
	setfillstyle(WHITE);
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);
	setfillstyle(BLACK);
	fillcircle(50,425,12.5);
}
/***************************************************************************************************************************************/
void move()/*难度方块移动效果*/
{
	int i;
	for(i=141;i<210;i++)/*伸展出9   X   9和16  X  16矩形*/
	{
		picture(i);
		Sleep(9);
		cover(i);
	}
		picture(i);
		setbkmode(DARKGRAY);
		outtextxy(i+36,48,"9   X   9");

	for(i=331;i<411;i++)
	{
		picture(i);
		Sleep(9);
		cover(i);
	}
		picture(i);
		setbkmode(DARKGRAY);
		outtextxy(i+36,48,"16  X  16");
}
/***************************************************************************************************************************************/
void stop()/*暂停图样*/
{	
	setcolor(WHITE);
	setfillstyle(WHITE);
	bar(38,348,47,372);
	bar(53,348,62,372);
}
/***************************************************************************************************************************************/
void keepon()/*继续图样*/
{
	int points[6];
	points[0]=38;points[1]=348;points[2]=38;points[3]=372;points[4]=62;points[5]=360;
	setcolor(WHITE);
	setfillstyle(WHITE);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
void picture(int x)/*难度方块*/
{
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	bar(x,30,x+120,80);
	rectangle(x,30,x+120,80);
}
/***************************************************************************************************************************************/
void cover(int x)/*覆盖难度方块*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(x,30,x+120,80);
	rectangle(x,30,x+120,80);
}
/***************************************************************************************************************************************/
void extend()/*伸展开始*/
{	
	/*"重来"清屏*/
	setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*覆盖前一轮残留的播放图样*/stop();/*暂停图样*/  
	setfillstyle(BLACK);bar(95,418,133,440);/*覆盖前一轮残留的剩雷数字*/
	setfillstyle(BLACK);bar(95,353,133,373);/*覆盖前一轮残留的时间数字*/
/***************************************************************************************************************************************/
	MOUSEMSG m; /*定义鼠标变量*/

	int  lastx=1,lasty=1;/*存储上一时刻鼠标所在位置*/
	while(true)/*"二重永真循环"用以捕获对"难度"的鼠标信息*/
	{
		m=GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN)/*按下左键*/
			if((m.x>211&&m.x<331)&&(m.y>30&&m.y<80))/*识别玩家"选难度时"点击"9   X   9"信息*/
			{
				PlaySound("\\扫雷\\音效\\Start.wav",NULL,SND_FILENAME|SND_ASYNC); 
				amount9();/*画表*/
				picture(210);/*先用难度矩形覆盖(为了将白色字体转换成红色字体)*/
				setcolor(LIGHTRED);
				outtextxy(211+36,48,"9   X   9");
/********************************************************布雷************************************************************/
				int x,y/*数组下标*/,s=0;/*布雷总数*/
				sum=0;/*初始化已翻方块个数*/
				minenum=10;/*初始化剩余雷数*/minenumber();/*剩余雷数字字样*/
				
				for(x=0;x<9;x++)/*初始化所有方块"未翻"*/
					for(y=0;y<9;y++)
						_map1[x][y]=UNHIT;/*UNHIT表示"未翻"*/
			
				for(x=0;x<9;x++)/*初始化所有方块"无雷"*/
					for(y=0;y<9;y++)
						map1[x][y]=NOMINE;/*NOMINE表示"无雷"*/
				
				srand((unsigned)time(NULL));/*利用time(NULL)获取时间实现播种*/ 
				while(true)
				{
					if(s<10)/*限制雷数10个*/
					{
						x=rand()%9;y=rand()%9;/*数组下标为0-8的随机整数*/
						if(map1[x][y]!=MINE)/*MINE表示"有雷"*/
						{
							map1[x][y]=MINE;
							s++;/*统计已布雷的个数*/
						}
					}
					else break;
				}
/********************************************************开始************************************************************/
				t1=time(NULL);/*获取开始系统时间*/
				int onoff=KEEPON;/*定义标记变量记录是否暂停过(KEEPON表示未暂停,STOP表示暂停过)*/
				while(true)
				{
					if(onoff==KEEPON)/*之前未暂停*/
						clock(t1);/*获取当前时间*/
					else/*之前暂停过*/
					{
						t1=t1+(t4-t3);/*弥补暂停的时间*/
						clock(t1);
					}
					onoff=KEEPON;/*重置继续标志*/
					m=GetMouseMsg();
					if(_map1[(lasty-130)/20][(lastx-210)/20]==UNHIT)/*第一次是充数,之后每一次都要检验上一时刻鼠标所在位置是否被扫过*/
						remove((lasty-130)/20,(lastx-210)/20);/*还原底色:第一次是充数,之后每一次都要把上一时刻遗留下来的光标覆盖还原成底色*/
					if((m.x>210&&m.x<390)&&(m.y>130&&m.y<310))/*鼠标在9X9表格范围内*/
					{
						if(_map1[(m.y-130)/20][(m.x-210)/20]==UNHIT)/*鼠标所在位置是"未翻"*/
						{	
							blank((m.y-130)/20,(m.x-210)/20);
							lastx=m.x;lasty=m.y;/*存储当前时刻鼠标横纵坐标,以备下一次覆盖使用*/
						}
						if(m.uMsg==WM_LBUTTONDOWN)/*左键点击*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;/*将横纵坐标换成数组下标*/
							sound9(x,y);
							judge9(x,y);/*调用9X9搜索函数*/
						}
						if(m.uMsg==WM_RBUTTONDOWN)/*右键点击*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							switch(_map1[x][y])
							{
								case UNHIT:/*鼠标所在位置是"未翻"*/
								{
									sign(x,y);/*红旗图样*/
									_map1[x][y]=MARK;
									minenum--;
									minenumber();
								}break;
								case MARK:/*鼠标所在位置是"红旗"*/
								{
									remain(x,y);/*问号图样*/
									_map1[x][y]=UNDETERMINE;
									minenum++;
									minenumber();
								}break;
								case UNDETERMINE:/*鼠标所在位置是"问号"*/
								{
									blank(x,y);/*空方块*/
									_map1[x][y]=UNHIT;
								}break;
							}		
						}
						if(m.uMsg==WM_LBUTTONDBLCLK)/*左键双击*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound9(x,y);
							if(_map1[x][y]==HIT)/*若是已翻方块*/
								open9(x,y);/*调用9X9开格函数*/
						}
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))/*识别玩家"游戏中"点击"暂停"信息*/
							{
								printf("\a");
								onoff=STOP;/*暂停标记,以便形成函数分支区别暂停与继续不同处理情况*/
								t3=time(NULL);/*即时获取"暂停时"的系统时间*/
								setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*覆盖暂停图样*/
								keepon();/*继续图样*/
								while(true)/*在"暂停中"等待鼠标响应*/
								{
									m=GetMouseMsg();
									if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))/*识别玩家"暂停中"点击"继续"信息*/
									{
										printf("\a");
										t4=time(NULL);/*即时获取"继续时"的系统时间*/
										setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*覆盖继续图样*/
										stop();/*暂停图样*/
										break;
									}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))/*识别玩家"暂停中"点击"重来"信息*/
											{outtextxy(211+36,48,"9   X   9");cover9();extend();}/*覆盖难度方块,回归到主函数*/
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*识别玩家"暂停中"点击"退出"信息*/
											{closegraph();exit(0);}/*关闭窗口并退出操作系统*/
								}
							}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))/*识别玩家"游戏中"点击"重来"信息*/
					{
						printf("\a");
						outtextxy(211+36,48,"9   X   9");cover9();extend();/*覆盖难度选择方块，回归到主函数*/
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*识别玩家"游戏中"点击"退出"信息*/
					{	
						printf("\a");
						closegraph();
						exit(0);/*关闭窗口并退出操作系统*/
					}
				}
			}
/***************************************************************************************************************************************/
			else if((m.x>411&&m.x<531)&&(m.y>30&&m.y<80))/*识别玩家“选难度时”点击“16  X  16”信息*/
			{
				PlaySound("\\扫雷\\音效\\Start.wav",NULL,SND_FILENAME|SND_ASYNC); 
				amount16();
				picture(411);
				setcolor(LIGHTRED);
				outtextxy(410+36,48,"16  X  16");
/********************************************************布雷************************************************************/
				int x,y,s=0;
				sum=0;
				minenum=40;minenumber();
				
				for(x=0;x<16;x++)
					for(y=0;y<16;y++)
						_map2[x][y]=UNHIT;
			
				for(x=0;x<16;x++)
					for(y=0;y<16;y++)
						map2[x][y]=NOMINE;
				
				srand((unsigned)time(NULL));
				while(true)
				{
					if(s<40)/*限制雷数40个*/
					{
						x=rand()%16;y=rand()%16;/*数组下标为0-15的随机整数*/
						if(map2[x][y]!=MINE)
						{
							map2[x][y]=MINE;
							s++;
						}
					}
					else break;
				}
/********************************************************开始************************************************************/
				t1=time(NULL);
				int onoff=KEEPON;
				while(true)
				{
					if(onoff==KEEPON)
						clock(t1);
					else	
					{
						t1=t1+(t4-t3);
						clock(t1);
					}
					onoff=KEEPON;
					m=GetMouseMsg();
					if(_map2[(lasty-130)/20][(lastx-210)/20]==UNHIT)
						remove((lasty-130)/20,(lastx-210)/20);
					if((m.x>210&&m.x<530)&&(m.y>130&&m.y<450))
					{
						if(_map2[(m.y-130)/20][(m.x-210)/20]==UNHIT)
						{	
							blank((m.y-130)/20,(m.x-210)/20);
							lastx=m.x;lasty=m.y;
						}
						if(m.uMsg==WM_LBUTTONDOWN)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound16(x,y);
							judge16(x,y);/*调用16X16搜索函数*/
						}
						if(m.uMsg==WM_RBUTTONDOWN)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							switch(_map2[x][y])
							{
								case UNHIT:
								{
									sign(x,y);
									_map2[x][y]=MARK;
									minenum--;
									minenumber();
								}break;
								case MARK:
								{
									remain(x,y);
									_map2[x][y]=UNDETERMINE;
									minenum++;
									minenumber();
								}break;
								case UNDETERMINE:
								{
									blank(x,y);
									_map2[x][y]=UNHIT;
								}break;
							}		
						}
						if(m.uMsg==WM_LBUTTONDBLCLK)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound16(x,y);
							if((_map2[x][y]==HIT))
								open16(x,y);/*调用16X16开格函数*/
						}
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))
							{
								printf("\a");
								onoff=STOP;
								t3=time(NULL);
								setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);
								keepon();
								while(true)
								{
									m=GetMouseMsg();
									if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))
									{
										printf("\a");
										t4=time(NULL);
										setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);
										stop();
										break;
									}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))
											{outtextxy(410+36,48,"16  X  16");cover16();extend();}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))
											{closegraph();exit(0);}
								}
							}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))
					{
						printf("\a");
						outtextxy(410+36,48,"16  X  16");cover16();extend();
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))
					{
						printf("\a");
						closegraph();exit(0);
					}
				}
/***************************************************************************************************************************************/				
			}
			else if((m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*识别玩家“选难度时”点击“退出”信息*/
			{	
				printf("\a");
				closegraph();exit(0);
			}
	}
}
/***************************************************************************************************************************************/
void amount9()/*9X9表格*/
{
	setcolor(WHITE);/*声明现在的边框颜色*/
	setfillstyle(DARKGRAY,24);/*声明现在的填充颜色*/
	bar(210,130,390,310);/*填充矩形范围*/
	for(int k=0;k<10;k++)/*画9x9的格子线*/
	{
		 line(210+20*k,130,210+20*k,310);
		 line(210,130+20*k,390,130+20*k);
	}
}
/***************************************************************************************************************************************/
void cover9()/*9X9覆盖表格*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(210,130,390,310);
	rectangle(210,130,390,310);
}
/***************************************************************************************************************************************/
void amount16()/*16X16表格*/
{
	setcolor(WHITE);/*声明现在的边框颜色*/
	setfillstyle(DARKGRAY,24);/*声明现在的填充颜色*/
	bar(210,130,530,450);/*填充矩形范围*/
	for(int k=0;k<17;k++)/*画16x16的格子线*/
	{
		line(210+20*k,130,210+20*k,450);
		line(210,130+20*k,530,130+20*k);
	}
}
/***************************************************************************************************************************************/
void cover16()/*16X16覆盖表格*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(210,130,530,450);
	rectangle(210,130,530,450);
}
/***************************************************************************************************************************************/
void clock(time_t t1)/*时间*/
{
	setcolor(WHITE);
	setfillstyle(BLACK);
	t2=time(NULL);
	char str[2];
	bar(95,353,133,373);
	sprintf(str,"%d",t2-t1);
	outtextxy(95,353,str);
}
/***************************************************************************************************************************************/
void minenumber()/*剩雷数字*/
{
	char str[2];
	setcolor(WHITE);
	setfillstyle(BLACK);
	bar(95,418,133,440);
	sprintf(str,"%d",minenum);
	outtextxy(95,418,str);	
}
/***************************************************************************************************************************************/
void mine(int x,int y)/*雷图样(坐标)*/
{
	blank((y-130)/20,(x-210)/20);
	int points1[6],points2[6];
	points1[0]=x;points1[1]=y;points1[2]=(int)(x+10*0.866);points1[3]=(int)(y+10*1.5);points1[4]=(int)(x-10*0.866);points1[5]=(int)(y+10*1.5);
	points2[0]=x;points2[1]=(int)(y+10*2);points2[2]=(int)(x-10*0.866);points2[3]=(int)(y+10*0.5);points2[4]=(int)(x+10*0.866);points2[5]=(int)(y+10*0.5);
	setfillstyle(WHITE);
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);
	setfillstyle(BLACK);
	fillcircle(x,y+10,5);
}
/***************************************************************************************************************************************/
void blank(int a,int b)/*光标覆盖(下标)*/
{	
	setcolor(WHITE);
	setfillstyle(LIGHTGRAY,24);
	fillrectangle(210+20*b,130+20*a,210+20*b+20,130+20*a+20);	
}
/***************************************************************************************************************************************/
void remove(int a,int b)/*光标还原(下标)*/
{	
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	fillrectangle(210+20*b,130+20*a,210+20*b+20,130+20*a+20);	
}
/***************************************************************************************************************************************/
void colornumber(int m,int x,int y)/*彩色数字(下标)*/
{
	char str[2];
	blank(x,y);
	switch(m)/*根据不同数字显示不同颜色*/
	{
		case 1:
			{
				setcolor(WHITE);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 2:
			{
				setcolor(LIGHTGREEN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 3:
			{
				setcolor(YELLOW);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 4:
			{
				setcolor(LIGHTCYAN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 5:
			{
				setcolor(LIGHTRED);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 6:
			{
				setcolor(BLACK);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 7:
			{
				setcolor(CYAN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 8:
			{
				setcolor(LIGHTMAGENTA);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
	}
}
/***************************************************************************************************************************************/
void sign(int a,int b)/*红旗图样(下标)*/
{
	int points[6];
	points[0]=210+20*b+10;points[1]=130+20*a+5;points[2]=210+20*b+10;points[3]=130+20*a+11;points[4]=210+20*b+4;points[5]=130+20*a+11;
	blank(a,b);/*显示带数字的空格*/
	setcolor(LIGHTRED);
	setfillstyle(LIGHTRED);
	fillpolygon(3,points);
	setcolor(WHITE);
	line(210+20*b+6,130+20*a+15,210+20*b+14,130+20*a+15);/*红旗横线*/
	line(210+20*b+6,130+20*a+16,210+20*b+14,130+20*a+16);/*加粗*/
	line(210+20*b+10,130+20*a+15,210+20*b+10,130+20*a+5);/*红旗竖线*/
	line(210+20*b+11,130+20*a+15,210+20*b+11,130+20*a+5);/*加粗*/
}
/***************************************************************************************************************************************/
void remain(int a,int b)/*问号图样(下标)*/
{
	blank(a,b);/*显示带数字的空格*/
	setbkmode(TRANSPARENT);
	outtextxy(210+20*b+6,130+20*a+3,"?");
}
/***************************************************************************************************************************************/
void number9(int n,int a,int b)/*9X9数字方块(下标)*/
{
	_map1[a][b]=HIT;/*已翻方块标记*/
	char str[20];/*接收姓名*/
	int old;/*接收旧记录*/

	if(n==0)/*若九宫格内没有雷*/
		blank(a,b);/*显示空格*/
	else
		colornumber(n,a,b);/*彩色数字图样*/
	sum++;/*已翻方块数目增1*/
	if(sum==71)/*已翻方块数目如果达到71个即胜利*/
	{
		PlaySound("\\扫雷\\音效\\Win.wav",NULL,SND_FILENAME|SND_ASYNC);

		/*最高记录判断*/
		FILE *fp1,*fp2;
		if((fp1=fopen("record9.txt","r"))==NULL)/*没有文件存在*/
		{
			fp2=fopen("record9.txt","w");
			InputBox(str,10,"恭喜您！！\n创新记录啦！！\n留下大名吧！！","新纪录");
			fprintf(fp2,"%s %d",str,t2-t1);/*将最高记录写入文件*/
			fclose(fp2);
		}
		else
		{
			fscanf(fp1,"%s %d",str,&old);/*读入旧记录*/
			if(t2-t1<old)/*新记录*/
			{
				fp2=fopen("record9.txt","w");
				InputBox(str,10,"恭喜您！！\n创新记录啦！！\n留下大名吧！！","新纪录");
				fprintf(fp2,"%s %d",str,t2-t1);/*将最高记录写入文件*/
				fclose(fp2);
			}
			else
			{	
				HWND wnd=GetHWnd();
				MessageBox(wnd,"离最高记录就差一点点啦~\n再接再厉哟~","提示",MB_OK|MB_ICONASTERISK);
			}
			fclose(fp1);
		}

		HWND wnd=GetHWnd();/*游戏胜利对话框*/
		if (MessageBox(wnd,"扫雷成功!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{setcolor(WHITE);outtextxy(211+36,48,"9   X   9");cover9();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void number16(int n,int a,int b)/*16X16数字方块(下标)*/
{
	_map2[a][b]=HIT;
	char str[20];
	int old;

	if(n==0)
		blank(a,b);
	else
		colornumber(n,a,b);
	sum++;
	if(sum==216)/*已翻方块数目如果达到216个即胜利*/
	{
		PlaySound("\\扫雷\\音效\\Win.wav",NULL,SND_FILENAME|SND_ASYNC);

		FILE *fp1,*fp2;
		if((fp1=fopen("record16.txt","r"))==NULL)
		{
			fp2=fopen("record16.txt","w");
			InputBox(str,10,"恭喜您！！\n创新记录啦！！\n留下大名吧！！","新纪录");
			fprintf(fp2,"%s %d",str,t2-t1);
			fclose(fp2);
		}
		else
		{
			fscanf(fp1,"%s %d",str,&old);
			if(t2-t1<old)
			{
				fp2=fopen("record16.txt","w");
				InputBox(str,10,"恭喜您！！\n创新记录啦！！\n留下大名吧！！","新纪录");
				fprintf(fp2,"%s %d",str,t2-t1);
				fclose(fp2);
			}
			else
			{	
				HWND wnd=GetHWnd();
				MessageBox(wnd,"离最高记录就差一点点啦~\n再接再厉哟~","提示",MB_OK|MB_ICONASTERISK);
			}
			fclose(fp1);
		}		

		HWND wnd=GetHWnd();
		if (MessageBox(wnd,"扫雷成功!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{setcolor(WHITE);outtextxy(410+36,48,"16  X  16");cover16();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void judge9(int i,int j)/*9X9搜索(下标)*/
{
	int num=0;/*统计九宫格内雷数*/
	if(_map1[i][j]==UNHIT||_map1[i][j]==UNDETERMINE)/*该位置是未翻方块或是问号方块*/
	{
		switch(map1[i][j])
		{
			case MINE:/*该位置有雷*/
			{
				for(int e=0;e<9;e++)/*摊牌布下的雷图样*/
					for(int f=0;f<9;f++)
						if(map1[e][f]==1)
							mine(210+20*f+10,130+20*e);
				HWND wnd=GetHWnd();/*游戏结束对话框*/
				if (MessageBox(wnd,"扫雷失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{outtextxy(211+36,48,"9   X   9");cover9();extend();}
				else 
					{closegraph();exit(0);}
			}
			case NOMINE:/*该位置无雷并搜索九宫格内雷数目*/
			{
				if(map1[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))/*排除边界情况*/
					num++;/*若有雷则num增1*/
				if(map1[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
					num++;
				if(map1[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
				if(map1[i][j-1]==MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
					num++;
				if(map1[i][j+1]==MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
				if(map1[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
					num++;
				if(map1[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
					num++;
				if(map1[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
			/*若该位置九宫格内无雷,则利用递归继续以九宫格为中心查找他们8个方块各自九宫格内的雷数目*/
				if(num==NOMINE)
				{
					number9(0,i,j);/*打印空白方块图样*/
					if((i-1)>=0&&(i-1)<=8&&((j-1)>=0&&(j-1)<=8))
						judge9(i-1,j-1);/*递归查找*/
					if((i-1)>=0&&(i-1)<=8&&(j>=0&&j<=8))
						judge9(i-1,j);			
					if((i-1)>=0&&(i-1)<=8&&((j+1)>=0&&(j+1)<=8))
						judge9(i-1,j+1);
					if((i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
						judge9(i,j-1);
					if((i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
						judge9(i,j+1);	
					if((i+1)>=0&&(i+1)<=8&&((j-1)>=0&&(j-1)<=8))
						judge9(i+1,j-1);
					if((i+1)>=0&&(i+1)<=8&&(j>=0&&j<=8))
						judge9(i+1,j);
					if((i+1)>=0&&(i+1)<=8&&((j+1)>=0&&(j+1)<=8))
						judge9(i+1,j+1);
				}
				else
				{
					number9(num,i,j);/*打印num数字方块图样*/
					return;/*退出子函数(递归出口)*/
				}
			}
		}
	}
}
/***************************************************************************************************************************************/
void open9(int i,int j)/*9X9开格(下标)*/
{
	int num=0/*记录有雷数目*/,all=0/*记录红旗和有雷匹配数目*/;
	/*检测有雷数*/
	if(map1[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
		num++;
	if(map1[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;
	if(map1[i][j-1]==MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i][j+1]==MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;
	if(map1[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
		num++;
	if(map1[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;	
	/*检测红旗和有雷位置是否匹配*/
	if(map1[i-1][j-1]==MINE&&_map1[i-1][j-1]==4&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;		
	if(map1[i-1][j]==MINE&&_map1[i-1][j]==4&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
		all++;					
	if(map1[i-1][j+1]==MINE&&_map1[i-1][j+1]==4&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;			
	if(map1[i][j-1]==MINE&&_map1[i][j-1]==4&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;					
	if(map1[i][j+1]==MINE&&_map1[i][j+1]==4&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;				
	if(map1[i+1][j-1]==MINE&&_map1[i+1][j-1]==4&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;				
	if(map1[i+1][j]==MINE&&_map1[i+1][j]==4&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
		all++;				
	if(map1[i+1][j+1]==MINE&&_map1[i+1][j+1]==4&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;		
	/*匹配*/
	if(all==num)
	{
		printf("\a");/*点击音效*/
		if(map1[i-1][j-1]!=MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))/*排除以雷为中心展开的错误递归*/
			judge9(i-1,j-1);/*递归查找*/
		if(map1[i-1][j]!=MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
			judge9(i-1,j);	
		if(map1[i-1][j+1]!=MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i-1,j+1);	
		if(map1[i][j-1]!=MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
			judge9(i,j-1);	
		if(map1[i][j+1]!=MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i,j+1);		
		if(map1[i+1][j-1]!=MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
			judge9(i+1,j-1);	
		if(map1[i+1][j]!=MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
			judge9(i+1,j);	
		if(map1[i+1][j+1]!=MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i+1,j+1);	
	}
	/*不匹配*/
	else 
	{
		PlaySound("\\扫雷\\音效\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);/*爆炸音效*/
		for(int e=0;e<9;e++)/*摊牌布下的雷*/
			for(int f=0;f<9;f++)
				if(map1[e][f]==1)
					mine(210+20*f+10,130+20*e);
		HWND wnd=GetHWnd();/*游戏结束对话框*/
		if (MessageBox(wnd,"扫雷失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{outtextxy(211+36,48,"9   X   9");cover9();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void judge16(int i,int j)/*16X16搜索(下标)*/
{
	int num=0;
	if(_map2[i][j]==UNHIT||_map2[i][j]==UNDETERMINE)
	{
		switch(map2[i][j])
		{
			case MINE:
			{
				for(int e=0;e<16;e++)/*摊牌布下的雷*/
					for(int f=0;f<16;f++)
						if(map2[e][f]==1)
							mine(210+20*f+10,130+20*e);
				HWND wnd=GetHWnd();/*游戏结束对话框*/
				if (MessageBox(wnd,"扫雷失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{outtextxy(410+36,48,"16  X  16");cover16();extend();}
				else {closegraph();exit(0);}
			}
			case NOMINE:
			{
				if(map2[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
					num++;
				if(map2[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				if(map2[i][j-1]==MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i][j+1]==MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				if(map2[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
					num++;
				if(map2[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				
				if(num==0)/*没有雷*/
				{
					number16(0,i,j);
					if((i-1)>=0&&(i-1)<=15&&((j-1)>=0&&(j-1)<=15))
						judge16(i-1,j-1);
					if((i-1)>=0&&(i-1)<=15&&(j>=0&&j<=15))
						judge16(i-1,j);			
					if((i-1)>=0&&(i-1)<=15&&((j+1)>=0&&(j+1)<=15))
						judge16(i-1,j+1);
					if((i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
						judge16(i,j-1);
					if((i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
						judge16(i,j+1);	
					if((i+1)>=0&&(i+1)<=15&&((j-1)>=0&&(j-1)<=15))
						judge16(i+1,j-1);
					if((i+1)>=0&&(i+1)<=15&&(j>=0&&j<=15))
						judge16(i+1,j);
					if((i+1)>=0&&(i+1)<=15&&((j+1)>=0&&(j+1)<=15))
						judge16(i+1,j+1);
				}
				else
				{
					number16(num,i,j);
					return;
				}
			}
		}
	}
}
/***************************************************************************************************************************************/
void open16(int i,int j)/*16X16开格(下标)*/
{
	int num=0,all=0;
	/*检测有雷数*/
	if(map2[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
		num++;
	if(map2[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	if(map2[i][j-1]==MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i][j+1]==MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	if(map2[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
		num++;
	if(map2[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	
	/*检测红旗和有雷位置是否匹配*/
	if(map2[i-1][j-1]==MINE&&_map2[i-1][j-1]==4&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;		
	if(map2[i-1][j]==MINE&&_map2[i-1][j]==4&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
		all++;					
	if(map2[i-1][j+1]==MINE&&_map2[i-1][j+1]==4&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;			
	if(map2[i][j-1]==MINE&&_map2[i][j-1]==4&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;					
	if(map2[i][j+1]==MINE&&_map2[i][j+1]==4&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;				
	if(map2[i+1][j-1]==MINE&&_map2[i+1][j-1]==4&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;				
	if(map2[i+1][j]==MINE&&_map2[i+1][j]==4&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
		all++;				
	if(map2[i+1][j+1]==MINE&&_map2[i+1][j+1]==4&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;	
	/*匹配*/
	if(all==num)
	{
		printf("\a");
		if(map2[i-1][j-1]!=MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i-1,j-1);
		if(map2[i-1][j]!=MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
			judge16(i-1,j);	
		if(map2[i-1][j+1]!=MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i-1,j+1);	
		if(map2[i][j-1]!=MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i,j-1);	
		if(map2[i][j+1]!=MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i,j+1);		
		if(map2[i+1][j-1]!=MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i+1,j-1);	
		if(map2[i+1][j]!=MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
			judge16(i+1,j);	
		if(map2[i+1][j+1]!=MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i+1,j+1);	
	}
	/*不匹配*/
	else 
	{
		PlaySound("\\扫雷\\音效\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);
		for(int e=0;e<16;e++)/*摊牌布下的雷*/
			for(int f=0;f<16;f++)
				if(map2[e][f]==1)
					mine(210+20*f+10,130+20*e);
		HWND wnd=GetHWnd();/*游戏结束对话框*/
		if (MessageBox(wnd,"扫雷失败!\n是否重来?","询问",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{outtextxy(410+36,48,"16  X  16");cover16();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void sound9(int i,int j)/*9X9音效*/
{
	if(map1[i][j]==MINE&&_map1[i][j]!=MARK)/*点击处是雷且未标记*/
	{
		PlaySound("\\扫雷\\音效\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);/*爆炸音效*/
		return;
	}
	if(_map1[i][j]==UNHIT||_map1[i][j]==UNDETERMINE)/*点击处未翻或问号*/
	{
		printf("\a");/*点击音效*/
		return;
	}
}
/***************************************************************************************************************************************/
void sound16(int i,int j)/*16X16音效*/
{
	if(map2[i][j]==MINE&&_map2[i][j]!=MARK)
	{
		PlaySound("\\扫雷\\音效\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);
		return;
	}
	if(_map2[i][j]==UNHIT||_map2[i][j]==UNDETERMINE)
	{
		printf("\a");
		return;
	}
}
/***************************************************************************************************************************************/
