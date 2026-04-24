#include "HashMap.hpp"
#include <iostream>


template <typename K, typename V>
HashMap<K, V>::HashMap(int size) : n(0) {
    // resize based on the amount all to nullptr
    data.resize(size, nullptr);

    //  create deleted node, with default of each data type
    deleted = new HashNode<K, V>(K(), V());
}


template <typename K, typename V>
bool HashMap<K, V>::empty() const {
    return n == 0;
}

template <typename K, typename V>
bool HashMap<K, V>::full() const {
    return n == data.size();
}


template <typename K, typename V>
int HashMap<K, V>::hash(const K& key) const {

    int hashSum = 0;

    for (char c : key) {
        hashSum += int(c);
    }

    return hashSum % data.size();
}


template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    if (full()) {
        return;
    }

    //  find the hash
    int index = hash(key);

    while (data[index] && data[index] != deleted) {
        index = (index + 1) % data.size(); // Go to the next position
    }

    //  Insert the node
    data[index] = new HashNode<K,V>(key, value);
    n++;
}

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key) {
    if (full()) {
        return;
    }

    //  find the hash
    int index = hash(key);

    while (data[index] && data[index] != deleted) {
        index = (index + 1) % data.size(); // Go to the next position
    }

    //  Insert the node
    data[index] = new HashNode<K,V>(key, 0);
    n++;


}

template <typename K, typename V>
void HashMap<K, V>::incrementValue(const K& key, const int& val) {
    data[hash(key)]->value += val;
}

template <typename K, typename V>
int HashMap<K, V>::searchIndex(const K& key) const {
    //  find the hash
    int index = hash(key);

    while (data[index] && data[index] != deleted) {
        if (data[index].key == key) {
            return index;
        }
        index = (index + 1) % data.size(); // Go to the next position
    }
    return -1;
}


template <typename K, typename V>
void HashMap<K, V>::print() const {
    std::cout << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout << i << " ";
        if (data[i] == nullptr) {
            std::cout << "nullptr\n";
        }
        else if (data[i] == deleted) {
            std::cout << "deleted\n";
        }
        else {
            std::cout << "{ " << data[i]->key << "; " << data[i]->value << " }\n";
        }
    }
    std::cout << std::endl;
    
}

template <typename K, typename V>
void HashMap<K, V>::mapOutput() const {
    std::cout << "Airport   Connections" << std::endl;

    for (int i = 0; i < data.size(); i++) {
        
        if (data[i]) {
            std::cout << data[i]->key << "       " << data[i]->value << std::endl;
        }
    }
}
