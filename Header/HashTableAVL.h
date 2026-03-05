#pragma once
template <typename V> 
    struct AVLNode;

template <typename T, typename V>
class HashTableAVL {
    T** list;
    int size;
    int count;
public:
    HashTableAVL( int size = 10) {
        if (size < 0)
            size *= -1;
        else if (size == 0)
            size = 10;
        list = new T * [size] {NULL};
        this->size = size;
        count = 0;
    }

    unsigned int hashFun(const unsigned int& key) {
        return (key * 265443576) % size;
    }

    unsigned int hashFun(const unsigned int& key, unsigned int mod) {
        return (key * 265443576) % mod;
    }

    void reHashingAVL(T** temp, AVLNode<V>* temp2, unsigned int newMod) {
        if (temp2 == NULL)
            return;
        unsigned int hashKey = hashFun(temp2->data.getKey(), newMod);
        if (temp[hashKey] == NULL)
            temp[hashKey] = new T;
        temp[hashKey]->insert(temp2->data);
        reHashingAVL(temp, temp2->left, newMod);
        reHashingAVL(temp, temp2->right, newMod);
    }

    void reHash() {
        unsigned int newSize = size * 2;
        T** temp = new T * [newSize] {NULL};
        for (int i = 0; i < size; i++) {
            if (list[i] != NULL)
                if (list[i]->getRoot() != nullptr)
                    reHashingAVL(temp, list[i]->getRoot(), newSize);
        }
			
        for (int i = 0; i < size; ++i) 
            if (list[i] != NULL) 
                delete list[i];
        delete[] list;

        list = temp;
        size = newSize;
        count = 0;
        for (int i = 0; i < size; ++i) 
            if (list[i] != nullptr) 
                ++count;
    }

    V* getNode(const unsigned int& id) {
        unsigned int hashKey = hashFun(id);
        return &list[hashKey]->getNode(id)->data;
    }

    void insert(const V& data) {
        unsigned int hashKey = hashFun(data.getKey());
        if (list[hashKey] == NULL) {
            list[hashKey] = new T;
            count++;
        }
        list[hashKey]->insert(data);
        if (count * 4 > 3 * size) 
            reHash();
    }

    void Delete(const unsigned int& id) {
        unsigned int hashKey = hashFun(id);
        if (list[hashKey] == NULL) {
            cout << "The value to be deleted not found!\n";
            return;
        }
        if (list[hashKey]->search(id))
            list[hashKey]->Delete(id);
        else {
            cout << "The value to be deleted not found!\n";
            return;
        }
        if (list[hashKey]->getRoot() == NULL) {
            delete list[hashKey];
            list[hashKey] = NULL;
            --count;
        }
        cout << "Successfully Deleted!\n";
    }

    bool search(const unsigned int& id) {
        unsigned int hashKey = hashFun(id);
        return (list[hashKey] != nullptr && list[hashKey]->search(id));
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (list[i] != NULL) {
                cout << endl;
				cout << "Bucket " << i << ":\n";
                list[i]->display();
            }
        }
    }

    int getTicketNumber(string customerId, int flightNumber) {
        for(int i=0;i<size;i++) {
            if(list[i] != NULL) {
                auto temp = list[i]->getNode(customerId, flightNumber);
                if(temp != NULL) {
                    return temp->data.getKey();
                }
            }
        }
        return -1;
    }

    void saveData(fstream& file) {
        for (int i = 0; i < size; i++) {
            if (list[i] != NULL) {
                list[i]->saveData(file);
            }
        }
	}

    ~HashTableAVL() {
        for (int i = 0; i < size; ++i) {
            if (list[i] != nullptr) delete list[i];
        }
        delete[] list;
    }

    int getBucketCount() const { return count; }
    int getTableSize() const { return size; }
};