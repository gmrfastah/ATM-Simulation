#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#define N 30

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
void insertname();
int isfull();
void upload();
void accnum();
void insertcard();
void Balance();
int menu();
void pass();
void upload2();
void download2();
int checkfile();


int main()
{
    insertcard();
    if(checkfile())
    {
       download2();
       l.accs++;
    }
    else
    {
        l.accs=0;
    }
    accnum();
    insertname();
    Balance();
    pass();
    upload();
    upload2();
    system("cls");
    printf("Account Successfully Created!");

}

int checkfile()
{
    FILE *fp;
    if (fp = fopen("data.dbf", "r"))
    {
        fclose(fp);
        return 1;
    }
    else
    {
        return 0;
    }
}

void insertname()
{
    system("cls");
    printf("Enter your Last Name: ");
    scanf(" %[^\n]",&l.data[l.accs].Lname);
    printf("\nEnter your First Name: ");
    scanf(" %[^\n]",&l.data[l.accs].Fname);
    printf("\nEnter your Middle Initial: ");
    scanf(" %[^\n]",&l.data[l.accs].Minitials);
    printf("Name created successfully");
    getch();
}

void accnum()
{
    system("cls");
    srand(time(NULL));
    int i,n=0;
    for(i=0;i<sizeof(l.data[l.accs].accnumb);i++)
    {
        if(n<4)
        {
           l.data[l.accs].accnumb[i]=48+rand()%8;
           n++;
        }
        else
        {
            l.data[l.accs].accnumb[i]=' ';
            n=0;
        }
    }
    l.data[l.accs].accnumb[19] = '\0';
    printf("Your account number is:\n");
    printf("%s",l.data[l.accs].accnumb);
    getch();
}

void Balance()
{
    float bal;
    system("cls");
    printf("How much money will you deposit?: \n");
    scanf("%f",&bal);
    if(bal<1000)
    {
        printf("You cant deposit below 1000");
        Balance();
        getch();
    }
    else
    l.data[l.accs].balance=bal;
    printf("Your Balance is: %.2f",l.data[l.accs].balance);
    getch();
}

void insertcard()
{
   FILE *fp;
   printf("Please insert card...\n");
   do
   {
      fp = fopen("d:\pinn.txt","w");
   }
      while (fp==NULL);
      fclose(fp);
}

void pass()
{
    system("cls");
    printf("\nEnter PIN:\n");
    for(i = 0; i < 6; i++)
        {
            l.data[l.accs].pincard[i] = getch();
            printf("*");
        }
    l.data[l.accs].pincard[7]='\0';
    printf("\nConfirm your PIN:\n");
    for(i = 0; i < 6; i++)
        {
            l.data[l.accs].pin2[i] = getch();
            printf("*");
        }
    l.data[l.accs].pin2[7]='\0';
    if(strcmp(l.data[l.accs].pincard,l.data[l.accs].pin2))
    {
        printf("Wrong PIN!");
        pass();
        getch();
    }
    else
    {
        printf("\nYou have successfully created your pin!");
        getch();
    }

}

void upload()
{
  FILE *fp;
  int i;
  fp=fopen("d:\pinn.dbf","w");
  fprintf(fp,"%d\n", l.accs);
  fprintf(fp,"%s\n",l.data[l.accs].Lname);
  fprintf(fp,"%s\n",l.data[l.accs].Fname);
  fprintf(fp,"%s\n",l.data[l.accs].Minitials);
  fprintf(fp,"%s\n",l.data[l.accs].accnumb);
  fprintf(fp,"%s\n",l.data[l.accs].pincard);
  fprintf(fp,"%f\n",l.data[l.accs].balance);
  fclose(fp);
}

void upload2()
{
  FILE *fp;
  int i;
  fp=fopen("data.dbf","w");
  fprintf(fp,"%d\n", l.accs);
   for(i = 0;i < l.accs+1;i++)
    {
        fprintf(fp,"%s\n", l.data[i].Lname);
        fprintf(fp,"%s\n", l.data[i].Fname);
        fprintf(fp,"%s\n", l.data[i].Minitials);
        fprintf(fp,"%s\n", l.data[i].accnumb);
        fprintf(fp,"%s\n", l.data[i].pincard);
        fprintf(fp,"%f\n", l.data[i].balance);
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
