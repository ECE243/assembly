#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

#define GRAVITATIONAL_CONSTANT -5

// Various data defining the state of a bubble that is bouncing across the screen
typedef struct bubble {
    int centerX, centerY;
    int radius;
    int xVelocity, yVelocity;
} Bubble;

/* Later, we will need to use a linked list

// An item in a singly-linked list of Bubble structs
struct bubbleLinkedListItem {
    Bubble* bubbleData;
    struct bubbleLinkedListItem* next;
};
typedef struct bubbleLinkedListItem* BubbleLinkedList;
// The list of all displayed bubbles
BubbleLinkedList* bubbles = NULL;
*/
// For now, an array of size 5 is okay for testing
Bubble bubbles[5];

typedef struct player {
    int x, y;
    int radius;
} Player;

//----------User Input Function Declarations------------
//------------------------------------------------------
void initializeInputIO();
void fetchInputs();

//-----------Graphics Function Declarations-------------
//------------------------------------------------------
void initializeGraphics();
void drawScreen();

volatile int pixel_buffer_start; // global variable
void clear_screen();
void waiting();
void draw_line(int x0, int y0, int x1, int y1, short int color);
void plot_pixel(int x, int y, short int line_color);
void circleBres(Bubble* bubble, short int color);

volatile int* const pixel_ctrl_ptr = (int*) 0xFF203020;


//-----------Game Logic Function Declarations-----------
//------------------------------------------------------
void initializeGame();
void updateGameState();

void moveBubble(Bubble* bubble);
void accelerateBubbleDown(Bubble* bubble);
void bounceBubbleOffScreen(Bubble* bubble);


int main(void) {
    initializeGraphics();
    initializeInputIO();
    initializeGame();

    while (1) {
        drawScreen();
        fetchInputs();
        updateGameState();
    }

    return 0;
}

//----------User Input Function Definitions-------------
//------------------------------------------------------
void initializeInputIO() {

}

void fetchInputs() {

}


//----------Graphics Function Definitions---------------
//------------------------------------------------------
void initializeGraphics() {
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
}

void drawScreen() {
    for (int i = 0; i < 5; i++) {
        circleBres(bubbles + i, 0x07E0);
    }

    waiting();

    for (int i = 0; i < 5; i++) {
        circleBres(bubbles + i, 0x0000);
    }
}

void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel(x, y, 0x0);
        }
    }
}

void circleBres(Bubble* bubble, short int color) {
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


void plot_pixel(int x, int y, short int line_color) {
    *(short int*) (pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void waiting() {
    volatile int* status = pixel_ctrl_ptr + 3;

    *pixel_ctrl_ptr = 1;

    while ((*status & 0x01) != 0) {
        status = status;
    }
}

//----------Game Logic Function Definitions-------------
//------------------------------------------------------
void initializeGame() {
    for (int i = 0; i < 5; i++) {
        bubbles[i].centerX = 50 * i;
        bubbles[i].centerY = 50;
        bubbles[i].radius = 20;

        bubbles[i].xVelocity = 1;
        bubbles[i].yVelocity = -5;
    }
}

void updateGameState() {
    for (int i = 0; i < 5; i++) {
        moveBubble(bubbles + i);
        accelerateBubbleDown(bubbles + i);
        bounceBubbleOffScreen(bubbles + i);
    }
}

void moveBubble(Bubble* bubble) {
    bubble->centerX += bubble->xVelocity;
    bubble->centerY += bubble->yVelocity;
}

void accelerateBubbleDown(Bubble* bubble) {
    bubble->yVelocity -= GRAVITATIONAL_CONSTANT;
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
        bubble->yVelocity *= -1;
    }

    // Bottom edge
    if (bubble->centerY + bubble->radius >= SCREEN_SIZE_Y) {
        bubble->centerY = SCREEN_SIZE_Y - bubble->radius;
        bubble->yVelocity *= -1;
    }
}






