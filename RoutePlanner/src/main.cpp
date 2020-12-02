#include <iostream>
#include "Astar.h"


int main() {
    int init[2]{ 0, 0 };
    int goal[2]{ 4, 5 };
    auto board = ReadBoardFile("board.txt");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
    // Tests
}