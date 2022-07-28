#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


bool found = false;
vector<char> solution;


// checks if the number given is repeated for that index
bool isRepeated(vector<char>& board, int index, char n){
  unordered_set<string> set;
  string number = to_string(n);
  string val;
  
  for(int i = 0; i < board.size();i++){
    val = to_string(board[i]);
    set.insert(val + "row" + to_string(i / 9));
    set.insert(val + "col" + to_string(i % 9));
    set.insert(val + "box" + to_string(int((i % 9 )/ 3)) + to_string(int(i / 27)));
  }
  if ((set.find(number + "row" + to_string(index / 9)) != set.end())
      || ((set.find(number + "col" + to_string(index % 9))) != set.end())
      || (set.find(number + "box" + to_string(int((index % 9 )/ 3)) + to_string(int(index / 27))) != set.end())){
      return true;
  }
  return false;
}

// prints vector in sudoku board form
void toString(const vector<char> board){
  int index = 0;
  
  cout << "+-------+-------+-------+" << endl; 
    for (int i = 0; i < 3; i++)                 
    {
        for (int j = 0; j < 3; j++)        
        {
            cout << "|";                      
            for (int k = 0; k < 3; k++)        
            {
                cout << " " << board[index] << " " << board[index+1]
                    << " "<< board[index+2] << " |";
                index += 3;
            }
            cout << endl;
        }
        cout << "+-------+-------+-------+" << endl;
    }
}

// converts a string to vector
vector<char> fromString(string sudoku){
  vector<char> board;
  
  for(int i =0; i < sudoku.size();i++){
    if(sudoku.at(i) != ' '){
      board.push_back(sudoku.at(i));
    }
  }
  return board;
}


// recursive function 
void sudoku(vector<char> board, int index){
  if(found) return;
  if(index >= 81){
    for(int i =0; i < board.size();i++){
      solution.push_back(board[i]);
    }
    found = true;
    return;
  }
  // if empty space, checks values that could be inserted and branches
  if(board[index] == '0'){
    bool added = false;
    for(int i = 1; i <= 9;i++){
      char target = char(i + 48);
      if(!isRepeated(board,index, target)){
        board[index] = target;
        added = true;
        sudoku(board, index + 1);
      }
    }
    if(!added) return;
  }else{
    sudoku(board, index + 1);
  }
}

int main() {
  string input = "4 0 3 0 5 1 0 6 0 0 5 0 6 0 3 1 0 4 1 0 8 2 4 0 3 5 0 9 0 5 0 6 0 0 7 1 8 0 2 9 0 0 0 3 0 0 1 6 0 7 0 2 0 5 0 3 0 1 0 4 0 8 0 6 9 0 8 2 0 0 4 0 2 0 4 0 3 0 7 0 9";
  // no solution sudoku board
  //string input = "4 4 3 0 5 1 0 6 0 0 5 0 6 0 3 1 0 4 1 0 8 2 4 0 3 5 0 9 0 5 0 6 0 0 7 1 8 0 2 9 0 0 0 3 0 0 1 6 0 7 0 2 0 5 0 3 0 1 0 4 0 8 0 6 9 0 8 2 0 0 4 0 2 0 4 0 3 0 7 0 9"; 
  //string input = "0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  vector<char> board = fromString(input);
  toString(board);
  sudoku(board,0);


  
  if(found){
    toString(solution);
  }else{
    cout << "not found";
  }
}