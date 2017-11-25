//
//  Player.hpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Person.hpp"

class Player : public Person
{
public:
    Player();
    virtual ~Player();
    
    virtual Answer judge(const Person& rival);     // �ǂ����邩���f
    
public:
    virtual const bool isAI() const { return false; }
};

#endif /* Player_hpp */
