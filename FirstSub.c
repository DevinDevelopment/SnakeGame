
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>


#define TIMEOUT 10
#define BLANK " " 

typedef struct point 
{
	int x;
	int y;
} point;

typedef enum 
{
    LEFT,
	RIGHT,
	UP,
	DOWN
} directionType;

int x, y, Randcoorx, Randcoory;
int maxX, maxY;
int nextX, nextY;
int snakeLength = 3;
int gameOver = 0;
int winner = 0;
int speed;
int winningLength, randomNum, randomNumm;
time_t trophyTime, currentTime;


directionType currentDir = RIGHT;
point snakeParts[255];
point trophy;



void drawborder();
void drawSnakeParts(point);
void cursesInit();
void init();
void snakeMovement();
void drawToScreen();
void createTrophy();
void spawnTrophy(point);
int timer(void);

int main(int ac, char *av[]) 
{
    WINDOW * win;
    speed = 10;
	cursesInit();
	init();

    
	while(1) 
    {
        
        int ch = getch();


        if(gameOver) 
        {
			sleep(2);
			init();
		}

        if(winner) 
        {
			sleep(2);
			init();
		}   

        drawToScreen();
		switch(ch) 
        {
            case KEY_UP:
                currentDir = UP;    
                break;
            case KEY_DOWN:
                currentDir = DOWN;    
                break;
            case KEY_LEFT:
                currentDir = LEFT;    
                break;
            case KEY_RIGHT:
                currentDir = RIGHT;    
                break;
            case 'x':
            case 'X':                
                endwin();
                return 0;
        timer();
        }
        timer();
        refresh();

        nextX = snakeParts[0].x;
		nextY = snakeParts[0].y;

		if(currentDir == RIGHT) 
        {
            nextX++;
            timer();
        }
	    else if(currentDir == LEFT) 
        {
            nextX--;
            timer();
        }
		else if(currentDir == UP) 
        {
            nextY--;
            timer();
        }
		else if(currentDir == DOWN) 
        {
            nextY++;
            timer();
        }

        if(nextX == trophy.x && nextY == trophy.y) 
        {
			point tail;
			tail.x = nextX;
			tail.y = nextY;
            speed++;
            snakeParts[snakeLength] = tail;
            

                for (int i = 0; i < randomNumm ; i++)	
                {
                point tail;
			    tail.x = nextX;
			    tail.y = nextY;
                speed+=3;
                snakeParts[snakeLength] = tail;
                snakeParts[snakeLength - 1].x = nextX;
		        snakeParts[snakeLength - 1].y = nextY;
                snakeLength ++;
                snakeMovement();
                }
            
			createTrophy();
		} 
        else 
        {
			for(int i = 0; i < snakeLength; i++)
            {
                //if snake runs into itself.
				if(nextX == snakeParts[i].x && nextY == snakeParts[i].y) 
                {
                    
					gameOver = 1;
					break;
				}              
			}		
		    snakeParts[snakeLength - 1].x = nextX;
		    snakeParts[snakeLength - 1].y = nextY;	


        }

		snakeMovement();
        //if snake runs into border
        if((nextX >= maxX || nextX < 2) || (nextY >= maxY || nextY < 2))
        {
			gameOver = 1;
		}

        if(snakeLength == winningLength)
        {
            winner = 1;
        }
        timer();
		drawToScreen();       
	}
	endwin(); 
	nocbreak();
    

	return 0;
}


void createTrophy() 
{
    randomNumm = (rand() % 3) +1;        
    trophy.x = (rand() % (maxX - 20)) + 10;
	trophy.y = (rand() % (maxY - 10)) + 5;
}

void drawSnakeParts(point drawPoint) 
{
	mvprintw(drawPoint.y, drawPoint.x, "o");
}

void spawnTrophy(point drawPoint) 
{
    
    
	mvprintw(drawPoint.y, drawPoint.x, "%d", randomNumm);
    trophyTime = time(NULL);
    
    }

void cursesInit() 
{
	initscr(); 
	noecho(); 
	keypad(stdscr, TRUE);
	cbreak();
	timeout(TIMEOUT);
	curs_set(FALSE); 

	getmaxyx(stdscr, maxY, maxX);
}

void init() 
{
	srand(time(NULL));

	currentDir = RIGHT;
	snakeLength = 3;
    gameOver = 0;
    winner = 0;

	clear();
    //drawborder();
		
	int j = 0;
	for(int i = snakeLength; i >= 0; i--) 
    {
		point currPoint;
			
		currPoint.x = i;
		currPoint.y = maxY / 2; 

		snakeParts[j] = currPoint;
            
		j++;
    }
    createTrophy();
    timer();
	refresh();
}


void snakeMovement() 
{
	point tmp = snakeParts[snakeLength - 1];

	for(int i = snakeLength - 1; i > 0; i--) 
    {
	 snakeParts[i] = snakeParts[i-1];

    if(nextX == trophy.x && nextY == trophy.y) 
        {
            nextX ++;
            nextY ++;
        }
	}
	snakeParts[0] = tmp;
}

void drawToScreen() 
{
    winningLength = COLS / 2;
    clear(); 
    

    if(winner)  
    {
        mvprintw(maxY / 2, maxX / 2, "Winner!");
        speed = 10;
    }

    if(gameOver)
    {
		mvprintw(maxY / 2, maxX / 2, "Game Over!");
        speed = 10;
    }

	for(int i = 0; i < snakeLength; i++) 
    {
		drawSnakeParts(snakeParts[i]);

	}
    box(stdscr, 0, 0);
    spawnTrophy(trophy);
    refresh();

	usleep(1000000/speed); 
}

int timer(void)
{
    currentTime = time(NULL);
    int delaytime = (rand() % 9) +1 ;

    if((currentTime - trophyTime) == delaytime)
    {
         createTrophy();
    }
 return 0;
}