//
//  Util.cpp
//  BlackJack
//
//  Created by ¬åŒ’‘¾ on 2017/08/11.
//  Copyright  2017”N ¬åŒ’‘¾. All rights reserved.
//

#include "Util.hpp"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>

static std::mt19937 _mt;

void Util::seedRandom()
{
    std::random_device rnd;
    _mt.seed(rnd());
}

int Util::getRandom(int min, int max)
{
    return min + _mt() % (max - min + 1);
}

int Util::getRandom(int max)
{
    return getRandom(0, max);
}

bool Util::inputYN()
{
    std::string s;
    do{
        s.clear();
        printf("->");
        std::cin >> s;
    }while((s != "y") && (s != "n"));
    return (s == "y") ? true : false;
}

int Util::inputNum(int min, int max)
{
    int ret = -1;
    std::string s;
    do{
        s.clear();
        printf("->");
        std::cin >> s;
        if(std::all_of(s.cbegin(), s.cend(), isdigit)){
            int num = std::atoi(s.c_str());
            if((num >= min) && (num <= max)){
                ret = num;
                break;
            }
        }
    }while(true);
    
    return ret;
}

int Util::inputNum(int num)
{
    return inputNum(num, num);
}
