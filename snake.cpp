#include <cstdlib>
#include <ncurses.h> 
#include <unistd.h> 

bool gameOver;
const int WIDTH = 20;
const int HEIGHT = 20;
int x, y; // Initail Position
int fruitX, fruitY; // Fruit Position
int score;

typedef enum DIRECTION {STOP =0, LEFT, RIGHT, UP, DOWN}
Dir;
Dir dir;

// Tail of Snake
int tailX[50], tailY[50];
int numTail=0;

void Setup()
{
    
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = WIDTH/2; // STARTING OF SNAKE X-POSITION
    y = HEIGHT/2; // STARTING OF SNAKE Y-POSITION
    fruitX = (rand() % WIDTH)+1; // STARTING OF FRUIT X-POSITION
    fruitY = (rand() % HEIGHT)+1; // STARTING OF FRUIT Y-POSITION
    score = 0;  
}

void Game()
{
    clear();
    
    for (int i=0; i<HEIGHT+2; i++)
    {
        for (int j=0; j<WIDTH+2; j++)
        {
            // Map Boundry 
            if (i==0 | i==21)
            {
                mvprintw(i, j, "0");
            }
            else if (j==0 | j==21)
            {
                mvprintw(i, j, "0");
            } 
            //Snake Head
            else if (i==y && j==x)
            {
                mvprintw(i, j, "0");
            }
            // FRUIT 
            else if (i==fruitY && j==fruitX)
            {
                mvprintw(i, j, "@");
            }
            else
            {   
                // TAIL OF SNAKE
                for (int k=0; k<numTail; k++)
                {
                    if (tailX[k]==j && tailY[k]==i)
                    {
                        mvprintw(i,j, "o");
                    }
                }

            }
            
        }
    }    
    //Draw Information
    mvprintw(4, 29, "       CONTROLS FOR THE GAME        ");
    mvprintw(5, 29, "Use direction keys to eat fruit");
    mvprintw(7, 43, "   ^ ");
    mvprintw(8, 43, "<     >");
    mvprintw(9, 43, "   v ");
    mvprintw(11, 29, " IF YOU COLLIDE WITH WALL OR TAIL THEN SNAKE WILL DIE");
    mvprintw(16, 29, "Score = %d", score);
//  mvprintw(17, 29, "$$ Remain Time = %d", current_time);
    refresh();
}

void Input()
{
    keypad(stdscr, TRUE); 
    halfdelay(1); 
//  Typed Key by Gamer
    int c = getch(); 
// Command 
    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_DOWN: 
            dir = UP;
            break;
        case KEY_UP:
            dir = DOWN;
            break;
        case KEY_EXIT:
            gameOver = true;
            break;

    }    

}


void Update()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    // NEW POSITION 
    for (int i=1; i<numTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        default: 
            break;
    }

//SNAKE OUT OF BOUNDRY  
    if (x>WIDTH || x<1 || y<1 || y>HEIGHT)
    {
        gameOver=true;
    }

//SCORE UPDATION   
    if (x==fruitX && y==fruitY)
    {
        score ++;
        fruitX = (rand() % WIDTH)+1;
        fruitY = (rand() % HEIGHT)+1;
        numTail++;
    }

    for (int i=0; i<numTail; i++)
    {
        if(tailX[i]==x && tailY[i]==y)
        {
            gameOver=true;
        }
        
    }

}


int main()
{
    Setup();

   while(!gameOver)
    {
        Game();
        Input();
        Update();

    }
    getch();
    sleep(1); 
    endwin();

    return 0;
}