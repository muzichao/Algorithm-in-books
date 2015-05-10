#include "hashtable.h"
#include <iostream>
#include <malloc.h>
#include <memory.h>

using namespace std;

// 构造函数
hashtable::hashtable(int HashTablsSize)
{
    iHashTableSize = HashTablsSize;
    iHashTableDataCount = 0; // Table中数据个数
    pHashTable = (Node**)malloc(sizeof(Node*) * iHashTableSize);
    if (NULL == pHashTable)
    {
        return;
    }
    memset(pHashTable, 0, sizeof(Node*) * iHashTableSize);
}

// 析构函数
hashtable::~hashtable()
{
    free(pHashTable);
    pHashTable = NULL; //释放内存后，将指针设置为NULL。避免产生“野指针”
    iHashTableSize = 0;
    iHashTableDataCount = 0;
}

// 哈希函数
int inline hashtable::HashFun(int val)
{
    return (val ^ 0xdeadbeef) % iHashTableSize;
}

bool hashtable::InsertHashTable(int val)
{
    int key = HashFun(val);

    // 先检测是否存在
    for(Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (val == p->value)
        {
            return true;
        }
    }

    // 不存在创建一个节点
    Node *pNode = new Node(val);
    if (NULL == pNode)
    {
        return false;
    }

    // 插入节点
    pNode->next = pHashTable[key];
    pHashTable[key] = pNode;

    iHashTableDataCount++; // Table中数据个数
    return true;
}

bool hashtable::FindHashTable(int val)
{
    int key = HashFun(val);

    for(Node *p = pHashTable[key]; p!= NULL; p = p->next)
    {
        if (val == p->value)
        {
            return true;
        }
    }
    return false;
}

int hashtable::SizeHashTable()
{
    return iHashTableSize;
}

void hashtable::ShowNodeLinkSize()
{
    unsigned int nodeLinkSizeA = 0;
    unsigned int nodeLinkSizeB = 0;
    unsigned int nodeLinkSizeC = 0;
    unsigned int nodeLinkSizeD = 0;
    unsigned int nodeLinkSizeE = 0;

    unsigned int *nodeLinkCount = new unsigned int [iHashTableSize];
    memset(nodeLinkCount, 0, sizeof(unsigned int) * iHashTableSize);

    Node *p;

    for (int i = 0; i < iHashTableSize; ++i)
    {
        for (Node *p = pHashTable[i]; p != NULL; p = p->next)
        {
            nodeLinkCount[i]++;
        }
    }

    for (int i = 0; i < iHashTableSize; ++i)
    {
        switch (nodeLinkCount[i])
        {
        case 0:
            nodeLinkSizeA++;
            break;
        case 1:
            nodeLinkSizeB++;
            break;
        case 2:
            nodeLinkSizeC++;
            break;
        case 3:
            nodeLinkSizeD++;
            break;
        default :
            nodeLinkSizeE++;
            break;
        }
    }

    delete [] nodeLinkCount;

    cout << "nodeLinkSizeA = " << nodeLinkSizeA  << endl;
    cout << "nodeLinkSizeB = " << nodeLinkSizeB  << endl;
    cout << "nodeLinkSizeC = " << nodeLinkSizeC  << endl;
    cout << "nodeLinkSizeD = " << nodeLinkSizeD  << endl;
    cout << "nodeLinkSizeE = " << nodeLinkSizeE  << endl;
    cout << nodeLinkSizeB + nodeLinkSizeC * 2 + nodeLinkSizeD * 3 + nodeLinkSizeE * 4 << endl;
}
