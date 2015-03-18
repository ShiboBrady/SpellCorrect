#ifndef WORD_H
#define WORD_H 

#include <string>

struct Word
{
    std::string word_;
    int med_;
    int frequence_;

    bool operator < (const Word &other) const {
        if(med_ != other.med_){
            return med_ > other.med_;
        }
        else if(frequence_ != other.frequence_){
            return frequence_ < other.frequence_;
        }
        else 
            return false;
    }
};


#endif  /*WORD_H*/
