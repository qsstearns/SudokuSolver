#include <iostream>
#include "simpleStack.h"

using namespace std;

void solve(uint16_t [9][9]);
bool findBest(uint16_t [9][9], Stack &s);
int countBits(unsigned int n);
bool validChoice(uint16_t &cell);

const uint16_t IS_FILLED_IN = 0x8000;
const uint16_t VALUE_MASK = 0x000f;
const uint16_t VALID_MASK = 0x1ff0;
uint16_t IS_1VALID = 0x0010;
uint16_t board[9][9];

int main(void){
    char cell;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin>>cell;
            if(cell == '.')
                board[i][j] = 0;
            else
                board[i][j] = IS_FILLED_IN + cell - '0';
        }
    }

    solve(board);

    return 0;
}

//procedure Solve
void solve(uint16_t board[9][9]){
    bool a;
    Stack s;
    int i,j;

//  select the best empty cell and place its location on the stack
    a = findBest(board, s);

        //  while true do
    while(true){
    //  let(i,j) be the location on top of the stack
        i = s.peek() / 9;
        j = s.peek() % 9;

    //      select the next valid choice for board[i][j]
    //      if no such choice exists then
    //          mark board[i][j] as not filled in
    //          pop the stack
    //          if the stack is empty then
    //              return the puzzle has no solution
    //          end if
    //          continue
    //      end if

        if(!validChoice(board[i][j])){
            board[i][j] &= ~IS_FILLED_IN;
            s.pop();
            if(s.isEmpty()){
                cout<<"The puzzle has no solution"<<endl;
                return;
            }
            continue;
        }

        //      select the best empty cell and place its location on the stack
        //      if no such cell exists then
        //          break
        //      end if
        //  end while

        a = findBest(board, s);
        if(a == 0)
            break;

    }
//  output the solution
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout<< (board[i][j] & VALUE_MASK) << " ";
        }
        cout<< endl;
    }
//end procedure
}

//procedure findBest
bool findBest(uint16_t board[9][9], Stack &s){
    int low,r2, c2, count, i2, j2, r, c, cell;

//for each empty cell board[i][j] do
//     mark all digits as valid choices
// end for

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if((board[i][j] & IS_FILLED_IN) == 0)
                board[i][j] = VALID_MASK;
        }
    }

//  for each filled in cell board[i][j] do
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if((board[i][j] & IS_FILLED_IN) != 0){
                uint16_t mask = ~(IS_1VALID << ((board[i][j] & VALUE_MASK)-1));

        //      for each unfilled cell in column j do
        //          mark digit in board[i][j] as an invalid choice
                for(int r = 0; r < 9; r++){
                    if((board[r][j] & IS_FILLED_IN) == 0)
                        board[r][j] &= mask;
                }
        //      end for

        //      for each unfilled cell in row i do
        //          mark digit in board[i][j] as an invalid choice
                for (int c=0;c<9;c++){
                    if ((board[i][c] & IS_FILLED_IN) == 0)
                        board[i][c] &= mask;
                }
        //      end for

        //      for each unfilled cell in the 3x3 block containing board[i][j] do
        //          mark digit in board[i][j]
                r = (i/3)*3;
                c = (j/3)*3;
                for(int r2 = 0; r2 < 3; r2++){
                    for(int c2 = 0; c2 < 3; c2++){
                        if((board[r+r2][c+c2] & IS_FILLED_IN) == 0)
                            board[r+r2][c+c2] &= mask;
                        }
                    }
    //                  end for
    //          end for
            }
        }
    }

// set low = 10
    low = 10;

//  for each empty cell board[i][j] do
//      count 1-bits in valid choices for board[i][j]
//      if count < low then
//          low = count
//          i(best) = i
//          j(best) = j
//      end if
//  end for

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if((board[i][j] & IS_FILLED_IN) == 0){
                count = countBits(board[i][j] & VALID_MASK);
                if(count < low){
                    low = count;
                     i2 = i;
                     j2 = j;
                }
            }
        }
    }

//  if low = 10 then
//      return false
//  end if

    if(low == 10){
        return false;
    }

//  mark board[i(best)][j(best)] as filled in
    board[i2][j2] |= IS_FILLED_IN;
    cell = i2 * 9 + j2;
//  push (i(best),j(best)) onto the stack
    s.push(cell);

//  return true
    return true;
//end procedure
}

int countBits(unsigned int n) {
    int
        count = 0;

    while ( n != 0) {
        count++;
        n &= n - 1;
    }

    return count;
}

bool validChoice(uint16_t &cell){
    uint16_t mask = IS_1VALID;

    for(int i = 0; i < 9; i++){
        if((cell & mask) != 0){
            cell &= ~(mask | VALUE_MASK);
            cell |= i + 1;
            return true;
        }
        mask <<= 1;
    }
    return false;
}
