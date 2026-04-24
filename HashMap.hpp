#ifndef HASHMAP_HPP
#define HASHMAP_HPP
//#include "HashNode.hpp"
#include <vector>

template <typename K, typename V>
class HashNode {
public:
    HashNode(const K& key, const V& value): key(key), value(value) {}
    K key;
    V value;
};

template <typename K, typename V>
class HashMap {
public:
    //  default is 389 as it is the closest prime above the 385 entries in airports.csv
    //  will probably change this to be higher to reduce colisions later
    HashMap(int size = 389);

    bool empty() const;
    bool full() const;

    void insert(const K& key, const V& value);

    //  Task 5 functions ===========================================
    //  overloaded to always start with value 0
    void insert(const K& key);
    //  will increment the value at pos key
    void incrementValue(const K& key, const int& val = 1);
    //  special print
    void mapOutput() const;
    //   ===========================================================

    void print() const;


private:
    std::vector<HashNode<K, V>*> data;
    int n; // The number of records in the table

    HashNode<K, V>* deleted;

    //  hash function
    int hash(const K& key) const;

    //  return the index, of the key, if the key exists else {-1}
    int searchIndex(const K& key) const;

};

#include "HashMap.tpp"

#endif
