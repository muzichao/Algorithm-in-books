#ifndef BINARY_TREE_CLASS_H
#define BINARY_TREE_CLASS_H

#define NULL 0

typedef int dataType;
struct BinaryTreeNode
{
    dataType value;
    BinaryTreeNode *pLeftChild, *pRightChild;

    BinaryTreeNode (dataType val)
    {
        this->value = val;
        this->pLeftChild = NULL;
        this->pRightChild = NULL;
    }
};

class binaryTreeClass
{
public:
    binaryTreeClass(); // 构造函数
    binaryTreeClass(int iNum); // 构造函数
    ~binaryTreeClass(); // 析构函数
    void CreateBinaryTree(); // 创建二叉树
    int HightBinaryTree(); // 二叉树高
    void LevelOrderBinaryTree(); // 层序遍历二叉树
    void LevelOrderBinaryTreeOpt(); // 优化的层序遍历二叉树
    void LevelOrderBinaryTreeOpt2(); // 优化的层序遍历二叉树
private:
    BinaryTreeNode *pRoot; // 根结点
    int iBTNodeNum; // 结点个数
    int HightBinaryTree(BinaryTreeNode *pNode); // 二叉树高
    void LevelOrderBinaryTree(BinaryTreeNode *pNode); // 层序遍历二叉树
    void PrintLevelBinaryTree(BinaryTreeNode *pNode, int iLevelCurrent, int iLevel); // 打印iLevel层的结点
    void LevelOrderBinaryTreeOpt(BinaryTreeNode *pNode); // 优化的层序遍历二叉树
    void LevelOrderBinaryTreeOpt2(BinaryTreeNode *pNode); // 优化的层序遍历二叉树
    void InsertBinaryTree(BinaryTreeNode *pSubRoot, BinaryTreeNode *pNode); // 结点插入二叉树
};
#endif // BINARY_TREE_CLASS_H
