#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<char>> floor;
int liveTiles = -1;

void goDown(int, int);
void goLeft(int, int);
void goRight(int, int);
void goUp(int, int);

void goDown (int line, int tile) {
    ++line;
    if (line < floor.size() && tile < floor[line].size()) {
        std::cout << floor[line][tile] << std::endl;
        switch (floor[line][tile]) {
            case '.': 
                floor[line][tile] = 'v';
                ++liveTiles;
                goDown(line, tile);
                break;
            case '/': 
                ++liveTiles;
                goLeft(line, tile);
                break;
            case '\\': 
                ++liveTiles;
                goRight(line, tile);
                break;
            case '|': 
                ++liveTiles;
                goDown(line, tile);
                break;
            case '-': 
                ++liveTiles;
                goLeft(line, tile);
                goRight(line, tile);
                break;
        }
    }
}

void goLeft (int line, int tile) {
    --tile;
    if (tile < 0) {return;}
    if (line < floor.size() && tile < floor[line].size()) {
        std::cout << floor[line][tile] << std::endl;
        switch (floor[line][tile]) {
            case '.': 
                floor[line][tile] = '<';
                ++liveTiles;
                goLeft(line, tile);
                break;
            case '/': 
                ++liveTiles;
                goDown(line, tile);
                break;
            case '\\': 
                ++liveTiles;
                goUp(line, tile);
                break;
            case '|': 
                ++liveTiles;
                goUp(line, tile);
                goDown(line, tile);
                break;
            case '-': 
                ++liveTiles;
                goLeft(line, tile);
                break;
        }
    }
}

void goRight (int line, int tile) {
    ++tile;
    if (line < floor.size() && tile < floor[line].size()) {
        std::cout << floor[line][tile] << std::endl;
        switch (floor[line][tile]) {
            case '.': 
                floor[line][tile] = '>';
                ++liveTiles;
                goRight(line, tile);
                break;
            case '/': 
                ++liveTiles;
                goUp(line, tile);
                break;
            case '\\': 
                ++liveTiles;
                goDown(line, tile);
                break;
            case '|': 
                ++liveTiles;
                goUp(line, tile);
                goDown(line, tile);
                break;
            case '-': 
                ++liveTiles;
                goRight(line, tile);
                break;
        }
    }
}

void goUp (int line, int tile) {
    --line;
    if (line < 0) {return;}
    if (line < floor.size() && tile < floor[line].size()) {
        std::cout << floor[line][tile] << std::endl;
        switch (floor[line][tile]) {
            case '.': 
                floor[line][tile] = '^';
                ++liveTiles;
                goUp(line, tile);
                break;
            case '/': 
                ++liveTiles;
                goRight(line, tile);
                break;
            case '\\': 
                ++liveTiles;
                goLeft(line, tile);
                break;
            case '|': 
                ++liveTiles;
                goUp(line, tile);
                break;
            case '-': 
                ++liveTiles;
                goLeft(line, tile);
                goRight(line, tile);
                break;
        }
    }
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
                floor.push_back(line);
                std::cout << "pushed back a line!" << std::endl;
                line.clear();
            }
        }
        floor.push_back(line);
        input.close();
    }
    //traverse matrice and write output
    goRight(0,-1);
    //send output to file
    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (auto& line : floor) {
            for (auto& tile : line) {
                output << tile;
            }
            output << '\n';
        }
    }
    output << "energized tiles: ";
    output << liveTiles << std::endl;
    output.close();
    return 0;
}
