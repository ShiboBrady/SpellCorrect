#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H 

class NonCopyable
{
    public:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable &other);
        void operator = (const NonCopyable &other);
};

#endif  /*NONCOPYABLE_H*/
