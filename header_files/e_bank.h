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
 * @retD: This is a string function parameter which provides the input for
 * for the cDV1 function.
 *
 * Description: This function is basically a validator function that validates
 * the input string provided by an interacting user. It also prompts the user
 * for string inputs as the case may be and then goes ahead to store those user
 * inputs data into a data structure provided by the struct CLIENTSDATA
 * data-type.
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

		printf(" Username: ");
		fgets(clientsData.userName, 50, stdin);
		(s_ret = sscanf(clientsData.userName, "%s", clientsData.userName)) ?
			s_ret : printf("sscanf Function Failed!");

		dataLength = strlen(clientsData.userName);

		if (dataLength != 8)
		{
			putchar('\n');
			printf(" Data entry failed! Your username must be 8 characters long.\n");
			printf("\n-----------------GOODBYE FROM E-BANKING SYSTEM-----------------");
			printf("\n\n");
			exit(1);
		}

		printf(" Password: ");
		fgets(clientsData.passWord, 50, stdin);
		(s_ret = sscanf(clientsData.passWord, "%s", clientsData.passWord)) ?
			s_ret : printf("sscanf Function Failed!");

		dataLength = strlen(clientsData.passWord);

		if (dataLength != 8)
		{
			putchar('\n');
			printf(" Data entry failed! Your password must be 8 characters long.\n");
			printf("\n-----------------GOODBYE FROM E-BANKING SYSTEM-----------------");
			printf("\n\n");
			exit(1);
		}

		printf(" Age: ");
		fgets(clientsData.age, 5, stdin);
		(s_ret = sscanf(clientsData.age, "%s",  clientsData.age)) ?
			s_ret : printf("sscanf Function Failed!");

		printf(" Email: ");
		fgets(clientsData.email, 45, stdin);
		(s_ret = sscanf(clientsData.email, "%s", clientsData.email)) ?
			s_ret : printf("sscanf Function Failed!");

		loadingDisplay();
		printf("\n Dear %s, your details have been successfuly submitted",
				clientsData.userName);
		printf("\n and your E- Bank account has been successfully opened!\n");
	}

	return (clientsData);
}

/**
 * pToDb - Print To Database Function.
 *
 * @retD: This is a string function parameter which provides the input for
 * for the pToDb function.
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
	if (strcmp(retD, "no") == 0)
	{
		struct CLIENTSDATA clientsData;
		FILE *file = fopen("database/clients_data.txt", "a+");

		clientsData = (*cDV1Fptr)(retD);

		fprintf(file, "%s\t\t%s\t%s\t%s\n",
				clientsData.userName,
				clientsData.passWord,
				clientsData.age,
				clientsData.email
		       );

		fclose(file);
	}
}

/**
 * cDV2 - Client Data Validator2 Function.
 * @retD: This is a string function parameter which provides the input for
 * for the cDV2 function.
 *
 * Description: This function is basically a validator function that validates
 * the username and password string inputs provided by an interacting user.
 */
void cDV2(char retD[5])
{
	struct VCLIENTSDATA vClientsData;
	struct CLIENTSDATA clientsData;

	FILE *file = fopen("database/clients_data.txt", "r+");
	int authLogin = 0, s_ret;

	if (strcmp(retD, "yes") == 0)
	{
		char buffer[150];

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
				printf("\n Dear %s, You Have Sucessfully Signed In!\n\n",
					clientsData.userName);
			}
		}

		fclose(file);

		if (authLogin == 0)
		{
			printf("\n Invalid Username and/or Password Entry!\n");
			printf("\n-----------------GOODBYE FROM E-BANKING SYSTEM-----------------");
			printf("\n\n");
			exit(1);
		}
	}
}

#endif /* _E_BANKING_H_ */
