#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../header_files/e_bank_variables.h"
#include "../header_files/e_bank.h"

/**
 * main - Program Entry Point.
 *
 * Description: The main function is the program's entry point of execution
 * where all other functions are called to execute their respective tasks.
 *
 * Return: This function returns zero upon successful execution.
 */
int main(void)
{
	char intialAction[50], response[5], control[5];
	int s_ret;
	struct VCLIENTSDATA vClientsData;

	/* Function Pointer Concept: Implementing Callback Function */
	struct CLIENTSDATA (*cDV1Fptr)(char retD[5]);

	cDV1Fptr = cDV1;

	printf("\n------------------WELCOME TO E-BANKING SYSTEM------------------\n");
	printf("\n Please, do you already have an account with us?\n");
	printf(" Enter (yes or no): ");
	fgets(intialAction, 50, stdin);

	(s_ret = (sscanf(intialAction, "%s", response) == 1)) ?
		s_ret : printf(" Operation Failed\n");

	if (strcmp(response, "no") == 0)
	{
		loadingDisplay();
		pToDb(response, cDV1Fptr);

		printf("\n Do you want to fund your account right away?\n");
		printf(" Kindly enter (yes or no): ");
		fgets(control, 5, stdin);
		(s_ret = sscanf(control, "%s", control)) ?
			s_ret : printf("sscanf Operation Failed!\n");

		if (strcmp(control, "yes") == 0)
		{
			loadingDisplay();
			strcpy(response, "yes");
			vClientsData = cDV2(response);
			DbValidator(vClientsData);
		}
		else
		{
			printf("\n You will be automatically prompted to fund your account on\n");
			printf(" your next sign in. The fund deposit is required to get your");
			printf("\n account activated!\n");
		}
	}
	else if (strcmp(response, "yes") == 0)
	{
		vClientsData = cDV2(response);
		DbValidator(vClientsData);
	}
	else
	{
		printf("\n Invalid Input!\n Try Again...\n");
	}

	printf("\n-----------------GOODBYE FROM E-BANKING SYSTEM-----------------\n");
	putchar('\n');

	return (0);
}

