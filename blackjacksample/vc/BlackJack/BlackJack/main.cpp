//
//  main.cpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
//

#include <stdio.h>
#include "GameControl.hpp"

int main(int argc, const char * argv[])
{
    printf("[Black Jack]\n");
    
    GameControl gc;
    while(gc.update());
    
    printf("�Q�[���I��\n");
    return 0;
}
