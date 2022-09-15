// by Christian Rahn


#include <FastLED.h>

// LEDs
#define LED_PIN D0
#define LED_NUM 11
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
#define LED_BRIGHTNESS 100

CRGB LED[LED_NUM];

// Colors
#define P1COLOR CHSV(172, 225, 255)    // Blue
#define P2COLOR CHSV(86, 255, 255)     // Green
#define DRAWCOLOR CHSV(0, 0, 255)      // White
#define WRONGCOLOR CHSV(255, 255, 255) // Red
#define LEDOFF CHSV(0, 0, 0)           // OFF

// Buttons
#define BUTTON1_PIN D5
#define BUTTON2_PIN D6
#define BUTTON3_PIN 1
#define BUTTON4_PIN D7
#define BUTTON5_PIN 3
#define BUTTON6_PIN D1
#define BUTTON7_PIN D2
#define BUTTON8_PIN D3
#define BUTTON9_PIN D4
#define BUTTONRST_PIN A0

int playerReset[3][3]{
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}};

int player1Field[3][3]{
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}};

int player2Field[3][3]{
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}};

bool gameWon = false;
byte activePlayer = 2;
byte playerMoves = 0;
bool switchingStatus = false;

void setup()
{
    activePlayer = randomizeBeginner();
    FastLED.setBrightness(LED_BRIGHTNESS);
    showPlayerLED(activePlayer);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LED, LED_NUM);
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);
    pinMode(BUTTON5_PIN, INPUT_PULLUP);
    pinMode(BUTTON6_PIN, INPUT_PULLUP);
    pinMode(BUTTON7_PIN, INPUT_PULLUP);
    pinMode(BUTTON8_PIN, INPUT_PULLUP);
    pinMode(BUTTON9_PIN, INPUT_PULLUP);
}

void loop()
{

    switchingStatus = buttonPress(player1Field, player2Field, activePlayer);
    showLEDs(player1Field, player2Field, activePlayer, true);

    if (gameWon == false)
    {
        if (activePlayer == 1)
        {
            gameWon = checkWin(player1Field, playerMoves);
        }
        else if (activePlayer == 2)
        {
            gameWon = checkWin(player2Field, playerMoves);
        }
    }
    else
    {
        if (playerMoves == 9)
        {
            for (int x = 0; x < 9; x++)
            {
                LED[x] = DRAWCOLOR;
            }
            FastLED.show();
            resetGame(playerReset);
        }
        else
        {
            showWin(activePlayer, player1Field, player2Field, playerReset);
            resetGame(playerReset);
        }
    }

    if (switchingStatus == true && gameWon == false)
    {
        activePlayer = switchPlayer(activePlayer);
        Serial.println(switchingStatus);
        switchingStatus = false;
    }
    Serial.println(switchingStatus);
    Serial.println("");
}

void showLEDs(int player1Field[3][3], int player2Field[3][3], int activePlayer, bool includePlayerLEDs)

{
    int playerField[3][3]{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    if (activePlayer == 1)
    {
        copyField(playerField, player1Field);
    }
    else if (activePlayer == 2)
    {
        copyField(playerField, player2Field);
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int LEDnumber = calculateLED(row, col);
            if (playerField[row][col] == 1)
            {
                if (activePlayer == 1)
                {
                    LED[LEDnumber] = P1COLOR;
                }
                else if (activePlayer == 2)
                {
                    LED[LEDnumber] = P2COLOR;
                }
            }
        }
    }

    if (includePlayerLEDs == true)
    {
        showPlayerLED(activePlayer);
    }

    FastLED.show();
}

void copyField(int changedField[3][3], int initialField[3][3])
{
    for (int col = 0; col < 3; col++)
    {
        for (int row = 0; row < 3; row++)
        {
            changedField[row][col] = initialField[row][col];
        }
    }
}

int calculateLED(int LEDrow, int LEDcol)
{
    return LEDrow * 3 + LEDcol;
}

int switchPlayer(int activePlayer)
{
    playerMoves += 1;
    if (activePlayer == 1)
    {
        return 2;
    }
    else if (activePlayer == 2)
    {
        return 1;
    }
}

int buttonPress(int player1Field[3][3], int player2Field[3][3], int activePlayer)
{
    if (digitalRead(BUTTON1_PIN) == LOW)
    {
        while (digitalRead(BUTTON1_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 0, 0, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 0, 0);
        }
        else
        {
            return false;
        }

        return true;
    }
    else if (digitalRead(BUTTON2_PIN) == LOW)
    {
        while (digitalRead(BUTTON2_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 0, 1, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 0, 1);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON3_PIN) == LOW)
    {
        while (digitalRead(BUTTON3_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 0, 2, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 0, 2);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON4_PIN) == LOW)
    {
        while (digitalRead(BUTTON4_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 1, 0, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 1, 0);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON5_PIN) == LOW)
    {
        while (digitalRead(BUTTON5_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 1, 1, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 1, 1);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON6_PIN) == LOW)
    {
        while (digitalRead(BUTTON6_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 1, 2, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 1, 2);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON7_PIN) == LOW)
    {
        while (digitalRead(BUTTON7_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 2, 0, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 2, 0);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON8_PIN) == LOW)
    {
        while (digitalRead(BUTTON8_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 2, 1, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 2, 1);
        }
        else
        {
            return false;
        }
        return true;
    }
    else if (digitalRead(BUTTON9_PIN) == LOW)
    {
        while (digitalRead(BUTTON9_PIN) == LOW)
        {
            delay(20);
        }
        if (wrongField(player1Field, player2Field, 2, 2, activePlayer) == false)
        {
            updateField(player1Field, player2Field, activePlayer, 2, 2);
        }
        else
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void updateField(int player1Field[3][3], int player2Field[3][3], int activePlayer, int row, int col)
{
    if (activePlayer == 1)
    {
        player1Field[row][col] = 1;
    }
    else if (activePlayer == 2)
    {
        player2Field[row][col] = 1;
    }
}

bool checkWin(int playerField[3][3], int moves)
{
    for (int row = 0; row < 3; row++)
    {
        if (
            ((playerField[row][0] == playerField[row][1]) && (playerField[row][1] == playerField[row][2])) || ((playerField[0][row] == playerField[1][row]) && (playerField[1][row] == playerField[2][row])))
        {
            return true;
        }
    }
    if (
        ((playerField[0][0] == playerField[1][1]) && (playerField[1][1] == playerField[2][2])) ||
        ((playerField[2][0] == playerField[1][1]) && (playerField[1][1] == playerField[0][2])))
    {
        return true;
    }
    else if (moves == 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void showWin(int playerWon, int player1Field[3][3], int player2Field[3][3], int resetField[3][3])
{
    if (playerWon == 1)
    {
        copyField(player2Field, resetField);
        showWinLEDs(player1Field, playerWon);
    }
    else if (playerWon == 2)
    {
        copyField(player1Field, resetField);
        showWinLEDs(player2Field, playerWon);
    }
}

void showWinLEDs(int playerWonField[3][3], int playerWon)
{
    for (int x = 0; x < 9; x++)
    {
        LED[x] = LEDOFF;
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int LEDnumber = calculateLED(row, col);

            if (playerWonField[row][col] == 1)
            {
                if (playerWon == 1)
                {
                    LED[LEDnumber] = P1COLOR;
                }
                else if (playerWon == 2)
                {
                    LED[LEDnumber] = P2COLOR;
                }
            }
        }
    }
    FastLED.show();
}

void resetGame(int resetField[3][3])
{
    while (gameWon == true)
    {
        if (analogRead(BUTTONRST_PIN) == 1024)
        {
            copyField(player1Field, resetField);
            copyField(player2Field, resetField);

            for (int x = 0; x < 9; x++)
            {
                LED[x] = LEDOFF;
            }

            playerMoves = 0;
            activePlayer = randomizeBeginner();
            showPlayerLED(activePlayer);
            FastLED.show();
            gameWon = false;
        }
        else
        {
            delay(1);
        }
    }
}

int randomizeBeginner()
{
    byte randomNumber = 0;
    randomNumber = random(1, 3);
    return randomNumber;
}

void showPlayerLED(int activePlayer)
{
    if (activePlayer == 1)
    {
        LED[9] = P1COLOR;
        LED[10] = LEDOFF;
    }
    else if (activePlayer == 2)
    {
        LED[9] = LEDOFF;
        LED[10] = P2COLOR;
    }
}

bool wrongField(int player1Field[3][3], int player2Field[3][3], int row, int col, int activePlayer)
{
    if (player1Field[row][col] == 1 || player2Field[row][col] == 1)
    {
        LED[calculateLED(row, col)] = WRONGCOLOR;
        FastLED.show();
        delay(400);
        showLEDs(player1Field, player2Field, 1, false);
        showLEDs(player1Field, player2Field, 2, false);
        return true;
    }
    else
    {
        return false;
    }
}
