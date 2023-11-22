
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//void create();
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
        struct denom s;
		fp4=fopen("atm.txt","r+");
		while(1)
		{
			fread(&s,sizeof(s),1,fp4);
			if (feof(fp4))
				break;
			printf("%d\t%d\n",s.de,s.nu);
		}
		fclose(fp4);

}