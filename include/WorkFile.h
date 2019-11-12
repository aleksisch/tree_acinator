#ifndef WORKFILE_H_INCLUDED
#define WORKFILE_H_INCLUDED

int FirstWordFromText(char** ptr_on_text, char* tmp_word);

void SkipToBrace(char** ptr_on_text);

char* ReadFile (const char* str, size_t *size, const char* chmod = "r");

const char* bool_to_str(bool a);

int GetString(char* str);

int PrintError(int err_code, const char* function_name = "");

#endif // WORKFILE_H_INCLUDED
