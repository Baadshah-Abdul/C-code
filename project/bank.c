#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNT 10
#define MAX_NAME_LENGTH 32

typedef struct {
    int accountNum;
    char name[MAX_NAME_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNT];
int accountCount = 0;

/*Function names*/
void create();
void display();
void delete();
void displayAll();
int search(int accountNumber);

int main() 
{
    int choice;
    
    printf("Simple Bank System\n");
   
    /*get choice*/
    while(1) 
	{
        printf("\n1 - Create Account\n");
        printf("2 - Display Account\n");
        printf("3 - Delete Account\n");
        printf("4 - Display All Accounts\n");
        printf("0 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) 
		{
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                delete();
                break;
            case 4:
                displayAll();
                break;
            case 0:
                printf("Exiting\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}
 /*create account*/
void create() 
{
	//check for maximum
    if (accountCount >= MAX_ACCOUNT) 
	{
        printf("Maximum number of accounts reached.\n");
        return;
    }
    
    Account newAccount;
    
	//create
    printf("\nCreate New Account\n");
    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNum);
    
    //check if exists
    if (search(newAccount.accountNum) != -1)
	{
        printf("Account number already exists.\n");
        return;
    }
    //take input asnd display
    printf("Enter account holder name: ");
    scanf(" %[^\n]", newAccount.name); // Read until newline
    
    printf("Enter initial balance: ");
    scanf("%f", &newAccount.balance);
    
    accounts[accountCount++] = newAccount;
    printf("Account created successfully!\n");
}


/*display accounts*/

void display() 
{
    int accountNum;
    
    printf("\nDisplay Account\n");
    printf("Enter account number: ");
    scanf("%d", &accountNum);
    
    int index = search(accountNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }
    
    printf("\nAccount Number: %d\n", accounts[index].accountNum);
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Balance: %.2f\n", accounts[index].balance);
}

/*delete accounts*/
void delete() 
{
    int accountNum;
    
    printf("\nDelete Account\n");
    printf("Enter account number to delete: ");
    scanf("%d", &accountNum);
    
    int index = search(accountNum);
    if (index == -1) 
	{
        printf("Account not found.\n");
        return;
    }
    
    //shift to save memory
	for (int i = index; i < accountCount - 1; i++)
	{
        accounts[i] = accounts[i + 1];
    }
    
    accountCount--;
    printf("Account deleted successfully.\n");
}

/*Display all accounts*/
void displayAll() 
{
    printf("\nAll Accounts\n");
    printf("--------------------------------\n");
    
	//check and show
    if (accountCount == 0)
	{
        printf("No accounts found.\n");
        return;
    }
    
    for (int i = 0; i < accountCount; i++)
	{
        printf("Account #%d\n", accounts[i].accountNum);
        printf("Holder: %s\n", accounts[i].name);
        printf("Balance: %.2f\n", accounts[i].balance);
        printf("--------------------------------\n");
    }
}

/*search account*/
int search(int accountNum)
{
    for (int i = 0; i < accountCount; i++) 
	{
        if (accounts[i].accountNum == accountNum)
		{
            return i;
        }
    }
    return -1;
}
