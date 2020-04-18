//
//  nonblockingqueue.cpp
//  fifo
//
//  Created by SarvanaKumar on 18/04/20.
//  Copyright © 2020 SarvanaKumar. All rights reserved.
//
#include "fifo.hpp"
#include <iostream>
#include <thread>

void nonblockingget_thread(FiFo<int> *myfifo)
{
    int *ptr = myfifo->get(false);
    if (ptr == NULL)
        cout << "Success: Get Thread: no blocking eventhough there is  no element in FiFO \n";
    else
        cout << "Failure: Get thread - got info from FiFO";
}
void put_thread(FiFo<int> *myfifo)
{
    int *ptr1 = new int;
    int *ptr2 = new int;
    int *ptr3 = new int;
    int *ptr4 = new int;
    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    *ptr4 = 4;
    cout << "PUT Thread: Put into FiFo: for get threads \n";
    myfifo->put(ptr1, false);
    myfifo->put(ptr2, false);
    myfifo->put(ptr3, false);
    
    bool put_success = myfifo->put(ptr4, false);
    if (put_success == false)
        cout << "Success: Cannot put elements more than FiFo capacity \n";
    else
        cout << "Failure: Can put elements more than FiFo capacity \n";
}

void get_thread1(FiFo<int> *myfifo)
{
    
    int *ptr =  myfifo->get(false);
    
    string output ="GET Thread 1: Element obtained is " + to_string(*ptr) + "\n";
    cout << output << flush;
}

void get_thread2(FiFo<int> *myfifo)
{
    int *ptr1 =  myfifo->get(false);
    int *ptr2 =  myfifo->get(false);
    
    
    string output1 = "GET Thread 2: Element obtained is " + to_string(*ptr1) + "\n";
    string output2 = "GET Thread 2: Element obtained is " + to_string(*ptr2) + "\n";
    cout << output1 << flush;
    cout << output2 << flush;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Non Blocking FIFO explanation \n" << flush;
    FiFo<int> myfifo(3);
    thread *t_nonblocking_get = new thread(nonblockingget_thread, &myfifo);
    t_nonblocking_get->join();
    
    thread *t_put = new thread(put_thread, &myfifo);
    t_put->join();
    thread *t_get1 = new thread(get_thread1, &myfifo);
    thread *t_get2 = new thread(get_thread2, &myfifo);
    t_get1->join();
    t_get2->join();
    
    cout << "All the Non blocking FIFO operation complete \n";
    return 0;
}

