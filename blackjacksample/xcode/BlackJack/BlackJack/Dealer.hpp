//
//  Dealer.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/15.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#ifndef Dealer_hpp
#define Dealer_hpp

#include "Person.hpp"

class Dealer : public Person
{
public:
    Dealer();
    virtual ~Dealer();
    
    virtual Answer judge(const Person& rival);     // どうするか判断
    
public:
    virtual const bool isAI() const { return true; }
};

#endif /* Dealer_hpp */
