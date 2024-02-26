#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

#define SIZE 3


void printBoard(Node* board) {
    int i, j;
    Node *t;
    t= board;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %c ", t->value);
            t=t->next;
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            printf("---+---+---\n");
        }
    }
  
}

int checkWin(Node* board, char player) {
    int i,j;
    Node *temp = board;
    char bd[3][3];
    for( i=0; i<3;i++)
     for ( j = 0; j < 3; j++) {
            bd[i][j] = temp->value;
            temp = temp->next;
        }
    printf("\n");
        
    for (i = 0; i < SIZE; i++) {
        if (bd[i][0] == player && bd[i][1] == player && bd[i][2] == player) {
            return 1; // Row win
        }
        if (bd[0][i] == player && bd[1][i] == player && bd[2][i] == player) {
            return 1; // Column win
        }
    }
    if (bd[0][0] == player && bd[1][1] == player && bd[2][2] == player) {
        return 1; // Diagonal win
    }
    if (bd[0][2] == player && bd[1][1] == player && bd[2][0] == player) {
        return 1; // Diagonal win
    }
    return 0;
}

void freeBoard(Node* board) {
    Node *t1,*t2;
    int i,j;
    t1=board;
    while(t1 != NULL)
    {
    	t2= t1->next;
        free(t1);
        t1=t2;
	}
}

void pvp()
{
	Node* board=NULL, *current,*t;
    char currentPlayer = 'X';
    int row, col, i, j;
    int moves = 0;
	int ch;
	
    // Initialize the board with empty nodes
  
   for ( i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
        	if(board == NULL)
        	{
        		board = malloc(sizeof(Node));
            	board->value = ' ';
            	board->next = NULL;
            	t = board;
			}
			else
			{
				t->next = malloc(sizeof(Node));
            	t->next->value = ' ';
            	t->next->next = NULL;
            	t=t->next;
			}
        }
    }
 
    
	while (1) {
        printBoard(board);
        printf("Player %c, enter row and column (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);
		t = board;
	
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE ) {
            printf("Invalid move. Try again.\n");
            continue;
        }
        printf("\n");
        t=board;
		for( i=0;i < (row * SIZE + col) ; i++)
		{
			
			t=t->next;
		}
		 if (t->value != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }
		
		t->value = currentPlayer;
        moves++;

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        } else if (moves == SIZE * SIZE) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Free memory for the board nodes
    freeBoard(board);
}

// Function for the computer's move (randomly chooses an empty cell)
int computerMove(Node *board) {
    int num,i;
    Node *temp = board;
    char bd[9];
    for( i=0; i<9;i++)
    {
    	 bd[i] = temp->value;
         temp = temp->next;
	}
	if(bd[4] == ' ')
		return 4;
	else
	{
		do {
       		num = rand() % 9;
    	 } while (bd[num] != ' ');
    return num;// Computer's symbol
	}
    
}

void pvc()
{
	Node* board=NULL, *current,*t;
	int cp=1;
    char currentPlayer = 'X';
    int row, col, i, j;
    int moves = 0;
	int num;
	
    // Initialize the board with empty nodes
  
   for ( i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
        	if(board == NULL)
        	{
        		board = malloc(sizeof(Node));
            	board->value = ' ';
            	board->next = NULL;
            	t = board;
			}
			else
			{
				t->next = malloc(sizeof(Node));
            	t->next->value = ' ';
            	t->next->next = NULL;
            	t=t->next;
			}
        }
    }
 
    
	while (1) {
        printBoard(board);
        
        if (cp)
        {
        	printf("Player %c, enter row and column (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);
		t = board;
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE ) {
            printf("Invalid move. Try again.\n");
            continue;
        }
        printf("\n");
        t=board;
		for( i=0;i < (row * SIZE + col) ; i++)
		{
			
			t=t->next;
		}
		 if (t->value != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }
		
		t->value = currentPlayer;
        moves++;
         if (checkWin(board, 'X')) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        } else if (moves == SIZE * SIZE) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }
        cp = 0;
		}
		
		else
		{
			printf("Computer's move:\n");
            num = computerMove(board);
            t=board;
            for( i=0;i < num ; i++)
			{
			
				t=t->next;
			}
            t->value = 'O';
			moves++;
             // Computer's turn
             if (checkWin(board, 'O')) {
            printBoard(board);
             printf("Computer wins! You lose!\n");
            break;
       		 } else if (moves == SIZE * SIZE) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        	}

            cp = 1; // Switch to the user's turn
		}
        

        
    }

    // Free memory for the board nodes
    freeBoard(board);
}

int menu()
{
	int ch;
	printf("1. Multi-Player\n2. Play with computer\n3. Exit\n");
	printf("Enter your choice : ");
	scanf("%d",&ch);
	return ch;
}

int main() {
    
	int ch;
    printf("Welcome to Tic-Tac-Toe!\n");
	for(ch = menu(); ch!=3; ch=menu())
	{
		switch(ch)
		{
			case 1 : pvp();
					break;
			case 2 : pvc();
					break;
			default : printf("Wrong Choice");
					  break;
		}
	}
    

    return 0;
}
