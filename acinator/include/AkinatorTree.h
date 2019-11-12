#ifndef AKINATORTREE_H
#define AKINATORTREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

struct Question
{
    char question[STR_LENGTH] = {};
    bool answer = false;
};

struct TreeNode
{
    char data[STR_LENGTH] {};
    TreeNode* left_child;
    TreeNode* right_child;

    TreeNode(const char* t_data = "666") :
        left_child(nullptr),
        right_child(nullptr)
    {
        strcpy(data, t_data);
    }
};

class AkinatorTree
{
    public:
        AkinatorTree();
        ~AkinatorTree();

        int play(TreeNode* current = nullptr);

        int GraphDump();

        int ReadGraphFile(const char* input_file = input_graph_file);

        int WriteGraphFile(const char* output_file = output_graph_file);

        int CompareNode(const char* first_name, const char* second_name);

        int ObjectInfo(const char* name);

    private:

        TreeNode* head_node;

        int NodeToFile(TreeNode* current_node, FILE* output_file);

        int FillGraph(TreeNode* current, char** ptr_on_text);

        int FillAnswer(TreeNode* cur_node, const char* left, const char* right, const char* question);

        int WriteDump(FILE* file, TreeNode* current = nullptr);

        int FreeTree(TreeNode* current);

        int PrintError(int err_code, const char* function_name = "");

        int GetNodeInfo(TreeNode* current, const char* name, Question* arr_q, int counter = 0);

        int WriteGraph(TreeNode* current_node, FILE* output_file);
};

int FirstWordFromText(char** ptr_on_text, char* word);
char* bool_to_str(bool a);

#endif // AKINATORTREE_H