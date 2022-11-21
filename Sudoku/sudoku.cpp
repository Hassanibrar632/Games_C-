#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime>

using namespace std;

enum DIFFICULTY{easy = 0, medium = 1, hard = 3};

class sudoku{
	private:
	int height, width, px, py, *level, checks, *answer_sheet, Allowed, hints, total;
	bool game_is_running;
	int *check_sheet;
	DIFFICULTY diff;

	public:
		sudoku(){
			srand(time(NULL));
			start();
			initilize();
			get_game_array();
			getch();
			system("cls");
		}
		
		~sudoku(){
			delete[] answer_sheet;
			delete[] level;
			delete[] check_sheet;
		}
		
		void logic(){
			bool flag = 0;
			for(int i=0; i<total; i++){
				if(level[i] != answer_sheet[i]){
					flag = 1;
					break;
				}
			}
			if(flag)
				game_is_running = true;
			else
				game_is_running = false;
		}
		
		void display(){
			cout << "Checks: " << checks << "\t\t\t\tHints: " << hints;
			cout << "\n\t\t\t";
			int i = 0;
			for(int i=1; i<=width*3+2; i++)
				cout << "\xB0";
			cout << "\n";
			for(int y=0; y<height*3; y++){
				cout << "\t\t\t\xB0";
				for(int x=0; x<width*3; x++){
					if(x%3==1 && y%3==1){
						if(level[i]==0)
							cout << "\x2E";
						else
							cout << level[i];
						i++;
					}else if(x%3==1 && y%3==0 && x/3==px && y/3==py){
						cout <<"\xDC";
					}else if(x%3==1 && y%3==2 && x/3==px && y/3==py){
						cout <<"\xDF";
					}else if(x%3==0 && y%3==1 && x/3==px && y/3==py){
						cout <<"\xDE";
					}else if(x%3==2 && y%3==1 && x/3==px && y/3==py){
						cout <<"\xDD";
					}else
					cout << " ";
					
				}
				cout << "\xB0\n";
			}
			cout << "\t\t\t";
			for(int i=1; i<=width*3+2; i++)
				cout << "\xB0";
		}
		
		void INPUT(){
			int index=px+(py*width);
			if(_kbhit){
				switch(_getch()){
					case '0':
						if(check_sheet[index]!=2)
							level[index]=0;
						break;
					case '1':
						if(check_sheet[index]!=2 && 1<=width)
							level[index]=1;
						break;
					case '2':
						if(check_sheet[index]!=2 && 2<=width)
							level[index]=2;
						break;
					case '3':
						if(check_sheet[index]!=2 && 3<=width)
							level[index]=3;
						break;
					case '4':
						if(check_sheet[index]!=2 && 4<=width)
							level[index]=4;
						break;
					case '5':
						if(check_sheet[index]!=2 && 5<=width)
							level[index]=5;
						break;
					case '6':
						if(check_sheet[index]!=2 && 6<=width)
							level[index]=6;
						break;
					case '7':
						if(check_sheet[index]!=2 && 7<=width)
							level[index]=7;
						break;
					case '8':
						if(check_sheet[index]!=2 && 8<=width)
							level[index]=8;
						break;
					case '9':
						if(check_sheet[index]!=2 && 9<=width)
							level[index]=9;
						break;
					case 'w':
						if(py>0){
							py--;
							index-=width;
						}
						break;
					case 'a':
						if(px>0){
							px--;
							index-=1;
						}
						break;
					case 's':
						if(py<height-1){
							index+=width;
							py++;
						}
						break;
					case 'd':
						if(px<width-1){
							index=+1;
							px++;
						}
						break;
					case 'c':
						if(checks>0){
							for(int i=0; i<total; i++){
								if(level[i]!=answer_sheet[i])
									level[i]=0;
							}
							checks--;
						}
							break;
					case 'h':
						if(hints>0){
							if(level[index]!=answer_sheet[index] && check_sheet[index]!=2){
								level[index]=answer_sheet[index];
								check_sheet[index] = 2;
								hints--;
							}else if(check_sheet[index]!=2){
								check_sheet[index] = 2;
								hints--;
							}
						}
						break;
					case 'q':
						game_is_running = false;
				}
			}
		}
		
		void get_game_array(){
			string  fill = "Sudoku_";
			if(diff == easy){
				fill += "easy.txt";
				total = 16;
			}
			else if(diff == medium){
				fill += "medium.txt";
				total = 36;
			}
			else if(diff == hard){
				fill += "hard.txt";
				total = 81;
			}
			fill_array(level, total);
			fill_array(answer_sheet, total);
			fill_array(check_sheet, total);
			ifstream file(fill.c_str());
			int which_one = rand()%5;
			int x, i=0, turns = rand()%5;
			while(file >> x){
				answer_sheet[i]=x;
				i++;
				if(i==total && turns==0){
					break;
				}
				if(i==total && turns>0){
					i=0; turns--;
				}
			}
			file.close();
			while(Allowed>0){
				i=rand()%total;
				if(level[i]==0){
					level[i] = answer_sheet[i];
					Allowed--;
				}
			}
			Fix();
		}
		
		void Fix(){
			for(int i=0; i<total; i++){
				if(level[i]!=0){
					check_sheet[i]=2;
				}
			}
		}
		
		template<class ARRAY>
		void fill_array(ARRAY* random,int total){
			for(int i=0; i<total; i++){
				random[i] = 0;
			}
		}
		
		void initilize(){
			switch(diff){
				case 0:
					checks = 3;
					Allowed = 6+rand()%3;
					hints = 3;
					height = width = 4;
					level = new int[16];
					answer_sheet = new int [16];
					check_sheet = new int [16];
					break;
				case 1:
					checks = 3;
					Allowed = 15+rand()%6;
					hints = 8+rand()%3;
					height = width = 6;
					level = new int[36];
					answer_sheet = new int [36];
					check_sheet = new int [36];
					break;
				case 3:
					checks = 3;
					Allowed = 40 + rand()%16;
					hints = 12 + rand()%3;
					height = width = 9;
					level = new int[81];
					answer_sheet = new int [81];
					check_sheet = new int [81];
			}
			px = py = 0;
		}
		
		void start(){
			int c;
			do{
				system("cls");
				cout << "CHOOSE any one:\n"
					 << "1) Play\n"
					 << "2) Rules\n"
					 << "3) Exit\n";
				cin >> c;
				switch(c){
					case 1:
						game_is_running = true;
						do{
							system("cls");
							cout << "Which Difficulty you want:\n"
								 << "1) Easy\n"
								 << "2) Medium\n"
								 << "3) Hard\n";
							cin >> c;
							switch(c){
								case 1:
									diff = easy;
									Easy();
									break;
								case 2:
									diff = medium;
									Medium();
									c = 3;
									break;
								case 3:
									diff = hard;
									Hard();
							}
						}while(c>3 || c<1);
						break;
					case 2:
						HELP();
						break;
					case 3:
						game_is_running = false;
				}
			}while(c>3 || c<1 || c==2);
		}
		
		void Hard(){
			cout << "1)make sure you have any same number vertically and horizontally\n";
			getch();
			cout << "2)not even in 3x3 box chunk(i hope you know){divide boxes into 3X3 from left to right and from up to down}\n";
			getch();
			cout << "3)numbers are from 1 to 9 and 0 means earse the the number\n";
			getch();
		}
		
		void Medium(){
			cout << "1)make sure you have any same number vertically and horizontally\n";
			getch();
			cout << "2)not even in 2x3 box chunk(i hope you know){divide boxes into 2X3 from left to right and from up to down}\n";
			getch();
			cout << "3)numbers are from 1 to 6 and 0 means earse the the number\n";
			getch();
		}
		
		void Easy(){
			cout << "1)make sure you have any same number vertically and horizontally\n";
			getch();
			cout << "2)not even in 2x2 box chunk(i hope you know){divide boxes into 2X2 from left to right and from up to down}\n";
			getch();
			cout << "3)numbers are from 1 to 4 and 0 means earse the the number\n";
			getch();
		}
		
		void HELP(){
			cout << "\tHELLO!! I hnow you hate reading but please go through controls once:\n"
				 << "\t\t\tw == up\n"
				 << "\t\t\ts == down\n"
				 << "\t\t\ta == left\n"
				 << "\t\t\td == right\n"
				 << "\t\t\tc == check for wrong\n"
				 << "\t\t\th == hint for missing\n";
				 getch();
			cout << "\t\t->important<-\n\t\tto delete a number enter-> 0 <-\n";
				 getch();
				 system("cls");
		}
		
		bool get_game_running(){
			return game_is_running;
		}
};

int main(){
	sudoku g;
	while(g.get_game_running()){
		g.display();
		g.INPUT();
		g.logic();
		Sleep(10);
		system("cls");
	}
	g.display();
	cout << "\t\t\tyou woonnnnn!!";
	getch();
}
