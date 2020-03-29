#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

typedef struct bubble {
    int x, y;
    int radius;
} Bubble;

typedef struct player {
    int x, y;
    int radius;
} Player;

//----------User Input Function Declarations------------
//------------------------------------------------------
void fetchInputs();

//-----------Graphics Function Declarations-------------
//------------------------------------------------------
void drawScreen();

volatile int pixel_buffer_start; // global variable
void clear_screen();
void waiting();
void draw_line(int x0, int y0, int x1, int y1, short int color);
void plot_pixel(int x, int y, short int line_color);
void swap(int* a, int* b);


//-----------Game Logic Function Declarations-----------
//------------------------------------------------------
void updateGameState();


int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    int x=150;
	int y=100;
    int reverse=0;
    clear_screen();
    
    while(1){
        
        
         circleBres(x, y, 40,0x07E0);    //from 40 to 197
        waiting();
        circleBres(x, y, 40,0x0000);    //from 40 to 97
        
        if(reverse==0)
        {
            y+=1;
            if(y==197)
                reverse=1;
        }
        if(reverse==1)
        {
            y-=1;
            if(y==40)
                reverse=0;
        }
        
    }
    
    clear_screen();
    
    return 0;
}

//----------User Input Function Definitions-------------
//------------------------------------------------------
void fetchInputs() {

}


//----------Graphics Function Definitions---------------
//------------------------------------------------------

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel(x, y, 0x0);
        }
    }
}

void circleBres(int xc, int yc, int r, short int color)
{ 	short int colour = color;
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    plot_pixel(xc+x, yc+y, colour);
    plot_pixel(xc-x, yc+y, colour);
    plot_pixel(xc+x, yc-y, colour);
    plot_pixel(xc-x, yc-y, colour);
    plot_pixel(xc+y, yc+x, colour);
    plot_pixel(xc-y, yc+x, colour);
    plot_pixel(xc+y, yc-x, colour);
    plot_pixel(xc-y, yc-x, colour); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
    plot_pixel(xc+x, yc+y, colour);
    plot_pixel(xc-x, yc+y, colour);
    plot_pixel(xc+x, yc-y, colour);
    plot_pixel(xc-x, yc-y, colour);
    plot_pixel(xc+y, yc+x, colour);
    plot_pixel(xc-y, yc+x, colour);
    plot_pixel(xc+y, yc-x, colour);
    plot_pixel(xc-y, yc-x, colour); 
    } 
} 


void plot_pixel(int x, int y, short int line_color) {
    *(short int*) (pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void waiting() {
    volatile int* pixel_ctrl_ptr = 0xFF203020;
    volatile int* status = (int*) 0xFF20302C;

    *pixel_ctrl_ptr = 1;

    while ((*status & 0x01) != 0) {
        status = status;
    }
}


//----------Game Logic Function Definitions-------------
//------------------------------------------------------
void updateGameState() {

}




