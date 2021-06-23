#include <iostream>
#include <cstdio>
#include <string>
#include <window.h>
#include <random>
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


char edgeMap[20][56] = { 
	{"1111111111111111111111111111111111111111111111111111111"}, 
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},  
	{"1000000000000000000000000000000000000000000000000000001"}, 
	{"1000000000000000000000000000000000000000000000000000001"},  
	{"1000000000000000000000000000000000000000000000000000001"}, 
	{"1000000000000000000000000000000000000000000000000000001"}, 
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000000000001"},
    {"1111111111111111111111111111111111111111111111111111111"}
};


char upMap[7][16] {
    {"##   ##  ###### "},
    {"##   ##   ##  ##"},
    {"##   ##   ##  ##"},
    {"##   ##   ##### "},
    {"##   ##   ##    "},
    {"##   ##   ##    "},
    {" #####   ####   "},
};


char downMap[7][34] {
    {"#####     #####   ##   ##  ##   ##"},
    {" ## ##   ##   ##  ##   ##  ###  ##"},
    {" ##  ##  ##   ##  ##   ##  #### ##"},
    {" ##  ##  ##   ##  ## # ##  ## ####"},
    {" ##  ##  ##   ##  #######  ##  ###"},
    {" ## ##   ##   ##  ### ###  ##   ##"},
    {"#####     #####   ##   ##  ##   ##"},
};


void init(); // initialize
void gotoxy(int, int); // set cursor to (x,y)
void setColor(int, int); // set color (for, back)

void gLoop(int); // 
void move(int*, int*, int, int, int*, int*); // x, y, _x, _y, key, playing
int keyControl(); // use "w,a,s,d" to move
void titleDraw(); // draw title
int menuDraw(); // draw menu and return what you choice
int maplistDraw(); // 
void infoDraw(); // draw info
void drawMap(int*, int*); // 
void drawUI(int*, int*, int*); // 

int generateNumber(); // generate 4 digit unoverlap number




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
    setColor(white, white);
	printf("\n\n\n");   
	printf("       ######      ##    ##   ##  ######    #####   ##   ##   \n");
	printf("        ##  ##    ####   ###  ##   ##  ##  ##   ##  ### ###   \n");
	printf("        ##  ##   ##  ##  #### ##   ##  ##  ##   ##  #######   \n");
	printf("        #####    ######  ## ####   ##  ##  ##   ##  ## # ##   \n");
	printf("        ####     ##  ##  ##  ###   ##  ##  ##   ##  ##   ##   \n");
    printf("        ## ##    ##  ##  ##   ##   ##  ##  ##   ##  ##   ##   \n");    
    printf("       ###  ##   ##  ##  ##   ##  ######    #####   ##   ##   \n");
    setColor(white, black);
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


int menuDraw(){
	int x = 24; 
	int y = 12;
	gotoxy(x-2, y);   
	printf("> game start");
	gotoxy(x, y+1);
	printf("game info");
	gotoxy(x, y+2);
	printf(" exit ");
	while(1) {   
		int n = keyControl();
		switch(n) {
			case UP: { 
				if(y > 12){ 
					gotoxy(x-2, y); 
					printf(" ");   
					gotoxy(x-2, --y);   
					printf(">");  
				}
				break;
			}
				
			case DOWN: { 
				if(y < 14) {  
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case SUBMIT: {
				return y-12;
			}
		}
	}
} 


void drawMap(int* x, int* y){
	system("cls");
	int h, w; // ����, ����  
	
	for(h=0; h<14; h++){ // ���α��̱���  
		for(w=0; w<56; w++){ // ���α��̱���  
			char temp = tempMap[h][w]; // �ӽ������� �� ������  
			if(temp == '0'){ // �� ����(����)
				setColor(black, black);  
				printf(" "); 
			} else if(temp == '1') { // ��(#)
				setColor(white, white);  
				printf("#"); 
			} else if(temp == 's') { // �÷��̾�(@) 
				*x = w; // �÷��̾� ��ǥ�� ����  
				*y = h;
				setColor(cyan, black);  
				printf("@");
			} else if(temp == 'q') { // ������(O)
				setColor(lightgreen, black);    
				printf("O"); 
			} else if(temp == 'k') { // ����(*) 
				setColor(yellow, black);
				printf("*"); 
			} else if(temp == 'l') { // ��� ��(+) 
				setColor(brown, black);
				printf("+");
			}
		}
		printf("\n"); // ���� �� ��������� ��ĭ �ٹٲ�  
	}
	setColor(white, black); // �ٽ� �⺻ �������� ���ƿ��� 
} 


vector<int> generateNumber() {
    random_device rd; 
    mt19937_64 mt(rd());
    uniform_int_distribution<int> range(0, 9);

    vector<int> v(4);
    v[0] = range(mt);
    v[1] = range(mt);

    while(1) {
        if(v[1]==v[0]) v[1] = range(mt); 
        else break;
    }

    v[2] = range(mt);

    while(1) {
        if(v[2]==v[0] || v[2]==v[1]) v[2] = range(mt);
        else break;
    }

    v[3] = range(mt);

    while(1) {
        if(v[3]==v[0] || v[3]==v[1] || v[3]==v[2]) v[3] = range(mt);
        else break;
    }

    return v;
}


void upDownLoop() {
    int playing = 1;

    while(playing) {

    }
}



// -------------------------------------------------------------------------------------------------


/*
char tempMap[14][56]; // �� �ӽ������� �迭  
char map1[14][56] = { // �����  
	// ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56��  
	{"1111111111111111111111111111111111111111111111111111111"}, // ���� ���̿� ���߾� 14��   
	{"1000000010000000000000000000000000000000000000000000001"},
	{"1000000010000000000000000000000000000000000000000000001"}, // 0 : �� ���� 
	{"1000100010000000000000000000000000000000000000000000001"}, // 1 : �� 
	{"1000100010000000000000000000000000000000000000000000001"}, // k : ���� 
	{"1000100010000000000000000000000000000000000000000000001"}, // l : ��� �� 
	{"1000100011111100000000000000000000000000000000000000001"}, // q : Ż�ⱸ  
	{"1000100000000100000000000000000000000000000000000000001"},
	{"1000100010000100000000000000000000000000000000000000001"},
	{"10001000100k0100000000000000000000000000000000001111111"},
	{"1000100010000100000000000000000000000000000000001000001"},
	{"10s010001111111111111111111111111111111111111111100q001"},
	{"10001000l0000000000000000000000000000000000000000000001"},
	{"1111111111111111111111111111111111111111111111111111111"}
};
char map2[14][56] = { // ������  
	// ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56��  
	{"1111111111111111111111111111111111111111111111111111111"}, // ���� ���̿� ���߾� 14��   
	{"100000100010001k000100000000001000100000100010100010001"},
	{"1000001010101011110101111101101010101110101010101000101"},
	{"1000101010001000k10101000101k01010101k10101000111111101"},
	{"1000100010111111110101010101111000100010101111100000001"},
	{"100011111l100000000101010100000001110110101000101011111"},
	{"1000100000101111111101010111011100000010001010001010001"},
	{"1000101111101000000001010000000111011010100010100010001"},
	{"10001010000010000001010110111100000000101010101010001l1"},
	{"10001010111010000001000000000101011110101010101011111l1"},
	{"100010101k001000000111101111000100001010101010001000001"},
	{"10s010101111111110110010100001011110100010111110100q001"},
	{"1000100000l000l0001000100011110000001010100000001000001"},
	{"1111111111111111111111111111111111111111111111111111111"}
};
  
void drawMap(int* x, int* y){
	system("cls");
	int h, w; // ����, ����  
	
	for(h=0; h<14; h++){ // ���α��̱���  
		for(w=0; w<56; w++){ // ���α��̱���  
			char temp = tempMap[h][w]; // �ӽ������� �� ������  
			if(temp == '0'){ // �� ����(����)
				setColor(black, black);  
				printf(" "); 
			} else if(temp == '1') { // ��(#)
				setColor(white, white);  
				printf("#"); 
			} else if(temp == 's') { // �÷��̾�(@) 
				*x = w; // �÷��̾� ��ǥ�� ����  
				*y = h;
				setColor(cyan, black);  
				printf("@");
			} else if(temp == 'q') { // ������(O)
				setColor(lightgreen, black);    
				printf("O"); 
			} else if(temp == 'k') { // ����(*) 
				setColor(yellow, black);
				printf("*"); 
			} else if(temp == 'l') { // ��� ��(+) 
				setColor(brown, black);
				printf("+");
			}
		}
		printf("\n"); // ���� �� ��������� ��ĭ �ٹٲ�  
	}
	setColor(white, black); // �ٽ� �⺻ �������� ���ƿ��� 
} 
// ���� ����  
void gLoop(int mapCode){
	int x, y; // �÷��̾� ��ǥ ���� ���� ����(x, y) 
	int key = 0; // ���� ���� ���庯��  
	
	int playing = 1; // 1�̸� ������, 0�̸� ���� ����  
	
	// mapNumber�� 0�̸� �����, 1�̸� ������, 2�̸�..
	//(�߰��ϽǺ��� �Ʒ��� ���� ������� �߰��Ͻø� �˴ϴ�)
	if(mapCode == 0){
		memcpy(tempMap, map1, sizeof(tempMap));
	} else if(mapCode == 1){
		memcpy(tempMap, map2, sizeof(tempMap));
	} // else if(...)
	
	drawMap(&x, &y); // �� ���� �� ��� 
	// �ʿ� ��ǥ �����͸� ����  
	
	// ���� ����  
	while(playing){
		drawUI(&x, &y, &key);
		
		switch(keyControl()){
			case UP:
				move(&x, &y, 0, -1, &key, &playing); // ����x, ����y, x�������� �̵��� ĭ, y�������� �̵��� ĭ  
				break;
				
			case DOWN:
				move(&x, &y, 0, 1, &key, &playing); // x��ġ�� �״��, y��ġ�� +1 (�Ʒ���) 
				break;
				
			case RIGHT:
				move(&x, &y, 1, 0, &key, &playing); // x��ġ�� +1, y�� �״��(������) 
				break;
				
			case LEFT:
				move(&x, &y, -1, 0, &key, &playing); // x��ġ�� -1, y�� �״��(����) 
				break;
				
			case SUBMIT:
				playing = 0; // 0�� �Ǹ� �ݺ� ����  
		} 
	}
	gotoxy(22, 8);
	printf("Game Clear!");
	Sleep(1500);
}
// �÷��̾� ��ǥ�� ������ �Լ�  
// ���� ��ǥ (x, y), ������ ��ǥ(_x, _y) 
void move(int* x, int* y, int _x, int _y, int* key, int* playing){
	// �̵��� ��ġ�� �ִ� �� �迭�� ���� �ӽ�����  
	char mapObject = tempMap[*y + _y][*x + _x];
	setColor(white, black); // �� �⺻��  
	
	if(mapObject == '0') {
		gotoxy(*x, *y);
		printf(" "); // ����� 
		
		setColor(cyan, black); // �� ����  
		gotoxy(*x + _x, *y + _y); // ������ ��ġ�� �̵� �� �÷��̾� ���  
		printf("@");
		
		*x += _x; // ���� ��ǥ������ �ݿ�  
		*y += _y;
	} else if(mapObject == 'k') { // �̵��� ��ġ�� ���谡 ������ ȹ��  
		*key += 1; // ���谹�� 1���� 
		tempMap[*y + _y][*x + _x] = '0'; // ȹ���Ͽ����� ������ �ִ� k�� 0���� ���� 
		gotoxy(*x + _x, *y + _y); // ���谡 �ִ� ��ġ�� ����  
		printf(" ");
	} else if(mapObject == 'l') {
		if(*key > 0){
			*key -= 1; // ���� 1�� �Ҹ�  
			tempMap[*y + _y][*x + _x] = '0'; // ���� �������� l �����͸� 0���� ����  
			setColor(white, black); // �� �⺻��  
			gotoxy(*x + _x, *y + _y);
			printf(" ");
		}
	} else if(mapObject == 'q') {
		*playing = 0; // 1: ���� ���� ��, 0: ���� ����  
	}
} 
// ���� �ϴܿ� ��ǥ �� ������ ���� ���  
void drawUI(int* x, int* y, int* key){
	setColor(white, black); // �� �⺻�� 
	gotoxy(3, 16);
	printf("��ġ: %02d, %02d", *x, *y); // x, y �� ��� 
	
	setColor(yellow, black);
	gotoxy(34, 16); 
	printf("����: %d��", *key);
}
int keyControl(){
	char temp = getch();
	
	if(temp == 'w' || temp == 'W'){
		return UP;
	} else if(temp == 'a' || temp == 'A'){
		return LEFT;
	} else if(temp == 's' || temp == 'S'){
		return DOWN;
	} else if(temp == 'd' || temp == 'D'){
		return RIGHT;
	} else if(temp == ' '){   
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
int menuDraw(){
	int x = 24; 
	int y = 12;
	gotoxy(x-2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("> ���ӽ���");
	gotoxy(x, y+1);
	printf("��������");
	gotoxy(x, y+2);
	printf("  ����  ");
	while(1){ // ���ѹݺ�  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch(n){
			case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w) 
				if(y > 12){ // y�� 12~14������ �̵�  
					gotoxy(x-2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
					printf(" "); // ���� ��ġ�� �����  
					gotoxy(x-2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
					printf(">"); // �ٽ� �׸���  
				}
				break;
			}
				
			case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s) 
				if(y < 14) { // �ִ� 14  
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case SUBMIT: {
				return y-12; // �����̽���(����)�Ǿ��� ��� y-12
				// y ���� ��ġ�� 12�����Ƿ� y-12 �� �ϸ� 0, 1, 2 �� ���ڸ� ���� �� �ִ�. 
			}
		}
	}
} 
int maplistDraw(){
	int x = 24;
	int y = 6;
	system("cls"); // ȭ�� ��� �����  
	printf("\n\n");
	printf("                      [ �� ���� ]\n\n");
	
	gotoxy(x-2, y);
	printf("> ����");
	gotoxy(x, y+1);
	printf("�����"); 
	gotoxy(x, y+2);
	printf("�ڷ�"); 
	
	while(1){  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch(n){
			case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w) 
				if(y > 6){ // y�� 6~9������ �̵�  
					gotoxy(x-2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
					printf(" "); // ���� ��ġ�� �����  
					gotoxy(x-2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
					printf(">"); // �ٽ� �׸���  
				}
				break;
			}
				
			case DOWN: {  
				if(y < 9) {   
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case SUBMIT: {
				return y-6; 
			}
		}
	}
}
void infoDraw(){
	system("cls");  
	printf("\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                    �̵�: W, A, S, D\n");
	printf("                    ����: �����̽���\n\n\n\n\n\n\n");
	printf("               ������: codevkr.tistory.com\n\n");
	printf("      �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");
	
	while(1){
		if(keyControl() == SUBMIT){
			break;
		}
	}
    return ;
}
