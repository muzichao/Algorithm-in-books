#include "hashtable.h"
#include <iostream>
#include <malloc.h>
#include <memory.h>

using namespace std;

// 构造函数
/************************************************************************/
/*函数名：hashtable
/*功  能：构造函数，对哈希表进行初始化
/*返回值：无
/************************************************************************/
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


/************************************************************************/
/*函数名：~hashtable
/*功  能：析构函数，清理释放内存
/*返回值：无
/************************************************************************/
hashtable::~hashtable()
{
    free(pHashTable);
    pHashTable = NULL; //释放内存后，将指针设置为NULL。避免产生“野指针”
    iHashTableSize = 0;
    iHashTableDataCount = 0;
}

/************************************************************************/
/*函数名：InitCryptTable
/*功  能：对哈希索引表预处理
/*返回值：无
/************************************************************************/
void hashtable::InitCryptTable()
{
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for ( index1 = 0; index1 < 0x100; index1++ )
    {
        for ( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )
        {
            unsigned long temp1, temp2;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);
            cryptTable[index2] = ( temp1 | temp2 );
        }
    }
}


/************************************************************************/
/*函数名：HashFun
/*功  能：哈希函数，计算字符串的哈希值
/*返回值：返回哈希值
/************************************************************************/
unsigned int hashtable::HashFun(hashNodeType val, unsigned int iHashType)
{
    unsigned int seed1 = 0x7FED7FED, seed2  = 0xEEEEEEEE;
    int ch;

    for (std::size_t i = 0; i < val.length(); i++)
    {
        ch = toupper(val[i]);
        seed1 = cryptTable[(iHashType << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }

    return seed1 % iHashTableSize;
}
/* End Of Blizzard Hash Function */

/************************************************************************/
/*函数名：InsertHashTable
/*功  能：哈希表插入函数，将新的选项插入哈希表
/*返回值：返回true或false
/************************************************************************/
bool hashtable::InsertHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val, 0);
    unsigned int nHashA = HashFun(val, 1);
    unsigned int nHashB = HashFun(val, 2);

    // 先检测是否存在
    for (Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (nHashA == p->nHashA && nHashB == p->nHashB)
        {
            return true;
        }
    }

    // 不存在创建一个节点
    Node *pNode = new Node(nHashA, nHashB);
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

/************************************************************************/
/*函数名：FindHashTable
/*功  能：哈希表查找函数，查找选项是否在哈希表中
/*返回值：返回true或false
/************************************************************************/
bool hashtable::FindHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val, 0);
    unsigned int nHashA = HashFun(val, 1);
    unsigned int nHashB = HashFun(val, 2);

    for (Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (nHashA == p->nHashA && nHashB == p->nHashB)
        {
            return true;
        }
    }
    return false;
}

/************************************************************************/
/*函数名：SizeHashTable
/*功  能：哈希表大小函数，计算哈希表的大小
/*返回值：返回哈希表的大小
/************************************************************************/
int hashtable::SizeHashTable()
{
    return iHashTableSize;
}

/************************************************************************/
/*函数名：ShowNodeLinkSize
/*功  能：哈希表显示函数，显示哈希表的信息
/*返回值：无
/************************************************************************/
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
