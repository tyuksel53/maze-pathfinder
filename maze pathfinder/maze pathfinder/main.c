#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
typedef enum { false, true } bool;

typedef struct path {
    int RowNum;
	int ColumnNum;
    struct path * next;
}path_t;
// defiantion of static global values
path_t *head = NULL;
static int exit = 0;

static int columnSize = 0;
static int rowSize = 0;

// enterance of the maze
static int startPointX = -1;
static int startPointY = -1;

// exit point of the maze
static int endPointX = -1;
static int endPointY = -1;

// funciton definations
int **maze_create(); 
bool maze_enter_exit_control(int **maze);
void show_maze(int **maze);
void find_a_way(int **maze, int currentX, int currentY);
bool control_path(int currentX,int currentY);
void add_pathValues(int valueX, int valueY);

void main()
{
	add_pathValues(1, 2);
	add_pathValues(2, 5);
	add_pathValues(3, 6);
	add_pathValues(4, 7);
	control_path(0, 0);
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
	
	//find_a_way(maze, startPointX, startPointY);
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
	printf("Please Enter Enterance of the Maze:\nRowNum--> ");
	scanf_s("%d", &startPointX);
	printf("ColumnNum --> ");
	scanf_s("%d", &startPointY);

	printf("Please Enter Exit Point of the Maze:\nRowNum--> ");
	scanf_s("%d", &endPointX);
	printf("ColumnNum --> ");
	scanf_s("%d", &endPointY);


	if (startPointX < rowSize && startPointY < rowSize && endPointX < columnSize && endPointY < columnSize)
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
/*void find_a_way(int **maze, int currentX, int currentY)
{
	if (currentX == endPointX && currentY == endPointY)
	{
		printf("end");
		exit = 1;
		return;
	}
	// go right
	if (currentY + 1 < columnSize && maze[currentX][currentY + 1] == 1  && exit == 0)
	{
		if (currentX == previousX && (currentY+1) == previousY)
		{

		}
		else
		{
			printf("3 ");
			find_a_way(maze, currentX, currentY + 1, currentX, currentY);
		}
		
	}
	// go left
	if (currentY -1 < columnSize &&  currentY >=0  && maze[currentX][currentY - 1] == 1  && exit == 0)
	{
		if (currentX == previousX && (currentY-1) == previousY)
		{

		}
		else
		{
			printf("4 ");
			find_a_way(maze, currentX, currentY - 1, currentX, currentY);
		}
	}
	// go down
	if (currentX + 1 < rowSize && maze[currentX+1][currentY] == 1 && exit == 0)
	{
		if ( (currentX+1) == previousX && currentY == previousY)
		{

		}
		else
		{
			printf("2 ");
			find_a_way(maze, currentX+1, currentY, currentX, currentY);
		}
	}
	//go up
	if (currentX - 1 < rowSize &&  currentX - 1 >= 0 && maze[currentX - 1][currentY] == 1 && exit == 0)
	{
		if ( (currentX-1) == previousX && currentY == previousY)
		{

		}
		else
		{
			printf("1 ");
			find_a_way(maze, currentX-1, currentY, currentX, currentY);
		}
	}
	return;
}*/
bool control_path(int currentX, int curretY)
{
	path_t *current = head;
	int i = 1;
	while (current != NULL) {
		printf("%d. |%d - %d\n", i, current->RowNum, current->ColumnNum);
		/*if ( current->ColumnNum == curretY && current->RowNum == currentX)
		{
			return false;
		}*/
		i++;
		current = current->next;
	}

	return true;
}
void add_pathValues(int valueX, int valueY)
{
	
	if (head == NULL)
	{
		head = malloc(sizeof(path_t));
		head->ColumnNum = valueY;
		head->RowNum = valueY;
		head->next = NULL;
		return;
	}
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = malloc(sizeof(path_t));
	head->next->ColumnNum = valueY;
	head->next->RowNum = valueX;
	head->next->next = NULL;
}