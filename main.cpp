#include <iostream>
#include "./include/AkinatorTree.h"

using namespace std;

int main()
{
    AkinatorTree akinator;

    akinator.ReadGraphFile();
    akinator.GraphToDot();

    while (true)
        if (akinator.Play() == END_OF_GAME) break;

    akinator.GraphToDot();
    akinator.WriteGraphFile(output_graph_file);
    system("pause");
}
