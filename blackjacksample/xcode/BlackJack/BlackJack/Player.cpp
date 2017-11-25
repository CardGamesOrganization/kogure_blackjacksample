//
//  Player.cpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#include "Player.hpp"
#include "common.h"
#include "Util.hpp"

Player::Player(){}

Player::~Player(){}

Person::Answer Player::judge(const Person& rival)
{
    Answer ans = Answer::None;
    
    show(true);
#ifndef DEBUG_DEALER_CARD_OPEN
    rival.show(false);
#else
    rival.show(true);
#endif
    printf("どうする？(1: ヒット、2: スタンド)\n");
    int select = Util::inputNum(1, 2);
    ans = (select == 1) ? Answer::Hit : Answer::Stand;
    
    _lastAnswer = ans;
    return ans;
}
