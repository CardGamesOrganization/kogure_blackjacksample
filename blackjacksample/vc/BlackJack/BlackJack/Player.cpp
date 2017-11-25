//
//  Player.cpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
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
    printf("�ǂ�����H(1: �q�b�g�A2: �X�^���h)\n");
    int select = Util::inputNum(1, 2);
    ans = (select == 1) ? Answer::Hit : Answer::Stand;
    
    _lastAnswer = ans;
    return ans;
}
