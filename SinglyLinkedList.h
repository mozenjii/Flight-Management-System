#pragma once

#include <iostream>
using namespace std;
template <typename K>
struct Node {
    K data;
    Node<K>* next;
    Node(const K& data) :data(data), next(NULL) {}
};


template <typename K, typename Z>
class SinglyLinkedList {
    Node<K>* head;
public:
    SinglyLinkedList() {
        head = NULL;
    }

    Node<K>* getHead() {
        return head;
    }

    Node<K>* getNode(const Z& value) {
        Node<K>* temp = head;
        while(temp && temp->data.getKey() != value)
            temp = temp->next;
        return temp;
    }

    void insert(K element) {
        Node<K>* ref = new Node<K>(element);
        if (head == NULL) {
            head = ref;
            return;
        }

        if (element.getKey() <= head->data.getKey()) {
            ref->next = head;
            head = ref;
            return;
        }
        Node<K>* temp = head;

        while (temp->next && temp->next->data.getKey() < element.getKey()) {
            temp = temp->next;
        }
		ref->next = (temp->next);
		temp->next = (ref);
       
    }

    bool search(const Z& value) {
        Node<K>* temp = head;
        while (!(temp == NULL || temp->data.getKey() == value)) {
            temp = temp->next;
        }
        if (temp != NULL)
            return true;
        else
            return false;
    }

    int getMiles(const Z& value) {
        Node<K>* temp = head;
        while(temp && temp->data.getKey() != value)
            temp = temp->next;
        if(temp)
            return temp->data.getMilesFromBeirut();
        return 0;
    }

    void deleteFromBeginning() {
        if (head == NULL) {
            cout << "Error: Empty list; deletion failed!!\n";
            return;
        }
        Node<K>* temp = head->next;
        delete head;
        head = temp;

    }

    void reverseList(Node<K>* node, Node<K>* preNode) {
        if (node->next != NULL) {
            if (preNode == NULL)
                reverseList(node->next, head);
            else
                reverseList(node->next, preNode->next);
        }
        else
            head = node;
        node->next = (preNode);
    }

    void reverseList() {
        if (head && head->next)
            reverseList(head, NULL);
    }

    void Delete(const Z& value) {
        Node<K>* temp = head;
        Node<K>* preN = head;
        while (temp != NULL && temp->data.getKey() != value) {
            preN = temp;
            temp = temp->next;
        }
        if (temp == NULL)
            cout << "Element being removed not found!\n";
        else if (temp->data.getKey() == value && temp == head) {
            preN = head->next;
            delete head;
            head = preN;
        }
        else if (temp->data.getKey() == value) {
            preN->next = (temp->next);
            delete temp;
        }

    }


    int size() {
        Node<K>* temp = head;
        int count = 0;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void assignValuesCount(int& businessClass, int& economyClass, Z key) {
        Node<K>* temp = head;
        while (!(temp == NULL || temp->data.getKey() == key)) {
            temp = temp->next;
        }
        if (temp != NULL) {
            businessClass = temp->data.getNumberOfSeatsPerClass(0);
            economyClass = temp->data.getNumberOfSeatsPerClass(1);
        }
        else {
			businessClass = 0;
			economyClass = 0;
        }
    }


    void display() {
        if (head == NULL) {
            cout << "The list is empty\n";
            return;
        }
        Node<K>* temp = head;
        do {
            temp->data.display();
            temp = temp->next;
			cout << endl;
        } while (temp != NULL);
    }

    class Iterator {
        Node<K>* ptr;
    public:
        Iterator(Node<K>* current) :ptr(current) {}
        Iterator& operator++() {
            if (ptr)
                ptr = ptr->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }

        K operator*() {
            return ptr->data;//78;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(NULL);
    }

};
