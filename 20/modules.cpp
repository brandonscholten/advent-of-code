#include <vector>
#include <string>
#include "modules.hpp"

Module::Module(const std::string& input) {
    int pos = input.find(" ");
    name = input.substr(1, pos-1);
    std::string result;
    for (size_t i = pos; pos < input.length(); ++i) {
        if (input[i] == ' ') {
            destinations.push_back(result);
            result.clear(); 
            continue;
        }
        if (input[i] == ',') { continue; }
        result.push_back(input[i]);
    }
}

void flipflop::receive(const bool& signal, std::map<std::string, Module> nodes) {
    //adjust state
    if (!signal) { state  = !state; }
    //send pulse and adjust counter
    for (auto& destination : destinations) {
        if (state) {++high;} else {++low;}
        nodes[destination].receive(state, nodes);
    }
}

void conjunction::receive(const bool& signal, std::map<std::string, Module> nodes) {
    memory.push_back(signal);
    bool pulse = false;
    for (auto signal : memory) {
        if (signal) {pulse = true;}
    }
    for (auto& destination : destinations) {
        if (pulse) {++high;} else {++low;}
        nodes[destination].receive(pulse, nodes);
    }
}

void broadcaster::receive(const bool& signal, std::map<std::string, Module> nodes) {
    for (auto& destination : destinations) {
        if (signal) {++high;} else {++low;}
        nodes[destination].receive(signal, nodes);
    }
}
