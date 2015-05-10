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
    BinaryTreeNode *GetRoot(); // 得到根结点
    void CreateBinaryTree(); // 创建二叉树
    bool IsEmptyBinaryTree(); // 判断二叉树是否为空
    int CountBinaryTree(); // 统计二叉树结点个数
    bool SearchKeyBinaryTree(dataType val); // 搜索二叉树
    BinaryTreeNode *SearchFatherBinaryTree(dataType val); // 查找关键字的父结点
    dataType MinimumBinaryTree(); // 查找二叉树的最小关键字
    dataType MaximumBinaryTree(); // 查找二叉树的最大关键字
    bool IsCompleteBinaryTree(); // 判断二叉树是否为完全二叉树
    int HightBinaryTree(); // 二叉树高
    void PreOrderBinaryTree(); // 前序遍历二叉树
    void InOrderBinaryTree(); // 中序遍历二叉树
    void PostOrderBinaryTree(); // 后序遍历二叉树
    void LevelOrderBinaryTree(); // 层序遍历二叉树
    bool DeleteBinaryTree(dataType val); // 删除二叉树中的某个结点
private:
    BinaryTreeNode *pRoot; // 根结点
    int iBTNodeNum; // 结点个数
    BinaryTreeNode *SearchKeyBinaryTree(BinaryTreeNode *pNode, dataType val); // 搜索二叉树
    BinaryTreeNode *SearchFatherBinaryTree(BinaryTreeNode *pNode, dataType val); // 查找关键字的父结点
    dataType MinimumBinaryTree(BinaryTreeNode *pNode); // 查找二叉树的最小关键字
    dataType MaximumBinaryTree(BinaryTreeNode *pNode); // 查找二叉树的最大关键字
    bool IsCompleteBinaryTree(BinaryTreeNode *pNode); // 判断二叉树是否为完全二叉树
    int CountBinaryTree(BinaryTreeNode *pNode); // 统计二叉树结点个数
    int HightBinaryTree(BinaryTreeNode *pNode); // 二叉树高
    void PreOrderBinaryTree(BinaryTreeNode *pNode); // 前序遍历二叉树
    void InOrderBinaryTree(BinaryTreeNode *pNode); // 中序遍历二叉树
    void PostOrderBinaryTree(BinaryTreeNode *pNode); // 后序遍历二叉树
    void LevelOrderBinaryTree(BinaryTreeNode *pNode); // 层序遍历二叉树
    void PrintLevelBinaryTree(BinaryTreeNode *pNode, int iLevelCurrent, int iLevel); // 打印iLevel层的结点
    void InsertBinaryTree(BinaryTreeNode *pSubRoot, BinaryTreeNode *pNode); // 结点插入二叉树
    bool DeleteBinaryTree(BinaryTreeNode *pSubRoot, dataType val); // 删除二叉树中的某个结点
};
#endif // BINARY_TREE_CLASS_H
