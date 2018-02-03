/*************************************
written by stephen klein
driver program for my library.c file

compiles with: gcc -o name drv.c library.c
**************************************/

#define WHITE 0xffff
#define BLACK 0x0000
#define RED   0xf800
#define GYB   0x3a0b

typedef unsigned short color_t;

void draw_serpent(char new_dir){
	static char dir = 'd';

}

int main(int argc, char** argv){
	int i,j,k;
	color_t rect_color,text_color;
	char c,str[2];
	init_graphics();
	clear_screen();
	draw_circle(100,100,50,GYB);
	while(getkey() != 'q'){

	}
	exit_graphics();
}
