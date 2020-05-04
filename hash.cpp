#include "hash.h"

main()
{
    hash hTable;
    hTable.insert("shashank", "orange");
    hTable.insert("shashank", "banana");
    hTable.insert("harry", "coke");
    hTable.insert("orson", "choclate");
    hTable.insert("shashank", "orange");
    hTable.insert("harry", "cig");
    hTable.insert("orson", "frooti");
    hTable.printTable();
    cout << "\n---------TABLE PRINTED------------\n";
    hTable.findDrink("orson");
    hTable.removeItem("shashank");
    hTable.printTable();
    cout << "\n---------TABLE PRINTED------------\n";

}

hash::hash()
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = new item;
        hashTable[i]->name = "empty";
        hashTable[i]->drink = "empty";
        hashTable[i]->next = NULL;
    }
}

hash::~hash()
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        item *current = hashTable[i];
        while (current != NULL)
        {
            hashTable[i] = hashTable[i]->next;
            delete current;
            current = hashTable[i];
        }
    }
}


int hash::hashCode(string key)
{
    int hash = 0;
    int index = 0;
    for (int i=0; i < key.length(); i++)
    {
        hash = hash + (int)key[i];
    }
    hash *= 17;
    index = hash % TABLE_SIZE;
    return index;
}

void hash::insert(string name, string drink)
{
    int index = hashCode(name);
    if (hashTable[index]->name == "empty")
    {
        hashTable[index]->name = name;
        hashTable[index]->drink = drink;
    }
    else
    {
        item *ptr = hashTable[index];
        item *newNode = new item;
        newNode->name = name;
        newNode->drink = drink;
        newNode->next = NULL;

        while(ptr->next)
        {
            ptr = ptr->next;
        }

        ptr->next = newNode;
    }
}

void hash::removeItem(string name)
{
    int index = hashCode(name);
    item *delPtr = hashTable[index];
    item *prev;
    bool found = false;

    if ((hashTable[index]->name == name) && (hashTable[index]->next == NULL))
    {
        hashTable[index]->name = "empty";
        hashTable[index]->drink = "empty";
    }
    else if ((hashTable[index]->name == name) && (hashTable[index]->next != NULL))
    {
        hashTable[index] = hashTable[index]->next;
        delete delPtr;
    }
    else
    {
        while (delPtr)
        {
            if (delPtr->name == name)
            {
                found = true;
                break;
            }

            prev = delPtr;
            delPtr = delPtr->next;
        }

        if (found)
        {
            prev->next = delPtr->next;
            delete delPtr;
        }
        else
        {
            cout << "--- data not found ---\n";
        }
    }
}


int hash::totalIndexItems(int index)
{
    int count = 0;
    item *ptr = hashTable[index];
    if (hashTable[index]->name != "empty")
    {
        while (ptr)
        {
            ptr = ptr->next;
            ++count;
        }
    }

    return count;
}

void hash::printTable()
{
    int num = 0;
    for (int i=0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i]->name != "empty")
        {
            num = totalIndexItems(i);
            cout << "name = " << hashTable[i]->name << endl;
            cout << "drink = " << hashTable[i]->drink << endl;
            cout << "num items in index " << i << " = " << num << endl;
        }
    }
}

void hash::findDrink(string name)
{
    int index = hashCode(name);
    item* ptr = hashTable[index];

    if (hashTable[index]->name == "empty")
    {
        cout << "no entry exists\n";
    }
    else
    {
        while (ptr)
        {
            if (ptr->name == name)
            {
                cout << "drink = " << ptr->drink << endl;
                break;
            }
            ptr = ptr->next;
        }
    }
}

