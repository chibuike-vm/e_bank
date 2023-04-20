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
	char intialAction[50], response[5];
	int s_ret;

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
	}
	else if (strcmp(response, "yes") == 0)
	{
		cDV2(response);
	}

	printf("\n-----------------GOODBYE FROM E-BANKING SYSTEM-----------------\n");
	putchar('\n');

	return (0);
}
