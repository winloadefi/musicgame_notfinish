#include <bits/stdc++.h>
#include <ctime>
#include <conio.h>
using namespace std;

int main() {
	cout << "请按照屏幕上的字符\"√\"按下键盘按键(1:D,2:f,3:J,4:K)\n按任意键开始游戏\n";
	getch();
	system("cls");
	time_t start = time(0);
	long Miss = 0, Tap = 0;
	char a[4] = {'d', 'f', 'j', 'k'}, b, c;
	while (time(0) - start < 15) {
		srand((int)time(0));
		b = rand() % 3;
		switch (b) {
			case 0:
				cout << "√ × × ×\n";
				break;
			case 1:
				cout << "× √ × ×\n";
				break;
			case 2:
				cout << "× × √ ×\n";
				break;
			case 3:
				cout << "× × × √\n";
				break;
		}
		c = getch();
		if (c == a[b]) {
			Tap++;
		} else {
			Miss++;
		}
		system("cls");
	}
	cout << "击中:" << Tap << " Miss:" << Miss;
	for (;;) {
	}
}