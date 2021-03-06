//
//  Util.hpp
//  BlackJack
//
//  Created by ¬å¾ on 2017/08/11.
//  Copyright  2017N ¬å¾. All rights reserved.
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
    
    // min ` max©ç_ÅlðÔ·
    static int getRandom(int min, int max);
    static int getRandom(int max);
    
    // üÍÖW
    static bool inputYN();
    static int inputNum(int min, int max);
    static int inputNum(int num);
};

#endif /* Util_hpp */
