#include "../include/AkinatorTree.h"

int FirstWordFromText(char** ptr_on_text, char* tmp_word)
{
    SkipToBrace(ptr_on_text);

    (*ptr_on_text)++;

    int counter = 0;

    bool is_one_quote = false;

    while (counter < STR_LENGTH &&
           **ptr_on_text != '{' &&
           **ptr_on_text != '}')
        {
            if (**ptr_on_text == '\"')
                is_one_quote = !is_one_quote;

            else if (is_one_quote)
                tmp_word[counter++] = **ptr_on_text;

            (*ptr_on_text)++;
        }

    if (counter > STR_LENGTH - 1)
        return LONG_STRING;

    if (strcmp(tmp_word, null_word) == 0)
    {
        (*ptr_on_text)++;
        return NIL;
    }

    return OK;
}

void SkipToBrace(char** ptr_on_text)
{
    while (**ptr_on_text != '{' &&
           **ptr_on_text != '}')
           (*ptr_on_text)++;
}

char* ReadFile (const char* str, size_t *size, const char* chmod)
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

const char* bool_to_str(bool a)
{
    if (a)
        return "Yes";

    else
        return "Not";
}

int GetString(char* str)
{
    fgets(str, STR_LENGTH, stdin);
    str[strlen(str) - 1] = '\0';
}


int PrintError(int err_code, const char* function_name)
{
    printf("Error occured in function %s code %d", function_name, err_code);
}
