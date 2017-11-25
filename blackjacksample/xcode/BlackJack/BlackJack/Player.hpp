//
//  Player.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Person.hpp"

class Player : public Person
{
public:
    Player();
    virtual ~Player();
    
    virtual Answer judge(const Person& rival);     // どうするか判断
    
public:
    virtual const bool isAI() const { return false; }
};

#endif /* Player_hpp */
