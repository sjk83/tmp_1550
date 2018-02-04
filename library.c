/***************************************
Written by stephen klein
for CS/COE 1550 project 1
****************************************/

//needed for nanosleep
#include <time.h>
//needed for terminal ioctl
#include <termios.h>
#include <sys/ioctl.h>
//ONLY HERE FOR DEBUGGING
//#include <stdio.h>
//posix stuffs
#include <unistd.h>
//includes for open/close
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//select stuffs
#include <sys/select.h>
//mmap stuff
#include <sys/mman.h>
#include <linux/fb.h>

typedef unsigned short color_t;
void throw_error(char *);

struct termios initial_term_settings;
color_t *screen;
size_t map_len;
int width;
int height;

void init_graphics(void){
//read terminal settings assuming /dev/tty
	int fd,i;
	struct termios new_term;
	struct fb_fix_screeninfo fixed_info;
	struct fb_var_screeninfo variable_info;
	off_t offset=0;
	fd = open("/dev/tty",O_RDWR);
	if(fd==-1){
		throw_error("tty open fail");
	}
	//reading term settings
	ioctl(fd, TCGETS, &initial_term_settings);
	new_term=initial_term_settings;
	//setting new term settings
	new_term.c_lflag &= ~ECHO;
	new_term.c_lflag &= ~ICANON;
	ioctl(fd,TCSETS,&new_term);
	close(fd);
	//opening and mapping fb0
	fd = open("/dev/fb0",O_RDWR);
	if(fd==-1){
		throw_error("open fb0 fail");
	}
	ioctl(fd,FBIOGET_VSCREENINFO,&variable_info);
	ioctl(fd,FBIOGET_FSCREENINFO,&fixed_info);
	//must divide line length by 2 to go from byte to pixel
	width=fixed_info.line_length/2;
	height=variable_info.yres_virtual;
	map_len=variable_info.yres_virtual*fixed_info.line_length;
	screen=(color_t *)mmap(NULL,map_len,PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
}

//cannot call throw_error from inside exit_graphics
void exit_graphics(void){
	int fd;
	munmap(screen,map_len);
	fd = open("/dev/tty",O_WRONLY);
	ioctl(fd,TCSETS,&initial_term_settings);
	close(fd);
}

void throw_error(char *str){
	int i=0;
	while(str[i]!='\0')
		write(1,&str[i++],1);
	write(1,"\n",2);
}

void clear_screen(void){
	//uses write() because that is a linux command, not stdio
	write(1,"\033[2J",6);
}

void sleep_ms(long ms){
	long i;
	struct timespec sleep_time;
	//must set tv_sec because maximum tv_nsec time is 1 second
	sleep_time.tv_sec=(int)(ms/1000);
	sleep_time.tv_nsec=(ms%1000)*1000000;
	nanosleep(&sleep_time, NULL);
}

char getkey(void){
	char c=0;
	fd_set rfds;
	struct timeval tv;
	int ret;
	//fd 0 = stdin?
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	tv.tv_sec=0;
	tv.tv_usec=0;
	ret = select(1, &rfds, NULL,NULL,&tv);
	if(ret == -1)
		throw_error("turds");
	else if(ret){
		read(STDIN_FILENO, &c, 1);
		return c;
	}else{
		return '\0';
	}
}

void draw_pixel(int x, int y, color_t color){
	if(x<width && y<height && x>=0 && y>=0)
		screen[x+y*width]=color;
}
void draw_rect(int x,int y,int w,int h, color_t color){
	int i;
	for(i=0;i<h*w;i++)
		draw_pixel(x+i%w,y+i/w,color);
}

void draw_circle(int x0, int y0, int radius, color_t color)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        draw_pixel(x0 + x, y0 + y,color);
        draw_pixel(x0 + y, y0 + x,color);
        draw_pixel(x0 - y, y0 + x,color);
        draw_pixel(x0 - x, y0 + y,color);
        draw_pixel(x0 - x, y0 - y,color);
        draw_pixel(x0 - y, y0 - x,color);
        draw_pixel(x0 + y, y0 - x,color);
        draw_pixel(x0 + x, y0 - y,color);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }

}
