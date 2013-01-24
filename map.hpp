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


#define ROWS3 5
#define COLS3 8

int initFood3[] ={0,0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,0,
		  0,1,1,1,1,0,0,0,
		  0,0,0,0,0,0,0,0};

		 
bool initWall3[] ={1,1,1,1,1,1,1,1,
		   1,0,0,0,0,0,0,1,
		   1,0,1,1,1,1,1,1,
		   1,0,0,0,0,0,0,1,
		   1,1,1,1,1,1,1,1};

#define ROWS4 11
#define COLS4 7

int initFood4[] ={0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,1,0,0,0,
		  0,0,0,0,0,0,0,
		  0,0,0,0,0,0,0};

bool initWall4[] ={1,1,1,1,1,1,1,
		   1,1,1,1,1,1,1,
		   1,1,1,0,1,1,1,
		   1,1,1,0,1,1,1,
		   1,1,1,0,1,1,1,
		   1,0,0,0,0,0,1,
		   1,0,1,1,1,0,1,
		   1,0,1,1,1,0,1,
		   1,0,0,0,0,0,1,
		   1,1,1,0,1,1,1,
		   1,1,1,1,1,1,1};


int* initFood = initFood2;
bool* initWall = initWall2;
double scale = 20;
double translate = 100;
int ROWS = ROWS2;
int COLS = COLS2;



#endif
