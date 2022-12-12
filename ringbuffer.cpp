#include "ringbuffer.h"

RingBuffer::RingBuffer(int size){
        buffer = new char[size];
        max_size = size;
}

void RingBuffer::push(char item){

   const QMutexLocker locker (&m_mutex);

   if (isFull()){

       return;
   }

    buffer[head]= item;
    head = head +1 % max_size;


}

char RingBuffer::pull(){ // or with pointer as arguments

    char tmp;

    const QMutexLocker locker (&m_mutex);

    if(isEmpty()){

        return 0;
    }

    tmp = buffer[tail];
    tail = tail +1% max_size;

    return tmp;
}

void RingBuffer::reset(){
    const QMutexLocker locker (&m_mutex);
    tail=0;
    head=0;
}

bool RingBuffer::isEmpty(){

    return head==tail;
}

bool RingBuffer::isFull(){
     return tail == (head+1)%max_size;
}
