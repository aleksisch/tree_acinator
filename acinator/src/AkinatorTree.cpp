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

NodeTree* AkinatorTree::CreateNode(char* value)
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


int AkinatorTree::ReadGraphFile(char* file_name)
{
    size_t size = 0;
    char* text = ReadFile(file_name, &size, "r");

    for (size_t ch = 0; ch < size;)
    {
        if (text[ch] == '{')
        {
            size_t start_data = ch;
            char cur_question[STR_LENGTH] = {};

            while (text[++ch] != '{' && text[ch] != '}')
            {
                cur_question[ch - start_data - 1] = text[ch];
            }



        }
        else ch++;
    }

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
