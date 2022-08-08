//#ifndef edit_h
//#define edit_h
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
int  flag=0;
typedef struct Article {
	char *word;
	struct Article *next;
}article;
void Add(article *&p);//��̬�洢һҳ����
void Length(article *&p);//ͳ��������
void Count(article *&p,int num);//ͳ��ĳһ�ַ������ֵĴ���
void Delete(article *&p);//ɾ��ĳһ�ִ�
void Print(article *&p);//�������
void Menu();//���˵�
void Add(article *&p) {
	printf ("���������£�ÿ�����80���ַ�����Ctrl+E(^E)Ϊ������\n");

	article *q = new article;            //����Ϊ������һ�����ӱ�ͷ���

	p = q;                      //��ͷָ��

	char tmp[100];

	while (1)

	{

		gets(tmp);                  //�����ַ���

		if (strlen(tmp) > 80)


		{

			printf("ÿ���������80���ַ�!");

			continue;

		}

		if (tmp[0] == 5)break;       //�����������^E�����˳�����

		q = q->next = new article;

		q->word = new char[strlen(tmp) + 1];    //Ϊ������ռ�

		strcpy(q->word, tmp);

		if (tmp[strlen(tmp) - 1] == 5) //��ȥ���һ�����Ʒ�^E

		{

			q->word[strlen(tmp) - 1] = '\0';

			break;

		}

	}

	q->next = NULL;                //���һ��ָ��Ϊ��

	p = p->next;

	printf("\n");
    flag=1;
}
void Length(article *&p) {
	if(!flag){
		cout<<"���������£�"<<endl;
		return ;
	}
	int sum = 0;
	article *q = p;
	while (q != NULL) {
		sum += strlen(q->word);
		q = q->next;
	}
	printf("����������Ϊ:%d\n", sum);
}
int count1(article *&p){

	article *q=p;
	int count=0;

	do{

		int Len=strlen(q->word);

		for(int i=0;i<Len;i++)

			if(q->word[i]==' ')count++;

	}

	while((q=q->next)!=NULL);
	return count;
}
int count2(article *&p){
	article *q=p;
	int count=0;

	do{

		int Len=strlen(q->word);

		for(int i=0;i<Len;i++)

			if(q->word[i]<='9'&&q->word[i]>='0')count++;

	}

	while((q=q->next)!=NULL);
	return count;
}
int count3(article *&p){
	article *q=p;
	int count=0;

	do{

		int Len=strlen(q->word);

		for(int i=0;i<Len;i++)

			if((q->word[i]<='z'&&q->word[i]>='a')||(q->word[i]<='Z'&&q->word[i]>='A'))count++;

	}

	while((q=q->next)!=NULL);
	return count;
}
int count4(article *&p,char *s){
	article *q=p;
	int count=0;
	int len2=strlen(s);

	do {

		int len1=strlen(q->word);

		for(int i=0;i<len1;i++)

		{

			if(q->word[i]==s[0])

			{

				int k=0;

				for(int j=0;j<len2;j++)

					if(q->word[i+j]==s[j]) k++;

				if(k==len2)    {count++;i=i+k-1;}

			}

		}

	}

	while((q=q->next)!=NULL);//��������
	return count;
}
void Count(article *&p, int num) {
	if(!flag){
		cout<<"���������£�"<<endl;
		return ;
	}
	int sum = 0;
	switch (num) {
	case 1:
		sum = count1(p);
		printf("�����й��пո�%d��\n",sum);
		break;
	case 2:
		sum = count2(p);
		printf("�����й�������%d��\n",sum);
		break;
	case 3:
		sum = count3(p);
		printf("�����й�����ĸ%d��\n",sum);
		break;
		default:
			char str[80];
			printf("������Ҫͳ�Ƶ��ַ���:");
			cin>>str;
			sum = count4(p,str);
			printf("�����й���\"%s\" %d��\n",str,sum);
			break;
	}

}
void delstringword(char *s,char *str)          //ɾ��ָ�����ַ���

{                        //*sΪ������ַ�����*strΪ��Ҫɾ�����ַ�


	char *p=strstr(s,str);    //���ַ�����Ѱ��str��һ�γ��ֵ�λ��

	char tmp[80];

	int len=strlen(s);

	int i=len-strlen(p);

	int j=i+strlen(str);

	int count=0;

	for(int m=0;m<i;m++)tmp[count++]=s[m];

	for(int n=j;n<len;n++)tmp[count++]=s[n];

	tmp[count]='\0';

	strcpy(s,tmp);

}
void Delete(article *&p){
	if(!flag){
		cout<<"���������£�"<<endl;
		return ;
	}
	article *q=p;
	char str[80];
	cout<<"������Ҫɾ�����ַ���:";
	cin>>str;
	do

	{

		if(strstr(q->word,str)!=NULL)delstringword(q->word,str);

	}

	while((q=q->next)!=NULL);
	cout<<"ɾ���������Ϊ��\n";
	Print(p);
}
void Print(article *&p){
	if(!flag){
		cout<<"���������£�"<<endl;
		return ;
	}
	article *q=p;            //����ָ��p

	do{

		printf("%s\n",q->word);

	}

	while((q=q->next)!=NULL);      //��������

	printf("\n");

}
void Menu() {

	printf("***********���±༭ϵͳ***********\n");

	printf("1:��������                    \n");

	printf("2:ͳ�������пո����          \n");

	printf("3:ͳ�����������ָ���          \n");

	printf("4:ͳ��������Ӣ����ĸ��        \n");

	printf("5:ɾ��������ָ���ַ���        \n");

	printf("6:ͳ��������ָ���ַ������ִ���\n");

	printf("7:ͳ�����������ַ���          \n");

	printf("8:�������                    \n");

	printf("9:�˳�ϵͳ                    \n");

	printf("******************************\n");

}
//#endif
