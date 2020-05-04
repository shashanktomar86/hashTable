#include <iostream>
#include <string>
using namespace std;

class hash
{
    public:
        hash();
        int hashCode(string key);
        void insert(string name, string drink);
        void removeItem(string name);
        int totalIndexItems(int index);
        void printTable();
        void findDrink(string name);
        ~hash(); 



    private:

        static const int TABLE_SIZE = 40;
        struct item
        {
            std::string name;
            std::string drink;
            item *next;
        };

        item *hashTable[TABLE_SIZE];

};
