#include <iostream>
#include "edit.h"
#include<conio.h>
#include<cstring>
#include<string>
using namespace std;

int main() {
	string ord;
	article *head;
	while (1) {
		Menu();
		cout << "请输入指令:";
		while (cin >> ord && (ord.size() > 1 || ord > "9" || ord < "1"))
			cout << "非法输入!请输入数字1~9" << endl;
		int a = atoi(ord.c_str());
		switch (a) {
			case 1:
				system("cls");
				Add(head);
				break;
			case 2:
				system("cls");
				Count(head, 1);
				break;
			case 3:
				system("cls");
				Count(head, 2);
				break;
			case 4:
				system("cls");
				Count(head, 3);
				break;
			case 5:
				system("cls");
				Delete(head);
				break;
			case 6:
				system("cls");
				Count(head, 4);
				break;
			case 7:
				system("cls");
				Length(head);
				break;
			case 8:
				system("cls");
				Print(head);
				break;
			default:
				return 0;
		}
	}
}
