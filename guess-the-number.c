/* Guess the number game in C. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Displays the main menu with the differents game's difficulties */
void displayMenu(void);

/* Generates a random integer between 'minRange' and 'maxRange' using
    'srand' and 'rand' functions. */
int generateRandomNumber(int minRange, int maxRange);

/* Use "displayMenu()" and ask to user enter a difficulty value. It
    can be 'E' for Easy, 'M' for Medium and 'H' for Hard. */
int getGameDifficulty(void);

/* Gets the user's number with scanf() displaying {param} prompt */
int getUserNumber(char* prompt);

/* If the user enter 'Y' we return 1 indicating that user wants to 
    play again or 0 else */
int playAgain(void);


/* Enumerations for represent game information like difficulty or
    the game status */
enum DIFFICULTY {EASY, MEDIUM, HARD};
enum GAME_STATUS {WIN, LOSE};


int main()
{
    enum DIFFICULTY gameDiff;
    enum GAME_STATUS gameStatus;

    /* Defining some internal game variables */
    int secretNumber;
    int userNumber;
    int minRange = 1;
    int maxRange;
    int remainingAttempts;

    /* Asking to user enter a difficulty value using `getGameDifficulty` */
    gameDiff = getGameDifficulty();

    /* Setting the ranges and attempts depending to difficulty value */
    switch (gameDiff) {
        case EASY:
            maxRange = 10;
            remainingAttempts = 4;
            break;
        
        case MEDIUM:
            maxRange = 25;
            remainingAttempts = 4;
            break;

        case HARD:
            maxRange = 50;
            remainingAttempts = 5;
            break;
    }

    /* After set the ranges, we can generate the secret number using 
        genenerateRandomNumber() */
    secretNumber = generateRandomNumber(minRange, maxRange);

    /* Starting the main loop in function of `remainingAttempts` variable */
    for (remainingAttempts; remainingAttempts > 0; remainingAttempts--) {
        printf("\nRemaining Attempts: %d\n", remainingAttempts);
        printf("-------------------------------");

        printf("\nI'm thinking in a number between %d and %d.", minRange, maxRange);
        printf("\nTry to guess it.\n" );

        /* Getting the user's number */
        userNumber = getUserNumber("Enter a number: ");

        /* Checking if `userNumber` is not out of: minRange > userNumber < maxRange. */
        if (userNumber < minRange || userNumber > maxRange) {
            printf("That number is out of range, bro ._.\nTry again.\n");
            ++remainingAttempts;
            continue;
        }

        /* Showing if user number is smaller or higher than secret number,
            if it is not smaller or higher means that both are equals, so
            user wins and then we set `gameStatus` to 'WIN' and we break the
            game loop. */
        if (userNumber < secretNumber) {
            printf("\nIncorrect. The secret number is higher.\n");
        } else if (userNumber > secretNumber) {
            printf("\nIncorrect. The secret number is lower.\n");
        } else {
            printf("\nCorrect. The secret number was: %d\nYou win.\n", secretNumber);
            gameStatus = WIN;
            break;
        }
    }

    /* If we got out of the game loop and `gameStatus` is different to 'WIN'
        means that user lose. */
    if (gameStatus != WIN) {
        gameStatus = LOSE;
        printf("\nAttempts completed. The secret number was: %d\n", secretNumber);
    }

    /* Asking to user to play again using playAgain(), if he doesn't want to.
        We just say "Goodbye" and the program ends. */
    if (playAgain()) {
        printf("\n");
        main();
    } else {
        printf("\nGoodbye :)\n");
    }

    return 0;
}

void displayMenu(void)
{
    printf("G U E S S  T H E  N U M B E R\n");
    printf("Select the difficulty: \n");
    printf("[E] Easy\n");
    printf("[M] Medium\n");
    printf("[H] Hard\n");
}

int generateRandomNumber(int minRange, int maxRange)
{
    srand(time(NULL));
    return minRange + (rand() % maxRange);
}

int getGameDifficulty(void)
{
    displayMenu();

    printf("-> ");
    char selectedDifficulty;
    scanf(" %c", &selectedDifficulty);
    
    switch (selectedDifficulty) {
        case 'e':
        case 'E':
            return EASY;
            break;

        case 'm':
        case 'M':
            return MEDIUM;
            break;
        
        case 'h':
        case 'H':
            return HARD;
            break;
        
        default:
            printf("\nThat was a invalid value :(\nTry again.\n\n");
            return getGameDifficulty();
    }
}

int getUserNumber(char* prompt)
{
    int n;

    printf("%s", prompt);
    scanf("%d", &n);

    return n;
}

int playAgain(void)
{
    char playAgain;
    printf("Do you wanna play again? [Y/N]: ");
    scanf(" %c", &playAgain);

    if (playAgain == 'Y' || playAgain == 'y') {
        return 1;
    }

    return 0;
}