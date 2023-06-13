#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <malloc.h>
const int MAXN = 1e6 + 10;
char n[128];
int planenum, passengernum;
typedef struct planemessage {
	char number[16];//������
	int maxbear;//����ؿ���
	char beginplace[64];//��ɵص�
	char endplace[64];//����ص�
	char begintime[16];//���ʱ��
	char endtime[16];//����ʱ��
	double price;//�۸�
	int planesum;//δ����λ��
	struct planemessage *next;
} planemessage;
planemessage * initLink() {
	planemessage * p = (planemessage*)malloc(sizeof(planemessage));
	p->next = NULL;
	return p;
}
planemessage *head = initLink();
struct passengermessage {
	char planenumer[16];//������
	char idnumber[32];//���֤��
	char name[16];//����
	char sex[8];//�Ա�
	char born[16];//��������
	int sitnumber;//��λ��
};
struct passengermessage passenger[MAXN];
void print(planemessage *&stu) {
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("��������\t����ؿ���\t��ɵص�\t���ʱ��\t����ص�\t����ʱ��\tƱ��\tʣ��Ʊ��\n");
	printf("\n");
	printf("%4s\t\t%5d\t\t%4s\t\t%4s\t\t%4s\t\t%4s\t\t%2.2lfԪ\t%4d\n", stu->number, stu->maxbear, stu->beginplace, stu->begintime, stu->endplace, stu->endtime, stu->price, stu->planesum);
	printf("\n");
	if ((stu->maxbear - stu->planesum) * 10 < stu->maxbear)
		printf("\t\tע:��Ʊ������������ؿ�����10%%������ȡ��\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	return ;
}
void cancel() {
	int flag = 0;
	printf("������ȡ���ĺ����:");
	scanf("%s", n);
	for (planemessage *plane = head; plane->next != NULL ; plane = plane->next) {
		if (!strcmp(plane->next->number, n)) {
			flag = 1;
			do {
				printf("�ҵ��ú��࣬�Ƿ�ɾ����(Y/N):");
				scanf("%s", n);
			} while ((n[0] != 'Y' && n[0] != 'N') || strlen(n) > 1);
			if (n[0] == 'Y') {
				planemessage *plane1 = plane->next;
				plane->next = plane->next->next;
				free(plane1);
				printf("ɾ���ɹ�!\n");
			} else return ;
		}
	}
	if (!flag)
		printf("δ�ҵ��ú���!\n");
	return ;
}
void cancelticket() {
	int flag = 0;
	char name[48], number[48];
	printf("����������:");
	scanf("%s", name);
	printf("�����뺽���:");
	scanf("%s", number);
	for (int i = 1; i <= passengernum; i++) {
		if (!strcmp(passenger[i].name, name) && !strcmp(passenger[i].planenumer, number)) {
			flag = 1;
			do {
				printf("��ѯ���ö������Ƿ�ȡ��?(Y/N):");
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
		printf("δ�ҵ���ض���!\n");
}
void checkplan1() {
	char name[16];
	int flag = 0;
	printf("�����뺽���:");
	scanf("%s", name);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next )
		if (!strcmp(plane->next->number, name)) {
			print(plane->next);
			flag = 1;
		}
	if (!flag)
		printf("δ�ҵ�����!\n");
	return;
}
void checkplan2() {
	int flag = 0;
	char place[24], time[24];
	printf("��������ɵص�:");
	scanf("%s", place);
	printf("���������ʱ��(��ʽxx:xx):");
	scanf("%s", time);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next) {
		if (!strcmp(plane->next->beginplace, place) && !strcmp(plane->next->begintime, time)) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("δ�ҵ�����!\n");
	return;
}
void checkplan3() {
	int flag = 0;
	char place[24];
	printf("�����뽵��ص�:");
	scanf("%s", place);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next)  {
		if (!strcmp(plane->next->endplace, place) ) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("δ�ҵ�����!\n");
	return;
}
void checkplan4() {
	int flag = 0;
	char place1[24], place2[24];
	printf("��������ɵص�:");
	scanf("%s", place1);
	printf("�����뽵��ص�:");
	scanf("%s", place2);
	for (planemessage *plane = head; plane->next != NULL; plane = plane->next)  {
		if (!strcmp(plane->next->beginplace, place1) && !strcmp(plane->next->endplace, place2)) {
			print(plane->next);
			flag = 1;
		}
	}
	if (!flag)
		printf("δ�ҵ�����!\n");
	return;
}

void checkplane() {
	printf("---------------------------------------\n");
	printf("      ��ѯ��ʽ\n");
	printf("      1.�����\n");
	printf("      2.��ɵص�����ʱ��\n");
	printf("      3.����ص�\n");
	printf("      4.��ɵص�ͽ���ص�\n");
	printf("---------------------------------------\n");
	do {
		printf("������������1~4:");
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
	printf("��������\t��λ��\t����\t\t���֤��\t�Ա�\t��������\n");
	printf("\n");
	printf("%8s\t%6d\t%4s\t\t%8s\t%4s\t%8s\n", stu.planenumer, stu.sitnumber, stu.name, stu.idnumber, stu.sex, stu.born);
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}
void checkticket() {
	int flag = 0;
	struct passengermessage pass;
	printf("����������:");
	scanf("%s", pass.name);
	printf("���������֤��:");
	scanf("%s", pass.idnumber);
	for (int i = 1; i <= passengernum; i++)
		if (!strcmp(pass.name, passenger[i].name) && !strcmp(pass.idnumber, passenger[i].idnumber)) {
			prints(passenger[i]);
			flag = 1;
		}
	if (!flag)
		printf("δ��ѯ���˿���Ϣ!\n");
}
void add() {
	int sum;
	char number[24];
	planemessage *plane = head;
	printf("�����������Ŀ:");
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++) {
		int flag = 0;
		printf("�����뺽����:");
		scanf("%s", number);
		for (; plane->next != NULL; plane = plane->next)
			if (!strcmp(plane->next->number, number)) {
				flag = 1;
				break;
			}
		if (flag == 1) {
			printf("�Ѵ��ڸú�����Ϣ��\n");
			continue ;
		}
		plane->next = (planemessage *)malloc(sizeof(planemessage));
		strcpy(plane->next->number, number);
		printf("����������ؿ���:");
		scanf("%d", &plane->next->maxbear);
		printf("��������ɵص�:");
		scanf("%s", plane->next->beginplace);
		printf("���������ʱ��(��ʽxx:xx):");
		scanf("%s", plane->next->begintime);
		printf("�����뽵��ص�:");
		scanf("%s", plane->next->endplace);
		printf("�����뽵��ʱ��:");
		scanf("%s", plane->next->endtime);
		printf("�����뵥��:");
		scanf("%lf", &plane->next->price);
		plane->next->planesum = plane->next->maxbear;
		FILE *fp;
		fp = fopen("test.txt", "a+");
		if (fp == NULL) {
			printf("�򿪺������ݿ�ʧ��!\n");
			exit(0);
		}
		fprintf(fp, "%s %d %s %s %s %s %lf %d\n", plane->next->number, plane->next->maxbear, plane->next->beginplace, plane->next->begintime, plane->next->endplace, plane->next->endtime, plane->next->price, plane->next->planesum);
		fclose(fp);
	}
}
void menu() {
	printf("****************************************\n");
	printf("          �˵�\n");
	printf("        1.���Ӻ����¼\n");
	printf("        2.�����ѯ\n");
	printf("        3.���ඩƱ\n");
	printf("        4.������Ʊ\n");
	printf("        5.��Ʊ��Ϣ��ѯ\n");
	printf("        6.ɾ�������¼\n");
	printf("        7.�˳�ϵͳ\n");
	printf("****************************************\n");
}
void writein() {
	FILE *fp;
	fp = fopen("test.txt", "r");
	if (fp == NULL) {
		printf("�򿪺������ݿ�ʧ��!\n");
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
	printf("����������:");
	scanf("%s", pass.name);
	printf("���������֤��:");
	scanf("%s", pass.idnumber);
	printf("�Ա�(��/Ů):");
	scanf("%s", pass.sex);
	printf("��������(xxxx��xx��):");
	scanf("%s", pass.born);
	printf("��¼�ɹ�!\n");
	printf("---------------------------------------\n");
	int sum;
	printf("�����붩Ʊ��Ŀ:");
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++) {
		struct planemessage plane1;
		printf("�����뺽���:");
		scanf("%s", plane1.number);
		printf("��������ɵص�:");
		scanf("%s", plane1.beginplace);
		printf("���������ʱ��:");
		scanf("%s", plane1.begintime);
		printf("�����뽵��ص�:");
		scanf("%s", plane1.endplace);
		int flag = 0;
		for (planemessage *plane = head; plane->next != NULL; plane = plane->next) {
			if (!strcmp(plane->next->number, plane1.number) && !strcmp(plane->next->beginplace, plane1.beginplace) && !strcmp(plane->next->begintime, plane1.begintime) && !strcmp(plane->next->endplace, plane1.endplace)) {
				flag = 1;
				if (plane->next->planesum) {
					flag = 2;
					strcpy(pass.planenumer, plane->next->number);
					pass.sitnumber = plane->next->maxbear - plane->next->planesum + 1;
					printf("��Ʊ�ɹ�!������λ����:%d\n", pass.sitnumber);
					(plane->next->planesum)--;
					passenger[++passengernum] = pass;
				}
			}
		}
		if (!flag)
			printf("��Ʊʧ�ܣ�δ�ҵ����������ĺ���\n");
		else if (flag == 1)
			printf("��Ʊʧ�ܣ�����Ʊ������!\n");
	}
}
int main() {
	writein();
	while (1) {
		menu();
		do {
			printf("������������1~7:");
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
			printf("�Ƿ񷵻ز˵�?(Y/N):");
			scanf("%s", n);
		} while ((n[0] != 'Y' && n[0] != 'N') || strlen(n) > 1);
		if (n[0] == 'Y') {
			system("cls");
			continue;
		} else
			return 0;
	}
}
