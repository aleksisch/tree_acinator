#ifndef AKINATORTREE_H
#define AKINATORTREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

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

        int GraphDump();
        int ReadGraphFile(const char* input_file = INPUT_GRAPH_FILE);

        int WriteGraph(NodeTree* current_node, FILE* output_file);
        int WriteGraphFile(const char* output_file = OUTPUT_GRAPH_FILE);
    protected:

    private:
        NodeTree* CreateNode(const char* data = "666");
        NodeTree* head_node;

        int NodeToFile(NodeTree* current_node, FILE* output_file);
        int FillGraph(NodeTree* current, char** ptr_on_text);
        int FillAnswer(NodeTree* cur_node, char* left, char* right, char* question);
        int WriteDump(FILE* file, NodeTree* current = nullptr);
        int FreeTree(NodeTree* current);
};

int FirstWordFromText(char** ptr_on_text, char* word);

#endif // AKINATORTREE_H
