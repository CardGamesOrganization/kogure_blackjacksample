//
//  CardUtil.cpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#include "CardUtil.hpp"
#include "common.h"

// カードのマーク
const char CardUtil::_marks[4] =
{
    'D', 'C', 'H', 'S'
};

const int CardUtil::_markSize = sizeof(_marks) / sizeof(_marks[0]);

// 数字以外のワード
std::map<int, char> CardUtil::_words =
{
    {0, 'A'}, {10, 'J'}, {11, 'Q'}, {12, 'K'}
};

// ワードのポイント
std::map<int, int> CardUtil::_points =
{
    {0, -1}, {10, 10}, {11, 10}, {12, 10}
};

bool CardUtil::getMarkNumber(int card, char* pMark, int* pNum)
{
    // 範囲外
    if((card < 0) || (card >= CARD_MAX)){
        return false;
    }
    
    if(pMark != NULL){
        *pMark = _marks[card % _markSize];
    }
    if(pNum != NULL){
        *pNum = card / _markSize;
    }
    
    return true;
}

char CardUtil::getNumberToWord(int num)
{
    // 想定外
    if(_words.count(num) == 0){
        return 0;
    }
    
    return _words[num];
}

int CardUtil::getNumberToPoint(int num)
{
    // 通常ポイント
    if(_points.count(num) == 0){
        return num + 1;
    }
    
    // ワードポイント
    return _points[num];
}

std::string CardUtil::getCardFormat(int card)
{
    std::string format;
    format.clear();
    
    char mark;
    int num;
    if(getMarkNumber(card, &mark, &num)){
        char buf[128] = {0, };
        char word = getNumberToWord(num);
        if(word != 0){
            SPRINTF(buf, "%c%c", mark, word);
        }
        else{
            SPRINTF(buf, "%c%d", mark, num + 1);
        }
        format.append(buf);
    }
    
    return format;
}
