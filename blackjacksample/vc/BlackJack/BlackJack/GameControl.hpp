//
//  GameControl.hpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright  2017年 小槫健太. All rights reserved.
//

#ifndef GameControl_hpp
#define GameControl_hpp

#include <iostream>
#include <vector>
#include <functional>

class Person;

class GameControl
{
private:
    enum class PersonNo{
        None = -1,
        Player,              // プレイヤー
        Dealer,              // ディーラー
        Max
    };
    
    enum class Result{
        None = -1,
        Judge,              // 判定
        BustPlayer,         // プレイヤーがバスト
        BustDealer,         // ディーラーがバスト
        Max
    };
    
public:
    GameControl();
    ~GameControl();
    
    bool update();      // 更新 falseを返すと終了
    
private:
    bool init();        // 初期化
    bool ready();       // 準備
    bool game();        // ゲーム中
    bool result();      // 結果
    bool release();     // 破棄
    
    void shuffleCard();         // カードをシャッフルする
    int drawCard(Person* const pPerson, int drawCount);      // カードを引く
    int drawCard(Person* const pPerson);
    int drawCard();             // 山札からカードを1枚引く
    int getNextTurn() const;    // 次のターン番号を取得、次のターンが無ければ-1
    int getWinnerNo() const;    // 勝者の番号を取得する 引き分けの場合は-1
    
private:
    std::function<bool()> _stepFunc;
    std::vector<Person*> _persons;      // 参加者
    std::vector<int> _cards;            // 山札
    int _turn;
    Result _result;
};

#endif /* GameControl_hpp */
