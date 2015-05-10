#include "binaryTreeClass.h"
#include <iostream>

using namespace std;

int main()
{
    binaryTreeClass myBinaryTree(10);
    myBinaryTree.CreateBinaryTree();

    cout << "Hight : " << myBinaryTree.HightBinaryTree() << endl;


    cout << "LevelOrder : " << endl;
    myBinaryTree.LevelOrderBinaryTree();

    cout << "LevelOrder Opt : " << endl;
    myBinaryTree.LevelOrderBinaryTreeOpt();

    cout << "LevelOrder Opt2 : " << endl;
    myBinaryTree.LevelOrderBinaryTreeOpt2();
    return 0;
}
