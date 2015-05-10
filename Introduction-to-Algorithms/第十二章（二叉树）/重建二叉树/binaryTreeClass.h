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
    void PreOrderBinaryTree(); // 前序遍历二叉树
    void InOrderBinaryTree(); // 中序遍历二叉树
    void PostOrderBinaryTree(); // 后序遍历二叉树
    void RebuildBinaryTreeByPreAndIn(); // 根据先序和中序遍历重建二叉树
    void RebuildBinaryTreeByPostAndIn(); // 根据后序和中序遍历重建二叉树

private:
    BinaryTreeNode *pRoot; // 根结点
    int iBTNodeNum; // 结点个数
    int HightBinaryTree(BinaryTreeNode *pNode); // 二叉树高
    void PreOrderBinaryTree(BinaryTreeNode *pNode); // 前序遍历二叉树
    void InOrderBinaryTree(BinaryTreeNode *pNode); // 中序遍历二叉树
    void PostOrderBinaryTree(BinaryTreeNode *pNode); // 后序遍历二叉树
    void RebuildBinaryTreeByPreAndIn(BinaryTreeNode **pNode, int *PreOrder, int *InOrder, int iBinaryTreeLength, int iInOrderStart, int iPreOrderStart); // 根据先序和中序遍历重建二叉树
    void RebuildBinaryTreeByPostAndIn(BinaryTreeNode **pNode, int *PostOrder, int *InOrder, int iBinaryTreeLength, int iInOrderStart, int iPostOrderStart); // 根据后序和中序遍历重建二叉树
    void InsertBinaryTree(BinaryTreeNode *pSubRoot, BinaryTreeNode *pNode); // 结点插入二叉树
};
#endif // BINARY_TREE_CLASS_H
