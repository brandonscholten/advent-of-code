#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "modules.hpp"

int main () {
    //map of modules
    std::map<std::string, Module> modules;
    //vector of names to index modules
    std::vector<std::string> names;
    //keep track of first module
    std::string first; 
    //read file, initialize modules, add to map
    std::ifstream input("input.txt");
    if (input.is_open()) {
        std::string line;
        std::getline(input, line);
        first = line.substr(1, line.find(" ")-1);
        while (!input.eof()) {
            std::string name = line.substr(1, line.find(" ")-1);
            names.push_back(name);
            switch (line[0]) {
                case '%':
                    flipflop n(line);
                    modules.insert(std::pair<std::string, Module>(name, n));
            }
            std::getline(input, line);
        }
        input.close();
    }
    //total number of high and low signals sent
    int high = 0; int low = 0;
    //loop 1000 times to simulate button presses:
    //  send a low pulse to the first module
    //  loop to add high and low values of each module
    for (int i = 0; i < 1000; ++i) {
        modules[first].receive(false, modules);
        for (auto& name : names) {
            high += modules[name].high;
            low += modules[name].low;
        }
    }
    //output result and end program
    std::cout << "low * high = ";
    std::cout << low*high << std::endl;
    return 0;
}
