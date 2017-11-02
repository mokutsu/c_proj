/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */

void init(void)
{
    // 5x5 board will have positions 0-4 x 0-4
    int dim = d-1;
    int number = (d*d) - 1;
    for (int i=0; i <= dim; i++) {
        for (int j=0; j <= dim; j++) {
            board[i][j] = number;
            number -= 1;
        }
    }
    if ((d*d) % 2 == 0) {
        board[dim][dim-1] = 2;
        board[dim][dim-2] = 1;
    }
    int space = 0;
    board[dim][dim] = space;
    // TODO
}
/**
 * Prints the board in its current state.
 */
void draw()
{
    int space = 0;
    int dim = d-1;
    for (int i=0; i <= dim; i++) {
        for (int j=0; j <= dim; j++) {
           if(board[i][j] == space) {
                printf("  _");
            } else {
                printf(" %2i", board[i][j]);
            }
        }
        printf("\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */

bool move(int tile)
{
    int dim = d-1;
    int row_num;
    int col_num;
    printf("tile is %i", tile);
    //eg 4 x 4 grid will have (0 - 3) x (0 - 3) with 1, 2, 3, 4
    for (int a=0; a <= dim; a++) {
        for (int b=0; b<=dim; b++) {
            if (board[a][b] == tile) {
                row_num = a;
                col_num = b;
                break;
            }
        }
    }

    printf("Tile is at board[%i][%i]\n", row_num, col_num);
    // int current_position = board[row_num][col_num];
    // if edge of board return false
    //check  if the current_position is beside the empty tile 
    // int right_tile = board[row_num][col_num+1];
    // int left_tile = board[row_num][col_num-1];
    // int top_tile = board[row_num-1][col_num];
    // int bot_tile = board[row_num+1][col_num];
    int space = 0;
    if (col_num < dim) {
        if (board[row_num][col_num+1] == space) {
            printf("_ is right of %i, dim: %i, col_num: %i, row_num: %i\n", tile, dim, col_num, row_num);
            board[row_num][col_num+1] = board[row_num][col_num];
            board[row_num][col_num] = space;
            return true;
        }
    }
    if (col_num > 0) {
        if (board[row_num][col_num-1] == space) {
            printf("_ is left of %i, dim: %i, col_num: %i, row_num: %i\n", tile, dim, col_num, row_num);
            board[row_num][col_num-1] = board[row_num][col_num];
            board[row_num][col_num] = space;
            return true;
        }
    }
    if (row_num < dim) {
        if (board[row_num+1][col_num] == space) {
            printf("_ is below %i, dim: %i, col_num: %i, row_num: %i\n", tile, dim, col_num, row_num);
            board[row_num+1][col_num] = board[row_num][col_num];
            board[row_num][col_num] = space;
            return true;
        }
    }
    if (row_num>0) {
        if (board[row_num-1][col_num] == space) {
            printf("_ is above %i, dim: %i, col_num: %i, row_num: %i\n", tile, dim, col_num, row_num);
            board[row_num-1][col_num] = board[row_num][col_num];
            board[row_num][col_num] = space;
            return true;
        }
    }
    
    return false;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int dim = d-1;
    int last = -1;
    for (int a=0; a <=dim; a++) {
        for (int b=0; b <=dim; b++) {
            if (a==dim && b==dim) {
                printf("a is %i, b is %i, dim is %i, d is %i \n", a, b, dim, d);
                return true;
            }
            // if we are not in the last space, check whether the last value is greater
            else {
                if (last > board[a][b]) {
                    printf("last is %i, board[%i][%i] = %i", last, a, b, board[a][b]);
                    return false;
                }
                last = board[a][b];
            }
        }
    }
    return true;
}
