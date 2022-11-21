#include <iostream>
#include <stdlib.h>
//#include <unistd.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

//DIRECTION (MY OWN VARIABLE).....................
enum DIRECTION{	STOP=0,	LEFT, RIGHT, UP, DOWN };


//VARIABLES.......................................
int HX[50], HY[50], score, FX, FY, Tails, SPEED = 1;
const int WIDTH = 25, HEIGHT = 25;
bool GAME_OVER;
DIRECTION dir;

//Functions.......................................
void INTRO();
void SETTING();
void HELP();
void START();
void DRAW();
void ENTERY();
void UPDATE();
void CHECKER();
void SLEEP();

//GAME CONTROL CENTER.............................
int main() {
	INTRO();
	START();
	while(!GAME_OVER){
		SLEEP();
		ENTERY();
		UPDATE();
		DRAW();
		CHECKER();	
	}
}

void INTRO(){
	cout << "\t\tHEllo bro i am so sorry i quit on my programming but now i am back and "
		 << "am ready to create some programs still dumb program but I just wanted to get a complete grip "
		 << "of the game developement and their logics after that my target will be sdl i hope you are "
		 << "reading but never-mind!!!!!   :-)  \n";
	cout << "\t\tSNAKE GAME !!!!!!!!  \t\tPRESS ANY KEY TO CONTINUE!";
	getch();
	system("cls");
	cout << "\n\t\t\t\t\tRULES\n"
		 << "1) Please normally i know there are bugs but are not as so serious just play\n"
		 << "2) I know after giving it a try you will complain that its not good.\n"
		 << "3) you will notice some controlls are missing so shut up give it a try then delete it\n";
	cout << "\t\tpress any key to play it you mind\n";
	getch();
	bool exit = 0;
	do{
		system("cls");
		cout << "\t\t\t\tWELCOME TO THE SNAKE GAME(CONCOLE BASED)\n"
			 << "1)\tPLAY\n"
			 << "2)\tSETTING\n"
			 << "3)\tHELP/control\n"
			 << "4)\tExit\n"
			 << "Enter your Command: ";
		int choice;
		cin >> choice;
		switch(choice){
			case 1:
				GAME_OVER = false;
				exit = 1;
				break;
			case 2:
				SETTING();
				break;
			case 4:
				GAME_OVER = true;
				exit = 1;
				break;
			case 3:
				HELP();
		}
	}while(!exit);
}

void SETTING(){
	bool done = false;
	do{
		system("cls");
		cout << "HERE YOU CAN CONTOL SPEED:\n"
			 << "1)\tfast\n"
			 << "2)\tnormal\n"
			 << "3)\tslow\n";
			 int choice;
			 cin >> choice;
		switch(choice){
			case 1:
				done = true;
				SPEED = 100;
				break;
			case 2:
				done = true;
				SPEED = 50;
				break;
			case 3:
				done = true;
				SPEED = 1;
				break;
		}
	}while(!done);
}

void HELP(){
	system("cls");
	cout << "USE \n\t\t\tW\t\tA\t\tS\t\tD\nKEYS TO MOVE AND PRESS Q TO EXIT\n";
	getch();
}
//START...........................................
void START(){
	HX[0] = WIDTH / 2;
	HY[0] = HEIGHT / 2;
	FX = (rand() % WIDTH-1) + 1;
	FY = (rand() % HEIGHT-1) + 1;
	score = 0;
	dir = STOP;
	Tails = 1;
}

//DRAW............................................
void DRAW(){
	system("cls");
	cout << "\n\n\t\t\t\tScore : " << score << endl;
	//first row...
	cout << "\t\t\t";
	for(int i=0 ; i <= WIDTH ; i++)
		cout << "\xB1";
	cout << "\n";
	
	//middle section...
	for(int i=1 ; i<HEIGHT ; i++){
		for(int j=0 ; j<=WIDTH ; j++){
			if(j==0 || j==WIDTH){
				if(j==0)
					cout << "\t\t\t";
				cout << "\xB1";
			}
			else if(j==HX[0] && i==HY[0])
					cout << "\xE9";
				else if(j==FX && i==FY)
					cout << "\xFE";
				else{
					bool PRINT = 0;
					for(int x = Tails; x>0; x--){
						if(HX[x]==j && HY[x]==i){
							cout << "\xDB";
							PRINT=1;
							break;
						}
					}
					if(!PRINT)
						cout << " ";
				}
		}
		cout  << endl;
	}
	
	//last row...
	cout << "\t\t\t";
	for(int i=0 ; i <= WIDTH ; i++)
		cout << "\xB1";
	cout << "\n";
		
}

void ENTERY(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				if(dir!=LEFT && dir!=RIGHT)
					dir = LEFT;
				break;
			case 'd':
				if(dir!=LEFT && dir!=RIGHT)
					dir = RIGHT;
				break;
			case 'w':
				if(dir!=UP && dir!=DOWN)
					dir = UP;
				break;
			case 's':
				if(dir!=UP && dir!=DOWN)
				dir = DOWN;
				break;
			case 'q':
				GAME_OVER = true;
		}
	}
}

void UPDATE(){
	for (int i = Tails; i > 0; i--){
		HX[i] = HX[i - 1];
		HY[i] = HY[i - 1];
	}
	switch(dir){
		case UP:
			HY[0]--;
			break;
		case DOWN:
			HY[0]++;
			break;
		case LEFT:
			HX[0]--;
			break;
		case RIGHT:
			HX[0]++;
			break;
	}
}

void CHECKER(){
	if(HX[0]<=0 || HY[0] <=0 || HX[0]==WIDTH || HY[0]==HEIGHT)
		GAME_OVER = true;
	for(int i = 1; i<Tails; i++)
		if(HX[0]==HX[i] && HY[0]==HY[i])
			GAME_OVER = true;
	if(HX[0]==FX && HY[0]==FY){
		score+=10;
		Tails++;
		FX = (rand()%(WIDTH-1))+1;
		FY = (rand()%(HEIGHT-1))+1;
	}
}

void SLEEP(){
	Sleep(250/SPEED);
	if (dir == LEFT || dir == RIGHT)
  		Sleep(5*2/SPEED);
	Sleep(100*2/SPEED);
	if (dir == UP || dir == DOWN)
		Sleep(90*2/SPEED);
}
