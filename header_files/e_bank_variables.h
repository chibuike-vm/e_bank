#ifndef _E_BANKING_VARIABLES_H_
#define _E_BANKING_VARIABLES_H_

/**
 * struct CLIENTSDATA - Structure Data-Type.
 *
 * @userName: This member stores the username of each client.
 * @passWord: This memeber stores the password of each client.
 * @email: This member stores the email of each client.
 * @age: This member stores the age of each client.
 *
 * Description: This CLIENTSDATA Structure Data-Type basically stores the input
 * data provided by the interacting user into its respective designated
 * members.
 */
struct CLIENTSDATA
{
	char userName[50];
	char passWord[50];
	char email[45];
	char age[5];
};

/**
 * struct VCLIENTSDATA - Structure Data-Type.
 *
 * @vUserName: This member stores the username of each client.
 * @vPassWord: This memeber stores the password of each client.
 * @vDepositAmt: This member stores the password of each client.
 *
 * Description: The VCLIENTSDATA Structure Data-Type basically stores the
 * verified username and pssword of each client.
 */
struct VCLIENTSDATA
{
	char vUserName[50];
	char vPassWord[50];
	int vDepositAmt;
};

#endif /* _E_BANKING_VARIABLES_H_ */
