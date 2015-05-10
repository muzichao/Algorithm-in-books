// 编程之美 3.6
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 判断两个单链表是否重叠，其中两个链表都不带环
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路：
// 1. 两两比较两个单链表的结点，看是否有相同结点
// 2. 利用哈希表的特性，判断是否有相同结点
// 3. 将链表One的尾与链表Two的头连接，然后判断新的链表是否有环
//    注意，此时改变了链表的结构，判断完之后应当恢复。
// 4. 判断两个链表的尾结点是否相同
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
/*函数名：CreateSingleLinkedList
/*功  能：创建单链表
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
/*函数名：IsOverlappedLinkedList
/*功  能：判断两个链表是否重叠
/*返回值：True 或 False
/************************************************************************/
bool IsOverlappedLinkedList(Node *pRootOne, Node *pRootTwo)
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
/*函数名：IsOverlappedLinkedListUsingCircul
/*功  能：判断两个链表是否重叠
/*返回值：True 或 False
/************************************************************************/
bool IsOverlappedLinkedListUsingCircul(Node *pRootOne, Node *pRootTwo)
{
    Node *pOne = pRootOne;
    Node *pTwo = pRootTwo;
    bool bIsCircul = 0;

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

    // 把链表One的尾部连接在链表Two的头部
    // 如果新链表有环，则必定重叠
    // 注意，此处会改变链表的结构，因此判断完应该要恢复
    pOne->next = pTwo;
    bIsCircul = IsCircularSingleLinkedList(pRootOne);
    pOne->next = NULL;

    return bIsCircul;
}


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

int main()
{
    Node *pRootOne, *pRootTwo, *pRootThree, *pRootFour;

    // 生成单链表One
    pRootOne = CreateSingleLinkedList();
    cout << "Linkedlist one: " << endl;
    ShowSingleLinkedList(pRootOne);

    // 生成单链表Two，并与One有重叠
    pRootTwo = CreateOverlappedSingleLinkedList(pRootOne);
    cout << "Linkedlist two: " << endl;
    ShowSingleLinkedList(pRootTwo);

    // 生成单链表Three
    pRootThree = CreateSingleLinkedList();
    cout << "Linkedlist three: " << endl;
    ShowSingleLinkedList(pRootThree);

    // 利用尾结点法判断One和Two，Three是否有重叠
    cout << "Linkedlist one and Linkedlist two is overlapped ? "
         << IsOverlappedLinkedList(pRootOne, pRootTwo) << endl ;
    cout << "Linkedlist one and Linkedlist three is overlapped ? "
         <<  IsOverlappedLinkedList(pRootOne, pRootThree) << endl << endl;

    // 创建带环的单链表Four
    pRootFour = CreateSingleCircularLinkedList();
    // 判断链表是否带环
    cout << "Linkedlist four has a circul ? "
         << IsCircularSingleLinkedList(pRootFour) << endl << endl;

    // 利用带环单链表的方法判断两个链表是否重叠
    cout << "Linkedlist one and Linkedlist two is overlapped ? "
         << IsOverlappedLinkedListUsingCircul(pRootOne, pRootTwo) << endl << endl;

    // 判断两个链表的结构是否改变
    cout << "Linkedlist one: " << endl;
    ShowSingleLinkedList(pRootOne);
    cout << "Linkedlist three: " << endl;
    ShowSingleLinkedList(pRootThree);

    // 利用带环单链表的方法判断两个链表是否重叠
    cout << "Linkedlist one and Linkedlist three is overlapped ? "
         <<  IsOverlappedLinkedListUsingCircul(pRootOne, pRootThree) << endl;

    return 0;
}
