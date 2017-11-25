//
//  Dealer.cpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/15.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#include "Dealer.hpp"
#include "common.h"
#ifdef MODE_XCODE
#include <unistd.h>
#else
#include <Windows.h>
#endif

Dealer::Dealer(){}

Dealer::~Dealer(){}

Person::Answer Dealer::judge(const Person& rival)
{
    Answer ans = Answer::None;
    
    printf("%s「どうすっかなー？？」\n", _name.c_str());
    // 少し待機(考えてるっぽく)
#ifdef MODE_XCODE
    sleep(3);
#else
    Sleep(3000);
#endif
    // 所持カードの合計数が特定値未満の場合はヒットし続ける
    ans = (getSumPoint(true) < AI_STAND_PTS) ? Answer::Hit : Answer::Stand;
    
    _lastAnswer = ans;
    return ans;
}
