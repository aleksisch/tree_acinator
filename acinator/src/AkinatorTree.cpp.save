#include "../include/AkinatorTree.h"

AkinatorTree::AkinatorTree()
{
    head_node = new NodeTree;
    strcpy(head_node->data, "Akinator");

}

AkinatorTree::~AkinatorTree()
{
    FreeTree(head_node);
}

int AkinatorTree::FreeTree(NodeTree* current)
{

    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
        FreeTree(current->left_child);

    if (current->right_child != nullptr)
        FreeTree(current->right_child);

    delete current;
}

NodeTree* AkinatorTree::CreateNode(const char* value)
{
    NodeTree* new_node = new NodeTree;
    strcpy(new_node->data, value);
    return new_node;
}

int AkinatorTree::FillAnswer(NodeTree* cur_node, char* left_value, char* right_value, char* question)
{
    cur_node->left_child = AkinatorTree::CreateNode(left_value);
    cur_node->right_child = AkinatorTree::CreateNode(right_value);
    strcpy(cur_node->data, question);
    return 0;
}

int AkinatorTree::play(NodeTree* current)
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

        fgets(answer, STR_LENGTH, stdin);
        answer[strlen(answer) - 1] = '\0';

        if (answer[0] == 'y' || answer[0] == 'Y')
            printf("haha\n");

        else
        {
            printf("Hmm, enter what about you think:\n");

            char ans[STR_LENGTH] = {};
            char new_q[STR_LENGTH] = {};

            fgets(ans, STR_LENGTH, stdin);
            ans[strlen(ans) - 1] = '\0';

            printf("Enter differences answer, no mean my object, yes mean your's\n");

            fgets(new_q, STR_LENGTH, stdin);
            new_q[strlen(new_q) - 1] = '\0';

            AkinatorTree::FillAnswer(current, ans, current->data, new_q);
        }
    }
    else
    {
        printf("%s or exit to go out\n", current->data);
        char answer[STR_LENGTH] = {0};

        fgets(answer, STR_LENGTH, stdin);
        answer[strlen(answer) - 1] = '\0';

        if (strcmp(answer, "exit") == 0)
            return END_OF_GAME;

        if (answer[0] == 'y' || answer[0] == 'Y')
            AkinatorTree::play(current->left_child);

        else
            AkinatorTree::play(current->right_child);
    }
    return OK;
}

char* ReadFile (const char* str, size_t *size, const char* chmod = "r")
{
    FILE *fp = NULL;

    if ((fp = fopen(str, chmod)) == NULL)
    {
        printf("Cannot find text\n");
        system("pause");
        exit(0);
    }

    fseek (fp, 0L, SEEK_END);

    *size = ftell(fp);

    char *text = (char *) calloc(*size + 1, sizeof(char));

    fseek (fp, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);

    text[*size] = '\0';

    fclose (fp);

    return text;
}

int AkinatorTree::FillGraph(NodeTree* current, char** ptr_on_text)
{
    char first_word[STR_LENGTH] = {};

    int err = FirstWordFromText(ptr_on_text, first_word);

    if (err == 0)
    {
        current->left_child = CreateNode(first_word);

        if ((*ptr_on_text)[0] == '{')
            err |= FillGraph(current->left_child, ptr_on_text);
        else (*ptr_on_text)++;
    }
    char second_word[STR_LENGTH] = {};

    err |= FirstWordFromText(ptr_on_text, second_word);

    if (err == OK)
    {
        current->right_child = CreateNode(second_word);

        if ((*ptr_on_text)[0] == '{')
            err |= FillGraph(current->right_child, ptr_on_text);
        else (*ptr_on_text)++;
    }

    (*ptr_on_text)++;

    if (err == NIL)
        return OK;

    return err;
}

int FirstWordFromText(char** ptr_on_text, char* tmp_word)
{
    (*ptr_on_text)++;
    int counter = 0;

    while ((counter < STR_LENGTH) &&
           ((*ptr_on_text))[0] != '{' &&
           ((*ptr_on_text))[0] != '}')
        {
            if ((*ptr_on_text)[0] != '\n')
                tmp_word[counter++] = (*ptr_on_text)[0];
            (*ptr_on_text)++;

        }

    if (counter + 1 == STR_LENGTH)
        return LONG_STRING;

    if (strcmp(tmp_word, null_word) == 0)
    {
        (*ptr_on_text)++;
        return NIL;
    }

    return OK;
}


int AkinatorTree::ReadGraphFile(const char* input_file)
{
    size_t size = 0;

    char* text = ReadFile(input_file, &size, "r");

    char first_word[STR_LENGTH] = {};

    int err = FirstWordFromText(&text, first_word);

    if (err) PrintError(err, "ReadGraphFile");

    strcpy(head_node->data, first_word);

    err |= FillGraph(head_node, &text);

    if (err) PrintError(err, "ReadGraphFile");

    GraphDump();
    return 0;
}

int AkinatorTree::NodeToFile(NodeTree* current_node, FILE* output_file)
{
    if (current_node  == nullptr)
        fprintf(output_file, "{%s", null_word);
    else
        fprintf(output_file, "{%s", current_node->data);
    if (current_node  != nullptr)
        WriteGraph(current_node, output_file);
    fprintf(output_file, "}");
}

int AkinatorTree::WriteGraph(NodeTree* current_node, FILE* output_file)
{
    NodeToFile(current_node->left_child, output_file);
    NodeToFile(current_node->right_child, output_file);

    return OK;
}

int AkinatorTree::WriteGraphFile(const char* output_file)
{
    FILE* graph_file = fopen(output_file, "w");

    fprintf(graph_file, " %s", head_node->data);

    WriteGraph(head_node, graph_file);
}

int AkinatorTree::WriteDump(FILE* file, NodeTree* current)
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

int AkinatorTree::GraphDump()
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

int AkinatorTree::PrintError(int err_code, const char* function_name)
{
    printf("Error occured in function %s code", function_name, err_code);

}
