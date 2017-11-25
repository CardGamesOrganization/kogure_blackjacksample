//
//  Person.cpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/15.
//  Copyright  2017�N ���匒��. All rights reserved.
//

#include "Person.hpp"
#include "common.h"
#include "CardUtil.hpp"

Person::Person() :
_lastAnswer(Answer::None),
_bustFlag(false)
{
    _name.clear();
    _cards.clear();
}

Person::~Person(){}

void Person::ready()
{
    _lastAnswer = Answer::None;
    _bustFlag = false;
    _cards.clear();
}

void Person::show(bool open) const
{
    printf("------------------------------------------------\n");
    char buf[256] = {0, };
    SPRINTF(buf, "%s ", _name.c_str());
    int i;
    for(i = 0; i < (int)_cards.size(); i++){
        if(i > 0){
            SPRINTF(buf, "%s | ", buf);        // �J�[�h�̋�؂�
        }
        
        // �ŏ��̈ꖇ�ڂ͕�����
        if((i == 0) && (!open)){
            SPRINTF(buf, "%s[�H]", buf);
        }
        else{
            std::string format = CardUtil::getCardFormat(_cards[i]);
            if(!format.empty()){
                SPRINTF(buf, "%s[%s]", buf, format.c_str());
            }
        }
    }
    
    // �J�[�h�̍��v��\��
    {
        const int pts = getSumPoint(open);
        SPRINTF(buf, "%s = %dPts", buf, pts);
        if(!open){
            SPRINTF(buf, "%s + �H", buf);
        }
    }
    
    printf("%s\n", buf);
    printf("------------------------------------------------\n");
}

void Person::dumpCard()
{
    std::vector<int>::iterator itr;
    for(itr = _cards.begin(); itr != _cards.end(); itr++){
        printf("%d\n", *itr);
    }
}

int Person::getSumPoint(bool open) const
{
    int sum = 0;
    int aceCount = 0;
    int i;
    for(i = 0; i < (int)_cards.size(); i++){
        // 1���ڂ𕚂��Ă�ꍇ�̓X�L�b�v
        if((i == 0) && (!open)){
            continue;
        }
        
        int num;
        if(CardUtil::getMarkNumber(_cards[i], NULL, &num)){
            // A
            if(num == 0){
                aceCount++;     // ���ƂŌv�Z
            }
            else{
                sum += CardUtil::getNumberToPoint(num);
            }
        }
    }
    
    for(i = 0; i < aceCount; i++){
        // 1 or 11��21�𒴂��Ȃ����`�F�b�N
        int s = sum + 11;
        if(s <= 21){
            sum = s;
        }
        else{
            sum += 1;       // �����Ă������Ȃ��Ă�1���Z
        }
    }
    
    return sum;
}

bool Person::addCard(int card)
{
    if((card < 0) || (card >= CARD_MAX)){
        return false;
    }
    
    _cards.push_back(card);
    checkBust();
    return true;
}

void Person::checkBust()
{
    if(getSumPoint(true) > 21){
        _bustFlag = true;
    }
}
