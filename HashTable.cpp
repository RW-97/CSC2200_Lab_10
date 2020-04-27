#include <iostream>

#include "HashTable.h"

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
    : tableSize(initTableSize)
{
    dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& source) {
    copyTable(source);
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>&
HashTable<DataType, KeyType>::operator=(const HashTable& source) {
    if (&source != this) {
	delete[] dataTable;
	copyTable(source);
    }

    return *this;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source) {
    tableSize = source.tableSize;
    dataTable = new BSTree<DataType, KeyType>[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        dataTable[i] = source.dataTable[i];
    }
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable() {
    delete[] dataTable;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem) {
    unsigned int loc = DataType::hash(newDataItem.getKey()) % tableSize;

    dataTable[loc].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey) {
    unsigned int loc = DataType::hash(deleteKey) % tableSize;

    return dataTable[loc].remove(deleteKey);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey,
					    DataType& returnItem) const
{

    int loc = DataType::hash(searchKey) % tableSize;

    return dataTable[loc].retrieve(searchKey, returnItem);
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear() {
   
    for (int i = 0; i < tableSize; ++i)
    {
        dataTable[i].clear();
    }
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const {
   
    for (int i = 0; i < tableSize; ++i)
    {
        if (dataTable[i].isEmpty() == false)
        {
            return false;
        }
    }

    return true;
}

#include <cmath>

template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const {
    int total = 0;

    for (int i = 0; i < tableSize; ++i) {
	total += dataTable[i].getCount();
    }

    double average = total / tableSize;
    double sum = 0.0;

    for (int i = 0; i < tableSize; ++i) {
	int size = dataTable[i].getCount();
	sum += (size - average) * (size - average);
    }

    return sqrt(sum / (tableSize - 1));
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}
