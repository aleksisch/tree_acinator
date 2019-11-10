#include <iostream>
#include "./include/AkinatorTree.h"

using namespace std;

int main()
{
    AkinatorTree akinator;
    akinator.ReadGraphFile();
    akinator.WriteGraphFile();
    system("pause");
}
