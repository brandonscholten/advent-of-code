#include <iostream>
#include <string>
#include "workflow.hpp"

part::part(const std::string& input){
    int pos = input.find('x')+2;
    x = stoi(input.substr(pos, input.find(',', pos)-1));
    pos = input.find('m')+2;
    m = stoi(input.substr(pos, input.find(',', pos)-1));
    pos = input.find('a')+2;
    a = stoi(input.substr(pos, input.find(',', pos)-1));
    pos = input.find('s')+2;
    s = stoi(input.substr(pos, input.find(',', pos)-1));
}

workflow::workflow(const std::string& input){
    size_t pos = input.find("{");
    //get the name of the workflow
    name = input.substr(0, pos-1);
    //get first category
    categories.push_back(input[pos+1]);
    //get most of the things
    for (pos; input[pos] != '}'; ++pos) {
        
        if (input[pos] == '>' || input[pos] == '<') {
            conditions.push_back(input[pos]);
            int end = input.find(":", pos);
            int threshold = stoi(input.substr(pos+1, end));
            thresholds.push_back(threshold);
        } else if (input[pos] == ':') {
            actions.push_back(input.substr(pos+1, input.find(",", pos)));
        } else if (input[pos] == ',') {
            categories.push_back(input[pos+1]);
        } else {
            continue;
        }
    }
    //push the default action (used if no conditions are true)
    actions.push_back(input.substr(input.find_last_of(","), pos-1));
}

int workflow::process(
    const part& part, 
    std::vector<workflow> flows,
    const std::string& action
    ) {
    //search vector for action then call process on it if action is not NULL
    if (action != "NULL") {
        for (auto& it : flows) {
            if (it.name == action) {
                it.process(part, flows);
            }
        }
    }
    //normal execution
    for (size_t i = 0; i < conditions.size(); ++i) {
        switch (conditions[i]) {
            case '<':
                if (categories[i] < thresholds[i]) {
                    if (actions[i] == "R") {return 0;}
                    if (actions[i] == "A") {return part.sum();}
                }
                return this->process(part, flows ,actions[i]);
                break;
            case '>':
                if (categories[i] > thresholds[i]) {
                    if (actions[i] == "R") {return 0;}
                    if (actions[i] == "A") {return part.sum();}
                }
                return this->process(part, flows ,actions[i]);
                break;
        }
    }
}
