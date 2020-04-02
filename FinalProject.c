#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

#define SMALLEST_BUBBLE_RADIUS 4
#define GRAVITATIONAL_CONSTANT 1
#define BONUS_Y_VELOCITY_AFTER_SPLIT -6

#define ARROW_SIZE_X 10
#define ARROW_SIZE_Y 10
#define ARROW_MOVE_SPEED 7

#define PLAYER_SIZE_X 22
#define PLAYER_SIZE_Y 30
#define PLAYER_MOVE_SPEED 3

#define PLAYER1_MOVE_LEFT_KEYBOARD_CODE 0x1C
#define PLAYER1_MOVE_RIGHT_KEYBOARD_CODE 0x23
#define PLAYER1_SHOOT_KEYBOARD_CODE 0x1D
#define PLAYER2_MOVE_LEFT_KEYBOARD_CODE 0x6B
#define PLAYER2_MOVE_RIGHT_KEYBOARD_CODE 0x74
#define PLAYER2_SHOOT_KEYBOARD_CODE 0x75

const int playerArray[] =
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
         0xa5, 0x08, 0x24, 0x00, 0x45, 0x00};

const int arrowArray[] =
        {0x00, 0x00, 0x82, 0x41, 0xf2, 0xcd, 0xb6, 0xe6, 0xa8, 0x8b, 0x00, 0x00, 0x60, 0x10, 0xb4, 0xe6, 0xff, 0xff,
         0xff, 0xff, 0xfe, 0xff, 0xc5, 0x6a, 0xe2, 0x49, 0xfd, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0x8f, 0xc5,
         0x81, 0x41, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0c, 0xb5, 0x00, 0x41, 0xaf, 0xee, 0xff, 0xff,
         0xff, 0xff, 0xfb, 0xff, 0xc3, 0x72, 0x00, 0x00, 0x20, 0x62, 0x52, 0xff, 0xfa, 0xff, 0xc5, 0xc4, 0x00, 0x08,
         0x00, 0x00, 0x00, 0x00, 0xa0, 0x9b, 0x43, 0xee, 0x40, 0x18, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x01, 0x73,
         0x81, 0xbc, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x41, 0x40, 0x6a, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00};

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
    while (currentListItem->next != NULL && currentListItem->next->bubbleData != bubbleToRemove) {
        currentListItem = currentListItem->next;
    }

    removeBubbleAfter(currentListItem);
}

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

    bool readyToShootArrow;
    Arrow* shootingArrow;
} Player;

//----------User Input Function Declarations------------
//------------------------------------------------------
void initializeInputIO();
void fetchInputs(Player* player1, Player* player2);

void setTimer();

volatile int* const LEDR_PTR = (int*) 0xFF200000;
volatile int* const SW_PTR = (int*) 0xFF200040;
volatile int* const KEY_PTR = (int*) 0xFF200050;
volatile int* const PS2_PTR = (int*) 0xFF200100;

//-----------Graphics Function Declarations-------------
//------------------------------------------------------
void initializeGraphics();
void drawScreen(const BubbleLinkedListItem* bubbleListHead, const Player* player1, const Player* player2);
void clear_screen();

void waiting();

void plot_pixel(int x, int y, short int line_color);
void drawLine(int x0, int y0, int x1, int y1, short int color);
void drawPlayer(const Player* player, bool erase);
void drawArrow(const Arrow* arrow, bool erase);
void drawBubble(const Bubble* bubble, short int color);

volatile int pixel_buffer_start; // global variable
volatile int* const pixel_ctrl_ptr = (int*) 0xFF203020;

//-----------Game Logic Function Declarations-----------
//------------------------------------------------------
void initializeGame(BubbleLinkedListItem** pBubblesListHead, Player** player1, Player** player2);
void updateGameState(BubbleLinkedListItem** pBubblesListHead, Player* player1, Player* player2);

void initializeBubblesList(BubbleLinkedListItem** pBubblesListHead);
Bubble* createBubble(int centerX, int centerY, int radius, int xVelocity, int yVelocity);

void initializePlayer(Player** player, int x, int y);
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

int main(void) {
    initializeGraphics();
    initializeInputIO();

    // The list of all the bouncing bubbles
    BubbleLinkedListItem* bubblesListHead;
    // Pointers to the player objects for the (up to) 2 players
    Player* player1;
    Player* player2;

    initializeGame(&bubblesListHead, &player1, &player2);

    while (!gameOver) {
        drawScreen(bubblesListHead, player1, player2);
        setTimer();
        fetchInputs(player1, player2);
        updateGameState(&bubblesListHead, player1, player2);
    }

    return 0;
}

//----------User Input Function Definitions-------------
//------------------------------------------------------
void initializeInputIO() {
    // Enable the keyboard
    *PS2_PTR = 0xF4;

    // Wait for the acknowledgement
    while ((*PS2_PTR & 0xFF) != 0xFA) {
    }
}

void fetchInputs(Player* player1, Player* player2) {
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

void setTimer() {

    *LEDR_PTR = 0x0fff;

}

//----------Graphics Function Definitions---------------
//------------------------------------------------------
void initializeGraphics() {
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
}

void drawScreen(const BubbleLinkedListItem* bubbleListHead, const Player* player1, const Player* player2) {
    const BubbleLinkedListItem* currentListItem = bubbleListHead;
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
        int red = ((playerArray[array + 1] & 0xF8) >> 3) << 11;
        int green = (((playerArray[array] & 0xE0) >> 5)) | ((playerArray[array + 1] & 0x7) << 3);

        int blue = playerArray[array] & 0x1f;
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
        int red = ((arrowArray[array + 1] & 0xF8) >> 3) << 11;
        int green = (((arrowArray[array] & 0xE0) >> 5)) | ((arrowArray[array + 1] & 0x7) << 3);

        int blue = (arrowArray[array] & 0x1f);
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
void initializeGame(BubbleLinkedListItem** pBubblesListHead, Player** player1, Player** player2) {
    initializeBubblesList(pBubblesListHead);

    initializePlayer(player1, (SCREEN_SIZE_X / 3) - (PLAYER_SIZE_X / 2), SCREEN_SIZE_Y - PLAYER_SIZE_Y);
    initializePlayer(player2, 2 * (SCREEN_SIZE_X / 3) - (PLAYER_SIZE_X / 2), SCREEN_SIZE_Y - PLAYER_SIZE_Y);
}

void initializeBubblesList(BubbleLinkedListItem** pBubblesListHead) {
    *pBubblesListHead = NULL;

    for (int i = 0; i < 1; i++) {
        addBubbleToEndOfList(pBubblesListHead, createBubble(50 * (i + 1), 50, 32, 1, 0));
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

void initializePlayer(Player** player, int x, int y) {
    *player = (Player*) malloc(sizeof(Player));
    (*player)->x = x;
    (*player)->y = y;
    (*player)->sizeX = PLAYER_SIZE_X;
    (*player)->sizeY = PLAYER_SIZE_Y;

    (*player)->requestMoveLeft = false;
    (*player)->requestMoveRight = false;
    (*player)->requestShoot = false;

    (*player)->readyToShootArrow = true;
    (*player)->shootingArrow = (Arrow*) malloc(sizeof(Arrow));
    initializePlayerShootingArrow(*player);
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
            break;
        }

        if (!player1->readyToShootArrow && checkArrowBubbleCollision(current->bubbleData, player1->shootingArrow)) {
            if (current->bubbleData->radius > SMALLEST_BUBBLE_RADIUS) {
                breakBubble(current);
            }
            else {
                removeBubbleFromList(pBubblesListHead, current->bubbleData);
                if (*pBubblesListHead == NULL) {
                    gameOver = true;
                    break;
                }
            }
            resetPlayerArrow(player1);
        }

        if (!player2->readyToShootArrow && checkArrowBubbleCollision(current->bubbleData, player2->shootingArrow)) {
            if (current->bubbleData->radius > SMALLEST_BUBBLE_RADIUS) {
                breakBubble(current);
            }
            else {
                removeBubbleFromList(pBubblesListHead, current->bubbleData);
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
    Bubble* secondSplitBubble = createBubble(firstSplitBubble->centerX, firstSplitBubble->centerY, firstSplitBubble->radius,
                                             firstSplitBubble->xVelocity, firstSplitBubble->yVelocity);
    addBubbleAfter(bubbleToBreakListItem, secondSplitBubble);

    // 1) Half the size of both bubbles
    // 2) Push them a bit in opposite directions along the x-axis (to create some separation from each
    //    other after the split)
    // 3) Ensure that the two duplicates move in opposite directions along the x-axis after the split
    // 4) Give each bubble a "bonus y-push" to award the player for the split

    firstSplitBubble->centerX += firstSplitBubble->xVelocity;
    firstSplitBubble->radius /= 2;
    firstSplitBubble->yVelocity += BONUS_Y_VELOCITY_AFTER_SPLIT;

    secondSplitBubble->centerX -= secondSplitBubble->xVelocity;
    secondSplitBubble->radius /= 2;
    secondSplitBubble->xVelocity = -secondSplitBubble->xVelocity;
    secondSplitBubble->yVelocity += BONUS_Y_VELOCITY_AFTER_SPLIT;

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
    return (bubble->centerX + bubble->radius >= arrow->x) &&
           (bubble->centerX - bubble->radius <= arrow->x + arrow->sizeX) &&
           (bubble->centerY + bubble->radius >= arrow->y) &&
           (bubble->centerY - bubble->radius <= arrow->y + arrow->sizeY);
}
