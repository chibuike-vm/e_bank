#ifndef _E_BANKING_H_
#define _E_BANKING_H_

/**
 * loadingDisplay - Mimics CSS Loading Display.
 *
 * Description: This function basically mimics the CSS loading display feature
 * and helps to boost user interactive experience.
 */
void loadingDisplay(void)
{
	int counter = 1;

	printf("\n Loading");
	fflush(stdout);

	while (counter <= 3)
	{
		sleep(1);
		putchar('.');
		fflush(stdout);
		counter++;
	}

	putchar('\n');
}

/**
 * cDV1 - Client Data Validator1 Function.
 *
 * @retD: This is a null terminated char array function parameter which
 * provides the input for for the cDV1 function.
 *
 * Description: This function is basically a validator function that validates
 * the input null terminated char array provided by an interacting user. It
 * also prompts the user for null terminated char array inputs as the case
 * may be and then goes ahead to store those user inputs data into a data
 * structure provided by the struct CLIENTSDATA data-type.
 *
 * Return: This function return struct CLIENTSDATA data-type upon successful
 * execution.
 */
struct CLIENTSDATA cDV1(char retD[5])
{
	struct CLIENTSDATA clientsData;
	int dataLength, s_ret;

	if (strcmp(retD, "no") == 0)
	{
		printf("\n Kindly, enter the following details to create your account\n");

/* The goto start1 statement executes from here */
start1:
		printf(" Username: ");
		fgets(clientsData.userName, 50, stdin);
		(s_ret = sscanf(clientsData.userName, "%s", clientsData.userName)) ?
					s_ret : printf("sscanf Function Failed!");

		dataLength = strlen(clientsData.userName);

		if (dataLength != 8)
		{
			putchar('\n');
			printf(" Data entry failed! Your username must be 8 characters long.\n\n");
			goto start1;
		}

/* The goto start2 statement executes from here */
start2:
		printf(" Password: ");
		fgets(clientsData.passWord, 50, stdin);
		(s_ret = sscanf(clientsData.passWord, "%s", clientsData.passWord)) ?
					s_ret : printf("sscanf Function Failed!");

		dataLength = strlen(clientsData.passWord);

		if (dataLength != 8)
		{
			putchar('\n');
			printf(" Data entry failed! Your password must be 8 characters long.\n\n");
			goto start2;
		}

		printf(" Age: ");
		fgets(clientsData.age, 5, stdin);
		(s_ret = sscanf(clientsData.age, "%s",  clientsData.age)) ?
				s_ret : printf("sscanf Function Failed!");

		printf(" Email: ");
		fgets(clientsData.email, 45, stdin);
		(s_ret = sscanf(clientsData.email, "%s", clientsData.email)) ?
				s_ret : printf("sscanf Function Failed!");
	}

	return (clientsData);
}

/**
 * pToDb - Print To Database Function.
 *
 * @retD: This is a null terminated char array function parameter which
 * provides the input for for the pToDb function.
 *
 * @cDV1Fptr: This is a function pointer passed as an argument/function
 * parameter which will is subsequently called back inside the parent function
 * scope.
 *
 * Description: This function basically prints all the data values provided by
 * the interacting user to a clients_data.txt file in the database directory.
 */
void pToDb(char retD[5], struct CLIENTSDATA (*cDV1Fptr)(char retD[5]))
{
	struct CLIENTSDATA clientsData;
	FILE *file = fopen("database/clients_data.txt", "a+");

	if (strcmp(retD, "no") == 0)
	{
		clientsData = (*cDV1Fptr)(retD);

		fprintf(file, "%s\t\t%s\t%s\t%s\n",
				clientsData.userName,
				clientsData.passWord,
				clientsData.age,
				clientsData.email
		       );
	}

	fclose(file);

	loadingDisplay();
	printf("\n Dear %s, your details have been submitted and your",
			clientsData.userName);
	printf("\n E-Bank account has been successfully created!\n");
}

/**
 * cDV2 - Client Data Validator2 Function.
 * @retD: This is a null terminated char array function parameter which
 * provides the input for for the cDV2 function.
 *
 * Description: This function is basically a validator function that validates
 * the username and password null terminated char array inputs provided by an
 * interacting user.
 *
 * Return: This function returns a vClientsData struct data-type upon
 * successful execution.
 */
struct VCLIENTSDATA cDV2(char retD[5])
{
	struct VCLIENTSDATA vClientsData;
	struct CLIENTSDATA clientsData;

	FILE *file = fopen("database/clients_data.txt", "r+");
	int authLogin = 0, s_ret, counter = 1;

	if (strcmp(retD, "yes") == 0)
	{
		char buffer[150];

		while (counter <= 4)
		{
			counter++;

			printf("\n Sign In to Your Account");
			printf("\n Username: ");
			fgets(vClientsData.vUserName, 50, stdin);
			(s_ret = sscanf(vClientsData.vUserName, "%s", vClientsData.vUserName)) ?
						s_ret : printf("sscanf Function Failed!");

			printf(" Password: ");
			fgets(vClientsData.vPassWord, 50, stdin);
			(s_ret = sscanf(vClientsData.vPassWord, "%s", vClientsData.vPassWord)) ?
						s_ret : printf("sscanf Function Failed!");

			while (fgets(buffer, 150, file) != NULL)
			{
				(s_ret = sscanf(buffer, "%s\t\t%s\t%s\t%s\n",
						clientsData.userName,
						clientsData.passWord,
						clientsData.age,
						clientsData.email
				)) ?
					s_ret : printf("sscanf Function Failed!");

				if ((strcmp(vClientsData.vUserName, clientsData.userName) == 0) &&
					(strcmp(vClientsData.vPassWord, clientsData.passWord) == 0))
				{
					authLogin += 1;
					loadingDisplay();
					printf("\n Dear %s, You Have Successfully Signed In!\n\n",
						clientsData.userName);

					/* counter asssigned 5 to terminate the parent loop */
					counter = 5;
				}
			}

			if (authLogin == 0 && counter < 4)
			{
				printf("\n Invalid Username and/or Password Entry!\n");
				rewind(file);
				continue;
			}

			if (counter == 4)
			{
				printf("\n Invalid Username and/or Password Entry!\n\n");
				printf("-----------------GOODBYE FROM E-BANKING SYSTEM-----------------");
				printf("\n\n");
				exit(1);
			}
		}
	}

	fclose(file);
	return (vClientsData);
}

/**
 * depositorFn - Depositor Function.
 *
 * Description: This function basically prompts the user to enter a deposit
 * amount as an input.
 *
 * Return: This function returns the amount of deposit entered by the user upon
 * successful execution.
 */
int depositorFn(void)
{
	char buffer[50];
	int depositAmt;

	printf(" How much US dollars do you want to fund your account with?");
	printf("\n Kindly enter the amount (in figures only): ");
	fgets(buffer, 50, stdin);

	/* sscanf returns zero (falsy expression) upon failure */
	if (sscanf(buffer, "%d", &depositAmt))
	{
		printf("\n You have successfully funded your account!\n\n");
		printf(" Your Account Balance: $%d\n", depositAmt);
	}

	return (depositAmt);
}

/**
 * printToDb - Print To clients_deposit.txt Database File.
 *
 * @vClientsData: This struct data-type parameter provides the clients username
 * data that gets printed to the clients_deposit.txt database file.
 *
 * @depositAmt: This parameter holds the clients deposit amount that gets
 * printed to the clients_deposit.txt database file.
 *
 * Description: This function basically prints the data held by its function
 * parameters to the clients_deposit.txt database file.
 */
void printToDb(struct VCLIENTSDATA vClientsData, int depositAmt)
{
	FILE *file = fopen("database/clients_deposit.txt", "a+");

	fprintf(file, "%s\t\t%d\n", vClientsData.vUserName, depositAmt);

	fclose(file);
}

/**
 * DbValidator - Database Validator Function.
 * @vClientsData: This function parameter holds the username data of the user
 * required by the Database Validator function.
 *
 * Description: This function searches the entire clients_deposit.txt database
 * file and then checks whether the vClientsData.vUserName data held by the
 * function parameter exists in the clients_deposit.txt database file and then
 * responds appropriately.
 */
void DbValidator(struct VCLIENTSDATA vClientsData)
{
	FILE *file = fopen("database/clients_deposit.txt", "r");
	char buffer[100];
	struct VCLIENTSDATA dBClientsData;
	int depositorFnRet, s_ret;


	while (fgets(buffer, 100, file) != NULL)
	{
		(s_ret = sscanf(buffer, "%s%d",
				dBClientsData.vUserName,
				&dBClientsData.vDepositAmt
		)) ?
			s_ret : printf("\n sscanf Operation Failed!\n");

		if (strcmp(vClientsData.vUserName, dBClientsData.vUserName) == 0)
		{
			break;
		}
	}

	if (strcmp(vClientsData.vUserName, dBClientsData.vUserName) == 0)
	{
		printf(" Your Account Balance: $%d\n", dBClientsData.vDepositAmt);
	}
	else
	{
		depositorFnRet = depositorFn();
		printToDb(vClientsData, depositorFnRet);

	}

	fclose(file);
}

#endif /* _E_BANKING_H_ */
