#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include<stdlib.h>
#include <QMutex>

class RingBuffer{
public :
    explicit RingBuffer(int size);

    void push(char item);
    char pull();
    void reset();
    bool isEmpty();
    bool isFull();
private:

    int head,tail=0;
    char *buffer;
    int max_size;
    mutable QMutex m_mutex;
};
#endif // RINGBUFFER_H
