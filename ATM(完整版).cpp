#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define MAX_PASSWORD 6

const char* show_realtime(time_t t)
{
	static char buf[32];
	char* p = NULL;
	time(&t);
	strcpy(buf, ctime(&t));
	p = strchr(buf, '\n');
	*p = '\0';
	return buf;
}


void color(int x)								// 0=黑色     8=灰色　
{										// 1=蓝色     9=淡蓝色
	if (x >= 0 && x <= 15)							// 2=绿色     10=淡绿色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	// 3=湖蓝色   11=淡浅绿色 
	else									// 4=红色     12=淡红色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	// 5=紫色     13=淡紫色 
}										// 6=黄色     14=淡黄色 
										// 7=白色     15=亮白色

int Y;
int language()
{
	int m;
	scanf("%d",&m);
	getchar();
	if (m)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
struct Account
{
	char name[100];//姓名
	char username[21];//账户
	char password[100];//密码
	char idCard[100];//身份证
	char phone[100];//电话号码
	float money;

	struct Account *next;
};

typedef struct Account Account;

Account *head = NULL;
Account *tail = NULL;

void iCard(Account *cru)
{
	char strd[21] = {'\0'};
	char str1[7] = "621668";
	char str2[4];
	char str3[11];
	int sum;


	sum = rand() % (100 - 10) + 10;
	sprintf(str2, "%d", sum);
	sprintf(str3, "%ld", time(NULL));

	strcat(strd, str1);
	strcat(strd, str2);
	strcat(strd, str3);
	for (int i = 0; i < 21; i++)
	{
		cru->username[i] = strd[i];
	}
	

}

void getpasswd(Account* pa)
{
	char c;
	int i = 0;
	while ((c = getch()) != '\r')
	{
		if (c == '\b'&&i>0)
		{
			pa->password[--i] = NULL;
			printf("\b");
			printf(" ");
			printf("\b");
			
		}
		if(c!='\b')
		{
			pa->password[i] = c;
			putchar('*');
			i++;
			if (i > MAX_PASSWORD)
			{
				pa->password[--i] = NULL;
				printf("\b");
				printf(" ");
				printf("\b");
			}
		}
		
		
	}
		if (Y)
		{
			printf(".......输入成功，回车继续\n");
		}
		else
		{
			printf(".......Enter successfully, press Enter to continue\n");
		}
	pa->password[i]='\0';
	return;
}

void addNode(Account *node)//Account链表的连接
{
	node->next = NULL;
	if (head == NULL)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
	}
}

struct TransactionRecord   //交易记录
{
	char username[100];
	char timestamp[50];//时间
	char type[20];//交易类型
	float amount;//数额 
	float money;//当前余额

	struct TransactionRecord * next;
};
typedef struct TransactionRecord TR;

TR * trHead = NULL;
TR * trTail = NULL;

void addNodeTR(TR *oNode)//TR链表的连接
{
	oNode->next = NULL;
	if (trHead == NULL)
	{
		trHead = oNode;
		trTail = oNode;
	}
	else
	{
		trTail->next = oNode;
		trTail = oNode;
	}
}


int init()
{
	FILE* fp = fopen("D:\\VS2015\\atm.txt", "r");
	FILE* fp2=fopen("D:\\VS2015\\transation_record.txt", "r");
	if ((fp == NULL)&&(fp2==NULL))
	{
		return 0;
	}
	else {
				while (!feof(fp))//将文件里的数据写到结构体数组中
				{
					//申请一块内存空间，然后把地址赋值给指针newNodeP 
					Account * newNodeP = (Account *)malloc(sizeof(Account));
					fscanf(fp, "%s %s %s %s %s %f\n", newNodeP->name, newNodeP->username, newNodeP->password, newNodeP->idCard, newNodeP->phone, &newNodeP->money);

					addNode(newNodeP);
				}
				while (!feof(fp2))
				{
					TR * newNodeTr=(TR *)malloc(sizeof(TR));
					fscanf(fp2, "%s %[^\t]%*c %s %f %f\n", newNodeTr->username, newNodeTr->timestamp, newNodeTr->type, &newNodeTr->amount,&newNodeTr->money);

					addNodeTR(newNodeTr);
				}
				return 1;
				fclose(fp);
				fclose(fp2);
		}
}


void printLinkedList()//输出链表里的数据
{
	Account *curP = head;
	TR* curP1 = trHead;
	while (curP != NULL)
	{
			if (Y)
			{
			printf("姓名:%-15s账号:%-22s密码:%-8s身份证:%-25s电话:%-12s余额:%f\n"
			, curP->name, curP->username, curP->password, curP->idCard, curP->phone, curP->money);
			}
			else
			{
			printf("name:%-15s ID:%-22s password:%-8s identity card:%-25s phone:%-12s balance:%f\n"
			, curP->name, curP->username, curP->password, curP->idCard, curP->phone, curP->money);
			}
			
		
		curP = curP->next;
	}
	printf("\n");
	while (curP1 != NULL)
	{
		if (Y)
		{
			printf("账号：%s\t时间：%s\t交易类型：%s\t交易金额：%f\t剩余金额：%f\n", curP1->username, curP1->timestamp, curP1->type, curP1->amount,curP1->money);
		}
		else
		{
			printf("ID：%s\t time：%s\t trade type：%s\t transaction amount：%f\t balance：%f\n", curP1->username, curP1->timestamp, curP1->type, curP1->amount,curP1->money);
		}

		curP1 = curP1->next;
	}
}

void exitFunction()//将链表里的数据写到atm.txt文件中
{
	FILE* fp = fopen("D:\\VS2015\\atm.txt", "w");
	Account * curP = head;
	while (curP != NULL)
	{
		fprintf(fp, "%-12s\t%-22s\t%-8s\t%-21s\t%-14s\t%f\n", curP->name, curP->username, curP->password, curP->idCard, curP->phone, curP->money);
		curP = curP->next;
	}
	fclose(fp);
}

void saveTransactionRecord()//交易记录存储到文件transation_record.txt中
{
	FILE* fP = fopen("D:\\VS2015\\transation_record.txt", "w");
	TR* curP = trHead;
	while (curP != NULL)
	{
		fprintf(fP, "%-22s%s\t%-10s%-15f\t%f\n", curP->username, curP->timestamp, curP->type, curP->amount,curP->money);
		curP = curP->next;
	}
	fclose(fP);
}



void signUp()//开户
{
	
	srand(time(0));
	Account * newNodeP = (Account *)malloc(sizeof(Account));
		if (Y)
		{
			printf("请输入姓名:");
			scanf("%s", newNodeP->name);

			iCard(newNodeP);
			printf("你的银行卡号是：%s\n", newNodeP->username);
			while (1)
			{
				char pass1[7] = { '\0' };
				char pass2[7] = { '\0' };
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						printf("-----密码至少6位且不包含空格-----\n请输入密码:");
						getpasswd(newNodeP);
						strcat(pass1, newNodeP->password);
					}
					else
					{
						printf("请在输入密码:");
						getpasswd(newNodeP);
						strcat(pass2, newNodeP->password);
					}

				}
				if (strcmp(pass1, pass2) == 0)
				{
					color(14);
					printf("密码创建成功！\n");
					color(7);
					break;
				}
				else
				{
					color(12);
					printf("密码创建失败，请重新输入！\n");
					color(7);
				}
			}
			


			printf("请输入身份证号码:");
			scanf("%s", newNodeP->idCard);

			printf("请输入电话号码:");
			scanf("%s", newNodeP->phone);
			getchar();

			newNodeP->money = 0.0f;

			addNode(newNodeP);
			color(14);
			printf("创建成功！\n");
			color(7);
		}
		else
		{
			printf("Please enter your name:");
			scanf("%s", newNodeP->name);

			iCard(newNodeP);
			printf("Your bank card number is：%s\n", newNodeP->username);

			while (1)
			{
				char pass1[7] = { '\0' };
				char pass2[7] = { '\0' };
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						printf("Minimum 6 Characters No Spaces\nenter your PIN:");
						getpasswd(newNodeP);
						strcat(pass1, newNodeP->password);
					}
					else
					{
						printf("Please enter your password again:");
						getpasswd(newNodeP);
						strcat(pass2, newNodeP->password);
					}

				}
				if (strcmp(pass1, pass2) == 0)
				{
					color(14);
					printf("Password created successfully！\n");
					color(7);
					break;
				}
				else
				{
					color(12);
					printf("Failed to create the password, Please enter a new password！\n");
					color(7);
				}
			}

			printf("please enter your ID number:");
			scanf("%s", newNodeP->idCard);

			printf("Please enter your phone number:");
			scanf("%s", newNodeP->phone);
			getchar();

			newNodeP->money = 0.0f;

			addNode(newNodeP);

			printf("for user admin！\n");
		}
	
	system("pause");
	system("cls");
}
Account * curAccount = NULL;//指向当前登录账户的指针 
int findAccount(Account a)
{
	Account *curP = head;
	while (curP != NULL)
	{
		if ((strcmp(curP->username, a.username) == 0) && (strcmp(curP->password, a.password) == 0))
		{
			curAccount = curP;
			return 1;
		}
		curP = curP->next;
	}
	return 0;
}

void updatePassword()//密码修改函数
{
		if (Y)
		{
			printf("请输入旧密码:\n");
			char oldPassword[100] = { '\0' };
			scanf("%s", oldPassword);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				//让其修改 
				printf("请输入新密码：\n");
				scanf("%s", curAccount->password);
				color(14);
				printf("----------------\n");
				printf("|--修改成功！--|\n");
				printf("----------------\n");
			}
			else
			{
				color(12);
				printf("--------------------------------\n");
				printf("|--旧密码输入错误，拒绝修改！--|\n");
				printf("--------------------------------\n");
			}
			color(7);
		}
		else
		{
			printf("Please importation of old passwords:\n");
			char oldPassword[100] = { '\0' };
			scanf("%s", oldPassword);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				//让其修改 
				printf("please enter new password：\n");
				scanf("%s", curAccount->password);
				printf("modify successfully！\n");
			}
			else
			{
				printf("The old password is incorrect and cannot be changed！\n");
			}
		}
	
}

void homePage()
{
	system("cls");
	updatePassword();
}



void saveMoney()//存款函数
{
		float money;
		if (Y)
		{
			printf("请输入存钱金额：");
			scanf("%f", &money);
			getchar();
			curAccount->money += money;
			printf("----------------\n");
			printf("|--存款成功！--|\n");
			printf("----------------\n");
		}
		else
		{
			printf("Please enter the deposit amount：");
			
			scanf("%f", &money);
			getchar();
			curAccount->money += money;
			printf("Deposit successfully！\n");
		}
	

		exitFunction();//保存数据（Account）

		TR *newNode = (TR *)malloc(sizeof(TR));

		char t[20] = { "存款/收入" };

		strcpy(newNode->username, curAccount->username);
		strcpy(newNode->type, t);        //记录交易类型
		newNode->amount = money;         //记录交易金额

		time_t the_time=0;
		strcpy(newNode->timestamp, show_realtime(the_time));
		//newNode->timestamp = time(NULL); //记录当前时间戳
		newNode->money=curAccount->money;//保存当前余额

		addNodeTR(newNode);     //链表连接（TR）
		saveTransactionRecord();//保存数据（TR）
	
}

void drawMoney()//取款函数
{
	if (Y)
	{
		printf("请输入取款金额:");
	}
	else
	{
		printf("Please enter the withdrawal amount:");
	}
	
	float money;
	scanf("%f", &money);
	getchar();

	if (money>curAccount->money)
	{
		color(12);
		if (Y)
		{
			printf("----------------\n");
			printf("|--金额不足！--|\n");
			printf("----------------\n");

		}
		else
		{
			printf("-------------------------\n");
			printf("|--insufficient fund！--|");
			printf("-------------------------\n");
		}
		color(7);
		
	}
	else
	{
		curAccount->money = curAccount->money - money;
		if (Y)
		{
			printf("---取款成功！---\n");
		}
		else
		{
			printf("---Withdrawals success！---\n");
		}

		exitFunction();   //保存数据（Account）

		TR *newNode = (TR *)malloc(sizeof(TR));
		char t[20] = { "取款/支出" };
		strcpy(newNode->username, curAccount->username);
		strcpy(newNode->type, t);          //记录交易类型
		newNode->amount = money;           //记录交易金额

		time_t the_time=0;
		strcpy(newNode->timestamp,show_realtime(the_time));
		//newNode->timestamp = time(NULL);   //记录当前时间戳
		newNode->money=curAccount->money;  //保存当前余额

		addNodeTR(newNode);     //链表连接（TR）
		saveTransactionRecord();//保存数据（TR）
		return;
		
	}
}

Account * findOtherAccount(char otherUsername[])
{
	Account * curp = head;
	while (curp != NULL)
	{
		if (strcmp(curp->username, otherUsername) == 0)
		{
			return curp;
		}
		curp = curp->next;
	}
	return NULL;
}


void transfer()
{
	color(7);
	if (Y)
	{
		printf("请输入对方账户：");
	}
	else
	{
		printf("Please enter your account：");
	}
	char otherUsername[100];
	scanf("%s", otherUsername);
	Account * otherAccont = findOtherAccount(otherUsername);
	if (otherAccont == NULL)
	{
		color(12);
		if (Y)
		{
			printf("------------------\n");
			printf("|--账户不存在！--|\n");
			printf("------------------\n");
		}
		else
		{
			printf("------------------------------\n");
			printf("|--Account does not exist！--|\n");
			printf("------------------------------\n");
		}
		color(7);
	}
	else
	{
		while(1)
		{
			color(7);
			if (Y)
			{
				printf("请输入转账金额：");
			}
			else
			{
				printf("Please enter the transfer amount：");
			}
			
			int money;
			scanf("%d", &money);
			getchar();

			if(money>curAccount->money)
			{
				color(12);
				if (Y)
				{
					printf("-------------------------\n");
					printf("|--当前账户余额不足!!!--|\n");
					printf("-------------------------\n");
				}
				else
				{
					printf("---------------------------------------------------\n");
					printf("///The current account balance is insufficient！///\n");
					printf("---------------------------------------------------\n");
				}
				color(7);
			}
			else
			{
		
				//当前账户余额变化：减少 
				curAccount->money = curAccount->money - money;
				//对方账户余额变化：增加
				otherAccont->money = otherAccont->money + money;

				color(14);
				if (Y)
				{
					printf("转账成功！\n");
				}
				else
				{
					printf("Transfer success！\n");
				}
				color(7);

				exitFunction();//保存数据（Account）

				TR *newNode = (TR *)malloc(sizeof(TR));

				char t[20] = { "转账/转入" };

				strcpy(newNode->username, curAccount->username);
				strcpy(newNode->type, t);        //记录交易类型
				newNode->amount = money;         //记录交易金额

				time_t the_time=0;
				strcpy(newNode->timestamp,show_realtime(the_time));
				//newNode->timestamp = time(NULL); //记录当前时间戳
				newNode->money = curAccount->money;//保存当前余额

				addNodeTR(newNode);     //链表连接（TR）

				TR *newNode1 = (TR *)malloc(sizeof(TR));
				char other[20] = { "转账/转出" };

				strcpy(newNode1->username, otherAccont->username);
				strcpy(newNode1->type, other);        //记录交易类型
				newNode1->amount = money;             //记录交易金额

				strcpy(newNode1->timestamp, show_realtime(the_time));
				//newNode1->timestamp = time(NULL);     //记录当前时间戳
				newNode1->money = otherAccont->money; //保存当前余额

				addNodeTR(newNode1);     //链表连接（TR）
				saveTransactionRecord();//保存数据（TR）
				break;
			}
		}

	}


}

void signIn() //登录函数
{
	for (int i = 0; i<3;i++)
	{
		color(7);
		Account a;
		if (Y)
		{
			printf("----------------------\n");
			printf("|------欢迎登录------|\n");
			printf("----------------------\n");
			
			printf("请输入账号：");
			scanf("%s", a.username);
			getchar();

			printf("请输入密码：");
		}
		else
		{
			printf("-----------------------\n");
			printf("|--Welcome to Log on--|\n");
			printf("-----------------------\n");
			printf("Please enter mail account username：");
			scanf("%s", a.username);
			getchar();

			printf("enter your PIN：");
		}
		
		getpasswd(&a);
		getchar();
		while (1)
		{
			if (findAccount(a))
			{
				system("cls");
				if (Y)
				{
					color(14);
					printf("////登录成功！////\n");
					color(3);
					printf("-------------------\n");
					printf("|--【1】修改密码--|\n");
					printf("-------------------\n");
					printf("|--【2】需要取款--|\n");
					printf("-------------------\n");
					printf("|--【3】需要存款--|\n");
					printf("-------------------\n");
					printf("|--【4】需要转账--|\n");
					printf("-------------------\n");
					printf("|--【5】退出登录--|\n");
					printf("-------------------\n");
				}
				else
				{
					color(14);
					printf("-------login successfully！------\n"); 
					color(3);
					printf("---------------------------------\n");
					printf("|--【1】change password---------|\n");
					printf("---------------------------------\n");
					printf("|--【2】Need to withdraw money--|\n");
					printf("---------------------------------\n");
					printf("|--【3】liquid funds------------|\n");
					printf("---------------------------------\n");
					printf("|--【4】Need to transfer--------|\n");
					printf("---------------------------------\n");
					printf("|--【5】Logout------------------|\n");
					printf("---------------------------------\n");
				}
				
				int iIint;
				scanf("%d", &iIint);
				getchar();
				if (iIint == 1)
				{
					homePage();  //修改密码
				}
				else if (iIint == 2)
				{
					drawMoney(); //取款
				}
				else if (iIint == 3)
				{
					saveMoney(); //存款
				}
				else if (iIint == 4)
				{
					transfer();//转账
				}
				else if (iIint == 5)
				{
					system("cls");
					system("color 07");
					return;
				}
				system("pause");
			}
			else
			{
				system("cls");
				system("color 0C");
				if (Y)
				{
					printf("---------------\n");
					printf("|--登录失败!--|\n");
					printf("---------------\n");
				}
				else
				{
					printf("-------------------\n");
					printf("|--Logon failed!--|\n");
					printf("-------------------\n");
				}
				break;
			}
		}
		
	}

}

int main()
{
	printf("------------------------\n");
	printf("|-------欢迎使用-------|\n");
	printf("------------------------\n");
	printf("|//【0】英文(English)//|\n");
	printf("------------------------\n");
	printf("|//【1】中文(Chinese)//|\n");
	printf("------------------------\n");
	
	Y=language();
	system("cls");
	int q = init();
	if (Y)
	{
		if (q == 0)
		{
			color(12);
			printf("----------------\n");
			printf("|--加载失败！--|\n");
			printf("----------------\n");
		}
		else
		{
			color(14);
			printf("----------------\n");
			printf("|--加载成功！--|\n");
			printf("----------------\n");
		}
		color(7);
	}
	else
	{
		if (q == 0)
		{
			color(12);
			printf("-----------------\n");
			printf("|--Load Fail！--|\n");
			printf("-----------------\n");
		}
		else
		{
			color(14);
			printf("-----------------------\n");
			printf("|--onload Function！--|\n");
			printf("-----------------------\n");
		}
		color(7);
	}
	
	char c;
	while (1)
	{
		if (Y)
		{
			printf("-----------------\n");
			printf("|///【1】开户///|\n");
			printf("-----------------\n");
			printf("|///【2】登录///|\n");
			printf("-----------------\n");
			printf("|///【3】退出///|\n");
			printf("-----------------\n");
		}
		else
		{
			printf("-------------------------\n");
			printf("|--【1】open an account-|\n");
			printf("-------------------------\n");
			printf("|--【2】Login-----------|\n");
			printf("-------------------------\n");
			printf("|--【3】exit------------|\n");
			printf("-------------------------\n");
		}
		scanf("%c", &c);
		getchar();

		switch (c)
		{
			case '1':signUp(); break;
			case '2':signIn(); break;
			case '3':
			{
				printLinkedList();
				saveTransactionRecord();
				exitFunction();
				system("pause");
				exit(NULL);
			}
		}
	}

	return 0;
}
