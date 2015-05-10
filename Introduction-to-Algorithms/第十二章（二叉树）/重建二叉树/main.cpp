#include "binaryTreeClass.h"
#include <iostream>

using namespace std;

int main()
{
    binaryTreeClass myBinaryTree(10);
    myBinaryTree.CreateBinaryTree();

    cout << "PreOrder : " << endl;
    myBinaryTree.PreOrderBinaryTree();
    cout << "InOrder : " << endl;
    myBinaryTree.InOrderBinaryTree();
    cout << "PostOrder : " << endl;
    myBinaryTree.PostOrderBinaryTree();

    cout << "Rebuild : " << endl;
    myBinaryTree.RebuildBinaryTreeByPreAndIn();

    cout << "Rebuild : " << endl;
    myBinaryTree.RebuildBinaryTreeByPostAndIn();
    return 0;
}
