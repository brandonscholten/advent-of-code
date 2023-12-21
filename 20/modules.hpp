#ifndef MODULES_HPP
#define MODULES_HPP

#include <vector>
#include <string>
#include <map>

class Module {
    public:
        Module(const std::string&);
        void receive(const bool&, std::map<std::string, Module>);
        std::string id() {return name;};
        std::string name;
        std::vector<std::string> destinations;
        int low = 0;
        int high = 0;
};

class flipflop : public Module{
    using Module::Module;
    public:
        void receive(const bool&, std::map<std::string, Module>);
    private:
        bool state = false;
};

class conjunction : public Module {
    using Module::Module;
    public:
        void receive(const bool&, std::map<std::string, Module>);
    private:
        std::vector<bool> memory;
};

class broadcaster : public Module {
    using Module::Module;
    public:
        void receive(const bool&, std::map<std::string, Module>);
};

#endif
