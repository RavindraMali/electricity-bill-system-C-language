/*++++++++++++++++++++++++++++++
	Electricity  bill payment management system.
	\login
		
	
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

	void line();
	void format();
	void header();
	void lines(int no);
	int adminLogin();//void AdminLogin
	void manageAdmin();
	void unitManagement();
	void unitList();
	void addPayee();
	void delete_payee();	
	void paymentDetails();
	void display();
	//global variable declaration.
	int ch,invalid=0;
	char clr;
	char username[20];
	char password[8];	
	//files
	char admin[30]="",pass[8]="";	
	FILE *adminFptr,*payeeFptr;
			
	struct admin
	{
		char uname[30];
		char password[8];
	};

	struct payee
	{
		int pid;
		char pfname[20];
		char plname[20];
		int hno;
		char area[100];
		long int pin;	
		int status;
	};

int main()
{
	if(adminLogin()==1)	//calling function adminLogin() for administrator login.
	{
		return 0;		
	}
	else
	{
		
	do
	{
	
			header();		
			printf("\n\tCHIOCE\tACTION\n");
			printf("\n\t[1]\tBILL PAYMENT\n\t[2]\tADD NEW PAYEE\n\t[3]\tLIST OF PAYEE\n\t[4]\tDELETE\n\t[5]\tADMIN PANEL\n\t[6]\tPAYMENT DETAILS\n\t[7]\tEXIT (LOGOUT)");
		
			line();

			printf("\n\tENTER YOUR CHOICE : ");
			scanf("%d",&ch);
	
	switch(ch)
		{
			case 1 : unitList();	
				break;
			case 2 : 
				addPayee();
				//display();
				break;
			case 3 : printf("\n\tRECORD'S OF PAYEES");
				display();
				break;
			case 4 :
				delete_payee();
				break;
			case 5 :
				main();
				break;	
			case 6 :
				paymentDetails();
				break;
			case 7 :
				printf("\n\tYOUR LOGOUT FROM SYSTEM...!");	
				return 0;
			default:
				printf("\n\tINVALID CHOICE..!\n\tCHOICE IS BETWEEN (1 TO 7 )");

		}
	
		printf("\n\tPRESS ANY NUMBER TO CONTINUE..! ");
		setbuf(stdin,NULL);
		if(scanf("%c",&clr))
		{
			system("clear");
		}
	
	}while(ch!=7);	

	}
			
	return 0;
}
void line()
{
	printf("\n\t");
	for(int i=0;i<90;i++)
		printf("_");
}
void lines(int no)
{
	printf("\n\t");
	for(int i=0;i<no;i++)
		printf("-");
}
void underscroll(int no)
{
	printf("\n\t");
	for(int i=0;i<no;i++)
		printf("_");
}
//Admin Login Code
int adminLogin()
{
		adminFptr=fopen("login.txt","r");
		if(adminFptr==NULL)
		{
		printf("\n\tFILe DOES NOT EXIST..!");		
		return 1;
		}
		do
		{
			header();		
			//Take input from admin of username and password 
				
			printf("\n\t\tENTER USERNAME :: ");
			scanf("%s",username);
			setbuf(stdin,NULL);			
				
			printf("\n\t\tENTER PASSWORD :: ");
			scanf("%s",password);
			setbuf(stdin,NULL);
			
			while(fscanf(adminFptr,"%s %s",admin,pass)!=EOF);
			/*
				printf("\n\tUsername : %s password : %s",admin,pass);						
			
			line();*/	
			if(strcmp(username,admin)==0 && strcmp(password,pass)==0)
			{
					break;
			}
			else
			{
				printf("\n\t* PLEASE PROVIDE VALID USERNAME AND PASSWORD ");
				invalid++;
			}
			if(invalid==3)
			{
				line();
				printf("\n\t** Something wents wrong...!");
				return 1;
			}
		}while(invalid!=0);
		printf("\n\n\tLOGIN SUCCESSFULLY DONE...\n");
		line();
		do
		{
			
			printf("\n\tCHIOCE\tACTION\n");
			printf("\n\t[1]\tMANAGE ADMIN\n\t[2]\tHOME\n\t[3]\tMANAGE UNIT RATES\n\t[4]\tLOGOUT");
		
			line();

			printf("\n\tENTER YOUR CHOICE : ");
			scanf("%d",&ch);
	
			
		switch(ch)
		{
			case 1 : manageAdmin();	
				break;
			case 2 : 
				return 0;
				break;
			case 3 :
				unitManagement();
				break; 
			case 4 :
				printf("\n\tYOUR LOGOUT FROM SYSTEM...!");	
				break;
			default:
				header();
				printf("\n\tINVALID CHOICE..!\n\tCHOICE IS BETWEEN (1 TO 4 )");

		}
		line();
		printf("\n\n\tPRESS ANY NUMBER TO CONTINUE..! ");
		setbuf(stdin,NULL);
		if(scanf("%c",&clr))
		{
			header();
			
		}
	
	}while(ch!=4);	


		fclose(adminFptr);
}
void manageAdmin()
{
	printf("\n\tADD NEW ADMIN : -");
	struct admin add;
	printf("\n\tENTER ADMIN USERNAME : ");
	scanf("%s",add.uname);
	setbuf(stdin,NULL);
	printf("\n\tENTER PASSWORD : ");
	scanf("%s",add.password);
	
	adminFptr=fopen("login.txt","w");
	if(adminFptr==NULL)
	{
		printf("\n\tFILe DOES NOT EXIST..!");		
	}	
	else
	{
	fprintf(adminFptr,"%s %s",add.uname,add.password);
	

	printf("\n\tADMIN ADDED SUCCESSFULLY...");
	}			
	fclose(adminFptr);
}	
//unit list
void unitList()
{
	int b,flag=0;
	struct payee p1;
	float u,arr[4];
	FILE *un,*payeeFptr2=fopen("payee.txt","r");	
	un=fopen("units.txt","r");
	
	line();
	printf("\n\t+-------------+----------------------------------+");	
	printf("\n\t| UNITS/MONTH |        PRICE PER UNIT            |");
	fscanf(un,"%f",&u);
	arr[0]=u;	
	printf("\n\t+-------------+----------------------------------+");
	printf("\n\t| ( 0 TO 50 ) |\t\t\tRS %5.2f / UNIT  |",u); 
	fscanf(un,"%f",&u);
	arr[1]=u;
	printf("\n\t+-------------+----------------------------------+");
	printf("\n\t| ( 0 TO 100) |\t\t\tRS %5.2f / UNIT  |",u);	
	fscanf(un,"%f",&u);
	arr[2]=u;
	printf("\n\t+-------------+----------------------------------+");
	printf("\n\t| ( 0 TO 250) |\t\t\tRS %5.2f / UNIT  |",u);
	fscanf(un,"%f",&u);
	arr[3]=u;
	printf("\n\t+-------------+----------------------------------+");
	printf("\n\t| 250+ ABOVE  |  \t\tRS %5.2f / UNIT  |",u);
	printf("\n\t+-------------+----------------------------------+");

	printf("\n\tENTER BILL NO (Bxxxx) : b");
	scanf("%d",&b);

	while(fread(&p1.pid,sizeof(struct payee),1,payeeFptr2)!=0 && p1.pid!=b);
	{
		if(b==p1.pid)
		{
			flag=1;
		}		
	}
	if(flag==0)
	{
		printf("\n\tINVALID BILL NO ..!");
	}
	else
	{
		int already,flag1=0;
		FILE *pf=fopen("paid.txt","r");
		while(fscanf(pf,"%d",&already)!=EOF)
		{
			if(p1.pid==already)
				flag1=1;
		}
		fclose(pf);
		if(flag1==0)
		{
			int con;
			float rate,total;
			printf("\n\tGENERATE BILL");
			do
			{
			printf("\n\tENTER CONSUMED UNITS :: ");
			scanf("%d",&con);
				if(con > 0 && con <= 50 )
				{
					total=con * arr[0];
					rate=arr[0];
				}
				else if(con > 50 && con <= 100 )
				{
					total=con * arr[1];
					rate=arr[1];
				}
				else if(con > 100 && con <= 250 )
				{
					total=con * arr[2];
					rate=arr[2];
				}
				else if(con > 250 )
				{
					total=con * arr[3];
					rate=arr[3];
				}
				else
				{
					printf("\n\tPROVIDE VALID UNITS..!");
				}
			}while(con < 0);

			printf("\n\t TOTAL AMOUNT TO COLLECT : %f",total);
			time_t t;
			time(&t);
		
			printf("\n\tTRANSECTION DATE :: %s",ctime(&t));
			printf("\n\t+-----------------------------------------------------------------+");
			printf("\n\t|             SOUTH GUJARAT VIJ COMPANY LIMITED                   |");
			printf("\n\t+-----------------------------------------------------------------+");
			printf("\n\t+-----------------------------------------------------------------+");
			printf("\n\t|								  |");
			printf("\n\t| BILL NO 	B%5d		PAYMENT TPYE 	ENERGY ( CASH )	  |",p1.pid);	
			printf("\n\t|								  |");	
			printf("\n\t| CONSUMED UNITS 	%4d	  RATE/UNIT	%f          |",con,rate);
			printf("\n\t|								  |");
			printf("\n\t|	               TRANCTION STATUS  SUCCESSFUL               |");	
			printf("\n\t+-------------+--------------------------------+------------------+");
			printf("\n\t| CONSUMER NO | NAME OF CONSUMER               | TRANCTION AMOUNT |");
			printf("\n\t+-------------+--------------------------------+------------------+");
			printf("\n\t|     %5d   |%14s%15s   |%17.6f |",p1.pid,p1.pfname,p1.plname,total);	
			printf("\n\t+-------------+--------------------------------+------------------+");
			printf("\n\t| 			    TOTAL AMOUNT(Rs)   |%17.6f |",total);
			printf("\n\t+----------------------------------------------+------------------+");

			FILE *bill=fopen("BILLS.txt","a");
		
			fprintf(bill,"\n\tTRANSECTION DATE :: %s",ctime(&t));
			fprintf(bill,"\n\t+-----------------------------------------------------------------+");
			fprintf(bill,"\n\t|             SOUTH GUJARAT VIJ COMPANY LIMITED                   |");
			fprintf(bill,"\n\t+-----------------------------------------------------------------+");
			fprintf(bill,"\n\t+-----------------------------------------------------------------+");
			fprintf(bill,"\n\t|								  |");
			fprintf(bill,"\n\t| BILL NO 	B%5d		PAYMENT TPYE 	ENERGY ( CASH )	  |",p1.pid);	
			fprintf(bill,"\n\t|								  |");	
			fprintf(bill,"\n\t| CONSUMED UNITS 	%4d	  RATE/UNIT	%f          |",con,rate);
			fprintf(bill,"\n\t|								  |");
			fprintf(bill,"\n\t|	               TRANCTION STATUS  SUCCESSFUL               |");	
			fprintf(bill,"\n\t+-------------+--------------------------------+------------------+");
			fprintf(bill,"\n\t| CONSUMER NO | NAME OF CONSUMER               | TRANCTION AMOUNT |");
			fprintf(bill,"\n\t+-------------+--------------------------------+------------------+");
			fprintf(bill,"\n\t|     %5d   |%14s%15s   |%17.6f |",p1.pid,p1.pfname,p1.plname,total);	
			fprintf(bill,"\n\t+-------------+--------------------------------+------------------+");
			fprintf(bill,"\n\t| 			    TOTAL AMOUNT(Rs)   |%17.6f |",total);
			fprintf(bill,"\n\t+----------------------------------------------+------------------+");		
			
		
			fprintf(bill,"\n______________________________________________________________________________________________________\n");
			fclose(bill);
			
			FILE *paid=fopen("paid.txt","a");
			fprintf(paid,"%d ",p1.pid);	
			fclose(paid);
		}
		else
		{
			printf("\n\tBILL ALREADY GENERATED  !");
		}
	}
}
void header()
{
		system("clear");
		printf("\n\t+------------------------------------------------------------------------------------------+");
		printf("\n\t|***************************** ELECTRICITY BILL PAYMENT SYSTEM ****************************|");
		printf("\n\t|******************************************************************************************|");
		printf("\n\t+------------------------------------------------------------------------------------------+");
}
void addPayee()
{
	struct payee p,ptr;
	int tmp;
	FILE *pc,*payeeFptr1=fopen("payee.txt","r");	
		
//	while(fread(&p1,sizeof(struct payee),1,payeeFptr1)!=0);
		
		while(fread(&ptr,sizeof(struct payee),1,payeeFptr1)!=0);
		
	tmp=0;
	tmp=ptr.pid;	
	p.pid=(++tmp);
		
	fclose(payeeFptr1); 
	
	pc=fopen("PAYEE.txt","a");
	payeeFptr=fopen("payee.txt","a");
	if(payeeFptr==NULL)
	{
		printf("\n\tFILE OF PAYEE LIST DOES NOT EXIST...!");
		exit(0);
	}
	

	printf("\n\tFILL DETAILS OF PAYEE : -");
	//printf("\n\tPAYEE ID : ");
	//scanf("%d",&p.pid);
	fname:	
	printf("\n\tFIRST NAME : ");
	setbuf(stdin,NULL);
	scanf("%s",p.pfname);
	for(int i=0;p.pfname[i]!='\0';i++)
	{	
		if(!isalpha(p.pfname[i]))
		{
			printf("\n\tFIRST NAME MUST BE A CHARACTER SET..!");
			goto fname;
		}		
	
	}
	
	lname:
	printf("\n\tLAST NAME : ");
	scanf("%s",p.plname);
	setbuf(stdin,NULL);	
	for(int i=0;p.plname[i]!='\0';i++)
	{	
		if(!isalpha(p.plname[i]))
		{
			printf("\n\tLAST NAME MUST BE A CHARACTER SET..!");
			goto lname;
		}		
	
	}

	printf("\n\tHOUSE/FLAT/PLOT NO : ");	
	scanf("%d",&p.hno);	
	printf("\n\tAREA : ");
	setbuf(stdin,NULL);	
	gets(p.area);
	
	
	printf("\tPIN-CODE : ");
	scanf("%ld",&p.pin);	

	p.status=0;
	fprintf(pc,"| B%4d | %20s | %20s | %5d | %50s | %6ld |\n",p.pid,p.pfname,p.plname,p.hno,p.area,p.pin);
	fprintf(pc,"+-------+----------------------+----------------------+-------+----------------------------------------------------+--------+\n");	
	fwrite(&p,sizeof(struct payee),1,payeeFptr);
	fclose(payeeFptr);
	fclose(pc);
			printf("\n\tRECORD INSERTED SUCCESSFULLY");		
	
}
void format()
{
printf("\n\t+------+-----------------+-----------------+------------+----------------------------------------------------+---------+");
}
void display()
{
	struct payee ptr;
	
	underscroll(120);
	format();
	printf("\n\t|BILLNO| FIRST NAME      | LAST NAME       |  H.NO/F.NO | AREA						     | PIN-CODE|");
	format();
	FILE *payeeFptr1=fopen("payee.txt","r");
	if(payeeFptr1==NULL)
	{
		printf("\n\tNO RECORD'S TO DISPLAY..!");
	}		
	else
	{
		while(fread(&ptr,sizeof(struct payee),1,payeeFptr1)!=0)
		{
			printf("\n\t|B%4d | %15s | %15s | %10d | %50s | %7ld |",ptr.pid,ptr.pfname,ptr.plname,ptr.hno,ptr.area,ptr.pin);	
			format();	
		}	
		underscroll(120);
	}
	fclose(payeeFptr1);	
}

void delete_payee()
{

	int Temp = 0, flag = 0, flv = 0;
	struct payee p;
	FILE *cfile,*cfile_TMP,*o_T;
	cfile_TMP = fopen("TMP.txt", "a");
	cfile = fopen("payee.txt", "r");
	o_T=fopen("PAYEE1.txt","w");
	if (cfile == NULL)
	{
		printf("\n\tNO RECORD AVAILABLE TO DELETE...!");
	}
	else
	{
	fprintf(o_T,"+-------+----------------------+----------------------+-------+----------------------------------------------------+--------+\n|BILL NO| FIRST NAME	       |LAST NAME             |F/NO   |  					Area       |pincode |\n+-------+----------------------+----------------------+-------+----------------------------------------------------+--------+\n");

		printf("\n\tENTER BILL NO WHICH YOU WANT TO DELETE (Bxxxx) : B");
		 scanf("%d", &Temp);
			
		while (fread(&p, sizeof(struct payee), 1, cfile))
		{
			if (p.pid != Temp)
			{
				fwrite(&p, sizeof(struct payee), 1, cfile_TMP);
	
			fprintf(o_T,"| B%4d | %20s | %20s | %5d | %50s | %6ld |\n",p.pid,p.pfname,p.plname,p.hno,p.area,p.pin);
fprintf(o_T,"+-------+----------------------+----------------------+-------+----------------------------------------------------+--------+\n");	
			}
			else
			{
				flag = 1;
			}
		}
	}

	
	fclose(cfile);
	fclose(cfile_TMP);
	fclose(o_T);
	remove("PAYEE.txt");
	remove("payee.txt");
	rename("TMP.txt", "payee.txt");
	rename("PAYEE1.txt","PAYEE.txt");
	if (flag)
	{
		printf("\n\tRecord Deleted Successfully.");
	}
	else
	{
		printf("\n\tNo Record For Delete.");
	}


}
void unitManagement()
{
	float u;
	FILE *unit=fopen("units.txt","w");
	printf("\n\tMANAGE RATE OF UNIT ");
	printf("\n\tUNITS\t\tRATE PER UNIT");

	printf("\n\t( 0 TO 50 )\t\t:: ");
	scanf("%f",&u);
	fprintf(unit,"%5.2f\n",u);
	printf("\n\t( 0 TO 100)\t\t:: ");
	scanf("%f",&u);
	fprintf(unit,"%5.2f\n",u);
	printf("\n\t( 0 TO 250)\t\t:: ");
	scanf("%f",&u);
	fprintf(unit,"%5.2f\n",u);
	printf("\n\t( 300+    )\t\t:: ");
	scanf("%f",&u);
	fprintf(unit,"%5.2f\n",u);
	fclose(unit);
}
void paymentDetails()
{

	struct payee ptr;
	int b,flag=0;
	FILE *p,*payeeFptr1=fopen("payee.txt","r");
	p=fopen("paid.txt","r");
	
	printf("\n\t+------+--------------------------------+--------+");
	printf("\n\t|BILLNO| NAME OF CONSUMER               | STATUS |");
	printf("\n\t+------+--------------------------------+--------+");	
	if(payeeFptr1==NULL)
	{
		printf("\n\tNO RECORD'S TO DISPLAY..!");
	}		
	else
	{
		while(fread(&ptr,sizeof(struct payee),1,payeeFptr1)!=0)
		{
			printf("\n\t|B%4d | %15s%15s | ",ptr.pid,ptr.pfname,ptr.plname);
			int already,flag=0;
			FILE *pf=fopen("paid.txt","r");
			while(fscanf(pf,"%d",&already)!=EOF)
			{	
				if(ptr.pid==already)
					flag=1;
			}
			fclose(pf);			
			if(flag==1)
			{
				printf("  PAID |");
			}
			else
			{
				printf("PENDING|");
			}
			printf("\n\t+------+--------------------------------+--------+");	
		}	
		underscroll(120);
	}
	fclose(payeeFptr1);	
}
