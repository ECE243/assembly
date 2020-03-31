#include <stdbool.h>
#include <stdlib.h>

int playerArray[] =
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x93, 0x05, 0x29, 0xa7, 0x62, 0x07, 0x8c, 0x67, 0x94,
         0xc4, 0x62, 0xa2, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0xe2, 0x28,
         0x27, 0x73, 0x08, 0xa5, 0x89, 0xd6, 0x89, 0xd6, 0xe9, 0xc5, 0x86, 0x73, 0xe1, 0x20, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x05, 0x21, 0x47, 0x94, 0xa9, 0xde, 0x0a, 0xe7, 0x0a, 0xe7, 0xea, 0xde,
         0xa8, 0xbd, 0xa4, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x83, 0xe5, 0x18, 0x07, 0x84,
         0xa9, 0xde, 0x2a, 0xe7, 0x0a, 0xe7, 0x0a, 0xe7, 0xa9, 0xbd, 0x04, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x10,
         0x48, 0x19, 0x20, 0x18, 0xef, 0x8b, 0x09, 0x6b, 0x69, 0x6b, 0x6a, 0x8c, 0x0a, 0xa5, 0xeb, 0xac, 0x08, 0x8c,
         0x64, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x22, 0x49, 0x07, 0x5a, 0x00, 0x00, 0x28, 0x19, 0x14, 0xad, 0x54, 0xbd, 0xe8, 0x8b, 0x2b, 0x73,
         0x4d, 0x6b, 0x0d, 0x6b, 0xef, 0x93, 0x28, 0x18, 0xe5, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x9b, 0xc7, 0x51, 0x8a, 0x19, 0x8b, 0x19,
         0x36, 0xa5, 0xd6, 0xcd, 0xa8, 0x8b, 0x0d, 0x9c, 0xb4, 0xdd, 0x53, 0xcd, 0xcd, 0x8b, 0x4c, 0x83, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x10,
         0x05, 0x6a, 0x08, 0xa3, 0x6a, 0x62, 0xac, 0x19, 0x30, 0x5b, 0xba, 0xde, 0x0e, 0x9c, 0xad, 0x93, 0x90, 0xb4,
         0x6f, 0xac, 0x4c, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x9a, 0x28, 0xb3, 0x0a, 0xe4, 0x0a, 0x93, 0xeb, 0x39,
         0xd7, 0xc5, 0xf2, 0xb4, 0x8d, 0x93, 0x2a, 0x8b, 0x24, 0x31, 0x6c, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x84, 0x49, 0xe7, 0xa2,
         0xa9, 0xcb, 0x0a, 0xec, 0xea, 0xdb, 0x29, 0x62, 0x6c, 0x4a, 0x2c, 0x7b, 0xa8, 0x8a, 0x08, 0xa3, 0xad, 0x8b,
         0x00, 0x00, 0x46, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x42, 0x08, 0x66, 0x82, 0x08, 0xab, 0xea, 0xe3, 0xea, 0xe3, 0xe7, 0xa2, 0xe7, 0x59, 0xa7, 0x41,
         0x27, 0x6a, 0xc7, 0x9a, 0x69, 0xbb, 0x49, 0xa3, 0x28, 0xab, 0x25, 0x72, 0x48, 0x5a, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa2, 0x28, 0xa7, 0x92, 0x89, 0xcb, 0xea, 0xdb,
         0xa9, 0xd3, 0xa9, 0xcb, 0x08, 0xab, 0x87, 0x8a, 0x25, 0x7a, 0x86, 0x8a, 0x08, 0xab, 0xa9, 0xd3, 0xeb, 0xc3,
         0xa8, 0x82, 0x6a, 0xa3, 0x44, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x83, 0x08, 0x06, 0x6a, 0x89, 0xcb, 0xca, 0xdb, 0x08, 0xab, 0xa9, 0xcb, 0x89, 0xc3, 0xa7, 0x92, 0x05, 0x72,
         0x43, 0x41, 0x66, 0x82, 0x49, 0xb3, 0x2e, 0xb4, 0x90, 0xb4, 0x6c, 0x8b, 0x65, 0x39, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x6a, 0xa6, 0x51, 0x67, 0x7a, 0x28, 0xb3, 0x69, 0xc3,
         0xaa, 0xcb, 0x28, 0xab, 0x87, 0x8a, 0x40, 0x28, 0x47, 0x62, 0x03, 0x31, 0x66, 0x82, 0xe9, 0x82, 0x4b, 0x83,
         0x2b, 0x7b, 0x07, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe5, 0x69,
         0x25, 0x7a, 0xa7, 0x92, 0xc7, 0x9a, 0x48, 0xb3, 0xaf, 0xc4, 0x70, 0xac, 0x70, 0xac, 0x2f, 0xa4, 0xa9, 0x62,
         0x84, 0x49, 0xa7, 0x92, 0x4b, 0x93, 0x00, 0x00, 0x69, 0x5a, 0xe7, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0xc4, 0x18, 0x64, 0x41, 0x26, 0x7a, 0x48, 0xbb, 0xea, 0xdb, 0x69, 0xc3, 0xab, 0xbb,
         0xd1, 0xcc, 0x73, 0xdd, 0xee, 0xa3, 0xc9, 0x82, 0xae, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x86, 0x31, 0x69, 0x5a,
         0xc6, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x18, 0x65, 0x41, 0x86, 0x8a,
         0x68, 0xc3, 0x0a, 0xec, 0x0a, 0xec, 0xa9, 0xcb, 0x89, 0xc3, 0x0c, 0xcc, 0xcb, 0xc3, 0xc9, 0xd3, 0xe7, 0xa2,
         0xea, 0xd3, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x06, 0x19, 0x68, 0x29, 0xea, 0x82, 0x29, 0xa3, 0xca, 0xd3, 0xea, 0xdb, 0xa7, 0x9a, 0x28, 0xb3,
         0x0a, 0xe4, 0x0a, 0xec, 0x0a, 0xec, 0xca, 0xdb, 0xe7, 0xa2, 0x11, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa7, 0x31, 0x67, 0x29, 0xc9, 0x31, 0xed, 0x62, 0xec, 0x6a,
         0xed, 0xab, 0x8a, 0xbb, 0x26, 0x7a, 0xa7, 0x9a, 0x48, 0xbb, 0x0a, 0xe4, 0x0a, 0xec, 0x0a, 0xec, 0xea, 0xdb,
         0x28, 0xa3, 0xc7, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x29,
         0x67, 0x21, 0xec, 0x6a, 0xd2, 0xbc, 0x8e, 0x7b, 0xcc, 0x5a, 0x4c, 0x7b, 0xa7, 0x92, 0xc5, 0x61, 0x86, 0x8a,
         0x28, 0xb3, 0xca, 0xdb, 0x0a, 0xec, 0x0a, 0xec, 0xca, 0xd3, 0x25, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x23, 0x31, 0x43, 0x00, 0xc7, 0x49, 0x6a, 0xbb, 0x2b, 0xec, 0x8e, 0xd4, 0x2c, 0x7b,
         0xee, 0x93, 0xa2, 0x18, 0x05, 0x6a, 0xe3, 0x20, 0x46, 0x82, 0xc7, 0xa2, 0x89, 0xcb, 0x0a, 0xe4, 0xea, 0xdb,
         0x08, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x31, 0x00, 0x00, 0x46, 0x7a, 0x69, 0xc3,
         0x0a, 0xec, 0x0a, 0xec, 0xea, 0xd3, 0x87, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x51, 0x69, 0xc3,
         0x05, 0x72, 0x08, 0xb3, 0xc9, 0xd3, 0xa9, 0xcb, 0xc7, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x03, 0x31, 0x87, 0x8a, 0x89, 0xcb, 0xea, 0xe3, 0x0a, 0xec, 0x0a, 0xe4, 0x89, 0xbb, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x29, 0x05, 0x72, 0x28, 0xb3, 0xc9, 0xdb, 0xca, 0xdb, 0x28, 0xb3,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x11, 0x23, 0x41, 0x28, 0xb3, 0xca, 0xdb, 0xc9, 0xd3, 0x48, 0xbb,
         0x08, 0xab, 0xe5, 0x69, 0x24, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x72,
         0xc7, 0x9a, 0x48, 0xbb, 0xa9, 0xd3, 0x48, 0xb3, 0x00, 0x00, 0x00, 0x00, 0x49, 0x11, 0xc7, 0x08, 0x4a, 0x52,
         0x4a, 0xa3, 0xa9, 0xd3, 0x89, 0xc3, 0x46, 0x82, 0x41, 0x10, 0x66, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0x61, 0xc6, 0x51, 0x4b, 0x83, 0x0c, 0x7b, 0xe7, 0x08, 0x00, 0x00,
         0x00, 0x00, 0x08, 0x11, 0x28, 0x11, 0x0b, 0x3a, 0x4d, 0x7b, 0xa7, 0x8a, 0xc7, 0x9a, 0xc5, 0x59, 0x43, 0x49,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x59, 0xc6, 0x10,
         0xa9, 0x29, 0xaa, 0x29, 0x07, 0x11, 0x06, 0x19, 0x21, 0x08, 0x6a, 0x19, 0x8b, 0x19, 0x49, 0x11, 0x28, 0x19,
         0x02, 0x00, 0x31, 0xff, 0xe5, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x10, 0x28, 0x11, 0x6a, 0x11, 0x6a, 0x19, 0x65, 0x00, 0x11, 0xcd,
         0x49, 0x11, 0xac, 0x19, 0x6a, 0x19, 0x42, 0x00, 0xc5, 0x10, 0x41, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x10, 0x6b, 0x19,
         0xac, 0x19, 0xab, 0x21, 0xec, 0x62, 0xca, 0x6a, 0x28, 0x11, 0x8c, 0x52, 0x8e, 0x83, 0x0b, 0x73, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0xe6, 0x10, 0x28, 0x11, 0x6a, 0x19, 0x6a, 0x19, 0x6b, 0x4a, 0xea, 0x39, 0xe6, 0x10,
         0xc9, 0x31, 0x6b, 0x4a, 0x49, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x19, 0xff, 0xff, 0x00, 0x10,
         0xa5, 0x08, 0x24, 0x00, 0x45, 0x00,};

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

#define GRAVITATIONAL_CONSTANT 1

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
    int sizeX, sizeY;
} Player;

// TODO: Temporary.. will add a linked list for this shortly
Player player1;

//----------User Input Function Declarations------------
//------------------------------------------------------
void initializeInputIO();
void fetchInputs();

//-----------Graphics Function Declarations-------------
//------------------------------------------------------
void initializeGraphics();
void drawScreen(BubbleLinkedListItem* bubbleListHead);
void drawPlayerStruct(Player player1);
volatile int pixel_buffer_start; // global variable
void clear_screen();
void waiting();
void draw_line(int x0, int y0, int x1, int y1, short int color);
void drawPlayerStruct(Player player1);
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
bool checkBubblePlayerCollision(Bubble* bubble, Player* player);

bool gameOver = false;

int main(void) {
    initializeGraphics();
    initializeInputIO();
    // The list of all displayed bubbles
    BubbleLinkedListItem* bubblesListHead = initializeGame();

    while (!gameOver) {
        drawScreen(bubblesListHead);
        fetchInputs();
        drawPlayerStruct(player1);
        updateGameState(bubblesListHead);
    }

    return 0;
}

//----------User Input Function Definitions-------------
//------------------------------------------------------
void initializeInputIO() {
    volatile int* keys = 0xFF200050;
    volatile int* LEDRpointer = 0xFF200000;
    volatile int* switches = 0xFF200040;
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
void drawPlayerStruct(Player player1) {
    int x = SCREEN_SIZE_X / 2 - 11;
    int y = SCREEN_SIZE_Y - 30;
    player1.x = SCREEN_SIZE_X / 2 - 11;
    player1.y = SCREEN_SIZE_Y - 30;
    player1.sizeX = 22;
    player1.sizeY = 30;

    for (int array = 0; array < player1.sizeX * 2 * player1.sizeY - 1; array += 2) {


        int red = ((playerArray[array + 1] & 0xF8) >> 3) << 11;
        int green = (((playerArray[array] & 0xE0) >> 5)) | ((playerArray[array + 1] & 0x7) << 3);

        int blue = (playerArray[array] & 0x1f);

        short int playerColor = red | ((green << 5) | blue);

        plot_pixel(x, y, playerColor);

        x += 1;
        if (x ==  player1.x + player1.sizeX) {
            x = player1.x;
            y += 1;
        }

    }

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

    for (int i = 0; i < 1; i++) {
        Bubble* bubbleToAdd = malloc(sizeof(Bubble));
        bubbleToAdd->centerX = 50 * (i + 1);
        bubbleToAdd->centerY = 50;
        bubbleToAdd->radius = 20;

        bubbleToAdd->xVelocity = 1;
        bubbleToAdd->yVelocity = 0;

        addBubbleToList(&bubblesListHead, bubbleToAdd);
    }

    player1.x = SCREEN_SIZE_X / 2 - 10;
    player1.y = SCREEN_SIZE_Y - 20;
    player1.sizeX = 20;
    player1.sizeY = 40;

    return bubblesListHead;
}

void updateGameState(BubbleLinkedListItem* bubbleListHead) {
    while (bubbleListHead != NULL) {
        moveBubble(bubbleListHead->bubbleData);
        bounceBubbleOffScreen(bubbleListHead->bubbleData);

        if (checkBubblePlayerCollision(bubbleListHead->bubbleData, &player1)) {
            gameOver = true;
            break;
        }

        accelerateBubbleDown(bubbleListHead->bubbleData);

        bubbleListHead = bubbleListHead->next;
    }
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
        bubble->yVelocity *= -1;
    }

    // Bottom edge
    if (bubble->centerY + bubble->radius >= SCREEN_SIZE_Y) {
        bubble->centerY = SCREEN_SIZE_Y - bubble->radius;
        bubble->yVelocity *= -1;
    }
}

bool checkBubblePlayerCollision(Bubble* bubble, Player* player) {
    return (bubble->centerX + bubble->radius >= player->x) &&
           (bubble->centerX - bubble->radius <= player->x + player->sizeX) &&
           (bubble->centerY + bubble->radius >= player->y) &&
           (bubble->centerY - bubble->radius <= player->y + player->sizeY);
}





