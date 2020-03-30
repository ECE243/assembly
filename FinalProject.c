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

// An item in a singly-linked list of Bubble structs
typedef struct bubbleLinkedListItem {
    Bubble* bubbleData;
    struct bubbleLinkedListItem* next;
} BubbleLinkedListItem;

void addBubbleToList(BubbleLinkedListItem** listHead, Bubble* bubbleToAdd) {
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

void removeBubbleFromList(BubbleLinkedListItem* listHead, Bubble* bubbleToRemove) {
    if (listHead == NULL) {
        return;
    }

    if (listHead->bubbleData == bubbleToRemove) {
        removeBubbleAtHead(&listHead);
        return;
    }
    while (listHead->next != NULL && listHead->next->bubbleData != bubbleToRemove) {
        listHead = listHead->next;
    }

    removeBubbleAfter(listHead);
}

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
void drawScreen(BubbleLinkedListItem* bubbleListHead);

volatile int pixel_buffer_start; // global variable
void clear_screen();
void waiting();
void draw_line(int x0, int y0, int x1, int y1, short int color);
void plot_pixel(int x, int y, short int line_color);
void circleBres(Bubble* bubble, short int color);

volatile int* const pixel_ctrl_ptr = (int*) 0xFF203020;


//-----------Game Logic Function Declarations-----------
//------------------------------------------------------
BubbleLinkedListItem* initializeGame();
void updateGameState(BubbleLinkedListItem* bubbleListHead);

void moveBubble(Bubble* bubble);
void accelerateBubbleDown(Bubble* bubble);
void bounceBubbleOffScreen(Bubble* bubble);


int main(void) {
    initializeGraphics();
    initializeInputIO();
    // The list of all displayed bubbles
    BubbleLinkedListItem* bubblesListHead = initializeGame();

    while (1) {
        drawScreen(bubblesListHead);
        fetchInputs();
        updateGameState(bubblesListHead);
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

void drawScreen(BubbleLinkedListItem* bubbleListHead) {
    BubbleLinkedListItem* currentListItem = bubbleListHead;
    while (currentListItem != NULL) {
        circleBres(currentListItem->bubbleData, 0x07E0);
        currentListItem = currentListItem->next;
    }

    waiting();

    currentListItem = bubbleListHead;
    while (currentListItem != NULL) {
        circleBres(currentListItem->bubbleData, 0x0000);
        currentListItem = currentListItem->next;
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
BubbleLinkedListItem* initializeGame() {
    BubbleLinkedListItem* bubblesListHead = NULL;

    for (int i = 0; i < 5; i++) {
        Bubble* bubbleToAdd = malloc(sizeof(Bubble));
        bubbleToAdd->centerX = 50 * i;
        bubbleToAdd->centerY = 50;
        bubbleToAdd->radius = 20;

        bubbleToAdd->xVelocity = 1;
        bubbleToAdd->yVelocity = 0;

        addBubbleToList(&bubblesListHead, bubbleToAdd);
    }

    return bubblesListHead;
}

void updateGameState(BubbleLinkedListItem* bubbleListHead) {
    while (bubbleListHead != NULL) {
        moveBubble(bubbleListHead->bubbleData);
        accelerateBubbleDown(bubbleListHead->bubbleData);
        bounceBubbleOffScreen(bubbleListHead->bubbleData);
        bubbleListHead = bubbleListHead->next;
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






