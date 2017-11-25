//
//  Util.hpp
//  BlackJack
//
//  Created by ¬åŒ’‘¾ on 2017/08/11.
//  Copyright  2017”N ¬åŒ’‘¾. All rights reserved.
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
    
    // min ` max‚©‚çƒ‰ƒ“ƒ_ƒ€‚Å”’l‚ğ•Ô‚·
    static int getRandom(int min, int max);
    static int getRandom(int max);
    
    // “ü—ÍŠÖŒW
    static bool inputYN();
    static int inputNum(int min, int max);
    static int inputNum(int num);
};

#endif /* Util_hpp */
