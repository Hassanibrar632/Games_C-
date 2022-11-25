#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int width, height, count = 0, score = 0;
bool GAME_OVER;
bool L1[49], L2[49], L3[49], L4[49];
int Px,Py;

void generate(bool array[]){
	for(int i=0; i<50; i++)
		array[i]=(rand()%2);
}

void start(int a, int b){
	width = a;
	height = b;
	GAME_OVER = false;
	generate(L1);
	generate(L2);
	generate(L3);
	generate(L4);
	Px = width/2;
	Py = height-1;
}

void draw(){
	cout << "\t\t\t\t\t\tSCORE:" << score << endl;
	cout << "\t\t\t";
	for(int i=0; i<=width; i++)
		cout << "\xB0";
	cout << endl;
	
	for(int i=1; i<height; i++){
		cout << "\t\t\t";
		for(int j=0 ; j<=width ; j++){
			if(j==0 || j==width)
				cout << "\xB0";
			else if(i==height-2 && L4[j]==true)
					cout << "\xFE";
			else if(i==height-4 && L3[j]==true)
					cout << "\xFE";
			else if(i==height-6 && L2[j]==true)
					cout << "\xFE";
			else if(i==height-8 && L1[j]==true)
					cout << "\xFE";
			else if(Px==j && Py==i)
				cout << "\xEA";
			else
				cout << " ";
		}
		cout << "\n";
	}
	
	cout << "\t\t\t";
	for(int i=0; i<=width; i++)
		cout << "\xB0";
	cout << endl;
}

void collision(){
	for(int j=0; j<width; j++){
		if(Py==2 && j==Px){
			if(L1[j]==true)
				GAME_OVER = true;	
		}else
		if(Py==4 && j==Px){
			if(L2[j]==true)
				GAME_OVER = true;
		}else
		if(Py==6 && j==Px){
			if(L3[j]==true)
				GAME_OVER = true;
		}else
		if(Py==8 && j==Px){
			if(L4[j]==true)
				GAME_OVER = true;
		}
	}
	
	if(Py==1){
		Sleep(2);
		score+=10;
		Py=height-1;
	}
}

void SWAP(bool* ARRAY, bool right){
	if(!right){
		bool first = ARRAY[0];
		for(int i=1; i<50; i++){
			ARRAY[i-1]=ARRAY[i];
		}
		ARRAY[49]=first;
	}
	else{
		bool last = ARRAY[49];
		for(int i=49; i>0; i--){
			ARRAY[i]=ARRAY[i-1];
		}
		ARRAY[0]=last;
	}
}

void GAME_LOGIC(){
	count++;
	if(count%4==0){
		SWAP(L4, false);
	}
	if(count%3==0){
		SWAP(L3, true);
	}
	if(count%2==0){
		SWAP(L2, false);
	}
	SWAP(L1, true);
}

void movement(){
	if(_kbhit()){
		switch(_getch()){
			case 'w':
				if(Py>1)
					Py--;
				break;
			case 'a':
				if(Px>1)
					Px--;
				break;
			case 's':
				if(Py<height-1)
					Py++;
				break;
			case 'd':
				if(Px<width-1)
					Px++;
				break;
			case 'q':
				GAME_OVER = true;
				break;
		}
	}
}

int main(){
	start(50,10);
	do{
		system("cls");
		movement();
		draw();
		collision();
		GAME_LOGIC();
		Sleep(25);
	}while(!GAME_OVER);
}
