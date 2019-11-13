#ifndef AKINATORTREE_H
#define AKINATORTREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "WorkFile.h"

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

        int GraphToDot();

        int Play();

        int PlayAkinator(TreeNode* current = nullptr);

        int ReadGraphFile(const char* input_file = input_graph_file);

        int WriteGraphFile(const char* output_file = output_graph_file);

        int CompareNode(const char* first_name, const char* second_name);

        int ObjectInfo(const char* name);

    private:

        void print_say(char* str);

        char tmp_to_printf[STR_LENGTH] = {};        //used to generate string with sprintf

        int FillGraph(TreeNode* current, char** ptr_on_text);

        TreeNode* head_node;

        int NodeToFile(TreeNode* current_node, FILE* output_file);

        int FillAnswer(TreeNode* cur_node, const char* left, const char* right, const char* question);

        int WriteDump(FILE* file, TreeNode* current = nullptr);

        void FreeTree(TreeNode* current);

        int GetNodeInfo(TreeNode* current, const char* name, Question* arr_q, int counter = 0);

        int WriteGraph(TreeNode* current_node, FILE* output_file);
};
#endif // AKINATORTREE_H
