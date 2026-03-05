#pragma once
#include <iostream>
#include <fstream>
#include "SinglyLinkedList.h"
#include "Plane.h"
using namespace std;

template <typename T>
struct DNode {
    T data;
    DNode<T>* next;
    DNode<T>* prev;
    DNode(const T& data) :data(data), next(NULL), prev(NULL) {}
};


template <typename T, typename K>
class DLinkedList{
    DNode<T>* head;
    DNode<T>* tail;
public:
    DLinkedList() {
        head = NULL;
        tail = NULL;
    }

    DNode<T>* getHead() {
        return head;
    }

    DNode<T>* getTail() {
        return tail;
    }

    DNode<T>* getNode(const K& value){
        DNode<T>* temp = head;
        while(temp && temp->data.getKey() != value)
            temp = temp->next;
        return temp;
    }

    void detectAndMergeDuplicateRequests() {
        DNode<T>* temp1 = head;
        DNode<T>* temp2;
        DNode<T>* prev;

        while (temp1) {
            temp2 = temp1->next;
            prev = temp1;
            while (temp2) {
                if (temp1->data.getKey() == temp2->data.getKey()) {
                    prev->next = (temp2->next);
                    delete temp2;
                    temp2 = prev->next;

                }
                else {
                    prev = temp2;
                    temp2 = temp2->next;
                }
            }
            temp1 = temp1->next;
        }
    }



    void insertAtBeginning(const T& element) {
        DNode<T>* ref = new DNode<T>(element);
        ref->next = (head);
        ref->prev = nullptr;
        if (head != nullptr) 
            head->prev = ref;
        head = ref;
        if (tail == nullptr) 
            tail = ref;

    }

    void insert(const T& element) {
        if (head == NULL) {
            this->insertAtBeginning(element);
            return;
        }
        DNode<T>* ref = new DNode<T>(element);
        tail->next = (ref);
        ref->prev = (tail);
		ref->next = NULL;
        tail = ref;

    }

    bool search(const K& value) {
        DNode<T>* temp = head;
        while (!(temp == NULL || temp->data.getKey() == value)) {
            temp = temp->next;
        }
        if (temp != NULL)
            return true;
        else
            return false;
    }


    void deleteFromBeginning() {
        if (head == NULL) {
            return;
        }
        DNode<T>* tmp = head;
        head = head->next;
        delete tmp;
        if (head != NULL)
            head->prev = NULL;
        else
            tail = NULL;


    }



    void traverse() {
        DNode<T>* temp = head;
        while (temp != NULL) {
            temp = temp->next;
        }
    }


    void deleteFromEnd() {
        if (head == NULL) {
            return;
        }
        DNode<T>* tmp = tail;
        tail = tail->prev;
        delete tmp;
        if (tail != NULL)
            tail->next = NULL;
        else
            head = NULL;
    }

    bool Delete(const K& value) {
		cout << "Reached Delete\n";
        if (head == NULL)
            return false;
		DNode<T>* temp = head;
        while(temp && temp->data.getKey() != value) 
            temp = temp->next;
		cout << "After While\n";
		if (!temp)
			return false;
        cout << "1\n";
        if (temp == head) {
			cout << "Reached delete from beginning\n";
            head = head->next;
            delete temp;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
        }
        else if (temp == tail) {
			cout << "Reached delete from end\n";
            tail = tail->prev;
			cout << "helppp\n";
            delete temp;
            if (tail != NULL)
                tail->next = NULL;
            else
                head = NULL;
            return true;
        }
        else{
			cout << "Reached middle deletion\n";
            if(temp->prev)
                temp->prev->next = (temp->next);
			if (temp->next)
                temp->next->prev = (temp->prev);
            delete temp;
        }
		cout << "Returning True\n"; 
		return true;
    }

    int getPosition(K value) {
        if (search(value)) {
            DNode<T>* temp = head;
            DNode<T>* temp2 = tail;
            int count = 1;
            int count2 = this->size();
            while (temp->data.getKey() != value && temp2->data.getKey() != value) {
                temp = temp->next;
                temp2 = temp2->prev;
                count2--;
                count++;
            }
            if (temp->data.getKey() == value)
                return count;
            else
                return count2;
        }
        else {
            return -1;
        }
    }

    int size() {
        DNode<T>* temp = head;
        int count = 0;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display() {
        if (head == NULL) {
            cout << "The list is empty\n";
            return;
        }
        DNode<T>* temp = head;
        cout << endl;
        do {
            if (temp->next != NULL)
                temp->data.display();
            else
                temp->data.display();
            temp = temp->next;
        } while (temp != NULL);
    }

    void display(string destination) {
        if (head == NULL) {
            cout << "The list is empty\n";
            return;
        }
        DNode<T>* temp = head;
        cout << endl;
        do {
            if(temp->data.getDestination() == destination)
				temp->data.display();
            temp = temp->next;
        } while (temp != NULL);
    }

    bool display(const K& value){
        if (head == NULL) 
            return false;
		DNode<T>* temp = head;
        while (!(temp == NULL || temp->data.getKey() == value)) {
            temp = temp->next;
        }
        if (temp != NULL)
            temp->data.display();
        else
            return false;
        return true;
    }


    bool updateData(const K& value, SinglyLinkedList<Plane, int>& planeList) {
        DNode<T>* temp = head;
        while (!(temp == NULL || temp->data.getKey() == value)) {
            temp = temp->next;
        }
        if (temp != NULL) {
            temp->data.updateData(planeList);
            return true;
        }
        else
            return false;
	}

    void saveData(fstream& file) {
        DNode<T>* temp = head;
        while (temp) {
            temp->data.saveData(file);
            temp = temp->next;
        }
	}

    ~DLinkedList() {
        DNode<T>* cur = head;
        DNode<T>* nxt;
        while (cur) {
            nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

};


