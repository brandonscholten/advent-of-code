#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>

std::vector<std::vector<char>> map;
int cost = 0;

int upCount = 0;
int downCount = 0;
int leftCount = 0;
int rightCount = 0;

void goDown(int, int, int&);
void goLeft(int, int, int&);
void goRight(int, int, int&);
void goUp(int, int, int&);
void choose(int, int);

void goDown (int row, int col, int& called) {
    if (map[row][col]) {
        ++called;
        map[row][col] = 'v';
        choose(row+1, col);
    }
}

void goLeft (int row, int col, int& called) {
    if (map[row][col]) {
        ++called;
        map[row][col] = '<';
        choose(row, col-1);
    }
}

void goRight (int row, int col, int& called) {
    if (map[row][col]) {
        ++called;
        map[row][col] = '>';
        choose(row, col+1);
    }
}

void goUp (int row, int col, int& called) {
    if (map[row][col]) {
        ++called;
        map[row][col] = '^';
        choose(row-1, col);
    }
}

void choose(int row, int col) {
    std::cout << "choosing direction" << std::endl;
    //check cost in four directions
    //add lowest cost to cost and call corresponding function to write characters
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    //up
    if (row-1 < 0 || row-1 > map.size()){
        up += 100; //ensure that this is too costly
    } else if (map[row-1][col]) {
        std::cout << "looking up" << std::endl;
        up += map[row-1][col];
    }
    //left
    if (col-1 < 0 || col-1 > map[row].size()){
        left += 100; //ensure that this is too costly
    } else if (map[row][col-1]) {
        std::cout << "looking left" << std::endl;
        left += map[row][col-1];
    }
    //right
    if (col+1 < 0 || col+1 > map[row].size()){
        right += 100; //ensure that up this too costly
    } else if (map[row][col+1]) {
        std::cout << "looking right" << std::endl;
        right += map[row][col+1];
    }
    //down
    if (row+1 < 0 || row+1 > map.size()){
        down += 100; //ensure that up this too costly
    } else if (map[row+1][col]) {
        std::cout << "looking down" << std::endl;
        down += map[row+1][col];
    }

    int lowest = std::min(up, std::min(down, std::min(left, right)));
    std::cout << "found lowest cost path" << std::endl;

    if (upCount >= 3) {
        lowest = std::min(down, std::min(left, right)); 
        upCount = 0;
    }

    if (downCount >= 3) {
        lowest = std::min(up, std::min(left, right));
        downCount = 0;
    }

    if (leftCount >= 3) {
        lowest = std::min(up, std::min(down, right)); 
        leftCount = 0;
    }

    if (rightCount >= 3) {
        lowest = std::min(up, std::min(down, left));
        rightCount = 0;
    }

    if (lowest == up && upCount < 3) {
        goUp(row, col, upCount);
    }

    if (lowest == down && downCount < 3) {
        goDown(row, col, downCount);
    }

    if (lowest == left && leftCount < 3) {
        goLeft(row, col, leftCount);
    }

    if (lowest == right && rightCount < 3) {
        goRight(row, col, rightCount);
    }


    cost += lowest;

}

int main() {
    //read file into a matrice
    std::ifstream input("input.txt");
    if (input.is_open()) {
        std::vector<char> line;
        char current;
        while(input.get(current) && input.eof() == false){
            if (current != '\n'){
                line.push_back(current);
            } else {
                map.push_back(line);
                std::cout << "pushed back a line!" << std::endl;
                line.clear();
            }
        }
        map.push_back(line);
        std::cout << "all lines pushed back" << std::endl;
        input.close();
        std::cout << "input file closed" << std::endl;
    }
    //traverse matrice and write output
    choose(0, 0);
    //send output to file
    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (auto& line : map) {
            for (auto& number : line) {
                output << number;
            }
            output << '\n';
        }
    }
    output << "cost: ";
    output << cost << std::endl;
    output.close();
    return 0;
}
