//
//  main.cpp
//  fifo
//
//  Created by SarvanaKumar on 18/04/20.
//  Copyright © 2020 SarvanaKumar. All rights reserved.
//
//BLOCKING QUEUE example

#include <iostream>
#include <thread>
#include "fifo.hpp"
#include <string>

void put_thread(FiFo<int> *myfifo)
{
    int *ptr1 = new int;
    int *ptr2 = new int;
    int *ptr3 = new int;
    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    cout << "PUT Thread: Put into FiFo: will unblock get threads \n";
    myfifo->put(ptr1);
    myfifo->put(ptr2);
    myfifo->put(ptr3);
}

void get_thread1(FiFo<int> *myfifo)
{
    cout << "GET Thread 1:  trying to get element from FiFo \n" ;
    
    int *ptr =  myfifo->get();
    
    string output ="GET Thread 1: Element obtained is " + to_string(*ptr) + "\n";
    cout << output << flush;
}

void get_thread2(FiFo<int> *myfifo)
{
    cout << "GET Thread 2:  trying to get element from FiFo \n";
    
    
    int *ptr1 =  myfifo->get();
    int *ptr2 =  myfifo->get();
    
    
    string output1 = "GET Thread 2: Element obtained is " + to_string(*ptr1) + "\n";
    string output2 = "GET Thread 2: Element obtained is " + to_string(*ptr2) + "\n";
    cout << output1 << flush;
    cout << output2 << flush;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Blocking FIFO explanation \n" << flush;
    FiFo<int> myfifo(3);
    
    thread *t_get1 = new thread(get_thread1, &myfifo);
    thread *t_put = new thread(put_thread, &myfifo);
    thread *t_get2 = new thread(get_thread2, &myfifo);
    t_get1->join();
    t_put->join();
    t_get2->join();
    
    cout << "All the blocking FIFO operation complete \n";
    return 0;
}

