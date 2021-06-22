#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <window.h>
using namespace std;

// make moving macro
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 

// color table
enum {
	black,
	blue,
	green, 
	cyan, 
	red, 
	purple, 
	brown, 
	lightgray, 
	darkgray, 
	lightblue, 
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

void init(); 
void gotoxy(int, int); // set cursor to (x,y)
void setColor(int, int); // set color (for, back)

void gLoop(int);
void move(int*, int*, int, int, int*, int*); // x, y, _x, _y, key, playing
int keyControl(); // use "w,a,s,d" to move
void titleDraw(); // draw title
int menuDraw(); // draw menu and return what you choice
int maplistDraw(); // 
void infoDraw(); // draw info
void drawMap(int*, int*); // 
void drawUI(int*, int*, int*); // 






int main(void) {
    init();
	
    while(1) {
		titleDraw();
	
        int menuCode = menuDraw();
		if(menuCode == 0) {
			int n = maplistDraw();
			
			if(n == 0) {
				gLoop(0);  
			} 
            else if(n == 1) {
				gLoop(1); 
			} 
		} 
        else if(menuCode == 1) {
			infoDraw(); 
		} 
        else if(menuCode == 2) {
			return 0; 
		}
		system("cls");
		setColor(white, black); 
	}
}

void init() {
	system("mode con cols=56 lines=20 | title SUPER-RANDOM"); 
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0; 
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle , &ConsoleCursor);
}


void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
} 


void setColor(int forground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16; 
	SetConsoleTextAttribute(consoleHandle, code);
}


int keyControl() {
	char temp = getch();
	
	if(temp == 'w' || temp == 'W') {
		return UP;
	} else if(temp == 'a' || temp == 'A') {
		return LEFT;
	} else if(temp == 's' || temp == 'S') {
		return DOWN;
	} else if(temp == 'd' || temp == 'D') {
		return RIGHT;
	} else if(temp == ' ') {   
		return SUBMIT;
	}
}


void titleDraw(){
	printf("\n\n\n\n");   
	printf("       ######      ##    ##   ##  ######    #####   ##   ##   \n");
	printf("        ##  ##    ####   ###  ##   ##  ##  ##   ##  ### ###   \n");
	printf("        ##  ##   ##  ##  #### ##   ##  ##  ##   ##  #######   \n");
	printf("        #####    ######  ## ####   ##  ##  ##   ##  ## # ##   \n");
	printf("        ####     ##  ##  ##  ###   ##  ##  ##   ##  ##   ##   \n");
    printf("        ## ##    ##  ##  ##   ##   ##  ##  ##   ##  ##   ##   \n");    
    printf("       ###  ##   ##  ##  ##   ##  ######    #####   ##   ##   \n");
} 


void infoDraw(){
	system("cls");  
	printf("\n\n");
	printf("               SUUUUPER-RANDOM\n\n");
	printf("               move: W, A, S, D\n");
	printf("               select: spacebar\n\n\n\n\n\n\n");
	printf("               maker: Kim Seonghyeon\n\n");
	printf("               just for practice.");
	
	while(1){
		if(keyControl() == SUBMIT){
			break;
		}
	}
}
