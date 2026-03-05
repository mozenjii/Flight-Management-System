#pragma once
#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;


template <typename K>
class Queue {
    Node <K>* front;
    Node <K>* rear;
    int size;
    int curr;
public:
    Queue(int size) :front(NULL), rear(NULL), size(size), curr(0) {}

    bool enqueue(K value) {
        if(curr+1 == size)
			return false;
        Node <K>* NEW = new Node<K>(value);
        if (rear == NULL) {
            rear = NEW;
            front = NEW;
        }
        else {
            rear->next = (NEW);
            rear = NEW;
        }
        curr++;
		return true;
    }

    int dequeue() {
        int data;
        if (front == rear)
            rear = NULL;

        if (front == NULL)
            return -1;
        else {
            Node<K>* temp = front;
            front = front->next;
			data = temp->data.getKey();
            delete temp;
        }
		curr--;
		return data;
    }

    void display() {
        Node<K>* temp = front;
        cout << endl;
        while (temp) {
            temp->data.display();
            temp = temp->next;
        }
    }

    int getSize() const {
        return size;
    }

    int getCurrentSize() const {
        return curr;
    }

    void incrementCurrentSize() {
        curr++;
    }

    ~Queue() {
        Node<K>* temp;
        while (front != NULL) {
            temp = front;
            front = front->next; 
            delete temp;
        }
    }

};