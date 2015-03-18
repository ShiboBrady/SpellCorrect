#ifndef EXCEPTION_H
#define EXCEPTION_H 

#include <iostream>
#include <string>
#include <exception>

class Exception:public std::exception
{
    public:
        //explicit Exception(const char* what);
        explicit Exception(const std::string &what);
        virtual ~Exception() throw(); // 表示该函数不抛出异常
        virtual const char *what() const throw();
        const char* stackTrace() const throw();
    private:
        void fillStackTrace();

        std::string message_;
        std::string stack_;
};

#endif  /*EXCEPTION_H*/
