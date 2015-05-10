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
    pHashTable = (Node **)malloc(sizeof(Node *) * iHashTableSize);
    if (NULL == pHashTable)
    {
        return;
    }
    memset(pHashTable, 0, sizeof(Node *) * iHashTableSize);
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
// int inline hashtable::HashFun(hashNodeType val)
// {
//     return (val ^ 0xdeadbeef) % iHashTableSize;
// }
/* End Of type int Hash Function */

// 哈希函数
// unsigned int inline hashtable::HashFun(hashNodeType val)
// {
//     unsigned int nHash = 0;
//     for (int i = 0; val[i] != '\0'; ++i)
//     {
//         nHash = (nHash << 5) + nHash + val[i];
//     }
//     return nHash % iHashTableSize;
// }
/* End Of times33 Hash Function */


// 哈希函数
// unsigned int inline hashtable::HashFun(hashNodeType val)
// {
//     unsigned int nHash = 0;
//     unsigned int seed = 131; //31 131 1313 13131

//     for (int i = 0; val[i] != '\0'; ++i)
//     {
//         nHash = nHash * seed + val[i];
//     }
//     return nHash % iHashTableSize;
// }
/* End Of BHDR Hash Function */

// 哈希函数
unsigned int inline hashtable::HashFun(hashNodeType val)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;

    for (std::size_t i = 0; i < val.length(); i++)
    {
        hash = hash * a + val[i];
        a    = a * b;
    }

    return hash % iHashTableSize;
}
/* End Of RS Hash Function */

bool hashtable::InsertHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val);

    // 先检测是否存在
    for (Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (val == p->nodeData)
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

bool hashtable::FindHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val);

    for (Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (val == p->nodeData)
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

    unsigned int hashTableAllCount = 0;

    // 统计每个位置上的节点数
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

        hashTableAllCount += nodeLinkCount[i];
    }

    cout << "空节点 ：nodeLinkSizeA = " << nodeLinkSizeA  << endl;
    cout << "单节点 ：nodeLinkSizeB = " << nodeLinkSizeB  << endl;
    cout << "两节点 ：nodeLinkSizeC = " << nodeLinkSizeC  << endl;
    cout << "三节点 ：nodeLinkSizeD = " << nodeLinkSizeD  << endl;
    cout << "四节点 ：nodeLinkSizeE = " << nodeLinkSizeE  << endl;
    cout << "总节点数 ：hashTableAllCount = " << hashTableAllCount << endl;
}
