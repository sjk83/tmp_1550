/*************************************
written by stephen klein
driver program for my library.c file

compiles with: gcc -o name drv.c library.c
**************************************/

#define WHITE 0xffff
#define BLACK 0x0000
#define RED   0xf800
#define GYB   0x3a0b

#include "stdio.h"

typedef unsigned short color_t;

color_t color_inc(){
	color_t color;
	static int i;
	if(i%6==1)
		color=0xf800;
	else if(i%6==2)
		color=0x001f;
	else if(i%6==3)
		color=0x07e0;
	else if(i%6==4)
		color=0xf81f;
	else if(i%6==5)
		color=0xffe0;
	else
		color=0x3a0b;
	i++;
	return color;
}

int main(int argc, char** argv){
	char c;
	int c_or_r = 0;
	int x=100,y=100,l=20,w=20,r=10;

	puts("\n\n\npress q to exit my stupid driver thing.");
	puts("c draws circles, r draws rectangles.");
	puts("a,s,w,d moves where the thing gets drawn.");
	puts("+ makes things bigger, - makes things smaller");
	sleep_ms(1000*5);
	puts("\n\npress b then enter to begin");
	while(getkey()!='b');

	init_graphics();
	clear_screen();
	c = 'r';

	while(c != 'q'){

		switch (c) {
			case 'c': c_or_r = 1;break;
			case 'r': c_or_r = 0;break;
			case '+': r++; l+=2; w+=2; break;
			case '-': r--; l-=2; w-=2; break;
			case 'a': x-=2; break;
			case 's': y+=2; break;
			case 'w': y-=2; break;
			case 'd': x+=2; break;
			default:  break;
		}
	  clear_screen();
		if(c_or_r){
			draw_circle(x+w/2,y+w/2,r,color_inc());
		}else{
			draw_rect(x,y,l,w,color_inc());
		}
		sleep_ms(1);
		c = getkey();
	}

	exit_graphics();
}
