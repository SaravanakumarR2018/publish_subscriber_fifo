//
//  fifo.hpp
//  fifo
//
//  Created by SarvanaKumar on 18/04/20.
//  Copyright © 2020 SarvanaKumar. All rights reserved.
//

#ifndef fifo_h
#define fifo_h
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;
/* FiFo is a first in first out queue
   This can act as a blocking queue as well as non-blocking queue
Blocking Queue functions:
 get() - returns the pointer at the front of queue
         the calling thread gets blocked if there is no element in queue
 put(T *ptr) - puts the pointer to the templated element into the queue
               the calling thread gets blocked if the queue capacity is full
                returns: true if element is pushed into queue
                    
 
 Non Blocking queue functions:
 get(false) - returns the pointer at the front of the queue
              if queue is empty returns NULL
              does not block the calling thread
 put(T *value, false) - puts the pointer to the templated element into the queue
                        the calling thread does not get blocked when the queue capacity is full
                        returns: true if element is pushed into queue
                                false if element cannot be pushed into queue as queue capacity is full
 
 */
template<typename T>
class FiFo
{
    class Node {
    public:
        Node(T *p, Node *n=NULL):next(n),value_ptr(p) {}
        Node *next;
        T * value_ptr;
    };
    Node *head;
    Node *tail;
    unsigned int count;
    unsigned int capacity;
    mutex mtx;
    condition_variable get_cv;
    condition_variable put_cv;
public:
    FiFo(int cpcty=1000):head(NULL),tail(NULL),count(0),capacity(cpcty) {}
    T *get(bool block=true);
    bool put(T *value, bool block = true);
    void show();
    
};

template<typename T>
void FiFo<T>::show() {
    Node *current = head;
    cout << "Elements in the FiFo:" << endl;
    while(current != NULL)
    {
        cout << *(current->value_ptr) << " ";
        current = current->next;
    }
    cout << endl;
}

template<typename T>
T * FiFo<T>::get(bool block)
{
    unique_lock<mutex> lock(mtx);
    if (block) {
        while(count == 0)
        {
            get_cv.wait(lock);
            
        }// avoiding spurious wakeup
    } else {
        if (count == 0) {
            return NULL;
        }
    }
    T *value = head->value_ptr;
    if (count == 1) {
        delete head;
        head = NULL;
        tail = NULL;
        count = 0;
        
    } else {
        Node *temp = head;
        head = head->next;
        count--;
        delete temp;
    }
    put_cv.notify_one();
    return value;
}
template<typename T>
bool FiFo<T>::put(T *value, bool block)
{
    unique_lock<mutex> lock(mtx);
    if (block) {
        while (count == capacity) {
            put_cv.wait(lock);
        }
    } else {
        if (count == capacity) {
            return false;
        }
    }
    Node *node = new Node(value);
    if (count == 0)
    {
        head = node;
        tail = node;
        count = 1;
    } else {
        tail->next = node;
        tail = node;
        count++;
    }
    get_cv.notify_one();
    return true;
}

#endif /* fifo_h */
