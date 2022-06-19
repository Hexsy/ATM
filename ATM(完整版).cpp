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


void color(int x)														// 0=��ɫ     8=��ɫ��
{																		// 1=��ɫ     9=����ɫ
	if (x >= 0 && x <= 15)												// 2=��ɫ     10=����ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	// 3=����ɫ	  11=��ǳ��ɫ 
	else																// 4=��ɫ     12=����ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	// 5=��ɫ     13=����ɫ 
}																		// 6=��ɫ     14=����ɫ 
																		// 7=��ɫ     15=����ɫ

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
	char name[100];//����
	char username[21]={'\0'};//�˻�
	char password[100];//����
	char idCard[100];//���֤
	char phone[100];//�绰����
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
			printf(".......����ɹ����س�����\n");
		}
		else
		{
			printf(".......Enter successfully, press Enter to continue\n");
		}
	pa->password[i]='\0';
	return;
}

void addNode(Account *node)//Account���������
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

struct TransactionRecord   //���׼�¼
{
	char username[100];
	char timestamp[50];//ʱ��
	char type[20];//��������
	float amount;//���� 
	float money;//��ǰ���

	struct TransactionRecord * next;
};
typedef struct TransactionRecord TR;

TR * trHead = NULL;
TR * trTail = NULL;

void addNodeTR(TR *oNode)//TR���������
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
				while (!feof(fp))//���ļ��������д���ṹ��������
				{
					//����һ���ڴ�ռ䣬Ȼ��ѵ�ַ��ֵ��ָ��newNodeP 
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


void printLinkedList()//��������������
{
	Account *curP = head;
	TR* curP1 = trHead;
	while (curP != NULL)
	{
			if (Y)
			{
			printf("����:%-15s�˺�:%-22s����:%-8s���֤:%-25s�绰:%-12s���:%f\n"
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
			printf("�˺ţ�%s\tʱ�䣺%s\t�������ͣ�%s\t���׽�%f\tʣ���%f\n", curP1->username, curP1->timestamp, curP1->type, curP1->amount,curP1->money);
		}
		else
		{
			printf("ID��%s\t time��%s\t trade type��%s\t transaction amount��%f\t balance��%f\n", curP1->username, curP1->timestamp, curP1->type, curP1->amount,curP1->money);
		}

		curP1 = curP1->next;
	}
}

void exitFunction()//�������������д��atm.txt�ļ���
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

void saveTransactionRecord()//���׼�¼�洢���ļ�transation_record.txt��
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



void signUp()//����
{
	
	srand(time(0));
	Account * newNodeP = (Account *)malloc(sizeof(Account));
		if (Y)
		{
			printf("����������:");
			scanf("%s", newNodeP->name);

			iCard(newNodeP);
			printf("������п����ǣ�%s\n", newNodeP->username);
			while (1)
			{
				char pass1[7] = { '\0' };
				char pass2[7] = { '\0' };
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						printf("-----��������6λ�Ҳ������ո�-----\n����������:");
						getpasswd(newNodeP);
						strcat(pass1, newNodeP->password);
					}
					else
					{
						printf("������������:");
						getpasswd(newNodeP);
						strcat(pass2, newNodeP->password);
					}

				}
				if (strcmp(pass1, pass2) == 0)
				{
					color(14);
					printf("���봴���ɹ���\n");
					color(7);
					break;
				}
				else
				{
					color(12);
					printf("���봴��ʧ�ܣ����������룡\n");
					color(7);
				}
			}
			


			printf("���������֤����:");
			scanf("%s", newNodeP->idCard);

			printf("������绰����:");
			scanf("%s", newNodeP->phone);
			getchar();

			newNodeP->money = 0.0f;

			addNode(newNodeP);
			color(14);
			printf("�����ɹ���\n");
			color(7);
		}
		else
		{
			printf("Please enter your name:");
			scanf("%s", newNodeP->name);

			iCard(newNodeP);
			printf("Your bank card number is��%s\n", newNodeP->username);

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
					printf("Password created successfully��\n");
					color(7);
					break;
				}
				else
				{
					color(12);
					printf("Failed to create the password, Please enter a new password��\n");
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

			printf("for user admin��\n");
		}
	
	system("pause");
	system("cls");
}
Account * curAccount = NULL;//ָ��ǰ��¼�˻���ָ�� 
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

void updatePassword()//�����޸ĺ���
{
		if (Y)
		{
			printf("�����������:\n");
			char oldPassword[100] = { '\0' };
			scanf("%s", oldPassword);
			if (strcmp(oldPassword, curAccount->password) == 0)
			{
				//�����޸� 
				printf("�����������룺\n");
				scanf("%s", curAccount->password);
				color(14);
				printf("----------------\n");
				printf("|--�޸ĳɹ���--|\n");
				printf("----------------\n");
			}
			else
			{
				color(12);
				printf("--------------------------------\n");
				printf("|--������������󣬾ܾ��޸ģ�--|\n");
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
				//�����޸� 
				printf("please enter new password��\n");
				scanf("%s", curAccount->password);
				printf("modify successfully��\n");
			}
			else
			{
				printf("The old password is incorrect and cannot be changed��\n");
			}
		}
	
}

void homePage()
{
	system("cls");
	updatePassword();
}



void saveMoney()//����
{
		float money;
		if (Y)
		{
			printf("�������Ǯ��");
			scanf("%f", &money);
			getchar();
			curAccount->money += money;
			printf("----------------\n");
			printf("|--���ɹ���--|\n");
			printf("----------------\n");
		}
		else
		{
			printf("Please enter the deposit amount��");
			
			scanf("%f", &money);
			getchar();
			curAccount->money += money;
			printf("Deposit successfully��\n");
		}
	

		exitFunction();//�������ݣ�Account��

		TR *newNode = (TR *)malloc(sizeof(TR));

		char t[20] = { "���/����" };

		strcpy(newNode->username, curAccount->username);
		strcpy(newNode->type, t);        //��¼��������
		newNode->amount = money;         //��¼���׽��

		time_t the_time=0;
		strcpy(newNode->timestamp, show_realtime(the_time));
		//newNode->timestamp = time(NULL); //��¼��ǰʱ���
		newNode->money=curAccount->money;//���浱ǰ���

		addNodeTR(newNode);     //�������ӣ�TR��
		saveTransactionRecord();//�������ݣ�TR��
	
}

void drawMoney()//ȡ���
{
	if (Y)
	{
		printf("������ȡ����:");
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
			printf("|--���㣡--|\n");
			printf("----------------\n");

		}
		else
		{
			printf("-------------------------\n");
			printf("|--insufficient fund��--|");
			printf("-------------------------\n");
		}
		color(7);
		
	}
	else
	{
		curAccount->money = curAccount->money - money;
		if (Y)
		{
			printf("---ȡ��ɹ���---\n");
		}
		else
		{
			printf("---Withdrawals success��---\n");
		}

		exitFunction();   //�������ݣ�Account��

		TR *newNode = (TR *)malloc(sizeof(TR));
		char t[20] = { "ȡ��/֧��" };
		strcpy(newNode->username, curAccount->username);
		strcpy(newNode->type, t);          //��¼��������
		newNode->amount = money;           //��¼���׽��

		time_t the_time=0;
		strcpy(newNode->timestamp,show_realtime(the_time));
		//newNode->timestamp = time(NULL);   //��¼��ǰʱ���
		newNode->money=curAccount->money;  //���浱ǰ���

		addNodeTR(newNode);     //�������ӣ�TR��
		saveTransactionRecord();//�������ݣ�TR��
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
		printf("������Է��˻���");
	}
	else
	{
		printf("Please enter your account��");
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
			printf("|--�˻������ڣ�--|\n");
			printf("------------------\n");
		}
		else
		{
			printf("------------------------------\n");
			printf("|--Account does not exist��--|\n");
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
				printf("������ת�˽�");
			}
			else
			{
				printf("Please enter the transfer amount��");
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
					printf("|--��ǰ�˻�����!!!--|\n");
					printf("-------------------------\n");
				}
				else
				{
					printf("---------------------------------------------------\n");
					printf("///The current account balance is insufficient��///\n");
					printf("---------------------------------------------------\n");
				}
				color(7);
			}
			else
			{
		
				//��ǰ�˻����仯������ 
				curAccount->money = curAccount->money - money;
				//�Է��˻����仯������
				otherAccont->money = otherAccont->money + money;

				color(14);
				if (Y)
				{
					printf("ת�˳ɹ���\n");
				}
				else
				{
					printf("Transfer success��\n");
				}
				color(7);

				exitFunction();//�������ݣ�Account��

				TR *newNode = (TR *)malloc(sizeof(TR));

				char t[20] = { "ת��/ת��" };

				strcpy(newNode->username, curAccount->username);
				strcpy(newNode->type, t);        //��¼��������
				newNode->amount = money;         //��¼���׽��

				time_t the_time=0;
				strcpy(newNode->timestamp,show_realtime(the_time));
				//newNode->timestamp = time(NULL); //��¼��ǰʱ���
				newNode->money = curAccount->money;//���浱ǰ���

				addNodeTR(newNode);     //�������ӣ�TR��

				TR *newNode1 = (TR *)malloc(sizeof(TR));
				char other[20] = { "ת��/ת��" };

				strcpy(newNode1->username, otherAccont->username);
				strcpy(newNode1->type, other);        //��¼��������
				newNode1->amount = money;             //��¼���׽��

				strcpy(newNode1->timestamp, show_realtime(the_time));
				//newNode1->timestamp = time(NULL);     //��¼��ǰʱ���
				newNode1->money = otherAccont->money; //���浱ǰ���

				addNodeTR(newNode1);     //�������ӣ�TR��
				saveTransactionRecord();//�������ݣ�TR��
				break;
			}
		}

	}


}

void signIn() //��¼����
{
	for (int i = 0; i<3;i++)
	{
		color(7);
		Account a;
		if (Y)
		{
			printf("----------------------\n");
			printf("|------��ӭ��¼------|\n");
			printf("----------------------\n");
			
			printf("�������˺ţ�");
			scanf("%s", a.username);
			getchar();

			printf("���������룺");
		}
		else
		{
			printf("-----------------------\n");
			printf("|--Welcome to Log on--|\n");
			printf("-----------------------\n");
			printf("Please enter mail account username��");
			scanf("%s", a.username);
			getchar();

			printf("enter your PIN��");
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
					printf("////��¼�ɹ���////\n");
					color(3);
					printf("-------------------\n");
					printf("|--��1���޸�����--|\n");
					printf("-------------------\n");
					printf("|--��2����Ҫȡ��--|\n");
					printf("-------------------\n");
					printf("|--��3����Ҫ���--|\n");
					printf("-------------------\n");
					printf("|--��4����Ҫת��--|\n");
					printf("-------------------\n");
					printf("|--��5���˳���¼--|\n");
					printf("-------------------\n");
				}
				else
				{
					color(14);
					printf("-------login successfully��------\n"); 
					color(3);
					printf("---------------------------------\n");
					printf("|--��1��change password---------|\n");
					printf("---------------------------------\n");
					printf("|--��2��Need to withdraw money--|\n");
					printf("---------------------------------\n");
					printf("|--��3��liquid funds------------|\n");
					printf("---------------------------------\n");
					printf("|--��4��Need to transfer--------|\n");
					printf("---------------------------------\n");
					printf("|--��5��Logout------------------|\n");
					printf("---------------------------------\n");
				}
				
				int iIint;
				scanf("%d", &iIint);
				getchar();
				if (iIint == 1)
				{
					homePage();  //�޸�����
				}
				else if (iIint == 2)
				{
					drawMoney(); //ȡ��
				}
				else if (iIint == 3)
				{
					saveMoney(); //���
				}
				else if (iIint == 4)
				{
					transfer();//ת��
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
					printf("|--��¼ʧ��!--|\n");
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
	printf("|-------��ӭʹ��-------|\n");
	printf("------------------------\n");
	printf("|//��0��Ӣ��(English)//|\n");
	printf("------------------------\n");
	printf("|//��1������(Chinese)//|\n");
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
			printf("|--����ʧ�ܣ�--|\n");
			printf("----------------\n");
		}
		else
		{
			color(14);
			printf("----------------\n");
			printf("|--���سɹ���--|\n");
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
			printf("|--Load Fail��--|\n");
			printf("-----------------\n");
		}
		else
		{
			color(14);
			printf("-----------------------\n");
			printf("|--onload Function��--|\n");
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
			printf("|///��1������///|\n");
			printf("-----------------\n");
			printf("|///��2����¼///|\n");
			printf("-----------------\n");
			printf("|///��3���˳�///|\n");
			printf("-----------------\n");
		}
		else
		{
			printf("-------------------------\n");
			printf("|--��1��open an account-|\n");
			printf("-------------------------\n");
			printf("|--��2��Login-----------|\n");
			printf("-------------------------\n");
			printf("|--��3��exit------------|\n");
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
