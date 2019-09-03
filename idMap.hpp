#include <string>

struct Node
{
    std::string name;
    Node *firstChild;
    Node *sibling;
    Node *parent;
};
