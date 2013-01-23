#ifndef MAP_HPP
#define MAP_HPP

#define ROWS1 15
#define COLS1 20

int initFood1[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		  0,10,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		  0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		  0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,
		  0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		  0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,10,0,
		  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 
bool initWall1[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		   1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		   1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0,1,
		   1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
		   1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,
		   1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		   1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

#define ROWS2 11
#define COLS2 20

int initFood2[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		  0,10,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		  0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		  0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,
		  0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		  0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		  0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		  0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,10,0,
		  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 
bool initWall2[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		   1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		   1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0,1,
		   1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
		   1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,
		   1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		   1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		   1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


int* initFood = initFood2;
bool* initWall = initWall2;

int ROWS = ROWS2;
int COLS = COLS2;

#endif
