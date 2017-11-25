//
//  Person.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/15.
//  Copyright  2017年 小槫健太. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <iostream>
#include <vector>

class Person
{
public:
    // 回答
    enum class Answer{
        None = -1,
        Hit,       // カードを引く
        Stand,     // 止める
        Max
    };
    
public:
    Person();
    virtual ~Person();
    
    void ready();               // 準備
    void show(bool open) const;       // 情報を表示する(open = trueだと全てを表示、falseだと1枚目を伏せた状態にし、ポイントも伏せて表示)
    void dumpCard();
    int getSumPoint(bool open) const;      // 手持ちの合計ポイントを取得する Aは都合の良い数値で換算される
    virtual Answer judge(const Person& rival) = 0;     // どうするか判断
    
public:
    void setName(const std::string& name){ _name = name; }
    const std::string& getName() const { return _name; }
    bool addCard(int card);
    const Answer getLastAnswer() const { return _lastAnswer; }
    const bool isBust() const { return _bustFlag; }
    virtual const bool isAI() const = 0;
    
private:
    void checkBust();       // バストしたかチェック
    
protected:
    std::string _name;          // 名前
    std::vector<int> _cards;    // 保持してるカード
    bool _bustFlag;             // バストフラグ
    Answer _lastAnswer;         // 最後に選択した回答
};

#endif /* Person_hpp */
