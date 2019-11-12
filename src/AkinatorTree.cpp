#include "../include/AkinatorTree.h"

AkinatorTree::AkinatorTree()
{
    head_node = new TreeNode;
    strcpy(head_node->data, "Akinator?");
}

AkinatorTree::~AkinatorTree()
{
    FreeTree(head_node);
}

void AkinatorTree::FreeTree(TreeNode* current)
{

    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
        FreeTree(current->left_child);

    if (current->right_child != nullptr)
        FreeTree(current->right_child);

    delete current;
}

int AkinatorTree::FillAnswer(TreeNode* cur_node, const char* left_value, const char* right_value, const char* question)
{
    cur_node->left_child  = new TreeNode(left_value);
    cur_node->right_child = new TreeNode(right_value);

    strcpy(cur_node->data, question);

    return 0;
}

int AkinatorTree::ObjectInfo(const char* name)
{
    Question* node_info = new Question[MAX_DEPTH];

    bool is_found = GetNodeInfo(head_node, name, node_info);

    if (is_found == NIL)
    {
        printf("Bad name");
        return BAD_NAME;
    }

    printf("%s:\n", name);

    while (strcmp(node_info->question, name))
    {
        printf("\"%s\" %s\n", node_info->question, bool_to_str((node_info)->answer));
        node_info++;
    }

    printf("\n");

    return 0;

}

int AkinatorTree::CompareNode(const char* first_name, const char* second_name)
{
    Question* first_info = new Question[MAX_DEPTH];

    int is_found_first = GetNodeInfo(head_node, first_name, first_info);

    Question* second_info = new Question[MAX_DEPTH];

    int is_found_second = GetNodeInfo(head_node, second_name, second_info);

    if (is_found_first == NIL)
    {
        printf("Bad first name");
        return BAD_NAME;
    }

    if (is_found_second == NIL)
    {
        printf("Bad first name");
        return BAD_NAME;
    }

    while (strcmp(first_info->question,
                  second_info->question) == 0 &&
                  first_info->answer     ==
                  second_info->answer)
    {
        printf("Both object is \"%s\" %s\n", first_info->question, bool_to_str(first_info->answer));
        first_info++;
        second_info++;
    }

    printf("Differences:\n");

    printf("\nfor %s:\n", first_name);

    while (strcmp(first_info->question, first_name))
    {
        printf("\"%s\" %s\n", first_info->question, bool_to_str(first_info->answer));
        first_info++;
    }

    printf("\nfor %s:\n", second_name);

    while (strcmp(second_info->question, second_name))
    {
        printf("\"%s\" %s\n", second_info->question, bool_to_str((second_info)->answer));
        second_info++;
    }

    printf("\n");

    return 0;
}

int AkinatorTree::GetNodeInfo(TreeNode* current, const char* name, Question* arr_q, int counter)
{
    if (current == nullptr) ;

    else if (strcmp(current->data, name) == 0)
    {
        strcpy(arr_q[counter].question, current->data);
        return OK;
    }

    else
    {
        strcpy(arr_q[counter].question, current->data);
        int res = OK;

        res = GetNodeInfo(current->left_child, name, arr_q, counter + 1);
        if (res == OK)
        {
            arr_q[counter].answer = true;
            return OK;
        }

        res = GetNodeInfo(current->right_child, name, arr_q, counter + 1);
        if (res == OK)
        {
            arr_q[counter].answer = false;
            return OK;
        }
    }

    return NIL;
}

int AkinatorTree::Play()
{
    printf("what will we do?\n1 - play akinator,\n"
           "2 - compare two object,\n"
           "3 - get information about object\n"
           "if you want end game enter exit: ");
    int type_play = 0;
    scanf("%d%*c", &type_play);

    if (type_play == 1)
        return PlayAkinator();

    if (type_play == 2)
    {
        char first_name[STR_LENGTH] = {};
        printf("enter first object name\n");
        GetString(first_name);

        char second_name[STR_LENGTH] = {};
        printf("Enter second object name\n");
        GetString(second_name);
        CompareNode(first_name, second_name);
    }

    else if (type_play == 3)
    {
        char first_name[STR_LENGTH] = {};
        printf("enter first object name\n");
        GetString(first_name);
        ObjectInfo(first_name);
    }

    else
        printf("exit");
        return END_OF_GAME;
    printf("there");
    return OK;
}

int AkinatorTree::PlayAkinator(TreeNode* current)
{
    if (current == nullptr)
    {
        printf("Ok, let's go\n");
        current = head_node;
    }

    if (current->right_child == nullptr && current->left_child == nullptr)
    {
        printf("I know it was %s? Yes?\n", current->data);

        char answer[STR_LENGTH] = {0};

        GetString(answer);

        if (answer[0] == 'y' || answer[0] == 'Y')
            printf("haha\n");

        else
        {
            printf("Hmm, enter what about you think:\n");

            char ans[STR_LENGTH] = {};
            GetString(ans);

            printf("Enter differences answer, no mean my object, yes mean your's\n");

            char new_q[STR_LENGTH] = {};
            GetString(new_q);

            AkinatorTree::FillAnswer(current, ans, current->data, new_q);
        }
    }
    else
    {
        printf("%s end\n", current->data);
        char answer[STR_LENGTH] = {};
        GetString(answer);

        if (strcmp(answer, "exit") == 0)
            return END_OF_GAME;

        if (answer[0] == 'y' || answer[0] == 'Y')
            AkinatorTree::PlayAkinator(current->left_child);

        else
            AkinatorTree::PlayAkinator(current->right_child);
    }
    return OK;
}


int AkinatorTree::FillGraph(TreeNode* current, char** ptr_on_text)
{
    char first_word[STR_LENGTH] = {};

    int err = FirstWordFromText(ptr_on_text, first_word);

    current->left_child = new TreeNode(first_word);

    if (err == OK)
        err |= FillGraph(current->left_child, ptr_on_text);

    char second_word[STR_LENGTH] = {};

    int err2 = FirstWordFromText(ptr_on_text, second_word);

    current->right_child = new TreeNode(second_word);

    if (err2 == OK)
        err2 |= FillGraph(current->right_child, ptr_on_text);

    SkipToBrace(ptr_on_text);

    if ((err  == NIL || err  == OK) ||
        (err2 == NIL || err2 == OK))
        return OK;

    return (err | err2);
}


int AkinatorTree::ReadGraphFile(const char* input_file)
{
    size_t size = 0;

    char* text = ReadFile(input_file, &size, "r");

    FirstWordFromText(&text, (head_node->data));

    int err = FillGraph(head_node, &text);

    if (err) PrintError(err, "ReadGraphFile");

    return 0;
}

int AkinatorTree::NodeToFile(TreeNode* current_node, FILE* output_file)
{
    if (current_node  != nullptr)
    {
        fprintf(output_file, "{ \n\t\"%s\"\n", current_node->data);
        WriteGraph(current_node, output_file);
    }

    fprintf(output_file, " }\n");
}

int AkinatorTree::WriteGraph(TreeNode* current_node, FILE* output_file)
{
    NodeToFile(current_node->left_child, output_file);
    NodeToFile(current_node->right_child, output_file);

    return OK;
}

int AkinatorTree::WriteGraphFile(const char* output_file)
{
    FILE* graph_file = fopen(output_file, "w");

    fprintf(graph_file, "{ \"%s\"\n", head_node->data);

    WriteGraph(head_node, graph_file);

    fprintf(graph_file, "}");

    fclose(graph_file);
}

int AkinatorTree::WriteDump(FILE* file, TreeNode* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->data), current->data);
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->left_child->data),
                                                          current->left_child->data);
        fprintf(file, "tree_node%p->tree_node%p\n\n", current->data, current->left_child->data);

        WriteDump(file, current->left_child);
    }

    if (current->right_child != nullptr)
    {
        fprintf(file, "tree_node%p [label = \"%s\"];\n", &(current->data), current->data);
        fprintf(file, "tree_node%p [label = \"%s\"];\n\n", &(current->right_child->data),
                                                          current->right_child->data);
        fprintf(file, "tree_node%p->tree_node%p\n\n", current->data, current->right_child->data);

        WriteDump(file, current->right_child);
    }
}

int AkinatorTree::GraphToDot()
{
    char input_path[STR_LENGTH] = {};
    sprintf(input_path, "%s%s", path_to_graphviz, output_graphviz);

    FILE* file_graph = fopen(input_path, "w");

    fprintf(file_graph, "digraph G{ \n");

    WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);

    char str_to_system[STR_LENGTH] = {};

    sprintf(str_to_system, "cd/d %s && dot.exe -Tjpg -O %s", path_to_graphviz, output_graphviz);

    system(str_to_system);
}
