#include "chess.h"


// Sets the space of the current square to the given space
void Square::setSpace(const Square& space)
{
    // Use const reference to avoid copying the Square object
    color = space.getColor();
    piece = space.getPiece();
}

// Constructor for the Square class
// Sets the current square to empty
void Square::setEmpty()
{
    // Use NONE instead of '0' for better readability
    color = NONE;
    piece = EMPTY;
}

// Gets the piece of the current square
Piece Square::getPiece() const
{
    return piece;
}

// Gets the color of the current square
Color Square::getColor() const
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
void Board::printBoard() const
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
                default:
                    cout << " Invalid Piece ";
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

        if (!isValidMove(x1, y1, x2, y2))
        {
            cout << "Invalid move, try again." << endl;
        }
        else if (!makeMove(x1, y1, x2, y2))
        {
            cout << "Invalid move, try again." << endl;
        }
        else
        {
            stop = true;
        }
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
        {
            square[j][i].setPieceAndColor(EMPTY, NONE);
        }
    }

    // Set the coordinates of the squares
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            square[i][j].setX(i);
            square[i][j].setY(j);
        }
    }
}

// Starts a game of chess
bool Board::playGame()
{
    system("cls");
    printBoard();
    return doMove();
}

bool Board::isValidMove(int x1, int y1, int x2, int y2) const
{
    //Check x, y coordinates in range 0 - 7
    if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7)
    {
        return false;
    }
    //Check if start and end is not same position
    if (x1 == x2 && y1 == y2)
    {
        return false;
    }
    //Check for occupying your player at destination
    if (square[x1][y1].getColor() == square[x2][y2].getColor())
    {
        return false;
    }
    if (square[x2][y2].getPiece() == EMPTY && square[x1][y1 
