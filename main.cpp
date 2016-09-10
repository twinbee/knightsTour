///////////////////////////////////////////////////////////////////////////
//
// Name: Matthew Bennett
// Class: Artificial Intelligence
// Date: 9-29-05
// Assignment: Knight's Tour, written in C++ using STL
//
// The program uses a recursive method to complete an exhaustive search
//  A knight moves around the chessboard in this pattern:
//  * * * or * * * or * * or * * or        or            *        * 
//      *    *        *        *    *               * or *    or  *
//                    *        *    * * *       * * *    * *    * *
//
// A solution is defined as a path across a chessboard in which all squares have
// been visited by the knight, without any square visited more than once.
// The goal of this code is to find as many solutions for an nxn chessboard as
// possible, where n is given at the start of the execution cycle.
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

using namespace std;

void print(vector <vector <int> > board);
bool unique(vector <vector <int> > board);
bool place(vector<vector <int> > & board, int move, int reqx, int reqy);
bool tryit(vector<vector <int> > board, int move,int nextx,int nexty,int nextd);
void abort(vector<vector <int> > & board, int piece);

int main(int argc, char *argv[])
{
  int dimension, start; //user input
  
  cout << "Enter the dimension of the board (square):";
  cin >> dimension;

    //create a chessboard
  vector<vector<int> > board;
  
   //dynamically size the board
  board.resize(dimension);
  for(int n=0; n<board.size(); n++)
    board[n].resize(dimension);

    //print the board reference
  for(int y=0; y<board.size(); y++) {
  for(int x=0; x<board[0].size(); x++) {
    board[x][y] = x+y*board.size(); } } 

  print(board);

    //zero the board
  for(int y=0; y<board.size(); y++) {
  for(int x=0; x<board[0].size(); x++) {
    board[x][y] = 0; } } 

  cout << "Enter the starting location:";
  cin >> start;

//for (start = 0; start < board.size()*board.size(); start ++)
    //start making moves based upon the position of 1.
  if (!tryit (board, 1, start%board.size(), start/board.size(), 0))
   cout << "NO [more] SOLUTIONS FOUND (UH-OH)!\n";

  system("PAUSE");
  return 0;
}

////////////////////////////////////////////////////////////////////
// place puts knight 'move' at the requested location (reqx,reqy) or
// returns false if there is already a knight there
///////////////////////////////////////////////////////////////////
bool place(vector<vector <int> > & board, int move, int reqx, int reqy)
{
 //off the chessboard and into stack memory
 if (reqx < 0 || reqx >= board.size())         return false;
 if (reqy < 0 || reqy >= board[reqx].size())   return false; 

 if (board[reqx][reqy] == 0)
 {
  board[reqx][reqy] = move;
  return true;
 }
 return false;
}

////////////////////////////////////////////////////////////////////
// removes a piece from the board by resetting its place to 0
///////////////////////////////////////////////////////////////////
void abort(vector<vector <int> > & board, int piece)
{
  for (int y = 0; y < board.size(); y++)
  for (int x = 0; x < board[y].size(); x++)
   if (board[x][y] == piece) board[x][y] = 0;
}
////////////////////////////////////////////////////////////////////
// print simply prints the current state of any board passed to it
///////////////////////////////////////////////////////////////////
void print(vector <vector <int> > board)
{
  for (int y = 0; y < board.size(); y++)
  { for (int x = 0; x < board[y].size(); x++)
    { 
      if (board[x][y] < 10) cout << ' ';
      if (board[x][y] < 100) cout << ' ';
      cout << board[x][y];
    }
    cout << endl; 
  }
}

//////////////////////////////////////////////////////////////////////
// detects whether a board is unique to previous boards passed to it
//////////////////////////////////////////////////////////////////////
bool unique(vector <vector <int> > board)
{
 static vector < vector <vector <int> > > boards;
 
 for (int x = 0; x < boards.size() ; x++)
 {
  if (boards[x] == board) return false;
 }
  boards.push_back(board);
  return true;
}

///////////////////////////////////////////////////////////////////////
// Recursive driver function try
///////////////////////////////////////////////////////////////////////
bool tryit(vector<vector <int> > board, int move, int nextx, int nexty, int nextd)
{
 static int calls = 0;

 calls++;
 if (!(calls%10000000)) cout << "\nRecursive Calls: " << calls/1000000 << " million.\n";

 int x=0, y=0;

 static bool debug = 0;

if (debug)
{
 print (board);
 cout << endl << "Move:  " << move << "    NextD: " << nextd << endl ;
 cout << "NextX: " << nextx << "    NextY: " << nexty << flush << endl ;
 // system("PAUSE");
}

 if (move == board.size()*board.size() + 1) 
 {
  if (unique(board))
  {
   print (board);
   cout << endl << "^^^^^ SOLUTION ^^^^^" << endl ;
   //system("PAUSE");
  }
  return true;
 }

switch (nextd)
{ //set the movement offsets
 case 0: // no movement
  x=0; y=0; break;
 case 1: //top right
  x=1; y=-2; break;
 case 2: //right top
  x=2; y=-1; break; 
 case 3: // right bottom
  x=2; y=1; break; 
 case 4: // bottom right
  x=1; y=2; break;
 case 5: // bottom left
  x=-1; y=2; break; 
 case 6: // left bottom
  x=-2; y=1; break;  
 case 7: // left top
  x=-2; y=-1; break;  
 case 8: // top left
  x=-1; y=-2; break;  

 //no other moves
 default:
  return false;
  //backtracking step
}

if (!place (board, move, nextx+x, nexty+y) )
{
 //no piece has been placed
 tryit(board, move, nextx, nexty, nextd+1); //try the next type of move here
}
else if (!tryit(board, move+1, nextx+x, nexty+y, 0))
 {
  //abort the next move
  abort(board, move+1);
  //and abort this move
  abort(board, move);
  
  //now try the next type of move
  tryit(board, move, nextx, nexty, nextd+1);
 }
}
