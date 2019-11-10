#include <iostream>
#include "./include/AkinatorTree.h"

using namespace std;

int main()
{
    AkinatorTree akinator;
    int i = 4;
    while(i--)
        akinator.play();
    akinator.GraphDump();
    system("pause");
}
