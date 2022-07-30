#include <FastLED.h>

// Variables LEDs
#define NUMLED 11
#define LED_TYPE WS2812B
#define PIN 5
#define COLOR_ORDER GRB

CRGB LED[NUMLED];

// Variables Buttons
#define BUTTON1PIN 2
#define BUTTON2PIN 4
#define BUTTON3PIN 20
#define BUTTON4PIN 16
#define BUTTON5PIN 7
#define BUTTON6PIN 6
#define BUTTON7PIN 19
#define BUTTON8PIN 18
#define BUTTON9PIN 17
#define BUTTON10PIN 21 //  reset

// Variables Player and Game
#define P1COLOR CHSV(172, 225, 255)  // Blue
#define P2COLOR CHSV(86, 255, 255)   // Green
#define WRONGCOLOR CHSV(255, 0, 255) // Red
#define DRAWCOLOR CHSV(0, 0, 255)    // White
#define LEDOFF CHSV(0, 0, 0)         // OFF

int activePlayer = 1;
bool gameWon = false;

int gameStatus[3][3] =
    {{10, 20, 30},
     {40, 50, 60},
     {70, 80, 90}};

int resetStatus[3][3] =
    {{10, 20, 30},
     {40, 50, 60},
     {70, 80, 90}};

int moveCount = 0;

void setup()
{
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(LED, NUMLED).setCorrection(TypicalLEDStrip);
    pinMode(BUTTON1PIN, INPUT_PULLUP);  // Button 1
    pinMode(BUTTON2PIN, INPUT_PULLUP);  // Button 2
    pinMode(BUTTON3PIN, INPUT_PULLUP);  // Button 3
    pinMode(BUTTON4PIN, INPUT_PULLUP);  // Button 4
    pinMode(BUTTON5PIN, INPUT_PULLUP);  // Button 5
    pinMode(BUTTON6PIN, INPUT_PULLUP);  // Button 6
    pinMode(BUTTON7PIN, INPUT_PULLUP);  // Button 7
    pinMode(BUTTON8PIN, INPUT_PULLUP);  // Button 8
    pinMode(BUTTON9PIN, INPUT_PULLUP);  // Button 9
    pinMode(BUTTON10PIN, INPUT_PULLUP); // Button reset
}

void loop()
{
    while (gameWon == false)
    {
        gameWon = checkWin(gameStatus, moveCount);
        resetGame(gameStatus, moveCount, resetStatus);
        pressButton(activePlayer, gameStatus);
        showLED(gameStatus);
        switchPlayer(activePlayer, moveCount);
    }
    playerWon(activePlayer);
}

// Check Game Status
bool checkWin(int gameStatus[3][3], int moveCount)
{
    for (int row = 1; row <= 3; row++)
    {
        if (gameStatus[row][1] == gameStatus[row][2] && gameStatus[row][2] == gameStatus[row][3] || gameStatus[1][row] == gameStatus[2][row] && gameStatus[2][row] == gameStatus[3][row])
        {
            return true;
        }
    }

    if (gameStatus[1][1] == gameStatus[2][2] && gameStatus[2][2] == gameStatus[3][3] || gameStatus[3][1] == gameStatus[2][2] && gameStatus[2][2] == gameStatus[1][3])
    {
        return true;
    }

    if (moveCount > 9)
    {
        for (int i = 1; i <= 9; i++)
        {
            LED[i] = DRAWCOLOR;
        }
    }
}

void pressButton(int activePlayer, int gameStatus[3][3])
{
    if (digitalRead(BUTTON1PIN) == LOW)
    {
        setBox(gameStatus, 1, 1, activePlayer);
    }
    else if (digitalRead(BUTTON2PIN) == LOW)
    {
        setBox(gameStatus, 1, 2, activePlayer);
    }
    else if (digitalRead(BUTTON3PIN) == LOW)
    {
        setBox(gameStatus, 1, 3, activePlayer);
    }
    else if (digitalRead(BUTTON4PIN) == LOW)
    {
        setBox(gameStatus, 2, 1, activePlayer);
    }
    else if (digitalRead(BUTTON5PIN) == LOW)
    {
        setBox(gameStatus, 2, 2, activePlayer);
    }
    else if (digitalRead(BUTTON6PIN) == LOW)
    {
        setBox(gameStatus, 2, 3, activePlayer);
    }
    else if (digitalRead(BUTTON7PIN) == LOW)
    {
        setBox(gameStatus, 3, 1, activePlayer);
    }
    else if (digitalRead(BUTTON8PIN) == LOW)
    {
        setBox(gameStatus, 3, 2, activePlayer);
    }
    else if (digitalRead(BUTTON9PIN) == LOW)
    {
        setBox(gameStatus, 3, 3, activePlayer);
    }
    else if (digitalRead(BUTTON10PIN) == LOW)
    {
        resetGame(gameStatus, moveCount, resetStatus);
    }
    else
    {
        pressButton(activePlayer, gameStatus);
    }
}

void setBox(int gameStatus[3][3], int col, int row, int activePlayer)
{
    if (gameStatus[row][col] == resetStatus[row][col])
    {
        gameStatus[row][col] = activePlayer;
    }
    else
    {
        for (int i = 0; i <= 9; i++)
        {
            LED[i] = WRONGCOLOR;
        }
        delay(1000);
        showLED(gameStatus);
    }
}

void switchPlayer(int activePlayer, int moveCount)
{
    if (activePlayer == 1)
    {
        activePlayer == 2;
        moveCount++;
        LED[10] = LEDOFF;
        LED[11] = P2COLOR;
    }
    else
    {
        activePlayer == 1;
        moveCount++;
        LED[11] = LEDOFF;
        LED[10] = P1COLOR;
    }
}

void showLED(int gameStatus[3][3])
{
    for (int row = 1; row <= 3; row++)
    {
        for (int col = 1; col <= 3; col++)
        {
            int position = calcPosition(row, col);
            if (gameStatus[row][col] == 1)
            {
                LED[position] = P1COLOR;
            }
            else if (gameStatus[row][col] == 2)
            {
                LED[position] = P2COLOR;
            }
            else
            {
                LED[position] = CHSV(0, 0, 0);
            }
        }
    }
}

int calcPosition(int row, int col)
{
    switch (row)
    {
    case 1:
        return col;
        break;
    case 2:
        return col + 3;
        break;
    case 3:
        return col + 6;
        break;
    default:
        break;
    }
}

void playerWon(int activePlayer)
{
    for (int i = 1; i <= 9; i++)
    {
        if (activePlayer == 1)
        {
            LED[i] = P1COLOR;
        }
        else
        {
            LED[i] = P2COLOR;
        }
    }
}

void resetGame(int gameStatus[3][3], int moveCount, int resetStatus[3][3])
{
    if (BUTTON10PIN == LOW)
    {
        gameStatus = resetStatus;
        moveCount = 0;
    }
}
