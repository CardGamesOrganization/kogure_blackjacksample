//
//  Dealer.hpp
//  BlackJack
//
//  Created by ¬åŒ’‘¾ on 2017/08/15.
//  Copyright  2017”N ¬åŒ’‘¾. All rights reserved.
//

#ifndef Dealer_hpp
#define Dealer_hpp

#include "Person.hpp"

class Dealer : public Person
{
public:
    Dealer();
    virtual ~Dealer();
    
    virtual Answer judge(const Person& rival);     // ‚Ç‚¤‚·‚é‚©”»’f
    
public:
    virtual const bool isAI() const { return true; }
};

#endif /* Dealer_hpp */
