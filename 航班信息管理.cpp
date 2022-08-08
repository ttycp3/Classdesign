#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <malloc.h>
const int MAXN = 1e6 + 10;
char n[128];
int planenum, passengernum;
typedef struct planemessage {
	char number[16];//航班编号
	int maxbear;//最大载客量
	char beginplace[64];//起飞地点
	char endplace[64];//降落地点
	char begintime[16];//起飞时间
	char endtime[16];//降落时间
	double price;//价格
	int planesum;//未定座位数
	struct planemessage *next;
} planemessage;
planemessage * initLink() {
	planemessage * p = (planemessage*)malloc(sizeof(planemessage));
	p->next = NULL;
	return p;
}
planemessage *head = initLink();
struct passengermessage {
	char planenumer[16];//航班编号
	char idnumber[32];//身份证号
	char name[16];//姓名
	char sex[8];//性别
	char born[16];//出生日期
	int sitnumber;//座位号
};
struct passengermessage passenger[MAXN];
void print(planemessage *&stu) {
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("航班名称\t最大载客数\t起飞地点\t起飞时间\t降落地点\t降落时间\t票价\t剩余票数\n");
	printf("\n");
	printf("%4s\t\t%5d\t\t%4s\t\t%4s\t\t%4s\t\t%4s\t\t%2.2lf元\t%4d\n", stu->number, stu->maxbear, stu->beginplace, stu->begintime, stu->endplace, stu->endtime, stu->price, stu->planesum);
	printf("\n");
	if ((stu->maxbear - stu->planesum) * 10 < stu->maxbear)
		printf("\t\t注:订票人数少于最大载客量的10%%，面临取消\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	return ;
}
void cancel() {
	int flag = 0;
	printf("请输入取消的航班号:");
	scanf("%s", n);
	for (planemessage *plane = head; plane->next != NULL ; plane = plane->next) {
		if (!strcmp(plane->next->number, n)) {
			flag = 1;
			do {
				printf("找到该航班，是否删除？(Y/N):");
				scanf("%s", n);
			} while ((n[0] != 'Y' && n[0] != 'N') || strlen(n) > 1);
			if (n[0] == 'Y') {
				planemessage *plane1 = plane->next;
				plane->next = plane->next->next;
				free(plane1);
				printf("删除成功!\n");
			} else return ;
		}
	}
	if (!flag)
		printf("未找到该航班!\n");
	return ;
}
void cancelticket() {
	int flag = 0;
	char name[48], number[48];
	printf("请输入姓名:");
	scanf("%s", name);
	printf("请输入航班号:");
	scanf("%s", number);
	for (int i = 1; i <= passengernum; i++) {
		if (!strcmp(passenger[i].name, name) && !strcmp(passenger[i].planenumer, number)) {
			flag = 1;
			do {
				printf("查询到该订单，是否取消?(Y/N):");
				scanf("%s", n);
			} while ((n[0] != 'Y' && n[0] != 'N') || strlen(n) > 1);
			if (n[0] == 'Y') {
				for (planemessage *plane = head; plane->next != NULL; plane = plane->next) {
					if (!strcmp(plane->next->number, number)) {
						(plane->next->planesum)++;
						break;
					}
				}
				for(int j=i;j<passengernum;j++){
					passenger[j]=passenger[j+1];
				}
				passengernum--;
			}
			else return;
		}
	}
	if(!flag)
		printf("未找到相关订单!\n");
}
void checkplan1() {
	char name[16];
	int flag = 0;
	printf("请输入航班号:");
	scanf("%s", name);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next )
		if (!strcmp(plane->next->number, name)) {
			print(plane->next);
			flag = 1;
		}
	if (!flag)
		printf("未找到航班!\n");
	return;
}
void checkplan2() {
	int flag = 0;
	char place[24], time[24];
	printf("请输入起飞地点:");
	scanf("%s", place);
	printf("请输入起飞时间(格式xx:xx):");
	scanf("%s", time);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next) {
		if (!strcmp(plane->next->beginplace, place) && !strcmp(plane->next->begintime, time)) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("未找到航班!\n");
	return;
}
void checkplan3() {
	int flag = 0;
	char place[24];
	printf("请输入降落地点:");
	scanf("%s", place);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next)  {
		if (!strcmp(plane->next->endplace, place) ) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("未找到航班!\n");
	return;
}
void checkplan4() {
	int flag = 0;
	char place1[24], place2[24];
	printf("请输入起飞地点:");
	scanf("%s", place1);
	printf("请输入降落地点:");
	scanf("%s", place2);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next)  {
		if (!strcmp(plane->next->beginplace, place1) && !strcmp(plane->next->endplace, place2)) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("未找到航班!\n");
	return;
}

void checkplane() {
	printf("---------------------------------------\n");
	printf("      查询方式\n");
	printf("      1.航班号\n");
	printf("      2.起飞地点和起飞时间\n");
	printf("      3.降落地点\n");
	printf("      4.起飞地点和降落地点\n");
	printf("---------------------------------------\n");
	do {
		printf("请输入操作编号1~4:");
		scanf("%s", n);
	} while (n[0] < '1' || n[0] > '4' || strlen(n) > 1);
	switch (n[0]) {
		case '1':
			system("cls");
			checkplan1();
			break;
		case '2':
			system("cls");
			checkplan2();
			break;
		case '3':
			system("cls");
			checkplan3();
			break;
		case '4':
			system("cls");
			checkplan4();
			break;
	}
}
void prints(struct passengermessage stu) {
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("航班名称\t座位号\t姓名\t\t身份证号\t性别\t出生日期\n");
	printf("\n");
	printf("%8s\t%6d\t%4s\t\t%8s\t%4s\t%8s\n", stu.planenumer, stu.sitnumber, stu.name, stu.idnumber, stu.sex, stu.born);
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}
void checkticket() {
	int flag = 0;
	struct passengermessage pass;
	printf("请输入姓名:");
	scanf("%s", pass.name);
	printf("请输入身份证号:");
	scanf("%s", pass.idnumber);
	for (int i = 1; i <= passengernum; i++)
		if (!strcmp(pass.name, passenger[i].name) && !strcmp(pass.idnumber, passenger[i].idnumber)) {
			prints(passenger[i]);
			flag = 1;
		}
	if (!flag)
		printf("未查询到乘客信息!\n");
}
void add() {
	int sum;
	char number[24];
	planemessage *plane = head;
	printf("请输入添加数目:");
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++) {
		int flag = 0;
		printf("请输入航班编号:");
		scanf("%s", number);
		for (; plane->next != NULL; plane = plane->next)
			if (!strcmp(plane->next->number, number)) {
				flag = 1;
				break;
			}
		if (flag == 1) {
			printf("已存在该航班信息！\n");
			continue ;
		}
		plane->next = (planemessage *)malloc(sizeof(planemessage));
		strcpy(plane->next->number, number);
		printf("请输入最大载客量:");
		scanf("%d", &plane->next->maxbear);
		printf("请输入起飞地点:");
		scanf("%s", plane->next->beginplace);
		printf("请输入起飞时间(格式xx:xx):");
		scanf("%s", plane->next->begintime);
		printf("请输入降落地点:");
		scanf("%s", plane->next->endplace);
		printf("请输入降落时间:");
		scanf("%s", plane->next->endtime);
		printf("请输入单价:");
		scanf("%lf", &plane->next->price);
		plane->next->planesum = plane->next->maxbear;
		FILE *fp;
		fp = fopen("test.txt", "a+");
		if (fp == NULL) {
			printf("打开航班数据库失败!\n");
			exit(0);
		}
		fprintf(fp, "%s %d %s %s %s %s %lf %d\n", plane->next->number, plane->next->maxbear, plane->next->beginplace, plane->next->begintime, plane->next->endplace, plane->next->endtime, plane->next->price, plane->next->planesum);
		fclose(fp);
	}
}
void menu() {
	printf("****************************************\n");
	printf("          菜单\n");
	printf("        1.增加航班记录\n");
	printf("        2.航班查询\n");
	printf("        3.航班订票\n");
	printf("        4.航班退票\n");
	printf("        5.订票信息查询\n");
	printf("        6.删除航班记录\n");
	printf("        7.退出系统\n");
	printf("****************************************\n");
}
void writein() {
	FILE *fp;
	fp = fopen("test.txt", "r");
	if (fp == NULL) {
		printf("打开航班数据库失败!\n");
		exit(0);
	}
	planemessage *HEAD = head;
	planemessage *plane = (planemessage *)malloc(sizeof(planemessage));
	int i = 1;
	while (fscanf(fp, "%s%d%s%s%s%s%lf%d", plane->number, &plane->maxbear, plane->beginplace, plane->begintime, plane->endplace, plane->endtime, &plane->price, &plane->planesum) != EOF) {
		i++;
		plane->next = HEAD->next;
		HEAD->next = plane;
		HEAD = HEAD->next;
		plane = (planemessage *)malloc(sizeof(planemessage));
	}
	fclose(fp);
	free(plane);
	planenum = i;
}
void order() {
	struct passengermessage pass;
	printf("请输入姓名:");
	scanf("%s", pass.name);
	printf("请输入身份证号:");
	scanf("%s", pass.idnumber);
	printf("性别(男/女):");
	scanf("%s", pass.sex);
	printf("出生年月(xxxx年xx月):");
	scanf("%s", pass.born);
	printf("登录成功!\n");
	printf("---------------------------------------\n");
	int sum;
	printf("请输入订票数目:");
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++) {
		struct planemessage plane1;
		printf("请输入航班号:");
		scanf("%s", plane1.number);
		printf("请输入起飞地点:");
		scanf("%s", plane1.beginplace);
		printf("请输入起飞时间:");
		scanf("%s", plane1.begintime);
		printf("请输入降落地点:");
		scanf("%s", plane1.endplace);
		int flag = 0;
		for (planemessage *plane = head; plane->next != NULL; plane = plane->next) {
			if (!strcmp(plane->next->number, plane1.number) && !strcmp(plane->next->beginplace, plane1.beginplace) && !strcmp(plane->next->begintime, plane1.begintime) && !strcmp(plane->next->endplace, plane1.endplace)) {
				flag = 1;
				if (plane->next->planesum) {
					flag = 2;
					strcpy(pass.planenumer, plane->next->number);
					pass.sitnumber = plane->next->maxbear - plane->next->planesum + 1;
					printf("订票成功!您的座位号是:%d\n", pass.sitnumber);
					(plane->next->planesum)--;
					passenger[++passengernum] = pass;
				}
			}
		}
		if (!flag)
			printf("订票失败，未找到符合条件的航班\n");
		else if (flag == 1)
			printf("订票失败，航班票数不足!\n");
	}
}
int main() {
	writein();
	while (1) {
		menu();
		do {
			printf("请输入操作编号1~7:");
			scanf("%s", n);
		} while (n[0] < '1' || n[0] > '7' || strlen(n) > 1);
		switch (n[0]) {
			case '1':
				system("cls");
				add();
				break;
			case '2':
				system("cls");
				checkplane();
				break;
			case '3':
				system("cls");
				order();
				break;
			case '4':
				system("cls");
				cancelticket();
				break;
			case '5':
				system("cls");
				checkticket();
				break;
			case '6':
				system("cls");
				cancel();
				break;
			case '7':
				return 0;
		}
		do {
			printf("是否返回菜单?(Y/N):");
			scanf("%s", n);
		} while ((n[0] != 'Y' && n[0] != 'N') || strlen(n) > 1);
		if (n[0] == 'Y') {
			system("cls");
			continue;
		} else
			return 0;
	}
}
