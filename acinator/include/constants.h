#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

static const char* null_word = "nil";
static const char* INPUT_GRAPH_FILE = "in_graph.txt";
static const char* OUTPUT_GRAPH_FILE = "out_graph.txt";
static const int STR_LENGTH = 255;

enum ReturnCode
{
    OK = 0,
    NIL,
    LONG_STRING,

};

#endif // CONSTANTS_H_INCLUDED
