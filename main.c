#include <stdio.h>
#include <string.h>
/********************************************************************************/
/*                          MACROS
*********************************************************************************/
#define configArrayLength   2
/********************************************************************************/
/*                          User Defined Data Types
*********************************************************************************/
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
/********************************************************************************/
/*                          Function Prototype
*********************************************************************************/
void drawBoard(uint8_t* board);
void updateBoard(uint8_t* board, uint8_t position, uint8_t value);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol);
void setPlayerConfig(uint8_t* configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t* board, uint8_t* gameState);


/********************************************************************************/
/*                          Global Variables
*********************************************************************************/
uint8_t position;
uint8_t error = 0;
/********************************************************************************/
/*                          Main function
*********************************************************************************/
int main(void)
{
    static uint8_t Board[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    static uint8_t configArray[configArrayLength] = { '0' };
    static uint8_t State;

    drawBoard(Board);
    getGameState(Board, &State);

    setPlayerConfig(configArray);

    static uint8_t player = 1;
    do
    {
        if (error != 0)
        {
            printf("Invalid.... please Select X or O");
            break;
        }

        player = (player % 2) ? 1 : 2;

        loadAndUpdate(player);
        updateBoard(Board, position, configArray[player - 1]);
        getGameState(Board, &State);

        player++;
        drawBoard(Board);
    } while (State == 2);

    if (State == 0)
    {
        printf("Player %d win", --player);
    }
    else if (State == 1)
    {
        printf("Game Draw\n");
    }
    else
    {
        // printf("Invalid.... please try again");
    }



    return 0;
}



/********************************************************************************/
/*                          Function Implementation
*********************************************************************************/
void drawBoard(uint8_t* board)
{
    printf("       |         |       \n");
    printf("    %c  |   %c     |    %c     \n ", board[1], board[2], board[3]);
    printf("______|_________|_______   \n");
    printf("       |         |       \n");
    printf("    %c  |   %c     |    %c     \n ", board[4], board[5], board[6]);
    printf("______|_________|_______   \n");
    printf("       |         |       \n");
    printf("    %c  |   %c     |    %c     \n ", board[7], board[8], board[9]);
    printf("      |         |       \n");
}


void updateBoard(uint8_t* board, uint8_t position, uint8_t value)
{
    board[position] = value;
}



uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t* symbol)
{
    uint8_t sym, returnStatus;

    static uint8_t flag = 0, prevSym;

    printf("Hello player %d\n", playerNumber);
    printf("Please choose your symbol(X or O): ");
    scanf(" %c", &sym);

    if (flag == 0)
    {
        if (sym == 'X' || sym == 'O')
        {
            *symbol = sym;
            prevSym = sym;
            flag = 1;
            returnStatus = 0;

        }
        else
        {
            returnStatus = 1;
        }
    }
    else if (flag == 1)
    {
        if ((prevSym != sym) && (sym == 'X' || sym == 'O'))
        {
            *symbol = sym;
            prevSym = sym;
            flag = 2;
            returnStatus = 0;
        }
        else
        {
            returnStatus = 1;
        }
    }
    else
    {
        returnStatus = 1;
    }

    return returnStatus;
}


void setPlayerConfig(uint8_t* configArray)
{
    uint8_t playerSymbol, playerNumber, retStatus;
    static uint8_t count = 0;

    while (count < configArrayLength)
    {
        printf("Player Number: ");
        scanf("%d", &playerNumber);
        retStatus = getPlayerSymbol(playerNumber, &playerSymbol);
        if (retStatus == 0)
            configArray[count] = playerSymbol;
        else
        {
            error = 2;
            break;
        }

        count++;
    }
}




void loadAndUpdate(uint8_t playerNumber)
{
    printf("player Number %d enter your position: ", playerNumber);
    scanf("%d", &position);

}




void getGameState(uint8_t* board, uint8_t* gameState)
{
    if (board[1] == board[2] && board[2] == board[3])
    {
        *gameState = 0;
    }
    else if (board[4] == board[5] && board[5] == board[6])
    {
        *gameState = 0;
    }
    else if (board[7] == board[8] && board[8] == board[9])
    {
        *gameState = 0;
    }
    else if (board[1] == board[4] && board[4] == board[7])
    {
        *gameState = 0;
    }
    else if (board[2] == board[5] && board[5] == board[8])
    {
        *gameState = 0;
    }
    else if (board[3] == board[6] && board[6] == board[9])
    {
        *gameState = 0;
    }
    else if (board[1] == board[5] && board[5] == board[9])
    {
        *gameState = 0;
    }
    else if (board[3] == board[5] && board[5] == board[7])
    {
        *gameState = 0;
    }
    else if (board[4] == board[5] && board[5] == board[6])
    {
        *gameState = 0;
    }
    else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
        board[4] != '4' && board[5] != '5' && board[6] != '6' &&
        board[7] != '7' && board[8] != '8' && board[9] != '9')
    {
        *gameState = 1;
    }

    else
    {
        *gameState = 2;
    }
}
