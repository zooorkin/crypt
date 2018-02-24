//
//  Zn.hpp
//  crypt
//
//  Created by Андрей Зорькин on 15.11.17.
//  Copyright © 2017 Андрей Зорькин. All rights reserved.
//

#ifndef Zn_hpp
#define Zn_hpp

#include <stdio.h>
#include <assert.h>

#include <iostream>

//class Zn{
//public:
//    const int n;
//    const int value;
//    
//    Zn(int n, int value):
//    n(n), value(value)
//    {
//    }
//    
//    Zn operator +(const Zn rightValue){
//        assert(n == rightValue.n);
//        return Zn(n, (value + rightValue.value) % n);
//    }
//};

class Z2{
public:
    bool value;
    
    Z2(int value):
    value(value%2){
        
    }
    Z2 operator +(const Z2 rightValue){
        return Z2(value + rightValue.value);
    }
    Z2 operator ++(){
        value = !value;
        return value;
    }
};

#endif /* Zn_hpp */
