#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    //integers representing current position
    int x = 1000;
    int y = 1000;
    //read file into matrices
    std::vector<int> xVec;
    std::vector<int> yVec;
    xVec.push_back(x);
    yVec.push_back(y);
    std::ifstream input("input.txt");
    if (input.is_open()) {
        std::string line;
        while(input.good()){
            std::getline(input, line);
            std::cout << "read line: " << line << std::endl;
            int pos = line.find(' ');
            char direction = line.substr(0, pos)[0];
            line.erase(0, pos+1);
            int length = stoi(line.substr(0, pos));
            switch (direction) {
                case 'U': y += length; break;
                case 'D': y -= length; break;
                case 'L': x -= length; break;
                case 'R': x += length; break;
            }
            xVec.push_back(x);
            yVec.push_back(y);
            std::cout << "pushed x: ";
            std::cout << x;
            std::cout << " y: ";
            std::cout << y << std::endl;
        }
        input.close();
        std::cout << "closed file." << std::endl;
    }
    //calculate area
    size_t i = 0;
    int totalOne = 0;
    int totalTwo = 0;
    while (i < xVec.size()) { totalOne += xVec[i]*yVec[i+1]; ++i;}
    i = 0;
    while (i < yVec.size()) { totalTwo += yVec[i]*xVec[i+1]; ++i;}
    //write output
    std::cout << (totalOne - totalTwo)/2;
    std::cout << " cubic meters" << std::endl;
    return 0;
}
