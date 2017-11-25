//
//  main.cpp
//  BlackJack
//
//  Created by ¬åŒ’‘¾ on 2017/08/11.
//  Copyright  2017”N ¬åŒ’‘¾. All rights reserved.
//

#include <stdio.h>
#include "GameControl.hpp"

int main(int argc, const char * argv[])
{
    printf("[Black Jack]\n");
    
    GameControl gc;
    while(gc.update());
    
    printf("ƒQ[ƒ€I—¹\n");
    return 0;
}
