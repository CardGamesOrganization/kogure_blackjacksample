//
//  CardUtil.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright  2017年 小槫健太. All rights reserved.
//

#ifndef CardUtil_hpp
#define CardUtil_hpp

#include <map>
#include <string>

class CardUtil
{
private:
    CardUtil(){}
    ~CardUtil(){}
    
public:
    static bool getMarkNumber(int card, char* pMark, int* pNum);      // カード番号からマークと番号を取得する
    static char getNumberToWord(int num);     // 番号からワードを取得する ワードが無い場合は0を返す
    static int getNumberToPoint(int num);     // 番号から実際の点数を取得する(A = -1, J Q K = 10, それ以外はその数字のまま返す)
    static std::string getCardFormat(int card); // カード番号から、決められたフォーマットで文字列として返す
    
private:
    static const char _marks[4];
    static const int _markSize;
    static std::map<int, char> _words;
    static std::map<int, int> _points;
};

#endif /* CardUtil_hpp */
