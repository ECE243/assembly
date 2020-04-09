#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

// Constants that can be tweaked to adjust various properties
// of the game that affect how difficult it is
#define SMALLEST_BUBBLE_RADIUS 4
#define GRAVITATIONAL_CONSTANT 1
#define LENGTH_OF_LEVEL_SECONDS 90
#define NUM_LEVELS_IN_GAME 4   // Maximum is 4 (but can be configured to any number below that)
#define BONUS_Y_VELOCITY_AFTER_SPLIT -3

#define ARROW_SIZE_X 10
#define ARROW_SIZE_Y 10
#define ARROW_MOVE_SPEED 9

#define PLAYER1_SIZE_X 22
#define PLAYER1_SIZE_Y 30
#define PLAYER2_SIZE_X 23
#define PLAYER2_SIZE_Y 30
#define PLAYER_MOVE_SPEED 3

// Key Codes for the player's controls on the PS2 Keyboard
#define PLAYER1_MOVE_LEFT_KEYBOARD_CODE 0x1C
#define PLAYER1_MOVE_RIGHT_KEYBOARD_CODE 0x23
#define PLAYER1_SHOOT_KEYBOARD_CODE 0x1D
#define PLAYER2_MOVE_LEFT_KEYBOARD_CODE 0x6B
#define PLAYER2_MOVE_RIGHT_KEYBOARD_CODE 0x74
#define PLAYER2_SHOOT_KEYBOARD_CODE 0x75
#define START_GAME_KEY_CODE 0x5A

//----------Graphics/Audio Array Definitions------------
//------------------------------------------------------
// Replace these empty arrays with those in /resources/arrayData.c
const int START_SCREEN_PIXEL_DATA[];
const int GAME_OVER_SCREEN_PIXEL_DATA[];
const int WINNING_TEXT_PIXEL_DATA[];

const int FIRST_PLAYER_PIXEL_DATA[];
const int SECOND_PLAYER_PIXEL_DATA[];
const int sadNaruto[];
const int ARROW_PIXEL_DATA[];

const int LEVEL_ONE_TEXT_PIXEL_DATA[];
const int LEVEL_TWO_TEXT_PIXEL_DATA[];
const int LEVEL_THREE_TEXT_PIXEL_DATA[];
const int LEVEL_FOUR_TEXT_PIXEL_DATA[];

const int HEX_DISPLAY_DATA[];

#define LOSING_MUSIC_DATA_SIZE 20805
const int LOSING_MUSIC_DATA[];

#define WINNING_MUSIC_DATA_SIZE 53128
const int WINNING_MUSIC_DATA[];

//------------------------------------------------------

// Various data defining the state of a bubble that is bouncing across the screen
typedef struct bubble {
    int centerX, centerY;
    int radius;
    int xVelocity, yVelocity;
} Bubble;

// An item in a singly-linked list of Bubble structs
typedef struct bubbleLinkedListItem {
    Bubble* bubbleData;
    struct bubbleLinkedListItem* next;
} BubbleLinkedListItem;

void addBubbleToEndOfList(BubbleLinkedListItem** listHead, Bubble* bubbleToAdd);
void addBubbleAfter(BubbleLinkedListItem* beforeItemToAdd, Bubble* bubbleToAdd);
void removeBubbleAtHead(BubbleLinkedListItem** plistHead);
void removeBubbleAfter(BubbleLinkedListItem* beforeItemToDelete);
void removeBubbleFromList(BubbleLinkedListItem** listHead, Bubble* bubbleToRemove);

typedef struct arrow {
    int x, y;
    int sizeX, sizeY;

    int xVelocity, yVelocity;
} Arrow;

typedef struct player {
    int x, y;
    int sizeX, sizeY;

    // Flags that represent the "intention" of the user controlling
    // the player (e.g. did they press the move left button?)
    bool requestMoveLeft, requestMoveRight, requestShoot;

    // The state of the player's arrow
    bool readyToShootArrow;
    Arrow* shootingArrow;

    int score;

    const int* playerPixelData;
} Player;

//----------IO Device Function/Global Declarations------
//------------------------------------------------------
void initializeIODevices();
void initializeTimer();
void initializeTimerProgressBar();

void updateIODevices(Player* player1, Player* player2);
void fetchKeyboardInputs(Player* player1, Player* player2);
void fetchTimerStatus();
void updateHEXDisplays(Player* player1, Player* player2);

void waitForStartKeyPress();

float map(float value, float istart, float istop, float ostart, float ostop);
void playGameEndAudio();

volatile int* const LEDR_PTR = (int*) 0xFF200000;
volatile int* const HEX_PORT1_PTR = (int*) 0xFF200020;
volatile int* const HEX_PORT2_PTR = (int*) 0xFF200030;
volatile int* const PS2_PTR = (int*) 0xFF200100;
volatile int* const AUDIO_PTR = (int*) 0xFF203040;
volatile int* const A9_TIMER_PTR = (int*) 0xFFFEC600;

int audio_buffer_index = 0;

//-----------Graphics Function/Global Declarations------
//------------------------------------------------------
void initializeGraphics();
void drawInGameScreen(const BubbleLinkedListItem* bubbleListHead, const Player* player1, const Player* player2,
                      int currentLevel);
void drawStartScreen();
void drawGameOverScreen();
void drawYouWin();
void clear_screen();
void drawLevel(const int array[]);
void waiting();

void plot_pixel(int x, int y, short int line_color);
void drawPlayer(const Player* player, bool erase);
void drawArrow(const Arrow* arrow, bool erase);
void drawBubble(const Bubble* bubble, short int color);

volatile int pixel_buffer_start;
volatile int* const pixel_ctrl_ptr = (int*) 0xFF203020;

//-----------Game Logic Function/Global Declarations----
//------------------------------------------------------
void initializeGame(BubbleLinkedListItem** pBubblesListHead, Player** player1, Player** player2, int currentLevel);
void updateGameState(BubbleLinkedListItem** pBubblesListHead, Player* player1, Player* player2);
void initializeHEXDisplays();
void initializeBubblesList(BubbleLinkedListItem** pBubblesListHead, int currentLevel);
Bubble* createBubble(int centerX, int centerY, int radius, int xVelocity, int yVelocity);
void initializePlayer(Player** player, int x, int y, int sizeX, int sizeY, const int* pixelData);
void initializePlayerShootingArrow(Player* player);

void moveBubble(Bubble* bubble);
void accelerateBubbleDown(Bubble* bubble);
void bounceBubbleOffScreen(Bubble* bubble);
void breakBubble(BubbleLinkedListItem* bubbleToBreakListItem);

void moveArrow(Arrow* arrow);
void destroyPlayerArrowAtTop(Player* player);
void resetPlayerArrow(Player* player);

void movePlayer(Player* player);
void checkAndServicePlayerShootRequest(Player* player);

bool checkBubblePlayerCollision(Bubble* bubble, Player* player);
bool checkArrowBubbleCollision(Bubble* bubble, Arrow* arrow);

bool gameOver = false;
bool outOfTime = false;
bool wasPlayerHit = false;

int main(void) {
    initializeGraphics();
    initializeIODevices();

    // The list of all the bouncing bubbles
    BubbleLinkedListItem* bubblesListHead;
    // Pointers to the player objects for the (up to) 2 players
    Player* player1;
    Player* player2;

    drawStartScreen();
    waitForStartKeyPress();

    int currentLevel = 1;
    while (currentLevel <= NUM_LEVELS_IN_GAME) {
        initializeGame(&bubblesListHead, &player1, &player2, currentLevel);

        clear_screen();
        if (currentLevel == 1) {
            drawLevel(LEVEL_ONE_TEXT_PIXEL_DATA);
        }
        if (currentLevel == 2) {
            drawLevel(LEVEL_TWO_TEXT_PIXEL_DATA);
        }
        if (currentLevel == 3) {
            drawLevel(LEVEL_THREE_TEXT_PIXEL_DATA);
        }
        if (currentLevel == 4) {
            drawLevel(LEVEL_FOUR_TEXT_PIXEL_DATA);
        }

        waitForStartKeyPress();
        clear_screen();

        while (!gameOver) {
            drawInGameScreen(bubblesListHead, player1, player2, currentLevel);
            updateIODevices(player1, player2);
            updateGameState(&bubblesListHead, player1, player2);
        }

        // If the player lost the previous level, end the game
        if (outOfTime || wasPlayerHit) {
            break;
        }
            // Otherwise, increment the level and continue running the game
        else {
            currentLevel++;

            // Reset the timer for the next level
            initializeTimer();
            initializeTimerProgressBar();

            gameOver = false;
        }
    }

    clear_screen();
    if (wasPlayerHit || outOfTime) {
        drawGameOverScreen();
        audio_buffer_index = 0;
        while (1) {
            playGameEndAudio(LOSING_MUSIC_DATA, LOSING_MUSIC_DATA_SIZE);
        }
    } else {
        drawYouWin();
        audio_buffer_index = 0;
        while (1) {
            playGameEndAudio(WINNING_MUSIC_DATA, WINNING_MUSIC_DATA_SIZE);
        }
    }

    return 0;
}

//----------IO Device Function Definitions-------------
//------------------------------------------------------
void initializeIODevices() {
    // PS2 Keyboard Initialization
    //----------------------------------------
    // Enable the keyboard
    *PS2_PTR = 0xF4;
    // Wait for the acknowledgement
    while ((*PS2_PTR & 0xFF) != 0xFA) {
    }

    // A9 Private Timer Initialization
    //----------------------------------------
    initializeTimer();

    initializeTimerProgressBar();

    initializeHEXDisplays();
}

void initializeHEXDisplays() {
    *HEX_PORT1_PTR = HEX_DISPLAY_DATA[0];
    *HEX_PORT2_PTR = HEX_DISPLAY_DATA[0];
}

void initializeTimer() {
    // Start the timer with a load value of 1/10 the length of the game (in clock cycles)
    *A9_TIMER_PTR = (LENGTH_OF_LEVEL_SECONDS / 10) * 200000000;
    *(A9_TIMER_PTR + 3) = 1; // Writing 1 to the F bit resets the timer
    *(A9_TIMER_PTR + 2) = 1; // Enable it so it continues counting
}

void initializeTimerProgressBar() {
    // At the beginning, the user has the full time remaining to complete the game
    // (i.e. all LEDs should be on to show a "full" progress bar)
    *LEDR_PTR = 0x3FF;
}

void updateIODevices(Player* player1, Player* player2) {
    fetchKeyboardInputs(player1, player2);
    fetchTimerStatus();
    updateHEXDisplays(player1, player2);
}

void fetchKeyboardInputs(Player* player1, Player* player2) {
    unsigned PS2Data = *PS2_PTR;
    // If no data is available to read, do nothing
    while ((PS2Data & 0x8000) != 0) {
        // If the key is E0, the key pressed is one of the arrow keys,
        // but to find out which we need to read the next input
        if ((PS2Data & 0xFF) == 0xE0) {
            do {
                PS2Data = *PS2_PTR;
            } while ((PS2Data & 0x8000) == 0);
        }

        // Every break sequence is initiated with 0xF0
        bool isBreakCode = (PS2Data & 0xFF) == 0xF0;

        // If a break code is encountered, determine which key was released
        if (isBreakCode) {
            // Wait for the next keycode in the break sequence to be
            // transmitted
            do {
                PS2Data = *PS2_PTR;
            } while ((PS2Data & 0x8000) == 0);
        }

        char pressedKeyCode = PS2Data & 0xFF;

        // Update the 'requestMoveLeft', 'requestMoveRight', and 'requestShoot' flags
        // of each player depending on what the user presses
        if (pressedKeyCode == PLAYER1_MOVE_LEFT_KEYBOARD_CODE) {
            player1->requestMoveLeft = !isBreakCode;
        } else if (pressedKeyCode == PLAYER1_MOVE_RIGHT_KEYBOARD_CODE) {
            player1->requestMoveRight = !isBreakCode;
        } else if (pressedKeyCode == PLAYER1_SHOOT_KEYBOARD_CODE) {
            player1->requestShoot = !isBreakCode;
        } else if (pressedKeyCode == PLAYER2_MOVE_LEFT_KEYBOARD_CODE) {
            player2->requestMoveLeft = !isBreakCode;
        } else if (pressedKeyCode == PLAYER2_MOVE_RIGHT_KEYBOARD_CODE) {
            player2->requestMoveRight = !isBreakCode;
        } else if (pressedKeyCode == PLAYER2_SHOOT_KEYBOARD_CODE) {
            player2->requestShoot = !isBreakCode;
        }

        PS2Data = *PS2_PTR;
    }
}

void fetchTimerStatus() {
    // If the F bit is set in the timer (meaning it has finished counting),
    // update the timer status
    if (*(A9_TIMER_PTR + 3) != 0) {
        // Update the timer progress bar by decreasing the time remaining
        // (this is done by logical right-shifting it)
        *LEDR_PTR = *LEDR_PTR >> 1;

        // If time is up, end the game and disable the timer
        if (*LEDR_PTR == 0) {
            gameOver = true;
            outOfTime = true;
            *(A9_TIMER_PTR + 2) = 0;
        }
            // Otherwise, restart the timer and continue
        else {
            initializeTimer();
        }
    }
}

void updateHEXDisplays(Player* player1, Player* player2) {
    *HEX_PORT1_PTR = (HEX_DISPLAY_DATA[player1->score / 10] << 8) | HEX_DISPLAY_DATA[player1->score % 10];
    *HEX_PORT2_PTR = (HEX_DISPLAY_DATA[player2->score / 10] << 8) | HEX_DISPLAY_DATA[player2->score % 10];
}

void waitForStartKeyPress() {
    bool enterKeyPressed = false;

    // This function actually will wait for both the key press, and the release
    // before giving control back to main()
    while (!enterKeyPressed) {
        unsigned PS2Data = *PS2_PTR;

        // Wait for a key to be pressed
        while ((PS2Data & 0x8000) == 0) {
            PS2Data = *PS2_PTR;
        }

        // If this was a break code, clear the buffer
        // and wait for the next key press (by restarting the outer loop)
        if ((PS2Data & 0xFF) == 0xF0) {
            while ((PS2Data & 0x8000) != 0) {
                PS2Data = *PS2_PTR;
            }
            continue;
        }

        // Ensure that it is the enter key
        enterKeyPressed = (PS2Data & 0xFF) == START_GAME_KEY_CODE;
    }
}

float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void playGameEndAudio(const int* musicData, int lengthOfMusic) {
    int fifospace = *(AUDIO_PTR + 1);

    while ((fifospace & 0x00FF0000) && (audio_buffer_index < lengthOfMusic)) {
        *(AUDIO_PTR + 2) = (int) map(musicData[audio_buffer_index], -32767, 32767, 0, 2000000000);
        *(AUDIO_PTR + 3) = (int) map(musicData[audio_buffer_index], -32767, 32767, 0, 2000000000);
        ++audio_buffer_index;
        fifospace = *(AUDIO_PTR + 1);
    }
}

//----------Graphics Function Definitions---------------
//------------------------------------------------------
void initializeGraphics() {
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
}

void drawInGameScreen(const BubbleLinkedListItem* bubbleListHead, const Player* player1, const Player* player2,
                      int currentLevel) {
    // this code is for all the initial conditions drawing,the players are drawn, the ball is drawn, the arrows will be drawn if shooting trigger is enabled
    const BubbleLinkedListItem* currentListItem = bubbleListHead;
    // code for drawing the ball
    while (currentListItem != NULL) {
        drawBubble(currentListItem->bubbleData, 0x07E0);
        currentListItem = currentListItem->next;
    }
    drawPlayer(player1, false);
    drawPlayer(player2, false);

    if (!player1->readyToShootArrow) {
        drawArrow(player1->shootingArrow, false);
    }

    if (!player2->readyToShootArrow) {
        drawArrow(player2->shootingArrow, false);
    }

    waiting();
    // this is for erasing, what has been drawen
    currentListItem = bubbleListHead;
    while (currentListItem != NULL) {
        drawBubble(currentListItem->bubbleData, 0x0000);
        currentListItem = currentListItem->next;
    }
    drawPlayer(player1, true);
    drawPlayer(player2, true);

    if (!player1->readyToShootArrow) {
        drawArrow(player1->shootingArrow, true);
    }

    if (!player2->readyToShootArrow) {
        drawArrow(player2->shootingArrow, true);
    }
}

// all the drawing, uses 565 rgb to traverse through the array, gets the r b and g values, put them in plot pixel to draw it.
void drawStartScreen() {
    int xCord = 0, yCord = 0;

    for (int size = 0; size < 320 * 2 * 240 - 1; size += 2) {
        int red = ((START_SCREEN_PIXEL_DATA[size + 1] & 0xF8) >> 3) << 11;
        int green = (((START_SCREEN_PIXEL_DATA[size] & 0xE0) >> 5)) | ((START_SCREEN_PIXEL_DATA[size + 1] & 0x7) << 3);

        int blue = (START_SCREEN_PIXEL_DATA[size] & 0x1f);

        short int rbg = red | ((green << 5) | blue);

        plot_pixel(xCord, yCord, rbg);

        xCord += 1;
        if (xCord == 320) {
            xCord = 0;
            yCord += 1;
        }
    }
}

void drawGameOverScreen() {
    {

        int xCord = 120, yCord = 120;

        for (int size = 0; size < 80 * 2 * 38 - 1; size += 2) {

            int red = ((GAME_OVER_SCREEN_PIXEL_DATA[size + 1] & 0xF8) >> 3) << 11;
            int green = (((GAME_OVER_SCREEN_PIXEL_DATA[size] & 0xE0) >> 5)) |
                        ((GAME_OVER_SCREEN_PIXEL_DATA[size + 1] & 0x7) << 3);

            int blue = (GAME_OVER_SCREEN_PIXEL_DATA[size] & 0x1f);

            short int rbg = red | ((green << 5) | blue);

            plot_pixel(xCord, yCord, rbg);

            xCord += 1;
            if (xCord == 200) {
                xCord = 120;
                yCord += 1;
            }
        }

        //153600
    }
}

void drawLevel(const int* array) {
    {

        int xCord = 120, yCord = 30;

        for (int size = 0; size < 78 * 2 * 28 - 1; size += 2) {

            int red = ((array[size + 1] & 0xF8) >> 3) << 11;
            int green = (((array[size] & 0xE0) >> 5)) | ((array[size + 1] & 0x7) << 3);

            int blue = (array[size] & 0x1f);

            short int rbg = red | ((green << 5) | blue);

            plot_pixel(xCord, yCord, rbg);

            xCord += 1;
            if (xCord == 198) {
                xCord = 120;
                yCord += 1;
            }
        }
    }
}

void drawYouWin() {

    {

        int xCord = 125, yCord = 101;

        for (int size = 0; size < 80 * 2 * 38 - 1; size += 2) {

            int red = ((WINNING_TEXT_PIXEL_DATA[size + 1] & 0xF8) >> 3) << 11;
            int green =
                    (((WINNING_TEXT_PIXEL_DATA[size] & 0xE0) >> 5)) | ((WINNING_TEXT_PIXEL_DATA[size + 1] & 0x7) << 3);

            int blue = (WINNING_TEXT_PIXEL_DATA[size] & 0x1f);

            short int rbg = red | ((green << 5) | blue);

            plot_pixel(xCord, yCord, rbg);

            xCord += 1;
            if (xCord == 195) {
                xCord = 125;
                yCord += 1;
            }
        }

        //153600
    }
}

void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel(x, y, 0x0);
        }
    }
}

void waiting() {
    volatile int* status = pixel_ctrl_ptr + 3;

    *pixel_ctrl_ptr = 1;

    while ((*status & 0x01) != 0) {
        status = status;
    }
}

void plot_pixel(int x, int y, short int line_color) {
    *(short int*) (pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void drawPlayer(const Player* player, bool erase) {
    int x = player->x;
    int y = player->y;
    short int playerColor;

    for (int array = 0; array < player->sizeX * 2 * player->sizeY - 1; array += 2) {
        int red = ((player->playerPixelData[array + 1] & 0xF8) >> 3) << 11;
        int green =
                (((player->playerPixelData[array] & 0xE0) >> 5)) | ((player->playerPixelData[array + 1] & 0x7) << 3);

        int blue = player->playerPixelData[array] & 0x1f;
        if (erase == true) {
            playerColor = 0x0;
        } else {
            playerColor = red | ((green << 5) | blue);
        }

        plot_pixel(x, y, playerColor);

        x += 1;
        if (x == player->x + player->sizeX) {
            x = player->x;
            y += 1;
        }
    }
}

void drawArrow(const Arrow* arrow, bool erase) {
    int x = arrow->x;
    int y = arrow->y;
    short int arrowColor;

    for (int array = 0; array < arrow->sizeX * 2 * arrow->sizeY - 1; array += 2) {
        int red = ((ARROW_PIXEL_DATA[array + 1] & 0xF8) >> 3) << 11;
        int green = (((ARROW_PIXEL_DATA[array] & 0xE0) >> 5)) | ((ARROW_PIXEL_DATA[array + 1] & 0x7) << 3);

        int blue = (ARROW_PIXEL_DATA[array] & 0x1f);
        if (erase == true) {
            arrowColor = 0x0;
        } else {
            arrowColor = red | ((green << 5) | blue);
        }

        plot_pixel(x, y, arrowColor);

        x += 1;
        if (x == arrow->x + arrow->sizeX) {
            x = arrow->x;
            y += 1;
        }
    }
}

// Uses Bresenham's Algorithm for drawing a circle (src: geeksforgeeks.com)
void drawBubble(const Bubble* bubble, short int color) {
    short int colour = color;
    int x = 0, y = bubble->radius;
    int d = 3 - 2 * bubble->radius;

    plot_pixel(bubble->centerX + x, bubble->centerY + y, colour);
    plot_pixel(bubble->centerX - x, bubble->centerY + y, colour);
    plot_pixel(bubble->centerX + x, bubble->centerY - y, colour);
    plot_pixel(bubble->centerX - x, bubble->centerY - y, colour);
    plot_pixel(bubble->centerX + y, bubble->centerY + x, colour);
    plot_pixel(bubble->centerX - y, bubble->centerY + x, colour);
    plot_pixel(bubble->centerX + y, bubble->centerY - x, colour);
    plot_pixel(bubble->centerX - y, bubble->centerY - x, colour);

    while (y >= x) {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        plot_pixel(bubble->centerX + x, bubble->centerY + y, colour);
        plot_pixel(bubble->centerX - x, bubble->centerY + y, colour);
        plot_pixel(bubble->centerX + x, bubble->centerY - y, colour);
        plot_pixel(bubble->centerX - x, bubble->centerY - y, colour);
        plot_pixel(bubble->centerX + y, bubble->centerY + x, colour);
        plot_pixel(bubble->centerX - y, bubble->centerY + x, colour);
        plot_pixel(bubble->centerX + y, bubble->centerY - x, colour);
        plot_pixel(bubble->centerX - y, bubble->centerY - x, colour);
    }
}

//----------Game Logic Function Definitions-------------
//------------------------------------------------------
void initializeGame(BubbleLinkedListItem** pBubblesListHead, Player** player1, Player** player2, int currentLevel) {
    initializeBubblesList(pBubblesListHead, currentLevel);

    initializePlayer(player1, (SCREEN_SIZE_X / 3) - (PLAYER1_SIZE_X / 2), SCREEN_SIZE_Y - PLAYER1_SIZE_Y,
                     PLAYER1_SIZE_X, PLAYER2_SIZE_Y, FIRST_PLAYER_PIXEL_DATA);
    initializePlayer(player2, 2 * (SCREEN_SIZE_X / 3) - (PLAYER1_SIZE_X / 2), SCREEN_SIZE_Y - PLAYER1_SIZE_Y,
                     PLAYER2_SIZE_X, PLAYER2_SIZE_Y, SECOND_PLAYER_PIXEL_DATA);
}

void initializeBubblesList(BubbleLinkedListItem** pBubblesListHead, int currentLevel) {
    *pBubblesListHead = NULL;

    if (currentLevel == 1) {
        // Add one bubble on the screen that is of "moderate size" (it has a horizontal velocity component)
        addBubbleToEndOfList(pBubblesListHead, createBubble(50, 50, 16, 1, 0));
    } else if (currentLevel == 2) {
        // Add two bubbles of the same size as before on the screen, with no horizontal velocity component
        addBubbleToEndOfList(pBubblesListHead, createBubble(50, 50, 16, 0, 0));
        addBubbleToEndOfList(pBubblesListHead, createBubble(SCREEN_SIZE_X - 50, 50, 16, 0, 0));
    } else if (currentLevel == 3) {
        // Add one bubble on the screen that is larger than the previous ones (it has a horizontal velocity component)
        addBubbleToEndOfList(pBubblesListHead, createBubble(50, 50, 32, 1, 0));
    } else {
        // Add two bubbles of the same size as before on the screen, only one of which has a horizontal velocity component
        addBubbleToEndOfList(pBubblesListHead, createBubble(50, 50, 32, 1, 0));
        addBubbleToEndOfList(pBubblesListHead, createBubble(SCREEN_SIZE_X - 50, 50, 32, 0, 0));
    }
}

Bubble* createBubble(int centerX, int centerY, int radius, int xVelocity, int yVelocity) {
    Bubble* newBubble = (Bubble*) malloc(sizeof(Bubble));
    newBubble->centerX = centerX;
    newBubble->centerY = centerY;
    newBubble->radius = radius;

    newBubble->xVelocity = xVelocity;
    newBubble->yVelocity = yVelocity;

    return newBubble;
}

void initializePlayer(Player** player, int x, int y, int sizeX, int sizeY, const int* pixelData) {
    *player = (Player*) malloc(sizeof(Player));
    (*player)->x = x;
    (*player)->y = y;
    (*player)->sizeX = sizeX;
    (*player)->sizeY = sizeY;

    (*player)->requestMoveLeft = false;
    (*player)->requestMoveRight = false;
    (*player)->requestShoot = false;

    (*player)->readyToShootArrow = true;
    (*player)->shootingArrow = (Arrow*) malloc(sizeof(Arrow));
    initializePlayerShootingArrow(*player);

    (*player)->score = 0;

    (*player)->playerPixelData = pixelData;
}

void initializePlayerShootingArrow(Player* player) {
    player->shootingArrow->x = player->x + (player->sizeX / 2) - (player->shootingArrow->sizeX / 2);
    player->shootingArrow->y = player->y;
    player->shootingArrow->sizeX = ARROW_SIZE_X;
    player->shootingArrow->sizeY = ARROW_SIZE_Y;
    player->shootingArrow->xVelocity = 0;
    player->shootingArrow->yVelocity = 0;
}

void updateGameState(BubbleLinkedListItem** pBubblesListHead, Player* player1, Player* player2) {
    BubbleLinkedListItem* current = *pBubblesListHead;

    while (current != NULL) {
        moveBubble(current->bubbleData);
        bounceBubbleOffScreen(current->bubbleData);

        if (checkBubblePlayerCollision(current->bubbleData, player1) ||
            checkBubblePlayerCollision(current->bubbleData, player2)) {
            gameOver = true;
            wasPlayerHit = true;
            break;
        }

        if (!player1->readyToShootArrow && checkArrowBubbleCollision(current->bubbleData, player1->shootingArrow)) {
            player1->score++; // Reward player1 for hitting the bubble

            // If the bubble is big enough to be broken further, split it into two bubbles
            if (current->bubbleData->radius > SMALLEST_BUBBLE_RADIUS) {
                breakBubble(current);
            }
                // Otherwise, simply destroy it
            else {
                removeBubbleFromList(pBubblesListHead, current->bubbleData);
                // If that was the last bubble, the game is over
                if (*pBubblesListHead == NULL) {
                    gameOver = true;
                    break;
                }
            }
            resetPlayerArrow(player1);
        }

        if (!player2->readyToShootArrow && checkArrowBubbleCollision(current->bubbleData, player2->shootingArrow)) {
            player2->score++; // Reward player2 for hitting the bubble

            // If the bubble is big enough to be broken further, split it into two bubbles
            if (current->bubbleData->radius > SMALLEST_BUBBLE_RADIUS) {
                breakBubble(current);
            }
                // Otherwise, simply destroy it
            else {
                removeBubbleFromList(pBubblesListHead, current->bubbleData);
                // If that was the last bubble, the game is over
                if (*pBubblesListHead == NULL) {
                    gameOver = true;
                    break;
                }
            }
            resetPlayerArrow(player2);
        }

        accelerateBubbleDown(current->bubbleData);

        current = current->next;
    }

    movePlayer(player1);
    movePlayer(player2);

    // If the player has shot the arrow (in which case, they aren't ready to shoot any more),
    // update the arrow and check for collisions with the top edge
    // (Note: collisions with a bubble are handled above)
    if (!player1->readyToShootArrow) {
        moveArrow(player1->shootingArrow);
        destroyPlayerArrowAtTop(player1);
    }

    if (!player2->readyToShootArrow) {
        moveArrow(player2->shootingArrow);
        destroyPlayerArrowAtTop(player2);
    }

    checkAndServicePlayerShootRequest(player1);
    checkAndServicePlayerShootRequest(player2);
}

void moveBubble(Bubble* bubble) {
    bubble->centerX += bubble->xVelocity;
    bubble->centerY += bubble->yVelocity;
}

void accelerateBubbleDown(Bubble* bubble) {
    bubble->yVelocity += GRAVITATIONAL_CONSTANT;
}

void bounceBubbleOffScreen(Bubble* bubble) {
    // Bounce the bubble off any of the four edges of the screen
    // In each bounce, two things are done:
    //
    // 1) "Push-back" is accounted for in the case that the bubble
    //    went too far past the boundary, by re-positioning it so that
    //    it just touches the boundary
    //
    // 2) A perfectly elastic bounce is performed (the velocity is simply
    //    flipped in direction but the magnitude is preserved)

    // Left edge
    if (bubble->centerX - bubble->radius <= 0) {
        bubble->centerX = bubble->radius;

        bubble->xVelocity *= -1;
    }

    // Right edge
    if (bubble->centerX + bubble->radius >= SCREEN_SIZE_X) {
        bubble->centerX = SCREEN_SIZE_X - bubble->radius;

        bubble->xVelocity *= -1;
    }

    // Top edge
    if (bubble->centerY - bubble->radius <= 0) {
        bubble->centerY = bubble->radius;

        accelerateBubbleDown(bubble);
        bubble->yVelocity *= -1;
    }

    // Bottom edge
    if (bubble->centerY + bubble->radius >= SCREEN_SIZE_Y) {
        bubble->centerY = SCREEN_SIZE_Y - bubble->radius;

        accelerateBubbleDown(bubble);
        bubble->yVelocity *= -1;
    }
}

void breakBubble(BubbleLinkedListItem* bubbleToBreakListItem) {
    // Break the bubble into two bubbles of equal size (the first of these bubbles
    // will overwrite the old one, and the second bubble will be added to the list
    // immediately after the first)

    Bubble* firstSplitBubble = bubbleToBreakListItem->bubbleData;

    // First duplicate the first bubble and add the copy immediately after it
    Bubble* secondSplitBubble =
            createBubble(firstSplitBubble->centerX, firstSplitBubble->centerY, firstSplitBubble->radius,
                         firstSplitBubble->xVelocity, firstSplitBubble->yVelocity);
    addBubbleAfter(bubbleToBreakListItem, secondSplitBubble);

    // 1) Half the size of both bubbles
    // 2) Push them a bit in opposite directions along the x-axis (to create some separation from each
    //    other after the split)
    // 3) Ensure that the two duplicates move in opposite directions along the x-axis after the split
    // 4) Give each of the broken bubbles a "bonus y-push" to award the player for the split (but only if it is moving down,
    //    fast enough, since if it is moving up and we push it further up, it will move faster than
    //    before (more kinetic energy) and that wouldn't be a bonus)

    if (firstSplitBubble->xVelocity == 0) {
        firstSplitBubble->xVelocity = 1;
    }
    firstSplitBubble->centerX += firstSplitBubble->xVelocity;
    firstSplitBubble->radius /= 2;
    if (firstSplitBubble->yVelocity >= - BONUS_Y_VELOCITY_AFTER_SPLIT) {
        firstSplitBubble->yVelocity += BONUS_Y_VELOCITY_AFTER_SPLIT;
    }

    if (secondSplitBubble->xVelocity == 0) {
        secondSplitBubble->xVelocity = -1;
    } else {
        secondSplitBubble->xVelocity = -secondSplitBubble->xVelocity;
    }
    secondSplitBubble->centerX += secondSplitBubble->xVelocity;
    secondSplitBubble->radius /= 2;
    if (secondSplitBubble->yVelocity >= - BONUS_Y_VELOCITY_AFTER_SPLIT) {
        secondSplitBubble->yVelocity += BONUS_Y_VELOCITY_AFTER_SPLIT;
    }
}

void moveArrow(Arrow* arrow) {
    arrow->x += arrow->xVelocity;
    arrow->y += arrow->yVelocity;
}

void checkAndServicePlayerShootRequest(Player* player) {
    // Only shoot if the player has requested to shoot, AND if
    // they are ready to do so (i.e. no currently active previous arrow)
    if (player->requestShoot && player->readyToShootArrow) {
        // Reposition the arrow to the new location
        player->shootingArrow->x = player->x + (player->sizeX / 2) - (player->shootingArrow->sizeX / 2);

        // Set it to start moving upwards
        player->shootingArrow->yVelocity = -ARROW_MOVE_SPEED;

        // Disallow any processing of further shooting requests as long as the current
        // arrow is still active
        player->readyToShootArrow = false;
    }
}

void destroyPlayerArrowAtTop(Player* player) {
    if (player->shootingArrow->y <= 0) {
        resetPlayerArrow(player);
    }
}

void resetPlayerArrow(Player* player) {
    initializePlayerShootingArrow(player);

    // Allow for the processing of subsequent (new) shooting requests
    player->readyToShootArrow = true;
}

void movePlayer(Player* player) {
    if (player->requestMoveLeft) {
        player->x -= PLAYER_MOVE_SPEED;

        // Constrain the player from moving off the screen (left edge)
        if (player->x < 0) {
            player->x = 0;
        }
    } else if (player->requestMoveRight) {
        player->x += PLAYER_MOVE_SPEED;

        // Constrain the player from moving off the screen (right edge)
        if (player->x + player->sizeX > SCREEN_SIZE_X) {
            player->x = SCREEN_SIZE_X - player->sizeX;
        }
    }
}

bool checkBubblePlayerCollision(Bubble* bubble, Player* player) {
    return (bubble->centerX + bubble->radius >= player->x) &&
           (bubble->centerX - bubble->radius <= player->x + player->sizeX) &&
           (bubble->centerY + bubble->radius >= player->y) &&
           (bubble->centerY - bubble->radius <= player->y + player->sizeY);
}

bool checkArrowBubbleCollision(Bubble* bubble, Arrow* arrow) {
    // Note: the y conditions are modified to ensure that
    // only the tops of arrows can hit bubbles

    return (bubble->centerX + bubble->radius >= arrow->x) &&
           (bubble->centerX - bubble->radius <= arrow->x + arrow->sizeX) &&
           (bubble->centerY + bubble->radius >= arrow->y) &&
           (bubble->centerY - bubble->radius <= arrow->y + arrow->sizeY);
}

void addBubbleToEndOfList(BubbleLinkedListItem** listHead, Bubble* bubbleToAdd) {
    if (listHead == NULL) {
        return;
    }

    // If the list is empty, insert the bubble at the beginning of the list
    if (*listHead == NULL) {
        *listHead = (BubbleLinkedListItem*) malloc(sizeof(BubbleLinkedListItem));
        (*listHead)->bubbleData = bubbleToAdd;
        (*listHead)->next = NULL;
        return;
    }

    BubbleLinkedListItem* currentListItem = *listHead;

    // Find the last element in the (non-empty) list
    while (currentListItem->next != NULL) {
        currentListItem = currentListItem->next;
    }

    // Add the bubble to the end of the list (after the last element found above)
    // inside a new BubbleLinkedListItem
    currentListItem->next = (BubbleLinkedListItem*) malloc(sizeof(BubbleLinkedListItem));
    currentListItem->next->bubbleData = bubbleToAdd;
    currentListItem->next->next = NULL;
}

void addBubbleAfter(BubbleLinkedListItem* beforeItemToAdd, Bubble* bubbleToAdd) {
    // If the list is empty, insert the bubble at the beginning of the list
    if (beforeItemToAdd == NULL) {
        return;
    }

    // Create a new BubbleLinkedListItem for the bubble that is to be added
    BubbleLinkedListItem* itemToAdd = (BubbleLinkedListItem*) malloc(sizeof(BubbleLinkedListItem));
    itemToAdd->bubbleData = bubbleToAdd;

    // Insert the new bubble item between the 'beforeItemToAdd' and whatever was after 'beforeItemToAdd'
    BubbleLinkedListItem* afterBubbleToAdd = beforeItemToAdd->next;
    beforeItemToAdd->next = itemToAdd;
    itemToAdd->next = afterBubbleToAdd;
}

void removeBubbleAtHead(BubbleLinkedListItem** plistHead) {
    BubbleLinkedListItem* listHead = *plistHead;
    if (listHead == NULL) {
        return;
    }

    // Remove the head from the list and update the list's head to point to the
    // next item in the list (which may or may not be NULL)
    *plistHead = listHead->next;

    // Free the memory allocated for the old list head
    free(listHead->bubbleData); // Free the bubble data at the old head
    listHead->bubbleData = NULL;
    listHead->next = NULL;
    free(listHead); // Free the old head list item
}

void removeBubbleAfter(BubbleLinkedListItem* beforeItemToDelete) {
    // If the specified bubble item doesn't exist, we don't need to do anything
    if (beforeItemToDelete == NULL) {
        return;
    }

    // If there is no item after the specified one, then we don't need to
    // delete anything
    BubbleLinkedListItem* itemToDelete = beforeItemToDelete->next;
    if (itemToDelete == NULL) {
        return;
    }

    // Remove the bubble from the list
    beforeItemToDelete->next = itemToDelete->next;

    // Free the memory allocated for the bubble list item
    free(itemToDelete->bubbleData); // Free the bubble data itself
    itemToDelete->bubbleData = NULL;
    itemToDelete->next = NULL;
    free(itemToDelete); // Free the list item
}

void removeBubbleFromList(BubbleLinkedListItem** listHead, Bubble* bubbleToRemove) {
    // If the list is empty, we don't need to do anything
    if (listHead == NULL) {
        return;
    }

    BubbleLinkedListItem* currentListItem = (*listHead);
    if (currentListItem == NULL) {
        return;
    }

    if (currentListItem->bubbleData == bubbleToRemove) {
        removeBubbleAtHead(listHead);
        return;
    }

    // Search the list for the bubble to remove
    while (currentListItem->next != NULL && currentListItem->next->bubbleData != bubbleToRemove) {
        currentListItem = currentListItem->next;
    }

    // Delete it using the pointer to the item before the one to delete
    removeBubbleAfter(currentListItem);
}
