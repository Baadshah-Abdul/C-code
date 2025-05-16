#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/*Random number generator b/w 1 & 6*/
int random_num(int max)
{
	int x;
	x = rand() % max + 1;
	return x;
}


/*calls random generator*/
int dice_generator(int num)
{
	srand(time(NULL));
	int dice = random_num(num);
	return dice;
}


int main()
{
	int balance = 1000, dice, dice_num = 5, bet, guess;
	
	printf("DICE ROLLING\n");
	printf("Starting Balance: $%d\n", balance);
	 
	game:
	
	/*asking for bet*/
	printf("Enter bet: $");
	scanf("%d", &bet);	dice = dice_generator(dice_num);

	/*enter guess*/
	printf("Guess a number b/w 1 & 6 & 0 means quit\n");
	scanf("%d", &guess);
	
	/*Quit*/
	if(guess == 0)
		return 0;
	
	/*right guess*/
	printf("Right Gues: %d\n", dice);
	
	
	/*calculate balance for win & loss*/
	if(dice == guess)
	{
		printf("Your guess was correct!! Bet multiplied by 3 and added\n");
		balance = balance + (bet * 3);	
		printf("New Balance: $%d \U0001F911\n", balance);

	}
	else if(dice != guess)
	{
		balance -= bet;
		printf("Your balance left: $%d \U0001F923\n", balance);
	}
	sleep(3);
	/*repeating*/
	if(balance > 0)
	{
		goto game;
	}
	if(balance < 0)
		printf("You owe me $%d \U0001F480\n", abs(balance));

	printf("HARAAM KA PAISA CHAHIYE TUJHE!!!!\n");
	return 0;
}

