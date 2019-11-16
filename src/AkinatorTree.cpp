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
        sprintf(tmp_to_printf, "Bad name");
        print_say(tmp_to_printf);
        memset(tmp_to_printf, 0, STR_LENGTH);

        return BAD_NAME;
    }

    sprintf(tmp_to_printf, "%s:\n", name);
    print_say(tmp_to_printf);

    while (strcmp(node_info->question, name))
    {
        sprintf(tmp_to_printf, "\"%s\" %s\n", node_info->question, bool_to_str((node_info)->answer));
        print_say(tmp_to_printf);

        node_info++;
    }

    printf("\n");

    return 0;

}

int AkinatorTree::CompareNode(const char* first_name, const char* second_name)
{
    char tmp_to_printf[STR_LENGTH] = {};
    Question* first_info = new Question[MAX_DEPTH];

    int is_found_first = GetNodeInfo(head_node, first_name, first_info);

    Question* second_info = new Question[MAX_DEPTH];

    int is_found_second = GetNodeInfo(head_node, second_name, second_info);

    if (is_found_first == NIL)
    {
        sprintf(tmp_to_printf, "Bad first name");
        print_say(tmp_to_printf);

        return BAD_NAME;
    }

    if (is_found_second == NIL)
    {
        sprintf(tmp_to_printf, "Bad first name");
        print_say(tmp_to_printf);

        return BAD_NAME;
    }

    while (strcmp(first_info->question,
                  second_info->question) == 0 &&
                  first_info->answer     ==
                  second_info->answer)
    {
        sprintf(tmp_to_printf, "Both object is \"%s\" %s\n", first_info->question, bool_to_str(first_info->answer));
        print_say(tmp_to_printf);

        first_info++;
        second_info++;
    }

    sprintf(tmp_to_printf, "Differences:\n");
    print_say(tmp_to_printf);

    sprintf(tmp_to_printf, "\nfor %s:\n", first_name);
    print_say(tmp_to_printf);

    while (strcmp(first_info->question, first_name))
    {
        sprintf(tmp_to_printf, "\"%s\" %s\n", first_info->question, bool_to_str(first_info->answer));
        print_say(tmp_to_printf);
        first_info++;
    }

    sprintf(tmp_to_printf, "\nfor %s:\n", second_name);
    print_say(tmp_to_printf);
    while (strcmp(second_info->question, second_name))
    {
        sprintf(tmp_to_printf, "\"%s\" %s\n", second_info->question, bool_to_str((second_info)->answer));
        print_say(tmp_to_printf);
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
    sprintf(tmp_to_printf, "what will we do?\n1 - play akinator,\n"
           "2 - compare two object,\n"
           "3 - get information about object\n"
           "if you want end game enter exit: ");
    print_say(tmp_to_printf);
    int type_play = 0;
    scanf("%d%*c", &type_play);

    if (type_play == 1)
        return PlayAkinator();

    if (type_play == 2)
    {
        char first_name[STR_LENGTH] = {};

        sprintf(tmp_to_printf, "enter first object name\n");
        print_say(tmp_to_printf);

        GetString(first_name);

        char second_name[STR_LENGTH] = {};

        sprintf(tmp_to_printf, "Enter second object name\n");
        print_say(tmp_to_printf);

        GetString(second_name);
        CompareNode(first_name, second_name);
    }

    else if (type_play == 3)
    {
        char first_name[STR_LENGTH] = {};

        sprintf(tmp_to_printf, "enter first object name\n");
        print_say(tmp_to_printf);

        GetString(first_name);
        ObjectInfo(first_name);
    }

    else
        sprintf(tmp_to_printf, "exit");
        print_say(tmp_to_printf);

        return END_OF_GAME;

    sprintf(tmp_to_printf, "there");
    print_say(tmp_to_printf);
    return OK;
}

int AkinatorTree::PlayAkinator(TreeNode* current)
{
    if (current == nullptr)
    {
        sprintf(tmp_to_printf, "Ok, let's go\n");
        print_say(tmp_to_printf);

        current = head_node;
    }

    if (current->right_child == nullptr && current->left_child == nullptr)
    {
        sprintf(tmp_to_printf, "I know it was %s? Yes?\n", current->data);
        print_say(tmp_to_printf);

        char answer[STR_LENGTH] = {0};

        GetString(answer);

        if (answer[0] == 'y' || answer[0] == 'Y')
        {
            sprintf(tmp_to_printf, "haha\n");
            print_say(tmp_to_printf);
        }
        else
        {
            sprintf(tmp_to_printf, "Hmm, enter what about you think:\n");
            print_say(tmp_to_printf);

            char ans[STR_LENGTH] = {};
            GetString(ans);

            sprintf(tmp_to_printf, "Enter differences answer, no mean my object, yes mean your's\n");
            print_say(tmp_to_printf);

            char new_q[STR_LENGTH] = {};
            GetString(new_q);

            AkinatorTree::FillAnswer(current, ans, current->data, new_q);
        }
    }
    else
    {
        sprintf(tmp_to_printf, "%s\n", current->data);
        print_say(tmp_to_printf);

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
    FILE* file_graph = fopen(output_graphviz, "w");

    fprintf(file_graph, "digraph G{ \n");

    WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);

    char str_to_system[STR_LENGTH] = {};

    sprintf(str_to_system, "dot -Tjpg -O %s", output_graphviz);

    system(str_to_system);
}

void AkinatorTree::print_say(char* str)
{
    printf(str);
    char console_msg[STR_LENGTH] = {};

    strcpy(console_msg, "echo \"");
    strcpy(console_msg + strlen(console_msg), str);
    strcpy(console_msg + strlen(console_msg), "\"| festival --tts");

    system(console_msg);
    memset(str, 0, STR_LENGTH * sizeof(char));

}
