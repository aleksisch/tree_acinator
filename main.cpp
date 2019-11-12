#include <iostream>
#include "./include/AkinatorTree.h"

using namespace std;

int main()
{
    AkinatorTree akinator;
    akinator.ReadGraphFile();

    while (true)
        if (akinator.Play() == END_OF_GAME) break;

    akinator.GraphDump();
    akinator.WriteGraphFile(input_graph_file);
    system("pause");
}
