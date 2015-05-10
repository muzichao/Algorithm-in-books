#include "binaryTreeClass.h"
#include <iostream>

using namespace std;

int main()
{
    binaryTreeClass myBinaryTree(10);
    myBinaryTree.CreateBinaryTree();

    cout << "Node numbers : " << myBinaryTree.CountBinaryTree() << endl;
    cout << "Empty : " << myBinaryTree.IsEmptyBinaryTree() << endl;
    cout << "Search : " << myBinaryTree.SearchKeyBinaryTree(72) << endl;
    cout << "Father of 72 : " << myBinaryTree.SearchFatherBinaryTree(72) << endl;
    cout << "pRoot : " << myBinaryTree.GetRoot() << endl;
    cout << "Minimum : " << myBinaryTree.MinimumBinaryTree() << endl;
    cout << "Maximum : " << myBinaryTree.MaximumBinaryTree() << endl;
    cout << "Complete : " << myBinaryTree.IsCompleteBinaryTree() << endl;
    cout << "Hight : " << myBinaryTree.HightBinaryTree() << endl;

    cout << "PreOrder : " << endl;
    myBinaryTree.PreOrderBinaryTree();
    cout << "InOrder : " << endl;
    myBinaryTree.InOrderBinaryTree();
    cout << "PostOrder : " << endl;
    myBinaryTree.PostOrderBinaryTree();
    cout << "LevelOrder : " << endl;
    myBinaryTree.LevelOrderBinaryTree();

    cout << "Delete ? : " << myBinaryTree.DeleteBinaryTree(30) << endl;

    cout << "PreOrder : " << endl;
    myBinaryTree.PreOrderBinaryTree();
    cout << "InOrder : " << endl;
    myBinaryTree.InOrderBinaryTree();
    cout << "PostOrder : " << endl;
    myBinaryTree.PostOrderBinaryTree();
    cout << "LevelOrder : " << endl;
    myBinaryTree.LevelOrderBinaryTree();

    return 0;
}
