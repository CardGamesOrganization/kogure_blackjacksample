//
//  Util.hpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
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
    
    // min �` max���烉���_���Ő��l��Ԃ�
    static int getRandom(int min, int max);
    static int getRandom(int max);
    
    // ���͊֌W
    static bool inputYN();
    static int inputNum(int min, int max);
    static int inputNum(int num);
};

#endif /* Util_hpp */
