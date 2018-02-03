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

color_t color_inc(){
	static color_t color;
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
	int i,j,k;
	color_t rect_color,text_color;
	char c,str[2];
	init_graphics();
	clear_screen();
	draw_rect(10,10,20,10,WHITE);
	while(getkey() != 'q');
	exit_graphics();
}
