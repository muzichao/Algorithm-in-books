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
        // 下个结点为空，则插入，否则继续寻找
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
        // 下个结点为空，则插入，否则继续寻找
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
/*函数名：HightBinaryTree
/*功  能：计算二叉树的高
/*返回值：二叉树的高度
/************************************************************************/
int binaryTreeClass::HightBinaryTree()
{
    return HightBinaryTree(pRoot);
}
int binaryTreeClass::HightBinaryTree(BinaryTreeNode *pNode)
{
    int iLeftHight = 0;
    int iRightHight = 0;

    // 如果为空，返回0，否则返回左右子树较大值 + 1
    if (NULL == pNode)
    {
        return 0;
    }
    else
    {
        iLeftHight = HightBinaryTree(pNode->pLeftChild);
        iRightHight = HightBinaryTree(pNode->pRightChild);

        return iLeftHight >= iRightHight ? 1 + iLeftHight : 1 + iRightHight;
    }
}


/************************************************************************/
/*函数名：LevelOrderBinaryTree
/*功  能：层序遍历二叉树：1层-2层-3层
/*返回值：无
/************************************************************************/
// 此方法的缺点在于，没访问一层都要从根结点开始访问，效率低
void binaryTreeClass::LevelOrderBinaryTree()
{
    // 判断是否为空，不为空再打印
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        LevelOrderBinaryTree(pRoot);
        cout << endl;
    }
}
void binaryTreeClass::LevelOrderBinaryTree(BinaryTreeNode *pNode)
{
    int iLevelBinaryTree = HightBinaryTree(); // 总层数
    for (int i = 1; i <= iLevelBinaryTree; ++i)
    {
        PrintLevelBinaryTree(pRoot, 1, i); // 分别打印没一层
        cout << endl;
    }
}

/************************************************************************/
/*函数名：PrintLevelBinaryTree
/*功  能：打印某一层的结点
/*返回值：无
/************************************************************************/
void binaryTreeClass::PrintLevelBinaryTree(BinaryTreeNode *pNode, int iLevelCurrent, int iLevel)
{
    // 找到需要打印的层，iLevelCurrent表示当前层数
    if (iLevelCurrent == iLevel)
    {
        cout << pNode->value << " ";
    }
    else
    {
        // 如果不是打印当前层，则移动到下一层，且层数加1
        if (NULL != pNode->pLeftChild)
        {
            PrintLevelBinaryTree(pNode->pLeftChild, iLevelCurrent + 1, iLevel);
        }
        if (NULL != pNode->pRightChild)
        {
            PrintLevelBinaryTree(pNode->pRightChild, iLevelCurrent + 1, iLevel);
        }
    }
}

/************************************************************************/
/*函数名：LevelOrderBinaryTreeOpt
/*功  能：层序遍历二叉树：1层-2层-3层
/*返回值：无
/************************************************************************/
void binaryTreeClass::LevelOrderBinaryTreeOpt()
{
    // 判断是否为空，不为空再打印
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        LevelOrderBinaryTreeOpt(pRoot);
        cout << endl;
    }
}
// 广度优先搜索，使用队列保存访问过的结点，不用每次从头结点开始
// 此时存在的问题是，不能在每一层结束时换行
void binaryTreeClass::LevelOrderBinaryTreeOpt(BinaryTreeNode *pNode)
{
    queue <BinaryTreeNode *> qNodeByLevel;
    qNodeByLevel.push(pNode); // 根结点入队
    while (!qNodeByLevel.empty())
    {
        pNode = qNodeByLevel.front(); // 返回队首元素
        qNodeByLevel.pop(); // 删除队首元素
        cout << pNode->value << " ";
        if (NULL != pNode->pLeftChild)
        {
            qNodeByLevel.push(pNode->pLeftChild); // 左子树入队
        }
        if (NULL != pNode->pRightChild)
        {
            qNodeByLevel.push(pNode->pRightChild); // 右子树入队
        }
    }
}

/************************************************************************/
/*函数名：LevelOrderBinaryTreeOpt2
/*功  能：层序遍历二叉树：1层-2层-3层
/*返回值：无
/************************************************************************/
void binaryTreeClass::LevelOrderBinaryTreeOpt2()
{
    // 判断是否为空，不为空再打印
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
    }
    else
    {
        LevelOrderBinaryTreeOpt2(pRoot);
        cout << endl;
    }
}
// 广度优先搜索，使用队列保存访问过的结点，不用每次从头结点开始
// 用一个NULL标识层的结束，队首出一个NULL，队尾进一个NULL
// 注意:当发现空指针(结束信号)时，要检查队列内是否还有结点，
// 如果没有的话还插入新的结束信号，则会做成死循环。
void binaryTreeClass::LevelOrderBinaryTreeOpt2(BinaryTreeNode *pNode)
{
    queue <BinaryTreeNode *> qNodeByLevel;
    qNodeByLevel.push(pNode); // 根结点入队
    qNodeByLevel.push(NULL); // 层结束标识

    while (!qNodeByLevel.empty())
    {
        pNode = qNodeByLevel.front(); // 返回队首元素
        qNodeByLevel.pop(); // 删除队首元素
        if (NULL != pNode)
        {
            cout << pNode->value << " ";

            if (NULL != pNode->pLeftChild)
            {
                qNodeByLevel.push(pNode->pLeftChild); // 左子树入队
            }
            if (NULL != pNode->pRightChild)
            {
                qNodeByLevel.push(pNode->pRightChild); // 右子树入队
            }
        }
        else if (!qNodeByLevel.empty())
        {
            qNodeByLevel.push(NULL);
            cout << endl;
        }
    }
}
