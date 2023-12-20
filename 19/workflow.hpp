#ifndef WORKFLOW_HPP
#define WORKFLOW_HPP
#include <vector>
#include <string>

class part {
    public:
        part(const std::string&);
        int sum() const {return x+m+a+s;};
        int x = 0;
        int m = 0;
        int a = 0;
        int s = 0;
};

class workflow {
    public:
        workflow(const std::string&);
        int process(
            const part&, std::vector<workflow>, 
            const std::string& action = "NULL"
            );
    private:
        std::string name;
        std::vector<char> categories;
        std::vector <char> conditions;
        std::vector <int> thresholds; 
        std::vector <std::string> actions;
};

#endif