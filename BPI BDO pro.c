#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define N 20
typedef struct input
{
    char Fname[31];
    char Minitials[31];
    char Lname[31];
    char accnumb[20];
    char pincard[7],pin2[7];
    float balance;
}input;

typedef struct accs
{
    input data[N];
    int accs;
    int i;
}
account;
account l;

int i;
int menu();
void anotransact();
void insertcard();
int pincode();
void withdraw();
void deposit();
void balanceinq();
void fundtransfer();
void changepin();
void upload();
void upload2();
void download();

void main()
{
    insertcard();
    download();
    download2();
    while(1)
    {
        switch(menu())
        {
            case 1 : system("cls");printf("Withdraw\n");withdraw();break;
            case 2 : system("cls");printf("Deposit\n");deposit();break;
            case 3 : system("cls");printf("Balance Inquiry\n");balanceinq();break;
            case 4 : system("cls");printf("Fund Transfer\n");fundtransfer();break;
            case 5 : system("cls");printf("Change Pin\n");changepin();break;
            case 6 : system("cls");upload();upload2();printf("Please Get your card!");exit(0);break;
            default: printf("Error!!!");getch();
        }
    }
}

int menu()
{
    int op;
    system("cls");
    printf("---------BPI BDO-------------\n");
    printf("=============================\n");
    printf("||1.) Withdraw              ||");
    printf("\n||2.) Deposit               ||");
    printf("\n||3.) Balance Inquiry       ||");
    printf("\n||4.) Fund Transfer         ||");
    printf("\n||5.) Change Pin            ||");
    printf("\n||6.) Exit                  ||");
    printf("\n=============================\n");
    printf("-----------------------------\n");
    printf("Choose from 1 to 6:\n");
    scanf("%d",&op);
    return op;
}

void withdraw()
{
     system("cls");
     if(pincode())
     {
         printf("\nWrong Pin!");
         getch();

     }
     else
     {
         int amountW,choice;
         float charge=0.20;
         printf("\nEnter amount to withdraw\n");
         scanf("%d",&amountW);
         if(amountW>l.data[l.i].balance)
         {
             printf("Insufficient Balance!\n");
         }
         else
         {
             if(amountW>=200)
             {
                 l.data[l.i].balance -= amountW;
                 l.data[l.i].balance -= charge;
                 printf("Here is your current balance: %.2f\n",l.data[l.i].balance);
             }
             else
             {
                 printf("Cannot Withdraw amount lower than 200!");
                 getch();
             }
         }
         anotransact();
     }
}

void deposit()
{
     system("cls");
     if(pincode())
     {
         printf("\nWrong Pin!");
         getch();
     }
     else
     {
         int amountD,choice;
         printf("\nPlease enter amount to deposit:\n");
         scanf("%d",&amountD);
         if(amountD<200)
         {
             printf("You can only deposit 200 pesos and above");
             menu();
             getch();
         }
         else
         l.data[l.i].balance += amountD;
         printf("Thank you for depositing!!Here is your current balance: %f",l.data[l.i].balance);
         anotransact();
     }
}

void balanceinq()
{
     system("cls");
     if(pincode())
     {
         printf("\nWrong Pin!");
         getch();
     }
     else
     {
         printf("\nName: %s,",l.data[l.i].Lname);
         printf(" %s",l.data[l.i].Fname);
         printf(" %s",l.data[l.i].Minitials);
         printf("\nYour Balance is %.2f",l.data[l.i].balance);
         anotransact();
     }
}

void changepin()
{
    system("cls");
    if(pincode())
    {
        printf("\nWrong PIN!");
        getch();
    }
    else
    {
         int j;
        printf("\nEnter PIN:\n");
        for(j = 0;j < 6;j++)
        {
            l.data[l.i].pincard[j] = getch();
            printf("*");
        }
        l.data[l.i].pincard[7]='\0';
        printf("\nConfirm your PIN:\n");
        for(j = 0;j < 6;j++)
        {
                l.data[l.i].pin2[j] = getch();
                printf("*");
        }
        l.data[l.i].pin2[7]='\0';
        if(strcmp(l.data[l.i].pincard,l.data[l.i].pin2))
        {
            printf("\nWrong PIN!");
            changepin();
            getch();
        }
        else
        {
            printf("You have successfully change your Pin!");
            getch();

        }

    }
}

void fundtransfer()
{
    system("cls");
    if(pincode())
    {
        printf("\nWrong Pin!");
        getch();
    }
    else
    {
        char receiver[20];
        int amountT;
        printf("\nEnter Bank Account Number of receiver: ");
        scanf(" %[^\n]",&receiver);
        for(i=0;i<l.accs+1;i++)
        {
           if(strcmp(receiver,l.data[i].accnumb)==0)
           {
               printf("Enter Amount to be send: ");
               scanf("%d",&amountT);
               if(amountT > l.data[l.i].balance)
               {
                   printf("Inssuficient balance");
                   getch();
                   break;
               }
               else
               {
                   l.data[l.i].balance -= amountT;
                   l.data[i].balance += amountT;
                   printf("Fund Transfered");
                   anotransact();
                   getch();
               }
           }
        }
    }
}

void anotransact()
{
    int choice;
    printf("\nDo you want to have another transaction?\n(Press 1 to proceed and 2 to end Transaction)\n");
    scanf("%d",&choice);
    if(choice==2)
    {
        upload();
        upload2();
        printf("Transaction Successful!!\nGet Cash,Eject card!");
        getch();
        exit(0);
    }
    else
    {
        menu();
    }
}

void download()
{
    FILE *fp;
    fp = fopen("d:\pinn.dbf", "r+");
    while(!feof(fp))
    {
        fscanf(fp,"%d", &l.i);
        fscanf(fp," %[^\n]\n", &l.data[l.i].Lname);
        fscanf(fp," %[^\n]\n", &l.data[l.i].Fname);
        fscanf(fp," %[^\n]\n", &l.data[l.i].Minitials);
        fscanf(fp," %[^\n]\n", &l.data[l.i].accnumb);
        fscanf(fp," %[^\n]\n", &l.data[l.i].pincard);
        fscanf(fp," %f\n", &l.data[l.i].balance);
    }
    fclose(fp);

}

void download2()
{
    FILE *fp;
    fp = fopen("data.dbf", "r");
    fscanf(fp,"%d\n", &l.accs);
    for(i = 0;i < l.accs+1;i++)
    {
        fscanf(fp," %[^\n]\n", &l.data[i].Lname);
        fscanf(fp," %[^\n]\n", &l.data[i].Fname);
        fscanf(fp," %[^\n]\n", &l.data[i].Minitials);
        fscanf(fp," %[^\n]\n", &l.data[i].accnumb);
        fscanf(fp," %[^\n]\n", &l.data[i].pincard);
        fscanf(fp," %f\n", &l.data[i].balance);
    }
    fclose(fp);

}

void upload()
{
  FILE *fp;
  fp=fopen("d:\pinn.dbf","w");
  int i;
  fprintf(fp,"%d\n", l.i);
  fprintf(fp,"%s\n",l.data[l.i].Lname);
  fprintf(fp,"%s\n",l.data[l.i].Fname);
  fprintf(fp,"%s\n",l.data[l.i].Minitials);
  fprintf(fp,"%s\n",l.data[l.i].accnumb);
  fprintf(fp,"%s\n",l.data[l.i].pincard);
  fprintf(fp,"%f\n",l.data[l.i].balance);
    fclose(fp);
}

void upload2()
{
    FILE *fp;
    int i;
    fp = fopen("data.dbf", "w");
    fprintf(fp,"%d\n", l.accs);
    for(i = 0;i < l.accs+1;i++)
    {
        fprintf(fp,"%s\n", l.data[i].Lname);
        fprintf(fp,"%s\n", l.data[i].Fname);
        fprintf(fp,"%s\n", l.data[i].Minitials);
        fprintf(fp,"%s\n", l.data[i].accnumb);
        fprintf(fp,"%s\n", l.data[i].pincard);
        fprintf(fp,"%.2f\n", l.data[i].balance);
    }
    fclose(fp);
}

int pincode()
{
   system("cls");
   char pin[7];
   int i;
   printf("Please enter 6-digit PIN: ");
   for(i=0;i<6;i++)
   {
      pin[i]=getch();
      printf("*");
   }
   pin[i]='\0';
   return (strcmp(pin,l.data[l.i].pincard));
}

void insertcard()
{
   FILE *fp;
   printf("Please insert card...\n");
   do
   {
      fp = fopen("d:\pinn.dbf","w");
   }
      while (fp==NULL);
      fclose(fp);
}
