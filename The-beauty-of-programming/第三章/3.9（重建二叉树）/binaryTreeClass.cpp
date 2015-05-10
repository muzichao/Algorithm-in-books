#include "binaryTreeClass.h"
#include <iostream>
#include <queue>
#include <stdlib.h>

using namespace std;

/************************************************************************/
/*函数名：binaryTreeClass
/*功  能：析构函数
/*返回值：无
/************************************************************************/
binaryTreeClass::binaryTreeClass()
{
    pRoot = NULL;
    iBTNodeNum = 1;
}
binaryTreeClass::binaryTreeClass(int iNum)
{
    pRoot = NULL;
    iBTNodeNum = iNum;
}

/************************************************************************/
/*函数名：~binaryTreeClass
/*功  能：析构函数
/*返回值：无
/************************************************************************/
binaryTreeClass::~binaryTreeClass()
{
    iBTNodeNum = 0;
    pRoot = NULL;
}

/************************************************************************/
/*函数名：CreateBinaryTree
/*功  能：创建二叉树
/*返回值：无
/************************************************************************/
void binaryTreeClass::CreateBinaryTree()
{
    BinaryTreeNode *pNode = NULL;

    srand(5);
    for (int i = 0; i < iBTNodeNum; ++i)
    {
        pNode = new BinaryTreeNode(rand() % 100);
        cout << pNode->value << " ";
        if (NULL == pRoot)
        {
            pRoot = pNode;
        }
        else
        {
            InsertBinaryTree(pRoot, pNode);
        }
    }
    cout << endl;
}

/************************************************************************/
/*函数名：InsertBinaryTree
/*功  能：结点插入二叉树
/*返回值：无
/************************************************************************/
void binaryTreeClass::InsertBinaryTree(BinaryTreeNode *pSubRoot, BinaryTreeNode *pNode)
{
    if (NULL == pNode || NULL == pSubRoot)
    {
        cout << "error!" << endl;
    }

    // 小的在左子树
    if (pNode->value <= pSubRoot->value)
    {
        // 下个结点为空,则插入,否则继续寻找
        if (NULL == pSubRoot->pLeftChild)
        {
            pSubRoot->pLeftChild = pNode;
        }
        else
        {
            InsertBinaryTree(pSubRoot->pLeftChild, pNode);
        }
    }
    else // 大的在右子树
    {
        // 下个结点为空,则插入,否则继续寻找
        if (NULL == pSubRoot->pRightChild)
        {
            pSubRoot->pRightChild = pNode;
        }
        else
        {
            InsertBinaryTree(pSubRoot->pRightChild, pNode);
        }
    }
}

/************************************************************************/
/*函数名：PreOrderBinaryTree
/*功  能：前序遍历二叉树：根-左-右
/*返回值：无
/************************************************************************/
void binaryTreeClass::PreOrderBinaryTree()
{
    // 先判断是否为空,不为空再遍历
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        PreOrderBinaryTree(pRoot);
        cout << endl;
    }
}
void binaryTreeClass::PreOrderBinaryTree(BinaryTreeNode *pNode)
{
    if (NULL != pNode)
    {
        // 先输出根结点,然后遍历左结点,遍历右结点
        cout << pNode->value << " ";
        if (NULL != pNode->pLeftChild)
        {
            PreOrderBinaryTree(pNode->pLeftChild);
        }
        if (NULL != pNode->pRightChild)
        {
            PreOrderBinaryTree(pNode->pRightChild);
        }
    }
}

/************************************************************************/
/*函数名：InOrderBinaryTree
/*功  能：中序遍历二叉树：左-根-右
/*返回值：无
/************************************************************************/
void binaryTreeClass::InOrderBinaryTree()
{
    // 先判断是否为空,不为空再遍历
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        InOrderBinaryTree(pRoot);
        cout << endl;
    }
}
void binaryTreeClass::InOrderBinaryTree(BinaryTreeNode *pNode)
{
    if (NULL != pNode)
    {
        // 先遍历左结点,然后输出根结点,遍历右结点
        if (NULL != pNode->pLeftChild)
        {
            InOrderBinaryTree(pNode->pLeftChild);
        }
        cout << pNode->value << " ";
        if (NULL != pNode->pRightChild)
        {
            InOrderBinaryTree(pNode->pRightChild);
        }
    }
}

/************************************************************************/
/*函数名：PostOrderBinaryTree
/*功  能：后序遍历二叉树：左-右-根
/*返回值：无
/************************************************************************/
void binaryTreeClass::PostOrderBinaryTree()
{
    // 先判断是否为空,不为空再遍历
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        PostOrderBinaryTree(pRoot);
        cout << endl;
    }
}
void binaryTreeClass::PostOrderBinaryTree(BinaryTreeNode *pNode)
{
    if (NULL != pNode)
    {
        // 先遍历左结点,再遍历右结点,然后输出根结点
        if (NULL != pNode->pLeftChild)
        {
            PostOrderBinaryTree(pNode->pLeftChild);
        }
        if (NULL != pNode->pRightChild)
        {
            PostOrderBinaryTree(pNode->pRightChild);
        }
        cout << pNode->value << " ";
    }
}

/************************************************************************/
/*函数名：RebuildBinaryTreeByPreAndIn
/*功  能：根据先序遍历和中序遍历重建二叉树
/*返回值：无
/************************************************************************/
void binaryTreeClass::RebuildBinaryTreeByPreAndIn()
{
    const int iBinaryTreeLength(10); // 定义常数
    // int PreOrder[iBinaryTreeLength] = {6, 4, 2, 1, 3, 5, 9, 8, 7, 10, 11};
    // int InOrder[iBinaryTreeLength] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int PreOrder[iBinaryTreeLength] = {54, 49, 30, 27, 48, 40, 93, 55, 60, 72};
    int InOrder[iBinaryTreeLength] = {27, 30, 40, 48, 49, 54, 55, 60, 72, 93};
    bool bFlag = true;

    BinaryTreeNode *pNewRoot = NULL;
    RebuildBinaryTreeByPreAndIn(&pNewRoot, PreOrder, InOrder, iBinaryTreeLength, 0, 0);

    if (NULL == pNewRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        InOrderBinaryTree(pNewRoot);
        cout << endl;
    }
}
// pNode：插入位置
// PreOrder：先序序列
// InOrder：中序序列
// iInOrderStart：在中序遍历中起始位置
// iPreOrderStart：在先序遍历中的起始位置
// iBinaryTreeLength：二叉树长度
void binaryTreeClass::RebuildBinaryTreeByPreAndIn(BinaryTreeNode **pNode, int *PreOrder, int *InOrder, int iBinaryTreeLength, int iInOrderStart, int iPreOrderStart)
{
    // 如果子树长度为0,错误
    if (0 == iBinaryTreeLength)
    {
        return;
    }

    // 当前指针指向根结点
    (*pNode) = new BinaryTreeNode(PreOrder[iPreOrderStart]);

    // 如果仅有一个结点直接返回即可
    if (1 == iBinaryTreeLength)
    {
        return;
    }

    // 查找该头结点在中序中的位置
    int iInOrderRoot = iInOrderStart;
    while (InOrder[iInOrderRoot] != (*pNode)->value)
    {
        iInOrderRoot++;
    }

    // 左子树处理
    // 左子树在先序中的起始位置 = 整树在先序中的起始位置 + 1
    int iPreOrderLeftStart = iPreOrderStart + 1; // 左子树在先序中的起始位置
    // 左子树的长度 = 根结点在中序中的位置 - 整树在中序中的起始位置
    int iBinaryTreeLeftLength = iInOrderRoot - iInOrderStart; // 左子树长度

    if (iBinaryTreeLeftLength >= 1)
    {
        RebuildBinaryTreeByPreAndIn(&((*pNode)->pLeftChild), PreOrder, InOrder, iBinaryTreeLeftLength, iInOrderStart, iPreOrderLeftStart);
    }

    // 右子树处理
    // 右子树在中序中的起始位置 = 根结点在中序中的位置 + 1
    int iInOrderRightStart = iInOrderRoot + 1; // 右子树在中序中的起始位置
    // 右子树的长度 = 整树的长度 - 左子树长度 - 1
    int iBinaryTreeRightLength = iBinaryTreeLength - iBinaryTreeLeftLength - 1; // 右子树长度
    // 右子树在先序中起始位置 = 左子树在先序中起始位置 + 左子树长度
    int iPreOrderRightStart = iPreOrderLeftStart + iBinaryTreeLeftLength;

    if (iBinaryTreeRightLength >= 1)
    {
        RebuildBinaryTreeByPreAndIn(&((*pNode)->pRightChild), PreOrder, InOrder, iBinaryTreeRightLength, iInOrderRightStart, iPreOrderRightStart);
    }
}

/************************************************************************/
/*函数名：RebuildBinaryTreeByPostAndIn
/*功  能：根据后序遍历和中序遍历重建二叉树
/*返回值：无
/************************************************************************/
void binaryTreeClass::RebuildBinaryTreeByPostAndIn()
{
    const int iBinaryTreeLength(10); // 定义常数
    // int PostOrder[iBinaryTreeLength] = {6, 4, 2, 1, 3, 5, 9, 8, 7, 10, 11};
    // int InOrder[iBinaryTreeLength] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int PostOrder[iBinaryTreeLength] = {27, 40, 48, 30, 49, 72, 60, 55, 93, 54};
    int InOrder[iBinaryTreeLength] = {27, 30, 40, 48, 49, 54, 55, 60, 72, 93};
    bool bFlag = true;

    BinaryTreeNode *pNewRoot = NULL;
    RebuildBinaryTreeByPostAndIn(&pNewRoot, PostOrder, InOrder, iBinaryTreeLength, 0, 0);

    if (NULL == pNewRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        InOrderBinaryTree(pNewRoot);
        cout << endl;
    }
}
// pNode：插入位置
// PostOrder：后序序列
// InOrder：中序序列
// iInOrderStart：在中序遍历中起始位置
// iPostOrderStart：在后序遍历中的起始位置
// iBinaryTreeLength：二叉树长度
void binaryTreeClass::RebuildBinaryTreeByPostAndIn(BinaryTreeNode **pNode, int *PostOrder, int *InOrder, int iBinaryTreeLength, int iInOrderStart, int iPostOrderStart)
{
    // 如果子树长度为0,错误
    if (0 == iBinaryTreeLength)
    {
        return;
    }

    // 根结点在后序中的位置
    int iPostOrderRoot = iPostOrderStart + iBinaryTreeLength - 1;

    // 当前指针指向根结点
    (*pNode) = new BinaryTreeNode(PostOrder[iPostOrderRoot]);

    // 如果仅有一个结点直接返回即可
    if (1 == iBinaryTreeLength)
    {
        return;
    }

    // 查找该头结点在中序中的位置
    int iInOrderRoot = iInOrderStart;
    while (InOrder[iInOrderRoot] != (*pNode)->value)
    {
        iInOrderRoot++;
    }

    // 左子树处理
    // 左子树在后序中的起始位置 = 整树在后序中的起始位置
    int iPostOrderLeftStart = iPostOrderStart;
    // 左子树的长度 = 根结点在中序中的位置 - 整树在中序中的起始位置
    int iBinaryTreeLeftLength = iInOrderRoot - iInOrderStart; // 左子树长度

    if (iBinaryTreeLeftLength >= 1)
    {
        RebuildBinaryTreeByPostAndIn(&((*pNode)->pLeftChild), PostOrder, InOrder, iBinaryTreeLeftLength, iInOrderStart, iPostOrderLeftStart);
    }

    // 右子树处理
    // 右子树在中序中的起始位置 = 根结点在中序中的位置 + 1
    int iInOrderRightStart = iInOrderRoot + 1;
    // 右子树的长度 = 整树的长度 - 左子树长度 - 1
    int iBinaryTreeRightLength = iBinaryTreeLength - iBinaryTreeLeftLength - 1; // 右子树长度
    // 右子树在后序中起始位置 = 左子树在先序中起始位置 + 左子树长度
    int iPostOrderRightStart = iPostOrderLeftStart + iBinaryTreeLeftLength;

    if (iBinaryTreeRightLength >= 1)
    {
        RebuildBinaryTreeByPostAndIn(&((*pNode)->pRightChild), PostOrder, InOrder, iBinaryTreeRightLength, iInOrderRightStart, iPostOrderRightStart);
    }
}
