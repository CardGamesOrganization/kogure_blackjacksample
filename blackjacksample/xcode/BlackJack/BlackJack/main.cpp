//
//  main.cpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#include <stdio.h>
#include "GameControl.hpp"

int main(int argc, const char * argv[])
{
    printf("[Black Jack]\n");
    
    GameControl gc;
    while(gc.update());
    
    printf("ゲーム終了\n");
    return 0;
}
