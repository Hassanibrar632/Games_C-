#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum DIRECTION{
	STOP=0, RIGHT=1, UPRIGHT=2, DOWNRIGHT=3, UPLEFT=4, LEFT=5, DOWNLEFT=6
};

class GAME_PADDLE{
	private:
		int STARTING_X_POS, STARTING_Y_POS, CURRENT_X_POS, CURRENT_Y_POS;
	public:
		GAME_PADDLE(int x, int y){
			STARTING_X_POS = CURRENT_X_POS = x;
			CURRENT_Y_POS = STARTING_Y_POS = y;
		}
		
		void RESET(){
			CURRENT_Y_POS = STARTING_Y_POS;
			CURRENT_X_POS = STARTING_X_POS;
		}
		
		inline void MOVE_UP(){
			CURRENT_Y_POS--;
		}
		
		inline void MOVE_DOWN(){
			CURRENT_Y_POS++;
		}
		
		inline int getX(){
			return CURRENT_X_POS;
		}
		
		inline int getY(){
			return CURRENT_Y_POS;
		}
};

class GAME_BALL{
	private:
		int STARTING_X_POS, STARTING_Y_POS, CURRENT_X_POS, CURRENT_Y_POS;
		DIRECTION BALL_DIR;
	public:
		GAME_BALL(int X,int Y){
			BALL_DIR = STOP;
			STARTING_X_POS = X;
			STARTING_Y_POS = Y;
			CURRENT_X_POS = X;
			CURRENT_Y_POS = Y;
		}
		
		void RESET(){
			BALL_DIR = STOP;
			CURRENT_X_POS = STARTING_X_POS;
			CURRENT_Y_POS = STARTING_Y_POS;
		}
		
		void RANDOM_DIRECTION(){
			BALL_DIR = (DIRECTION)((rand()%6)+1);
		}
		
		void CHANGE_DIRECTION(DIRECTION d){
			BALL_DIR = d;
		}
		
		void MOVEMENT(){
			switch(BALL_DIR){
				case RIGHT:
					CURRENT_X_POS--;
					break;
				case UPRIGHT:
					CURRENT_X_POS--; CURRENT_Y_POS--;
					break;
				case DOWNRIGHT:
					CURRENT_X_POS--; CURRENT_Y_POS++;
					break;
				case LEFT:
					CURRENT_X_POS++;
					break;
				case UPLEFT:
					CURRENT_X_POS++; CURRENT_Y_POS--;
					break;
				case DOWNLEFT:
					CURRENT_X_POS++; CURRENT_Y_POS++;
					break;
			}
		}
		
		inline int getX(){
			return CURRENT_X_POS;
		}
		
		inline int getY(){
			return CURRENT_Y_POS;
		}
		
		inline DIRECTION get_direction(){
			return BALL_DIR;
		}
};

class GAME_MANAGER{
	private:
		bool GAME_OVER;
		GAME_PADDLE *P1, *P2;
		GAME_BALL *BALL;
		int HEIGHT,WIDTH;
		char U1, D1;
	public:
		GAME_MANAGER(int x , int y){
			srand(time(NULL));
			HEIGHT = y;
			WIDTH = x;
			GAME_OVER = false;
			U1 = 'w';
			D1 = 's';
			BALL = new GAME_BALL(WIDTH/2, HEIGHT/2);
			P1 = new GAME_PADDLE(2, HEIGHT/2);
			P2 = new GAME_PADDLE(WIDTH-2, HEIGHT/2);
		}
		
		~GAME_MANAGER(){
			delete BALL, P1, P2;
		}
		
		void DRAW(){
			//firt line
			for(int i = 0; i<=WIDTH; i++)
				cout << "\xB2";
			cout << "\n";
			
			//middle part
			for(int i = 1; i<HEIGHT; i++){
				for(int j=0; j<=WIDTH; j++){
					if(j==0 || j==WIDTH)
						cout << "\xB2";
					else if(j==BALL->getX() && i==BALL->getY())
						cout << "O";
					else if(j==P1->getX() && i==P1->getY())
						cout << "\xDE";
					else if(j==P2->getX() && i==P2->getY())
						cout << "\xDD";
						
					else if((j==P1->getX() && i==P1->getY()-1))
						cout << "\xDE";
					else if((j==P1->getX() && i==P1->getY()+1))
						cout << "\xDE";
					else if((j==P2->getX() && i==P2->getY()-1))
						cout << "\xDD";
					else if((j==P2->getX() && i==P2->getY()+1))
						cout << "\xDD";
					else
						cout << " ";
				}
				cout << "\n";
			}
			
			//end line
			for(int i = 0; i<=WIDTH; i++)
				cout << "\xB2";
			cout << "\n";
		}
		
		
		void MOVEMENT(){
			if(_kbhit()){
				char HIT=_getch();
				if(BALL->get_direction()==STOP)
					BALL->RANDOM_DIRECTION();
				if(HIT==U1){
					if(P1->getY()-2!=0)
						P1->MOVE_UP();
					if(P2->getY()+2!=HEIGHT)
						P2->MOVE_DOWN();
				}else if(HIT==D1){
					if(P1->getY()+2!=HEIGHT)
						P1->MOVE_DOWN();
					if(P2->getY()-2!=0)
						P2->MOVE_UP();
				}else if(HIT=='q')
					GAME_OVER = true;
			}
			GAME_LOGIC();
			BALL->MOVEMENT();
		}
		
		void GAME_LOGIC(){
			if(BALL->getX()-1==P1->getX() && BALL->getY()==P1->getY())
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+4));
			if(BALL->getX()+1==P2->getX() && BALL->getY()==P2->getY())
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+1));
			
			if(BALL->getX()-1==P1->getX() && BALL->getY()==P1->getY()+1)
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+4));
			if(BALL->getX()+1==P2->getX() && BALL->getY()==P2->getY()+1)
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+1));
			if(BALL->getX()-1==P1->getX() && BALL->getY()==P1->getY()-1)
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+4));
			if(BALL->getX()+1==P2->getX() && BALL->getY()==P2->getY()-1)
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+1));
			if(BALL->getX()-1==P1->getX() && BALL->getY()==P1->getY())
				BALL->CHANGE_DIRECTION((DIRECTION)((rand()%3)+4));
			
			if(BALL->getY()==1){
				if(BALL->get_direction()==UPRIGHT)
					BALL->CHANGE_DIRECTION(DOWNRIGHT);
				else
					BALL->CHANGE_DIRECTION(DOWNLEFT);
			}else if(BALL->getY()+1==HEIGHT){
				if(BALL->get_direction()==DOWNRIGHT)
					BALL->CHANGE_DIRECTION(UPRIGHT);
				else
					BALL->CHANGE_DIRECTION(UPLEFT);
			}
			
			if(BALL->getX()==0 || BALL->getX()==WIDTH){
				BALL->RESET();
				P1->RESET();
				P2->RESET();
			}
		}
		
		void Run(){
			do{
				MOVEMENT();
				DRAW();
				Sleep(100);
				system("cls");
				}while(!GAME_OVER);
		}
};

int main(){
	GAME_MANAGER Game(50 , 20);
	Game.Run();
}
