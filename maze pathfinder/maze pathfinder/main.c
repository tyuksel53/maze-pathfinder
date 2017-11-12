#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
/*
	date: 12.11.2017
	author:yuksel algorithm 
*/
typedef enum { false, true } bool;

typedef struct path {
    int RowNum;
	int ColumnNum;
    struct path * next;
}path_t;
// --->defination of static global values
path_t  *head = NULL;
path_t  *head_control = NULL;
static int exit = 0;

static int columnSize = 0;
static int rowSize = 0;

// enterance of the maze
static int startPointX = -1;
static int startPointY = -1;

// exit point of the maze
static int endPointX = -1;
static int endPointY = -1;

// --->defination of static global values end

// --->funciton definations
int **maze_create(); 
bool maze_enter_exit_control(int **maze);
void show_maze(int **maze);
void find_a_way(int **maze, int currentX, int currentY);
bool control_path(int currentX,int currentY);
void add_pathValues(int valueX, int valueY);
void print_maze_way_out();
void add_pathValues_Control(int valueX, int valueY);
// --->function definations end

void main()
{
	int ** maze = maze_create();
	show_maze(maze);

	bool check = false;
	while (true)
	{
		check = maze_enter_exit_control(maze);
		if (check)
		{
			break;
		}
		else
		{
			printf("\nWrong !!!!! Entrance point or exit point\n\n");
		}
	}
	add_pathValues(startPointX,startPointY);
	find_a_way(maze, startPointX, startPointY);

	if (exit == 0)
	{
		printf("\nThere is no way sorry....");
	}
	else
	{
		printf("\n---------HERE IS YOUR WAY-----------\n\n");
		print_maze_way_out(maze);
	}

	system("PAUSE");
}
int **maze_create()
{ //creates a matrix based on columsize value and rowsize value and it contains only ones and zeros(randomly genareted)
	printf("Please Enter the size of row:\n--> ");
	scanf_s("%d", &rowSize);
	printf("Please Enter the size of column:\n--> ");
	scanf_s("%d", &columnSize);

	srand(time(NULL));
	int **maze = (int **)malloc(sizeof(int) * rowSize);
	int i, j;

	for (i = 0; i < rowSize; i++)
	{
		maze[i] = (int *)malloc(sizeof(int)* columnSize);
	}

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < columnSize; j++)
		{
			maze[i][j] = rand() % 2;
		}
	}

	return maze;
}
void show_maze(int	**maze) // displays maze to screen
{
	printf("\n");
	int i, j;

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < columnSize; j++)
		{
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}
bool maze_enter_exit_control(int **maze)//controls the exit and entrance points
{
	printf("\nPlease Enter Enterance of the Maze:\nRowNum--> ");
	scanf_s("%d", &startPointX);
	printf("ColumnNum --> ");
	scanf_s("%d", &startPointY);

	printf("Please Enter Exit Point of the Maze:\nRowNum--> ");
	scanf_s("%d", &endPointX);
	printf("ColumnNum --> ");
	scanf_s("%d", &endPointY);


	if (startPointX < rowSize && startPointY < columnSize && endPointX < rowSize && endPointY < columnSize)
	{
		if (maze[startPointX][startPointY] == 1 && maze[endPointX][endPointY] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}
void find_a_way(int **maze, int currentX, int currentY)
{
	if (currentX == endPointX && currentY == endPointY)
	{
		//printf("end\n");
		exit = 1;
		return;
	}
	// go right
	if (currentY + 1 < columnSize && maze[currentX][currentY + 1] == 1  && exit == 0)
	{
		if ( control_path(currentX,currentY+1,0) )
		{
			//printf("(%d,%d) -> (%d,%d)\n", currentX, currentY, currentX, currentY+1);
			add_pathValues(currentX, currentY+1);
			find_a_way(maze, currentX, currentY + 1, currentX, currentY);
		}
		
	}
	// go left
	if (currentY -1 < columnSize &&  currentY >=0  && maze[currentX][currentY - 1] == 1  && exit == 0)
	{
		if ( control_path(currentX, currentY - 1,0) )
		{
			//printf("(%d,%d) -> (%d,%d)\n", currentX, currentY, currentX, currentY - 1);
			add_pathValues(currentX, currentY - 1);
			find_a_way(maze, currentX, currentY - 1, currentX, currentY);
		}
	}
	// go down
	if (currentX + 1 < rowSize && maze[currentX+1][currentY] == 1 && exit == 0)
	{
		if ( control_path(currentX+1, currentY,0) )
		{
			//printf("(%d,%d) -> (%d,%d)\n", currentX, currentY, currentX+1, currentY);
			add_pathValues(currentX+1, currentY);
			find_a_way(maze, currentX+1, currentY, currentX, currentY);
		}
	}
	//go up
	if (currentX - 1 < rowSize &&  currentX - 1 >= 0 && maze[currentX - 1][currentY] == 1 && exit == 0)
	{
		if ( control_path(currentX-1, currentY,0) )
		{
			//printf("(%d,%d) -> (%d,%d)\n", currentX, currentY, currentX-1, currentY);
			add_pathValues(currentX-1, currentY);
			find_a_way(maze, currentX-1, currentY, currentX, currentY);
		}
	}
	if (exit == 0)
	{
		add_pathValues_Control(currentX, currentY);
	}
	return;
}
void print_maze_way_out(int **maze)
{
	int i, j = 0;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < columnSize; j++)
		{
			printf("%d ", maze[i][j]);
		}
		if (i == rowSize / 2)
		{
			printf("   ----->     ");
		}
		else
		{
			printf("              ");
		}
		for (j = 0; j < columnSize; j++)
		{
			if (control_path(i,j,0) == false)
			{
				if (control_path(i, j, 1) == false)
				{
					printf("0 ");
				}
				else
				{
					printf("1 ");
				}
				
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
}
bool control_path(int currentX, int curretY,int type)
{
	if (type == 0)
	{
		path_t *current = head;
		//int i = 1;
		while (current != NULL) {
			if (current->ColumnNum == curretY && current->RowNum == currentX)
			{
				return false;
			}
			//printf("%d. | (%d,%d)\n", i, current->RowNum, current->ColumnNum);
			current = current->next;
			//i++;
		}

		return true;
	}
	else
	{
		path_t *current = head_control;
		while (current != NULL) {
			if (current->ColumnNum == curretY && current->RowNum == currentX)
			{
				return false;
			}
			current = current->next;
		}

		return true;
	}
	
}
void add_pathValues(int valueX, int valueY)
{
		path_t * firstDot = (path_t *) malloc(sizeof(path_t));
		firstDot->RowNum = valueX;
		firstDot->ColumnNum = valueY;
		firstDot->next = head;
		head = firstDot;
}
void add_pathValues_Control(int valueX, int valueY)
{
	path_t * firstDot = (path_t *)malloc(sizeof(path_t));
	firstDot->RowNum = valueX;
	firstDot->ColumnNum = valueY;
	firstDot->next = head_control;
	head_control = firstDot;
}