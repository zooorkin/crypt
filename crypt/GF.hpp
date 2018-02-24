//
//  GF.hpp
//  crypt
//
//  Created by Андрей Зорькин on 15.11.17.
//  Copyright © 2017 Андрей Зорькин. All rights reserved.
//

#ifndef GF_hpp
#define GF_hpp

#include <stdio.h>
#include <vector>



//template <typename SomeZn>
//class GFk {
//public:
//
//    const int k;
//    SomeZn* array;
//    
//
//    GFk(int k, SomeZn* array = nullptr):
//    k(k)
//    {
//        array = new SomeZn[k];
//        if (array != nullptr){
//        for (int i = 0; i < k; ++i)
//            this->array[i] = array[i];
//        }
//    }
//    
//    GFk<SomeZn> operator +(GFk<SomeZn> rightValue){
//        GFk<SomeZn> r = GFk<SomeZn>(k );
//    }
//    
//    ~GFk(){
//        delete[] array;
//    }
//    
//    
//};

class GF{
public:
    const unsigned char p = 200; // 128 + 64 + 8 == 1100 1000
    unsigned char value;
    
    GF(unsigned int value):
    value(value){
        
    }
    GF operator +(GF rightValue){
        return GF(value^rightValue.value);
    }
    
    GF operator +(unsigned char rightValue){
        return GF(value^rightValue);
    }
    
    GF operator ++(){
        return GF(value + 1);
    }
    
    int print(){
        return static_cast<int>(value);
    }
    
};

#endif /* GF_hpp */
