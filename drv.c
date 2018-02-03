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
	draw_text(50,50,"screen cleared",WHITE);
	sleep_ms(1000);
	draw_text(50,80,"rectangle time",WHITE);
	sleep_ms(1000);
	//filling the screen with rectangle nonsense
	for(i=480;i>0;i-=10){
		draw_rect(0,0,160+i,i,color_inc());
	}
	draw_text(52,197,"rectangles seem to be working",BLACK);
	clear_screen();
	draw_text(50,197,"press q to exit program.",WHITE);
	draw_text(50,213,"press other keys...",WHITE);
	i=0;j=0;k=0;
	str[1]='\0';
	c=getkey();
	//dumb rectangle drawing, key getting, nonsense
	while(c!='q'){
		draw_rect(i,j,8,16,RED);
		c=getkey();
		sleep_ms(30);
		
		draw_rect(i,j,8,20,color_inc());
		str[0]=c;
		draw_text(i,j+2,str,WHITE);
		i+=8;
		if(i>=640){
			i=0;
			j+=20;
		}
		if(j>=480){
			clear_screen();
			j=0;
		}
	}
	exit_graphics();
}
