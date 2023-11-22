//ATM SIMULATOR
//i)Login using Username and password,ii)Look at balance statement,iii)Withdraw money - balance should be checked and updated,
//iv)Allow the user to change the password,v)Deposit money,vi)Keep track of total amount in terms of denomination.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//void create();
int login();
void save_file(int);
void save_file_atm(int);
void change_pin(char []);
void balance_stmt(char[]);
void withdraw(char []);
void deposit(char []);
void balance(char [],int,int);
void denom_wd(int);
int denom_dp(int);

struct customer
{
	char name[20];
	int pin;
	int money;	
};

struct denom
{
	int de;
	int nu;
};


int main()
{	
	system("cls");
	login();
	return 0;
}

int login()	//User can use atm services if he enters correct username and pin.
			//This function verifies his details and allows him to select an option. 
{
	FILE *fp;
	struct customer e;
	int found=0;
	printf("\n\n****************** Welcome to our ATM services ************************\n\n");
	char user_name[20];
	printf("\tEnter username      : ");
	scanf("%s",user_name);
	int c;
	fp=fopen("details.txt","r+");
	do
	{
		c=1;
		fread(&e,sizeof(e),1,fp);
		if (feof(fp))
			break;
		if (strcmp(user_name,e.name)==0)		//Verifying username
		{
			found=1;
			int pin_no;
			printf("****Enter your secret pin number : ");
			scanf("%d",&pin_no);
	
			if (pin_no==e.pin)					//Verifying pinnumber
			{
	   		printf("\n\n\t****** Welcome back %s to our ATM ******\n\n",user_name);
	   		int choice;
			printf(" ~~~~~ Choose an option from Below ~~~~~\n");
			printf("\t\t1) Balance statement\n\t\t2) Pin Change\n\t\t3) Cash Withdrawl\n\t\t4) Deposit Money\n\t\t5) EXIT\n");
			scanf("%d",&choice);
			printf("Selected choice is : %d \n\n",choice);

			switch(choice)	//Switch statement allows the user to select an option and calls a function accordingly.
			{
				case 1:
					balance_stmt(user_name);
					printf("\n\n\tThank you for using our services.\n\n");
					break;
				case 2:
					change_pin(user_name);
					printf("\n\n\tThank you for using our services.\n\n");
					break;
				case 3:
					withdraw(user_name);
					printf("\n\n\tThank you for using our services.\n\n");
					break;
				case 4:
					deposit(user_name);
					printf("\n\n\tThank you for using our services.\n\n");
					break;
				case 5:
					printf("\n \t\tYou loggedout successfully\n");
					printf("\n\n\tThank you for using our services.\n\n");
					exit(0);
					break;
				default:
					printf("\t!!!  INVALID  CHOICE  !!!\n");
					printf("\n\n\tThank you for using our services.\n\n");
					exit(0);
			}
			printf("*********************************************************************");
			fclose(fp);

			printf("\n\nDo you wish to do another transaction? If yes enter 1,else any othernumber to exit\n");
			fflush(stdin);
			scanf("%d",&c);

			}

			else
			{
				c=0;
				printf("\n---------- Invalid pin number.Please enter a valid one!!! --------------\n");
				printf("\n\t\tThank you for using our services.\n\n");
			}	
		}
	
	}while(c==1);

	if (found==0)
	{
		printf("\n\n\t\t\tUSERNAME NOT FOUND !!!\n\n");	
	}	
	return 0;
}

//To print the balance statement of user's account
void balance_stmt(char user_name[])
{
	struct customer e; 
	FILE* fp=fopen("details.txt","r");

	while(1)
	{
		fread(&e,sizeof(e),1,fp);
		if(feof(fp))
		{
			break;
		}
		if(!(strcmp(user_name,e.name)))
		{
			printf("*======================================================\n");
			printf("*	DATE : %s\t\tTIME :%s	 \n",__DATE__,__TIME__);
			printf("*		~ ATM TRANSACTION ~			\n");	
			printf("*______________________________________________________\n\n");
			printf("	NAME 		      : %s\n",e.name);
			printf("	Available Balance : Rs.%d \n",e.money);
			printf("*======================================================\n");
		}
	}

}

//To change the pin number of the user
void change_pin(char user_name[20])	//This function is used to to change his pin.
{
	struct customer e;
	
	FILE *fp;
	FILE *fp1;
	fp=fopen("details.txt","r+");
	fp1=fopen("details2.txt","w");

	int pin_no,found=0;
	printf("Enter your current pin number:");
	scanf("%d",&pin_no);

	while(1)
	{
		fread(&e,sizeof(e),1,fp);
		
		
		if (feof(fp))
		{
			break;
		}

		if (e.pin==pin_no && strcmp(user_name,e.name)==0)
		{
			found=1;
			int newpin_no;
			printf("Enter your new pin number:");
			scanf("%d",&newpin_no);
			e.pin=newpin_no;
			int i;
			fwrite(&e,sizeof(e),1,fp1);
		}
		else
		{
			fwrite(&e,sizeof(e),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	save_file(found);

}

//Used to save the details.txt file aftermodifications during a transaction 
void save_file(int found)
{
	
	FILE *fp;
	FILE *fp1;

	if (found==0)
		printf("\n--------------- Invalid pin number.Please enter a valid one ----------------\n");
	else
	{
		struct customer e1;
		fp=fopen("details.txt","w");
		fp1=fopen("details2.txt","r+");
		while (1)
		{
			fread(&e1,sizeof(e1),1,fp1);
			
			if (feof(fp1))
				break;
			fwrite(&e1,sizeof(e1),1,fp);
		}
		printf("");
		fclose(fp);
		fclose(fp1);
	}
}

//Used to modify the atm.txt file denominations after a transaction
void save_file_atm(int found)
{
	
	FILE *fp;
	FILE *fp1;
	struct denom s;
	fp=fopen("atm.txt","w");
	fp1=fopen("atm2.txt","r+");
	while (1)
	{
		fread(&s,sizeof(s),1,fp1);
	
		if (feof(fp1))
			break;
		fwrite(&s,sizeof(s),1,fp);
	}
	printf("");
	fclose(fp);
	fclose(fp1);
}

//Used to withdraw money
void withdraw(char user_name[20])
{
	struct customer e;
	struct denom s;
	FILE *fp;
	FILE *fp1;
	fp=fopen("details.txt","r+");
	fp1=fopen("details2.txt","w");
	FILE* fp2=fopen("atm.txt","r");
	int note2000,note100,note200,note500;
	int pin_no,found=0;
	printf("****Enter your pin number:");
	scanf("%d",&pin_no);
	while(1)
	{
		fread(&s,sizeof(s),1,fp2);		
		if (feof(fp2))
		{
			break;
		}	
		if((s.de)==2000)
		{
			note2000=s.nu;
		}
		if((s.de)==500)
		{
			note500=s.nu;
		}
		if((s.de)==200)
		{
			note200=s.nu;
		}
		if((s.de)==100)
		{
			note100=s.nu;
		}			
	}
	int k=note2000*2000+note500*500+note200*200+note100*100;
	fclose(fp2);	
	while(1)
	{
		fread(&e,sizeof(e),1,fp);
		
		
		if (feof(fp))
		{
			break;
		}

		if (e.pin==pin_no && strcmp(user_name,e.name)==0)
		{
			found=1;
			int wd,m;
			printf("Enter the amount to withdraw:");
			scanf("%d",&wd);
			int k=note2000*2000+note500*500+note200*200+note100*100;
			if((wd>e.money))
			{
				printf("\tInsufficient balance !!!\n");
			}
			else if(wd%100)
			{
				printf("These money cant be withdrawn with atm denominations !\n");
			}
			else if(wd>k)
			{
				printf("Low money in atm cant initialize the transaction");
			}
			else
			{
				m=e.money;
				e.money=e.money-wd;
				
				denom_wd(wd);
				balance(user_name,m,e.money);
				
				printf("\nYou withdrawn the amount Rs.%d  SUCCESFULLY!!\n",wd);
			}
			fwrite(&e,sizeof(e),1,fp1);
		}
		else
		{
			fwrite(&e,sizeof(e),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	save_file(1);
}

//Used to find the denominations of withdrawn money
void denom_wd(int amount)
{
	struct denom s;
		
	FILE* fp2=fopen("atm.txt","r");
	FILE* fp3=fopen("atm2.txt","w");
	int m;
	int  note2000=0,note500=0,note200=0,note100=0;
	if(fp2==NULL || fp3==NULL)
	{
		printf("File not opened");
	}
	else
	{
		m=amount;
		while(1)
		{
			fread(&s,sizeof(s),1,fp2);
		
			if (feof(fp2))
			{
				break;
			}
			if((amount >= 2000) && (s.de==2000))
    		{
       			if((amount/2000)<=s.nu)
       			{
       				note2000 = amount/2000;
        			amount -= note2000 * 2000;
       			}
       			else
       			{
       				note2000 = s.nu;
       			}      
       			s.nu-=note2000; 				
    		}
    		if((amount >= 500) && (s.de==500))
    		{
        		if((amount/500)<=s.nu)
       			{
       				note500 = amount/500;
        			amount -= note500 * 500;
       			}
       			else
       			{
       				note500 = s.nu;
       			} 
       			s.nu-=note500;
    		}
    		if((amount >= 200) && (s.de==200))
    		{
        		if((amount/200)<=s.nu)
       			{
       				note200 = amount/200;
        			amount -= note200 *200;
       			}
       			else
       			{
       				note200 = s.nu;
       			}
       			s.nu-=note200;
    		}
    		if((amount >= 100) && (s.de==100))
    		{
        		if((amount/100)<=s.nu)
       			{
       				note100 = amount/100;
        			amount -= note100 *100;
       			}
       			else
       			{
       				note100 = s.nu;
       			}
       			s.nu-=note100;
    		}
			
			fwrite(&s,sizeof(s),1,fp3);			
		}
		fclose(fp2);
		fclose(fp3);
		save_file_atm(1);
	}
	
	printf(" Your withdrawn money in denominations : \n");
	printf("\tno of 2000Notes:%d\tno of 500Notes:%d\n\tno of 200Notes:%d\tno of 100Notes:%d\n",note2000,note500,note200,note100);
}

//Used to display the balance after a transaction
void balance(char user_name[20],int initialmoney,int avlbalance)
{
	printf("*=====================================================\n");
	printf("*	DATE : %s \t\t TIME : %s	 \n",__DATE__,__TIME__);
	printf("*			ATM TRANSACTION				\n");
	printf("*_____________________________________________________\n\n");	
	printf("	NAME 		: %s\n",user_name);
	printf("	Balance before TRANSACTION: %d \n",initialmoney);
	printf("	Available Balance	: Rs.%d \n",avlbalance);
	printf("*=====================================================\n");	
}

//Used to deposit money
void deposit(char user_name[20])
{
	struct customer e;
	
	FILE *fp;
	FILE *fp1;
	fp=fopen("details.txt","r+");
	fp1=fopen("details2.txt","w");

	int pin_no,found=0;
	printf("Enter your pin number:");
	scanf("%d",&pin_no);

	while(1)
	{
		fread(&e,sizeof(e),1,fp);
		
		if (feof(fp))
		{
			break;
		}

		if (e.pin==pin_no && strcmp(user_name,e.name)==0)
		{
			found=1;
			int dep,m;
			printf("Enter the amount to deposit:");
			scanf("%d",&dep);
			if((dep<=0) || (dep%100 != 0))
			{
				printf("!!\tThis amount is not taken by atm\t!!");
			}
			else
			{
				int k=denom_dp(dep);
				if(k)
				{
					m=e.money;
					e.money=e.money+dep;
					balance(user_name,m,e.money);
					printf("\nYou deposited the amount Rs.%d  SUCCESFULLY!!\n",dep);
				}
			}
			
			fwrite(&e,sizeof(e),1,fp1);
		}
		else
		{
			fwrite(&e,sizeof(e),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	save_file(found);
	
}

//used to check the deposited moey denominations
int denom_dp(int amount)
{
	
	struct denom s;		
	FILE* fp2=fopen("atm.txt","r");
	FILE* fp3=fopen("atm2.txt","w");
	int m;
	int  note2000=0,note500=0,note200=0,note100=0;
	if(fp2==NULL || fp3==NULL)
	{
		printf("File not opened");
		return 0;
	}
	else
	{
		m=amount;
		printf("Enter no of 2000notes:");
		scanf("%d",&note2000);
		printf("Enter no of 500notes:");
		scanf("%d",&note500);
		printf("Enter no of 200notes:");
		scanf("%d",&note200);
		printf("Enter no of 100notes:");
		scanf("%d",&note100);
		int k=note2000*2000+note500*500+note200*200+note100*100;
		if((amount%100 ==0) && k==amount)
		{
			while(1)
			{
				fread(&s,sizeof(s),1,fp2);		
				if (feof(fp2))
				{
					break;
				}	
				if((s.de)==2000)
				{
					s.nu+=note2000;
				}
				if((s.de)==500)
				{
					s.nu+=note500;
				}
				if((s.de)==200)
				{
					s.nu+=note200;
				}
				if((s.de)==100)
				{
					s.nu+=note100;
				}

				fwrite(&s,sizeof(s),1,fp3);			
			}

			fclose(fp2);
			fclose(fp3);
			save_file_atm(1);
			return 1;
		}
		else
		{
			printf("\n!!Your transaction can't be done at this moment.You may have given us wrong denominations!!\n");
			return 0;
		}
	
	}	
}


//Writing and displaying information - details.txt and atm.txt
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//void create();
int main()
{
	FILE *fp;
	fp=fopen("details.txt","w+");
	int i;
	for (i=0;i<3;i++)
	{
		struct customer t1;
		printf("Enter name ,pin ,money :");
		scanf("%s%d%d",t1.name,&t1.pin,&t1.money);
		fwrite(&t1,sizeof(t1),1,fp);
	}
	fclose(fp);
	// Display information in details file
	//FILE *fp;
	fp=fopen("details.txt","r+");
	printf("%-10s%-10s%-7s \n","NAME","PIN","MONEY");
	while(1)
	{
		struct customer t1;
		fread(&t1,sizeof(t1),1,fp);
		if (feof(fp))
			break;
		printf("%s\t%d\t%d\n",t1.name,t1.pin,t1.money);
	}
	fclose(fp);



	//To Display information in details.txt file
	fp=fopen("details.txt","r+");
	printf("%-10s%-10s%-7s \n","NAME","PIN","MONEY");
	while(1)
	{
		struct customer t1;
		//printf("Enter name,pin,money");
		//scanf("%s%d%d",t1.name,&t1.pin,&t1.money);
		fread(&t1,sizeof(t1),1,fp);
		if (feof(fp))
			break;
		printf("%s\t%d\t%d\n",t1.name,t1.pin,t1.money);
	}
	fclose(fp);
			//To Display information in atm.txt file
		FILE *fp4;
		fp4=fopen("atm.txt","r+");
		while(1)
		{
			fread(&s,sizeof(s),1,fp4);
			if (feof(fp4))
				break;
			printf("%d\t%d\n",s.de,s.nu);
		}
		fclose(fp4);

}*/
	/*
	//Writing to atm.txt
	FILE* fp=fopen("atm.txt","w");
	int i,n,d;
	if(fp==NULL)
	{
		printf("File not opened");
	}
	else
	{
		for(int i=0;i<4;i++)
		{
			printf("Enter d and n");
			scanf("%d%d",&d,&n);
			s.de=d;
			s.nu=n;
			fwrite(&s,sizeof(s),1,fp);
		}
		fclose(fp);
	}
		//To Display information in atm.txt file
		FILE *fp4;
		fp4=fopen("atm.txt","r+");
		while(1)
		{
			fread(&s,sizeof(s),1,fp4);
			if (feof(fp4))
				break;
			printf("%d\t%d\n",s.de,s.nu);
		}
		fclose(fp4);
	*/