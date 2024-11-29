#include "chess.h"

// Constructor for the Square class
Square::Square()
{
    piece = EMPTY;
    color = NONE;
}

// Sets the space of the current square to the given space
void Square::setSpace(Square* space)
{
    color = space->getColor();
    piece = space->getPiece();
}

// Sets the current square to empty
void Square::setEmpty()
{
    color = NONE;
    piece = EMPTY;
}

// Gets the piece of the current square
Piece Square::getPiece()
{
    return piece;
}

// Gets the color of the current square
Color Square::getColor()
{
    return color;
}

// Sets the piece and color of the current square
void Square::setPieceAndColor(Piece p, Color c)
{
    piece = p;
    color = c;
}

// Prints the board in a human-readable format
void Board::printBoard()
{
    using namespace std;
    cout << "  y: 0  1  2  3  4  5  6  7" << endl << "x:" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << " " << i << "   ";
        for (int j = 0; j < 8; j++)
        {
            Piece p = square[i][j].getPiece();
            Color c = square[i][j].getColor();

            switch (p)
            {
                case KING: (c == WHITE) ? cout << " K " : cout << " k ";
                    break;
                case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
                    break;
                case BISHOP: (c == WHITE) ? cout << " B " : cout << " b ";
                    break;
                case KNIGHT: (c == WHITE) ? cout << " H " : cout << " h ";
                    break;
                case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
                    break;
                case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
                    break;
                case EMPTY: cout << " " << "\21" << " ";
                    break;
                default: cout << "XXX";
                    break;
            }
        }
        cout << endl;
    }
}

// Makes a move on the board, returns true if the move is valid, false otherwise
bool Board::doMove()
{
    using namespace std;
    string move;
    int x1, x2, y1, y2;
    bool stop = false;

    while (!stop)
    {
        (turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
        cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
        cin >> move;
        x1 = move[0] - 48;
        y1 = move[1] - 48;
        x2 = move[2] - 48;
        y2 = move[3] - 48;

        if (getSquare(x1, y1)->getColor() == turn)
        {
            if (makeMove(x1, y1, x2, y2) == false)
            {
                cout << "Invalid move, try again." << endl;
            }
            else
                stop = true;
        }
        else
            cout << "That's not your piece. Try again." << endl;
    }

    // Check if the game is over
    if (getSquare(x2, y2)->getPiece() == KING)
    {
        if (getSquare(x1, y1)->getColor() == WHITE)
        {
            cout << "WHITE WINS" << endl;
            return false;
        }
        else
        {
            cout << "BLACK WINS" << endl;
            return false;
        }
    }

    // Switch the turn
    if (turn == BLACK)
        turn = WHITE;
    else
        turn = BLACK;

    return true;
}

// Initializes the board with the starting positions of the pieces
void Board::setBoard()
{
    // Initialize the pieces for white
    square[0][0].setPieceAndColor(ROOK, WHITE);
    square[1][0].setPieceAndColor(KNIGHT, WHITE);
    square[2][0].setPieceAndColor(BISHOP, WHITE);
    square[3][0].setPieceAndColor(QUEEN, WHITE);
    square[4][0].setPieceAndColor(KING, WHITE);
    square[5][0].setPieceAndColor(BISHOP, WHITE);
    square[6][0].setPieceAndColor(KNIGHT, WHITE);
    square[7][0].setPieceAndColor(ROOK, WHITE);

    // Initialize the pieces for black
    square[0][7].setPieceAndColor(ROOK, BLACK);
    square[1][7].setPieceAndColor(KNIGHT, BLACK);
    square[2][7].setPieceAndColor(BISHOP, BLACK);
    square[3][7].setPieceAndColor(QUEEN, BLACK);
    square[4][7].setPieceAndColor(KING, BLACK);
    square[5][7].setPieceAndColor(BISHOP, BLACK);
    square[6][7].setPieceAndColor(KNIGHT, BLACK);
    square[7][7].setPieceAndColor(ROOK, BLACK);

    // Initialize the pawns
    for (int i = 0; i < 8; i++)
    {
        square[i][1].setPieceAndColor(PAWN, WHITE);
        square[i][6].setPieceAndColor(PAWN, BLACK);
    }

    // Clear the rest of the board
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
            square[j][i].setPieceAndColor(EMPTY, NONE);
    }

    // Set the coordinates of the squares
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            square[i][j].setX(i);
            square[i][j].setY(j);
        }
}

// Starts a game of chess
bool Board::playGame()
{
    system("cls");
    printBoard();
    return doMove();
}
