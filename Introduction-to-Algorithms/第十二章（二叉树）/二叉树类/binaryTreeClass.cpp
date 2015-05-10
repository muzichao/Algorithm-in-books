#include "binaryTreeClass.h"
#include <iostream>
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
/*函数名：GetRoot
/*功  能：取根结点
/*返回值：返回根结点
/************************************************************************/
BinaryTreeNode *binaryTreeClass::GetRoot()
{
    return pRoot;
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
        cout << endl;
    }
}

/************************************************************************/
/*函数名：IsEmptyBinaryTree
/*功  能：判断二叉树是否为空
/*返回值：返回True或False
/************************************************************************/
bool binaryTreeClass::IsEmptyBinaryTree()
{
    if (NULL == pRoot)
        return true;
    else
        return false;
}

/************************************************************************/
/*函数名：CountBinaryTree
/*功  能：统计二叉树结点个数
/*返回值：结点个数
/************************************************************************/
int binaryTreeClass::CountBinaryTree()
{
    if (NULL == pRoot)
    {
        return 0;
    }
    else
    {
        return CountBinaryTree(pRoot);
    }
}
int binaryTreeClass::CountBinaryTree(BinaryTreeNode *pNode)
{
    // 左空右不空；左不空右空；左右都不空；左右都空
    if (NULL != pNode->pLeftChild && NULL == pNode->pRightChild)
    {
        return 1 + CountBinaryTree(pNode->pLeftChild);
    }
    else if (NULL == pNode->pLeftChild && NULL != pNode->pRightChild)
    {
        return 1 + CountBinaryTree(pNode->pRightChild);
    }
    else if (NULL != pNode->pLeftChild && NULL != pNode->pRightChild)
    {
        return 1 + CountBinaryTree(pNode->pLeftChild) + CountBinaryTree(pNode->pRightChild);
    }
    else
    {
        return 1;
    }
}

/************************************************************************/
/*函数名：SearchKeyBinaryTree()
/*功  能：搜索二叉树，判断关键字是否存在
/*返回值：True 或者 False
/************************************************************************/
bool binaryTreeClass::SearchKeyBinaryTree(dataType val)
{
    if (NULL == SearchKeyBinaryTree(pRoot, val))
    {
        return false;
    }
    else
    {
        return true;
    }
}
BinaryTreeNode *binaryTreeClass::SearchKeyBinaryTree(BinaryTreeNode *pNode, dataType val)
{
    if (NULL == pNode)
    {
        return NULL;
    }
    else
    {
        if (val == pNode->value)
        {
            return pNode;
        }
        else if (val < pNode->value) // 小值在左子树
        {
            return SearchKeyBinaryTree(pNode->pLeftChild, val);
        }
        else // 大值在右子树
        {
            return SearchKeyBinaryTree(pNode->pRightChild, val);
        }
    }
}

/************************************************************************/
/*函数名：SearchFatherBinaryTree
/*功  能：搜索关键字的父结点
/*返回值：父结点的指针
/************************************************************************/
BinaryTreeNode *binaryTreeClass::SearchFatherBinaryTree(dataType val)
{
    BinaryTreeNode *pNode;
    if (NULL != pRoot)
    {
        return SearchFatherBinaryTree(pRoot, val);
    }

    return NULL;
}
BinaryTreeNode *binaryTreeClass::SearchFatherBinaryTree(BinaryTreeNode *pNode, dataType val)
{
    // 如果根结点是要查找的结点，直接返回根结点指针
    if (val == pNode->value)
    {
        return pNode;
    }
    // 如果左子树不空，则查找
    if (NULL != pNode->pLeftChild && val < pNode->value)
    {
        if (val == pNode->pLeftChild->value)
        {
            return pNode;
        }
        else if (val < pNode->value)
        {
            return SearchFatherBinaryTree(pNode->pLeftChild, val);
        }
    }
    // 如果右子树不空，查找右子树
    if (NULL != pNode->pRightChild && val > pNode->value)
    {
        if (val == pNode->pRightChild->value)
        {
            return pNode;
        }
        else if (val > pNode->value)
        {
            return SearchFatherBinaryTree(pNode->pRightChild, val);
        }
    }

    return NULL;
}

/************************************************************************/
/*函数名：MinimumBinaryTree
/*功  能：查找二叉树中的最小关键字
/*返回值：返回最小关键字
/************************************************************************/
dataType binaryTreeClass::MinimumBinaryTree()
{
    if (NULL == pRoot)
    {
        cout << "Empty!" << endl;
        return 0;
    }
    else
    {
        return MinimumBinaryTree(pRoot);
    }

}
dataType binaryTreeClass::MinimumBinaryTree(BinaryTreeNode *pNode)
{
    // 最小值必定在最左最小结点
    while (NULL != pNode->pLeftChild)
    {
        pNode = pNode->pLeftChild;
    }

    return pNode->value;
}

/************************************************************************/
/*函数名：MaximumBinaryTree
/*功  能：查找二叉树中的最大关键字
/*返回值：返回最大关键字
/************************************************************************/
dataType binaryTreeClass::MaximumBinaryTree()
{
    BinaryTreeNode *pNode = pRoot;

    if (NULL == pNode)
    {
        cout << "Empty!" << endl;
        return 0;
    }
    else
    {
        return MaximumBinaryTree(pRoot);
    }
}
dataType binaryTreeClass::MaximumBinaryTree(BinaryTreeNode *pNode)
{
    // 最大值必定在最右最下结点
    while (NULL != pNode->pRightChild)
    {
        pNode = pNode->pRightChild;
    }

    return pNode->value;
}

/************************************************************************/
/*函数名：IsCompleteBinaryTree
/*功  能：判断二叉树是否为完全二叉树
/*返回值：返回True或False
/************************************************************************/
bool binaryTreeClass::IsCompleteBinaryTree()
{
    // 根结点为空，是完全二叉树
    if (NULL == pRoot)
        return true;
    else
        return IsCompleteBinaryTree(pRoot);
}

bool binaryTreeClass::IsCompleteBinaryTree(BinaryTreeNode *pNode)
{
    // 左右子树一空一不空肯定不是完全二叉树
    if (NULL == pNode->pLeftChild ^ NULL == pNode->pRightChild)
    {
        return false;
    }
    else if (NULL == pNode->pLeftChild && NULL == pNode->pRightChild)
    {
        return true;
    }
    else // 左右子树都不空的话分别判断左右子树是否是完全二叉树
    {
        return IsCompleteBinaryTree(pRoot->pLeftChild) && IsCompleteBinaryTree(pRoot->pRightChild);
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
/*函数名：PreOrderBinaryTree
/*功  能：前序遍历二叉树：根-左-右
/*返回值：无
/************************************************************************/
void binaryTreeClass::PreOrderBinaryTree()
{
    // 先判断是否为空，不为空再遍历
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
        // 先输出根结点，然后遍历左结点，遍历右结点
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
    // 先判断是否为空，不为空再遍历
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
        // 先遍历左结点，然后输出根结点，遍历右结点
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
    // 先判断是否为空，不为空再遍历
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
        // 先遍历左结点，再遍历右结点，然后输出根结点
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
/*函数名：LevelOrderBinaryTree
/*功  能：层序遍历二叉树：1层-2层-3层
/*返回值：无
/************************************************************************/
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
/*函数名：DeleteBinaryTree
/*功  能：删除结点
/*返回值：无
/************************************************************************/
bool binaryTreeClass::DeleteBinaryTree(dataType val)
{
    if (NULL == pRoot)
    {
        return true;
    }
    else
    {
        return DeleteBinaryTree(pRoot, val);
    }
}
bool binaryTreeClass::DeleteBinaryTree(BinaryTreeNode *pSubRoot, dataType val)
{
    BinaryTreeNode *pNode = SearchKeyBinaryTree(pSubRoot, val);
    BinaryTreeNode *pNodeFather = SearchFatherBinaryTree(pSubRoot, val);

    // 不存在该结点
    if (NULL == pNode)
    {
        return true;
    }
    // 如果左右子树均为空，直接删除
    if (NULL == pNode->pLeftChild && NULL == pNode->pRightChild)
    {
        if (pNodeFather->pLeftChild == pNode)
        {
            pNodeFather->pLeftChild = NULL;
        }
        else
        {
            pNodeFather->pRightChild = NULL;
        }
        delete pNode;
        return true;
    }
    // 如果左子树空，右子树不空，直接把右子树接到父结点
    if (NULL == pNode->pLeftChild && NULL != pNode->pRightChild)
    {
        if (pNodeFather->pLeftChild == pNode)
        {
            pNodeFather->pLeftChild = pNode->pRightChild;
        }
        else
        {
            pNodeFather->pRightChild = pNode->pRightChild;
        }
        delete pNode;
        return true;
    }
    // 如果左子树不空，右子树空，直接把左子树接到父结点
    if (NULL != pNode->pLeftChild && NULL == pNode->pRightChild)
    {
        if (pNodeFather->pLeftChild == pNode)
        {
            pNodeFather->pLeftChild = pNode->pLeftChild;
        }
        else
        {
            pNodeFather->pRightChild = pNode->pLeftChild;
        }
        delete pNode;
        return true;
    }
    // 如果左右子树都不空，则用右子树的最小值替换该值，并删除右子树的最小值
    if (NULL != pNode->pLeftChild && NULL != pNode->pRightChild)
    {
        pNode->value = MinimumBinaryTree(pNode->pRightChild);
        DeleteBinaryTree(pNode->pRightChild, pNode->value);
        return true;
    }
    return false;
}
