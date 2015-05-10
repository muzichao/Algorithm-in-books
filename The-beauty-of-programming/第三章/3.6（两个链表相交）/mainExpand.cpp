// 编程之美 3.6
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 判断两个单链表是否重叠，其中两个链表可能带环
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 分析：
// 1. 两个链表一个有环，一个无环，必定不重叠
// 2. 两个都无环，用无环链表的判断法
// 3. 两个都有环，用有环链表的判断法
// 对于两个无环的链表：
// 1. 两两比较两个单链表的结点，看是否有相同结点
// 2. 利用哈希表的特性，判断是否有相同结点
// 3. 将链表One的尾与链表Two的头连接，然后判断新的链表是否有环
//    注意，此时改变了链表的结构，判断完之后应当恢复。
// 4. 判断两个链表的尾结点是否相同
// 对于两个有环的链表
// 1. 标记第一个链表中环上的一点
// 2. 标记第二个链表中环上的一点
// 3. 遍历第二个环，看是否有结点与第一个链表中标记的结点相同。
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include <iostream>
#include <stdlib.h>

using namespace std;

// 链表中的结点
struct Node
{
    int value;
    Node *next;

    Node (int val)
    {
        this->value = val;
        this->next = NULL;
    }
};

/************************************************************************/
/*函数名：ShowSingleLinkedList
/*功  能：显示单链表
/*返回值：无
/************************************************************************/
void ShowSingleLinkedList(Node *pRoot)
{
    Node *pNode;

    while (NULL != pRoot)
    {
        cout << pRoot->value << " ";
        pRoot = pRoot->next;
    }
    cout << endl << endl;
}

/************************************************************************/
/*函数名：IsCircularSingleLinkedList
/*功  能：判断单链表是否有环
/*返回值：True 或 False
/************************************************************************/
bool IsCircularSingleLinkedList(Node *pRoot)
{
    Node *pFast = pRoot, *pSlow = pRoot;

    while (pFast && pFast->next)
    {
        pSlow = pSlow->next;
        pFast = pFast->next->next;

        if (pFast == pSlow)
        {
            break;
        }
    }

    if (pFast == pSlow)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************************/
/*函数名：CreateSingleLinkedList
/*功  能：创建无环单链表
/*返回值：返回头指针
/************************************************************************/
Node *CreateSingleLinkedList()
{
    Node *pNode = NULL;
    Node *pRoot = NULL;
    int iLength = 15; // 链表长度

    for (int i = 0; i < iLength; ++i)
    {
        // 如果链表为空则头部指向新的结点
        if (NULL == pRoot)
        {
            pRoot = new Node(rand());
            if (pRoot == NULL)
                cout << "error!" << endl;
        }
        else // 如果链表不为空则新的结点插入头部
        {
            pNode = new Node(rand());
            if (pNode == NULL)
                cout << "error!" << endl;

            pNode->next = pRoot;
            pRoot = pNode;
        }
    }

    return pRoot;
}

/************************************************************************/
/*函数名：CreateSingleCircularLinkedList
/*功  能：创建带环的单链表
/*返回值：返回头指针
/************************************************************************/
Node *CreateSingleCircularLinkedList()
{
    Node *pNode = NULL;
    Node *pRoot = NULL;
    Node *pCircul = NULL;
    int iLength = 15; // 链表长度

    for (int i = 0; i < iLength; ++i)
    {
        // 如果链表为空则头部指向新的结点
        if (NULL == pRoot)
        {
            pRoot = new Node(rand());
            if (pRoot == NULL)
                cout << "error!" << endl;
        }
        else // 如果链表不为空则新的结点插入头部
        {
            pNode = new Node(rand());
            if (pNode == NULL)
                cout << "error!" << endl;

            pNode->next = pRoot;
            pRoot = pNode;
        }
    }

    // 查找需要连接成环的位置
    pCircul = pRoot;
    for (int i = 0; i < 5; ++i)
    {
        pCircul = pCircul->next;
    }

    // 让pNode指向尾结点
    while (pNode->next != NULL)
    {
        pNode = pNode->next;
    }

    pNode->next = pCircul; // 环封闭

    return pRoot;
}

/************************************************************************/
/*函数名：CreateOverlappedSingleLinkedList
/*功  能：创建重叠的单链表
/*返回值：返回头指针
/************************************************************************/
Node *CreateOverlappedSingleLinkedList(Node *pOriginalRoot)
{
    Node *pNode = NULL;
    Node *pRoot = NULL;
    int iLength = 5; // 链表长度

    for (int i = 0; i < iLength; ++i)
    {
        // 如果链表为空则头部指向新的结点
        if (NULL == pRoot)
        {
            pRoot = new Node(rand());
            if (pRoot == NULL)
                cout << "error!" << endl;
        }
        else // 如果链表不为空则新的结点插入头部
        {
            pNode = new Node(rand());
            if (pNode == NULL)
                cout << "error!" << endl;

            pNode->next = pRoot;
            pRoot = pNode;
        }
    }

    // 原始单链表平移一定长度，作为重叠开始部份
    for (int i = 0; i < iLength; ++i)
    {
        pOriginalRoot = pOriginalRoot->next;
    }

    // 让pNode指向尾结点
    while (pNode->next != NULL)
    {
        pNode = pNode->next;
    }

    pNode->next = pOriginalRoot; // 连接

    return pRoot;
}

/************************************************************************/
/*函数名：IsOverlappedLinkedListWithoutCircle
/*功  能：判断两个无环链表是否重叠
/*返回值：True 或 False
/************************************************************************/
bool IsOverlappedLinkedListWithoutCircle(Node *pRootOne, Node *pRootTwo)
{
    Node *pOne = pRootOne;
    Node *pTwo = pRootTwo;

    // 如果某个链表为空，则必定没有重叠
    if (pOne == NULL | pTwo == NULL)
    {
        return false;
    }

    // 查找链表One的尾结点
    while (pOne->next != NULL)
    {
        pOne = pOne->next;
    }

    // 查找链表Two的尾结点
    while (pTwo->next != NULL)
    {
        pTwo = pTwo->next;
    }

    // 如果链表One和Two的尾结点相同则必定向重叠
    // 否则一定没有重叠
    if (pOne == pTwo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************************/
/*函数名：IsOverlappedCircularSingleLinkedList
/*功  能：判断带环的两个链表是否重叠
/*返回值：True 或 False
/************************************************************************/
bool IsOverlappedCircularSingleLinkedList(Node *pRootOne, Node *pRootTwo)
{
    Node *pFast = pRootOne; // 每次移动两个结点
    Node *pSlow = pRootOne; // 每次移动一个结点
    Node *pCirculFlagOne = NULL; // 标记第一个链表中环上的一点

    // 找到第一个链表中环上的一个结点
    while (pFast && pFast->next)
    {
        pSlow = pSlow->next;
        pFast = pFast->next->next;

        if (pFast == pSlow)
        {
            pCirculFlagOne = pFast; // 标记第一个链表中环上的一点
            break;
        }
    }

    pFast = pRootTwo; // 每次移动两个结点
    pSlow = pRootTwo; // 每次移动一个结点
    // 找到第二个链表中环上的一个结点
    while (pFast && pFast->next)
    {
        pSlow = pSlow->next;
        pFast = pFast->next->next;

        if (pFast == pSlow)
        {
            break;
        }
    }

    // 此时pFast和pSlow均在第二个链表的换上，用pSlow作为起始遍历标志
    // 用pFast遍历第二链表的环
    while (pFast != pCirculFlagOne && pFast->next != pSlow)
    {
        pFast = pFast->next;
    }

    // 如果pFast与pCirculFlagOne指向同一位置，则说明重叠
    if (pFast == pCirculFlagOne)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************************/
/*函数名：IsOverlappedLinkedList
/*功  能：判断任意两个链表是否重叠
/*返回值：True 或 False
/************************************************************************/
bool IsOverlappedLinkedList(Node *pRootOne, Node *pRootTwo)
{
    Node *pOne = pRootOne;
    Node *pTwo = pRootTwo;
    bool bHasCircleOne = IsCircularSingleLinkedList(pOne);
    bool bHasCircleTwo = IsCircularSingleLinkedList(pTwo);

    // 一个有环一个无环必定不重叠
    // 两个都无环，用无环链表的判断法
    // 两个都有环，用有环链表的判断法
    if (bHasCircleOne != bHasCircleTwo)
    {
        return false;
    }
    else if (bHasCircleOne == 0)
    {
        return IsOverlappedLinkedListWithoutCircle(pOne, pTwo);
    }
    else
    {
        return IsOverlappedCircularSingleLinkedList(pOne, pTwo);
    }

}

// 链表One，Two，Three带环
// 链表One，Two重叠
// 链表Four，Five，Six不带环
// 链表Four，Five重叠
int main()
{
    Node *pRootOne, *pRootTwo, *pRootThree, *pRootFour, *pRootFive, *pRootSix;

    // 生成带环单链表One
    pRootOne = CreateSingleCircularLinkedList();

    // 生成带环单链表Two，并与One有重叠
    pRootTwo = CreateOverlappedSingleLinkedList(pRootOne);

    // 生成带环单链表Three
    pRootThree = CreateSingleCircularLinkedList();

    // 生成无环单链表Four
    pRootFour = CreateSingleLinkedList();

    // 生成无环单链表Five，并与Four有重叠
    pRootFive = CreateOverlappedSingleLinkedList(pRootFour);

    // 生成无环单链表Six
    pRootSix = CreateSingleLinkedList();

    // 判断两个链表是否重叠
    cout << "Linkedlist one and Linkedlist two is overlapped ? "
         << IsOverlappedLinkedList(pRootOne, pRootTwo) << endl << endl;

    cout << "Linkedlist one and Linkedlist three is overlapped ? "
         << IsOverlappedLinkedList(pRootOne, pRootThree) << endl << endl;

    cout << "Linkedlist four and Linkedlist five is overlapped ? "
         << IsOverlappedLinkedList(pRootFour, pRootFive) << endl << endl;

    cout << "Linkedlist four and Linkedlist six is overlapped ? "
         << IsOverlappedLinkedList(pRootFour, pRootSix) << endl << endl;

    cout << "Linkedlist one and Linkedlist four is overlapped ? "
         << IsOverlappedLinkedList(pRootOne, pRootFour) << endl << endl;
    return 0;
}
