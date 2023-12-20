#include <iostream>
#include <fstream>
#include <string>
#include "workflow.hpp"

int main() {
    std::vector<workflow> workflows;
    std::vector<part> parts;
    //reading file and adding total
    int total = 0;
    bool flow = true;
    std::string line;
    std::ifstream input("input.txt");
    if (input.is_open()) {
        while (!input.eof()) {
            std::getline(input, line);
            if (line.length() < 2) {flow = false;}
            if (flow) {workflows.push_back(workflow(line));}
            else if (line.length() > 2) {parts.push_back(part(line));}
        }
        input.close();
    }
    for (auto& part : parts) {
        total += workflows[0].process(part, workflows);
    }
    std::cout << "rating sum: ";
    std::cout << total << std::endl;
}
