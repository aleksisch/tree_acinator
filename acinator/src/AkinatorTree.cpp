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
        printf("%s\n", current->data);
        char answer[STR_LENGTH] = {0};

        fgets(answer, STR_LENGTH, stdin);
        answer[strlen(answer) - 1] = '\0';

        if (answer[0] == 'y' || answer[0] == 'Y')
            AkinatorTree::play(current->left_child);
        else
            AkinatorTree::play(current->right_child);
    }
    return 0;
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
    printf("%s\n\n", *ptr_on_text);

    char first_word[STR_LENGTH] = {};

    int err = FirstWordFromText(ptr_on_text, first_word);

    if (err == 0)
    {
        current->left_child = CreateNode(first_word);

        if ((*ptr_on_text)[0] == '{')
            FillGraph(current->left_child, ptr_on_text);
        else (*ptr_on_text)++;
    }
    char second_word[STR_LENGTH] = {};

    err = FirstWordFromText(ptr_on_text, second_word);

    if (err == 0)
    {
        current->right_child = CreateNode(second_word);

        if ((*ptr_on_text)[0] == '{')
            FillGraph(current->right_child, ptr_on_text);
        else (*ptr_on_text)++;
    }
    (*ptr_on_text)++;
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

            printf("in func %c %s\n", (*ptr_on_text)[0],  tmp_word);

        }

    if (counter + 1 == STR_LENGTH)
        return 2;

    if (strcmp(tmp_word, "nil") == 0)
    {
        (*ptr_on_text)++;
        return 1;
    }

    return 0;
}


int AkinatorTree::ReadGraphFile(const char* file_name)
{
    size_t size = 0;

    char* text = ReadFile(file_name, &size, "r");

    char first_word[STR_LENGTH] = {};

    FirstWordFromText(&text, first_word);

    printf("data %s\n", first_word);

    strcpy(head_node->data, first_word);

    FillGraph(head_node, &text);

    GraphDump();
    return 0;
}

int AkinatorTree::WriteDump(FILE* file, NodeTree* current)
{
    if (current == nullptr)
        current = head_node;

    if (current->left_child != nullptr)
    {
        fprintf(file, "\"%s\"->\"%s\"\n", current->data, current->left_child->data);
        WriteDump(file, current->left_child);
    }

    if (current->right_child != nullptr)
    {
        fprintf(file, "\"%s\"->\"%s\"\n", current->data, current->right_child->data);
        WriteDump(file, current->right_child);
    }
}

int AkinatorTree::GraphDump()
{
    FILE* file_graph = fopen("./graphviz/tmp_dump.dt", "w");
    fprintf(file_graph, "digraph G{ ");

    WriteDump(file_graph);

    fprintf(file_graph, "}");

    fclose(file_graph);
    system("cd/d ./graphviz/ && dot.exe -Tjpg -O tmp_dump.dt");

}
