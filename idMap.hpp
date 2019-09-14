#include <map>

std::map<std::string, int> commandID;
void declareID()
{
    commandID.insert(std::pair<std::string, int>("exit", 0));
    commandID.insert(std::pair<std::string, int>("ndir", 1));
    commandID.insert(std::pair<std::string, int>("cd", 3));
    commandID.insert(std::pair<std::string, int>("yash", 4));
    commandID.insert(std::pair<std::string, int>("lst", 5));
    commandID.insert(std::pair<std::string, int>("guide", 6));
    commandID.insert(std::pair<std::string, int>("pdr", 7));
    commandID.insert(std::pair<std::string, int>("ddir", 8));
    commandID.insert(std::pair<std::string, int>("clr", 9));
    commandID.insert(std::pair<std::string, int>("fnd", 11));
    commandID.insert(std::pair<std::string, int>("cp", 12));
    commandID.insert(std::pair<std::string, int>("pst", 13));
}
