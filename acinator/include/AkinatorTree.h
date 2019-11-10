#ifndef AKINATORTREE_H
#define AKINATORTREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const int STR_LENGTH = 255;

struct NodeTree
{
    char data[STR_LENGTH] {};
    NodeTree* left_child;
    NodeTree* right_child;
    NodeTree() :left_child(nullptr),
                right_child(nullptr)
                {}
};

class AkinatorTree
{
    public:
        AkinatorTree();
        ~AkinatorTree();
        int play(NodeTree* current = nullptr);
        int ReadGraphFile(char* file_name);
    protected:

    private:
        NodeTree* CreateNode(char* data);
        int FillAnswer(NodeTree* cur_node, char* left, char* right, char* question);
        NodeTree* head_node;

};

bool IsEnterYes(char* str);

#endif // AKINATORTREE_H
