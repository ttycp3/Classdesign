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
void Add(article *&p);//静态存储一页文章
void Length(article *&p);//统计总字数
void Count(article *&p,int num);//统计某一字符串出现的次数
void Delete(article *&p);//删除某一字串
void Print(article *&p);//文章输出
void Menu();//主菜单
void Add(article *&p) {
	printf ("请输入文章，每行最多80个字符，以Ctrl+E(^E)为结束符\n");

	article *q = new article;            //首先为链表建立一个附加表头结点

	p = q;                      //表头指针

	char tmp[100];

	while (1)

	{

		gets(tmp);                  //输入字符串

		if (strlen(tmp) > 80)


		{

			printf("每行最多输入80个字符!");

			continue;

		}

		if (tmp[0] == 5)break;       //如果发现输入^E，则退出输入

		q = q->next = new article;

		q->word = new char[strlen(tmp) + 1];    //为结点分配空间

		strcpy(q->word, tmp);

		if (tmp[strlen(tmp) - 1] == 5) //除去最后一个控制符^E

		{

			q->word[strlen(tmp) - 1] = '\0';

			break;

		}

	}

	q->next = NULL;                //最后一个指针为空

	p = p->next;

	printf("\n");
    flag=1;
}
void Length(article *&p) {
	if(!flag){
		cout<<"请输入文章！"<<endl;
		return ;
	}
	int sum = 0;
	article *q = p;
	while (q != NULL) {
		sum += strlen(q->word);
		q = q->next;
	}
	printf("文章总字数为:%d\n", sum);
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

	while((q=q->next)!=NULL);//遍历链表
	return count;
}
void Count(article *&p, int num) {
	if(!flag){
		cout<<"请输入文章！"<<endl;
		return ;
	}
	int sum = 0;
	switch (num) {
	case 1:
		sum = count1(p);
		printf("文章中共有空格%d个\n",sum);
		break;
	case 2:
		sum = count2(p);
		printf("文章中共有数字%d个\n",sum);
		break;
	case 3:
		sum = count3(p);
		printf("文章中共有字母%d个\n",sum);
		break;
		default:
			char str[80];
			printf("请输入要统计的字符串:");
			cin>>str;
			sum = count4(p,str);
			printf("文章中共有\"%s\" %d个\n",str,sum);
			break;
	}

}
void delstringword(char *s,char *str)          //删除指定的字符串

{                        //*s为输入的字符串，*str为将要删除的字符


	char *p=strstr(s,str);    //从字符串中寻找str第一次出现的位置

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
		cout<<"请输入文章！"<<endl;
		return ;
	}
	article *q=p;
	char str[80];
	cout<<"请输入要删除的字符串:";
	cin>>str;
	do

	{

		if(strstr(q->word,str)!=NULL)delstringword(q->word,str);

	}

	while((q=q->next)!=NULL);
	cout<<"删除后的文章为：\n";
	Print(p);
}
void Print(article *&p){
	if(!flag){
		cout<<"请输入文章！"<<endl;
		return ;
	}
	article *q=p;            //定义指针p

	do{

		printf("%s\n",q->word);

	}

	while((q=q->next)!=NULL);      //遍历链表

	printf("\n");

}
void Menu() {

	printf("***********文章编辑系统***********\n");

	printf("1:输入文章                    \n");

	printf("2:统计文章中空格个数          \n");

	printf("3:统计文章中数字个数          \n");

	printf("4:统计文章中英文字母数        \n");

	printf("5:删除文章中指定字符串        \n");

	printf("6:统计文章中指定字符串出现次数\n");

	printf("7:统计文章中总字符数          \n");

	printf("8:输出文章                    \n");

	printf("9:退出系统                    \n");

	printf("******************************\n");

}
//#endif
