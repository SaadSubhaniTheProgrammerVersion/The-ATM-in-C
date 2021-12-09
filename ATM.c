#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
void login();
void create_account();    //making fucntions for easier readablility
void withdrawl();
void deposit();
void afterlogin();
void summary();
void delay();
char username[20], password[20], name[20];
char finalsummary[500] = { 0 };
char summ[20] = "summary_";//to be catenated later with username
time_t date;
int initial;    //some global variables which have to be used in almost all functions
FILE* userptr = NULL;
FILE* sumptr = NULL;

int main()
{

	int choice1 = 0;//first choice of the user

	printf("****************************************Welcome to NUST cash withdrawl/deposit ATM**************************************\n");
	
	do {
		printf("1.Login\n2.Create Account\n3.Cash Withdrawl (Take out Cash from Account)\n4.Cash Deposit (Fill Cash into Account)\n5.Account Summary\n6.Exit\n");

			printf("\nChoose what do you want to do: ");
			scanf("%d", &choice1);//in first choice user cannot deposit or withdraw cash as he has to login to some account firs
	
		if(choice1== 1)
			login();
		else if(choice1== 2)
			create_account();
		else if (choice1 == 3)
		{
			printf("\nPlease login or create your account first.\n");
			delay(1);
			system("cls");
		}
		else if (choice1 == 4)
		{
			printf("\nPlease login or create your account first.\n");
			delay(1);
			system("cls");
		}
		else if (choice1 == 5)
		{

			printf("\nPlease login or create your account first.\n");
			delay(1);
			system("cls");
		}
		else if (choice1 == 6)
		{
			printf("\nThank you for using NUST withdrawl/deposit ATM. Do give us another visit next time.\n");
		}
		else
		{
			printf("\nWrong input. Please try again.\n");
			system("cls");
		}
		
	} while (choice1 == 3|| choice1 == 4|| choice1 == 5);
	return 0;
}
void afterlogin()//after loggin in wihdrawl and deposit are availble to the user to be used
{
	int choice2 = 0;
	printf("1.Login\n2.Create Account\n3.Cash Withdrawl (Take out Cash from account)\n4.Cash Deposit (Fill Cash in Account)\n5.Account Summary\n6.Exit\n");
again:
	printf("\nChoose what do you want to do: ");
	scanf("%d", &choice2); //after login user has all the choices available
	switch (choice2)
	{
	case 1:
		login();
		break;
	case 2:
		create_account();
		break;
	case 3:
		withdrawl();
		break;
	case 4:
		deposit();
		break;
	case 5:
		summary();
		break;
	case 6:
		printf("\n****************Thank you for using NUST withdrawl/deposit ATM. Do give us another visit next time.*******************\n");
		break;
	default:
		printf("\nWrong input. Please try again.\n");
		goto again;
		break;
	}
}
void create_account()//function to create account
{
	char firstname[20], lastname[20];

	//demanding info for account creation

	printf("\nEnter first name: ");
	scanf("%s", &firstname);
	printf("Enter last name: ");
	scanf("%s", &lastname);
	printf("Enter username(without spaces): ");
	scanf("%s", &username);
	printf("Enter your password: ");
	scanf("%s", &password);
	printf("Please enter the amount of your intial deposit: ");
	scanf("%d", &initial);

	while (initial % 10 != 0)//only multiple of 10 can be deposited
	{
		printf("\nInitial deposit should be a multiple of 10. Try Again.\n");
		printf("Please enter the amount of your intial deposit: ");
		scanf("%d", &initial);
	}

	strcpy(name, username);
	strcat(summ, name);//did this so that I can give name to my summary file that is summary_(user)

	userptr = fopen(username, "w");//this file stores passwords and deposit
	sumptr = fopen(summ, "w");//this file stores all summary with dates and transactions

	time(&date);//storing the time for summary
	fprintf(userptr, "%s\n", password);
	fprintf(userptr, "%d", initial);
	fprintf(sumptr, "Account Created on %sIntial Deposit was %d\n", ctime(&date), initial);

	fclose(userptr);
	fclose(sumptr);

	system("cls");
	printf("*****Account Successfully created. Now Login to your account for cash deposit/withdrawl*****.\n\n\n");
	main();//returning to main for logging in
}
void login()
{
	char passwordcheck[20], string[100];
	printf("\nEnter your username: ");
	scanf("%s", &username);

	if ((userptr = fopen(username, "r")) == NULL)/*if username doesnt exist then NULL file will be created otherwise already present file will be read.*/
	{
		printf("This account does not exist. Press any key to continue to new account creation");
		getchar();
		create_account();
	}
	else
	{
		printf("Enter your password: ");
		scanf("%s", &password);

		time(&date);
		sumptr = fopen(summ, "a+");
		fprintf(sumptr, "\nAccount logged in on %s.\n)", ctime(&date));
	}

	fscanf(userptr, "%s", passwordcheck);//gets password from file
	fscanf(userptr, "%s", string);//gets the initial deposit from file

	initial = atoi(string);// storing the string of initial deposit in the file to inital integer to be used in program 

	if (strcmp(passwordcheck, password) != 0)/*checks password stored in file with the currently entered password. If they match function returns 0 and not 0 if the passwords do not match*/
	{
		printf("\nPassword Wrong. Please try again.\n");
		login();
	}
	else//correct password
	{
		system("cls");
		printf("**********************Congratulations! You have been successfully been logged into your account************************\n");

	}
	printf("*******************************We welcome you back to the NUST withdrawl/deposit ATM.*********************************\n"
		"\nYour current balance is = Rs.%d\n\n", initial);
	afterlogin();
	fclose(userptr);
	fclose(sumptr);

}


void withdrawl()//function for withdrawing amount
{
	int withamount = 0;
	printf("\n\nEnter the amount you want to withdraw from your account.\n");
	scanf("%d", &withamount);
	while (withamount > initial)
	{
		printf("\nINSUFFICIENT BALANCE.\nAmount being withdrawn cannot be greater than the current balance in the account.\nTry Again.\n");
		printf("\nEnter the amount you want to withdraw from your account.\n");
		scanf("%d", &withamount);
	}
	initial -= withamount;
	printf("\n\nNow your current balance is = Rs.%d\n\n", initial);
	sumptr = fopen(summ, "a+");//updating summary
	time(&date);

	fprintf(sumptr, "\nAmount %d was withdrawn from account on %sRemaining balance was %d.\n", withamount, ctime(&date), initial);

	userptr = fopen(username, "w");//updating the whole file again to store deposit changes

	fprintf(userptr, "%s\n", password);
	fprintf(userptr, "%d", initial);

	fclose(userptr);
	fclose(sumptr);
	afterlogin();//returning to the menu
}
void deposit()  //cash filler function
{
	int depositamount = 0;
	printf("\nEnter the amount you want to deposit in the ATM: ");
	scanf("%d", &depositamount);
	while (depositamount % 10 != 0)//amount bring deposited should be the multiple of 10
	{
		printf("\nAmount being deposited should be a multiple of 10. Please try again.\n");
		printf("\nEnter the amount you want to deposit in the ATM: ");
		scanf("%d", &depositamount);
	}
	initial += depositamount;

	sumptr = fopen(summ, "a+");//updating summary
	printf("\n\nNow your current balance is = Rs.%d\n\n", initial);
	time(&date);
	fprintf(sumptr, "\nAmount %d was deposited into your account on %sUpdated balance was %d.\n", depositamount, ctime(&date), initial);

	userptr = fopen(username, "w");//updating the whole file again to store deposit changes

	fprintf(userptr, "%s\n", password);
	fprintf(userptr, "%d", initial);

	fclose(userptr);
	fclose(sumptr);
	afterlogin();
}
void summary()
{
	system("cls");
	char passwordcheck[20], string[100];

	//Taking username and pasword again

	printf("\nEnter your username: ");
	scanf("%s", &username);

	if ((userptr = fopen(username, "r")) == NULL)/*if username doesnt exist then NULL file will be created otherwise already present file will be read.*/
	{
		printf("This account does not exist. Press any key to continue to new account creation");
		getchar();
		create_account();
	}
	else//if username exists
	{
		printf("Enter your password: ");
		scanf("%s", &password);
	}
	fscanf(userptr, "%s", passwordcheck);//gets password from file

	if (strcmp(passwordcheck, password) != 0)/*compares file stored password to recently entered password. If they match strcmp returns 0 otherwise not*/
	{
		printf("\nPassword Wrong. Please try again.");
		fclose(userptr);
		login();
	}

	else//correct password
	{

		printf("\nHello %s. Your user summary is as follows: \n\n", username);
		fflush(sumptr);
		sumptr = fopen(summ, "r");

		char a = fgetc(sumptr);// in order to get the summary from the file until it ends
		while (a != EOF)
		{
			fgets(finalsummary, 500, sumptr);
			printf("%c%s", a, finalsummary);
			a = fgetc(sumptr);
		}

		printf("\n");
		fclose(userptr);
		fclose(sumptr);

		afterlogin();
	}



}
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds)
		;
}
