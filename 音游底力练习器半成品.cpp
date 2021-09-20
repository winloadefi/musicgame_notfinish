/*
第一次修改优化了随机数,代码见 https://www.bilibili.com/read/cv11974105
第二次修改修复了输出错误，代码已删除。
第三次修改做到了下落式，代码已删除。
第四次修改修复了刷新屏幕时闪烁以及时间和规定时间内击中数量显示不正确的Bug。
Version4.1修复了4号位空白问题
Version5目前属于测试版
Version4.1.1 大量双押等你挑战! 类似于别踩白块禅模式,20秒电脑版。
Version 4.1.2 增加了数据输出到文件功能
Version 4.2.1 对双押增加了判定区间
Version 4.2.1.1 修复按r继续游戏时数据没有清空问题
推荐编译器(编辑器):Dev-C++(下载页面：https://lanzoux.com/imXG3gpfjej)
Dev-C++备用下载页面: https://lanzoui.com/imXG3gpfjej
Dev-C++适用于Windows7-64Bit以上。
若您是XP系统请使用VC6.0以上。
*/
#include <fstream>//文件读写头文件
#include <iostream>//输入输出头文件
#include <stdlib.h>//system函数头文件
#include <conio.h>//检测键盘按键头文件
#include <windows.h>//Windows API头文件
#include <iomanip>//保留x位小数头文件
#include <ctime>
using namespace std;
int Tap = 0, b[8], j[8];//b[8]和j[8]是用于输出(双押)的(7行)，Tap是用于计数的。

char a[4] = {'d', 'f', 'j', 'k'}, k, c; //键位以及按键输入变量
double d = 0;//若击错则给此变量赋值游玩时间，否则直接输出20.00"

void gotoxy(short x, short y) {//控制台光标移动函数
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
SYSTEMTIME time1, start, step, step2;//定义时间变量:time1,开始，双押判定开始，双押判定结束
bool SingleOrDual;//单双判定变量
namespace gamestart {
	ofstream fout("游玩数据.txt", ios::app);//若有文件则追加，否则新建
	void gameinit() {//游戏初始化函数
		for (int i = 1; i <= 7; i++) {//对b[8] j[8]进行随机数初始化
			b[i] = rand() % 4;
			j[i] = rand() % 4;
		}
	} void gamert() {//游戏运行时函数
		Tap = 0;
		long long start1 = start.wDay * 86400000 + start.wHour * 3600000 + start.wMinute * 60000 + start.wSecond * 1000 +
		                   start.wMilliseconds;//从现在开始计时，将系统时间(总毫秒数)赋值给start1(给start变量赋值时间操作在主函数)。
		while (start.wDay * 86400000 + start.wHour * 3600000 + start.wMinute * 60000 + start.wSecond * 1000 +
		        start.wMilliseconds - start1 <= 20000) {//限时20秒
			GetLocalTime(&start);//不停的对start变量进行赋值时间
			for (int i = 1; i <= 7; i++) {//根据b[i]和j[i]的数值输出
				if (b[i] == 0 && j[i] == 0)
					cout << "■ □ □ □\n";
				else if (b[i] == 0 && j[i] == 1)
					cout << "■ ■ □ □\n";
				else if (b[i] == 0 && j[i] == 2)
					cout << "■ □ ■ □\n";
				else if (b[i] == 0 && j[i] == 3)
					cout << "■ □ □ ■\n";
				else if (b[i] == 1 && j[i] == 0)
					cout << "■ ■ □ □\n";
				else if (b[i] == 1 && j[i] == 1)
					cout << "□ ■ □ □\n";
				else if (b[i] == 1 && j[i] == 2)
					cout << "□ ■ ■ □\n";
				else if (b[i] == 1 && j[i] == 3)
					cout << "□ ■ □ ■\n";
				else if (b[i] == 2 && j[i] == 0)
					cout << "■ □ ■ □\n";
				else if (b[i] == 2 && j[i] == 1)
					cout << "□ ■ ■ □\n";
				else if (b[i] == 2 && j[i] == 2)
					cout << "□ □ ■ □\n";
				else if (b[i] == 2 && j[i] == 3)
					cout << "□ □ ■ ■\n";
				else if (b[i] == 3 && j[i] == 0)
					cout << "■ □ □ ■\n";
				else if (b[i] == 3 && j[i] == 1)
					cout << "□ ■ □ ■\n";
				else if (b[i] == 3 && j[i] == 2)
					cout << "□ □ ■ ■\n";
				else if (b[i] == 3 && j[i] == 3)
					cout << "□ □ □ ■\n";
			}
			//接下来的两个if语句是判断是否为双押(双押率为75%)
			if (b[7] != j[7]) {//如果是双押
				SingleOrDual = true; //如果是双押则将true赋值给单双判断变量
				c = getch();//将按下的键盘按键赋值给c
				GetLocalTime(&step);//对双押开始变量赋值时间
				while (true) {//开始双押循环
					GetLocalTime(&step2);//不停的对双押结束变量赋值时间
					if (kbhit()) {//如果按下了按键
						k = getch();//就把按下的按键赋值给k
						break;//然后跳出循环
					} else if ((step2.wDay * 86400000 + step2.wHour * 3600000 + step2.wMinute * 60000 + step2.wSecond * 1000 +
					            step2.wMilliseconds) - (
					               step.wDay * 86400000 + step.wHour * 3600000 + step.wMinute * 60000 + step.wSecond * 1000 +
					               step.wMilliseconds) >= 320)//否则判断双押之间经过的时间是否超过320ms
						break;//如果是就跳出循环,游戏结束。
				}
			} else {//如果是单押
				SingleOrDual = false; //否则将false赋值给单双判断变量
				c = getch();//把键盘按键赋值给c
				k = c;//让k和c相同
			}
			if ((c == a[b[7]] || k == a[b[7]]) && (c == a[j[7]] || k == a[j[7]])) {//判断是否击中,此if语句为击中
				if (b[7] == j[7])
					Tap++;//是单押则击中+1
				else
					Tap += 2; //否则则击中+2
				b[7] = b[6];
				b[6] = b[5];
				b[5] = b[4];
				b[4] = b[3];
				b[3] = b[2];
				b[2] = b[1];
				b[1] = rand() % 4;
				j[7] = j[6];
				j[6] = j[5];
				j[5] = j[4];
				j[4] = j[3];
				j[3] = j[2];
				j[2] = j[1];
				j[1] = rand() % 4;//b[8],j[8]均向后移动一位，然后在第一位赋值随机数
				gotoxy(0, 0);//回到左上角，下次输出就会覆盖本次输出。
			} else {//如果没有击中
				d = double(start.wDay * 86400000 + start.wHour * 3600000 + start.wMinute * 60000 + start.wSecond * 1000 +
				           start.wMilliseconds -
				           start1) / 1000;//将本次游戏耗时赋值给d,单位: Second
				system("cls");//执行完毕，清除屏幕。然后输出结果
				break;//跳出循环
			}
			gotoxy(0, 0);//回到左上角
		}
		system("cls");//在循环结束后清除屏幕
		if (d == 0) {//如果d没有被赋值(说明时间用完了)
			if (SingleOrDual == false) { //如果最后是单押
				cout << "时间到!\n击中:" << Tap - 1 << " 耗时约20.00\"";//输出结果(击中-1)
				fout << time1.wYear << "年" << time1.wMonth << "月" << time1.wDay << "日 " << time1.wHour << ":" << time1.wMinute << ":"
				     << time1.wSecond << " 击中:" << Tap - 1 << " 耗时约20\"\n";//输出结果和结束时的时间到文件;
			} else { //如果最后是双押
				cout << "时间到!\n击中:" << Tap - 1 << " 耗时约20.00\"";//输出结果(击中-2)
				fout << time1.wYear << "年" << time1.wMonth << "月" << time1.wDay << "日 " << time1.wHour << ":" << time1.wMinute << ":"
				     << time1.wSecond << " 击中:" << Tap - 1 << " 耗时约20\"\n";//输出结果和结束时的时间到文件;
			}
		} else {//如果时间没用完
			if (SingleOrDual) {
				cout << fixed << setprecision(2) << "您击错了。\n击中:" << Tap + 1 << " 耗时约" << d <<
				     '\"';//输出经过的时间(保留两位小数)和结果
				fout << time1.wYear << "年" << time1.wMonth << "月" << time1.wDay << "日 " << time1.wHour << ":" << time1.wMinute << ":"
				     << time1.wSecond << " 击中:" << Tap + 1 << " 耗时约" << d << "\"\n";
			}//输出结果和结束时的时间到文件
			if (!SingleOrDual) {
				cout << fixed << setprecision(2) << "您击错了。\n击中:" << Tap << " 耗时约" << d <<
				     '\"';//输出经过的时间(保留两位小数)和结果
				fout << time1.wYear << "年" << time1.wMonth << "月" << time1.wDay << "日 " << time1.wHour << ":" << time1.wMinute << ":"
				     << time1.wSecond << " 击中:" << Tap << " 耗时约" << d << "\"\n";
			}//输出结果和结束时的时间到文件
		}
	}
} int main() {
	cout << "请按照屏幕上的字符\"■\"按下键盘按键(1:D,2:f,3:J,4:K)\n按任意键开始游戏\n";
	getch();
	system("cls");
	srand(time(0));
	while (1) {
		gamestart::gameinit();
		GetLocalTime(&time1);
		GetLocalTime(&start);
		gamestart::gamert();
		cout << "\n按r继续游戏，按其他键结束。\n";
		char z;
		z = getch();
		system("cls");
		if (z != 'r' && z != 'R')
			break;
	}
	cout << "游玩数据已经保存到本目录下的 \"游玩数据.txt\"。";
}
