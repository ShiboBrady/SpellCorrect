#ifndef QUEUE_HPP
#define QUEUE_HPP 
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>


template <typename T> class Queue;
template <typename T>
class Node
{
    friend class Queue<T>;
    public:
        Node(T data = 0, Node *next = NULL)
            :data_(data), next_(next){}
    private:
        T data_;
        Node *next_;
};

template <typename T>
class Queue
{
    public:
        typedef Node<T>* p_node;
        Queue();
        Queue(const Queue &other);
        Queue &operator = (const Queue &other);
        ~Queue();

        void clear();
        void enqueue(const T &data);
        void dequeue(T &data);
        bool isEmpty();
        size_t getSize();
    private:
        p_node front_;
        p_node rear_;
        size_t size_;
};

template <typename T>
inline Queue<T>::Queue()
    :front_(NULL),
     rear_(NULL),
     size_(0)
{}

template <typename T>
inline Queue<T>::Queue(const Queue &other)
    :front_(NULL),
     rear_(NULL),
     size_(0)
{
    p_node p = other.front_;
    while(p != NULL){
        enqueue(p->data_);
        p = p->next_;
    }
}

template <typename T>
inline Queue<T> &Queue<T>::operator = (const Queue &other)
{
    if(this != &other){
        clear();
        p_node p = other.front_;
        while(p != NULL){
            enqueue(p->data_);
        }
    }
    return *this;
}

template <typename T>
inline Queue<T>::~Queue()
{
    clear();
}

template <typename T>
inline void Queue<T>::clear()
{
    p_node p;
    while(front_ != NULL){
        p = front_;
        front_ = front_->next_;
        delete p;
    }
    rear_ = NULL;
    size_ = 0;
}

template <typename T>
inline void Queue<T>::enqueue(const T &data)
{
    p_node p = new Node<T>(data);
    if(front_ == NULL)
        front_ = rear_ = p;
    else{
        rear_->next_ = p;
        rear_ = p;
    }
    size_ ++;
}

template <typename T>
inline void Queue<T>::dequeue(T &data)
{
    assert(!isEmpty());
    data = front_->data_;
    front_ = front_->next_;
    size_--;
}

template <typename T>
inline bool Queue<T>::isEmpty()
{
    return front_ == NULL;
}

template <typename T>
inline size_t Queue<T>::getSize()
{
    return size_;
}


#endif  /*QUEUE_H*/
