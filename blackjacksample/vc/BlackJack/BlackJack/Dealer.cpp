//
//  Dealer.cpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/15.
//  Copyright  2017�N ���匒��. All rights reserved.
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
    
    printf("%s�u�ǂ��������ȁ[�H�H�v\n", _name.c_str());
    // �����ҋ@(�l���Ă���ۂ�)
#ifdef MODE_XCODE
    sleep(3);
#else
    Sleep(3000);
#endif
    // �����J�[�h�̍��v��������l�����̏ꍇ�̓q�b�g��������
    ans = (getSumPoint(true) < AI_STAND_PTS) ? Answer::Hit : Answer::Stand;
    
    _lastAnswer = ans;
    return ans;
}
