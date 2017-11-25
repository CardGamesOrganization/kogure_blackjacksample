//
//  Util.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

class Util
{
private:
    Util(){}
    ~Util(){}
    
public:
    static void seedRandom();
    
    // min 〜 maxからランダムで数値を返す
    static int getRandom(int min, int max);
    static int getRandom(int max);
    
    // 入力関係
    static bool inputYN();
    static int inputNum(int min, int max);
    static int inputNum(int num);
};

#endif /* Util_hpp */
