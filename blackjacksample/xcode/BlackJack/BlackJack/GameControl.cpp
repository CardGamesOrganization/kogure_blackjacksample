//
//  GameControl.cpp
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#include "GameControl.hpp"
#include "common.h"
#include "Util.hpp"
#include "CardUtil.hpp"
#include "Person.hpp"
#include "Player.hpp"
#include "Dealer.hpp"
#include <map>
#ifdef MODE_XCODE
#include <unistd.h>
#else
#include <Windows.h>
#endif

// 画面遷移マクロ
#define CHANGE_STEP(func){\
    _stepFunc = std::bind(&func, this);\
}

GameControl::GameControl()
{
    Util::seedRandom();
    _cards.clear();
    CHANGE_STEP(GameControl::init);
}

GameControl::~GameControl(){}

bool GameControl::update()
{
    return _stepFunc();
}

bool GameControl::init()
{
    _persons.clear();
    
    int i;
    for(i = 0; i < (int)PersonNo::Max; i++){
        if((PersonNo)i == PersonNo::Player){
            Player* pPlayer = new Player();
            std::string name;
            do{
                name.clear();
                printf("あなたの名前を入力:");
                std::cin >> name;
                printf("「%s」でよろしいですか？(y/n)\n", name.c_str());
            }while(!Util::inputYN());
            pPlayer->setName(name);
            _persons.push_back(pPlayer);
        }
        else{
            Dealer* pDealer = new Dealer();
            pDealer->setName(std::string("ディーラー"));        // 複数人数参加の場合は"ディーラー" + 番号を設定するが、今回は固定
            _persons.push_back(pDealer);
        }
    }
    
    CHANGE_STEP(GameControl::ready);
    return true;
}

bool GameControl::ready()
{
    printf("ゲームスタート!\n");
    shuffleCard();
    
    // まずは全員2枚ずつカードを引く
    {
        std::vector<Person*>::iterator itr;
        for(itr = _persons.begin(); itr != _persons.end(); itr++){
            (*itr)->ready();
            drawCard(*itr, 2);
        }
    }
    
    _turn = 0;
    _result = Result::None;
    
    CHANGE_STEP(GameControl::game);
    return true;
}

bool GameControl::game()
{
    bool continueFlag = true;
    do{
        Person* const pPerson = _persons[_turn];
        printf("\n>>>%sのターン<<<\n", pPerson->getName().c_str());
        
        int nextTurn = (_turn + 1) % (int)_persons.size();
        const Person::Answer ans = pPerson->judge(*_persons[nextTurn]);
        switch (ans) {
            case Person::Answer::Hit:
            {
                printf("%sはヒットしました\n", pPerson->getName().c_str());
                const int card = drawCard(pPerson);
                std::string format = CardUtil::getCardFormat(card);
                if(!format.empty()){
                    printf("カードは[%s]でした\n", format.c_str());
                }
            }
                break;
            case Person::Answer::Stand:
                printf("%sはスタンドしました\n", pPerson->getName().c_str());
                break;
                
            default:
                break;
        }
#ifdef MODE_XCODE
        sleep(3);           // 待機
#else
        Sleep(3000);        // 待機
#endif
        
        int turn = getNextTurn();
        
        const bool bust = pPerson->isBust();
        // 全員がスタンドしたかバストした場合、結果へ
        if((turn < 0) || bust){
            if(bust){
                _result = (!pPerson->isAI()) ? Result::BustPlayer : Result::BustDealer;
            }
            else{
                _result = Result::Judge;
            }
            
            CHANGE_STEP(GameControl::result);
            continueFlag = false;
        }
        
        _turn = turn;
    }while(continueFlag);
    
    return true;
}

bool GameControl::result()
{
    printf("\n>>>>>>>>>>結果発表<<<<<<<<<<\n");
    {
        std::vector<Person*>::iterator itr;
        for(itr = _persons.begin(); itr != _persons.end(); itr++){
            (*itr)->show(true);
        }
    }
    
    switch (_result) {
        case Result::Judge:
        {
            char buf[256] = {0, };
            const int winner = getWinnerNo();
            if(winner < 0){
                SPRINTF(buf, "引き分け");
            }
            else{
                SPRINTF(buf, "%sの", _persons[(int)PersonNo::Player]->getName().c_str());
                switch ((PersonNo)winner) {
                    case PersonNo::Player:
                        SPRINTF(buf, "%s勝ち！", buf);
                        break;
                    case PersonNo::Dealer:
                        SPRINTF(buf, "%s負け", buf);
                        break;
                        
                    default:
                        break;
                }
            }
            
            printf("%s\n", buf);
            
        }
            break;
        case Result::BustPlayer:
        {
            char buf[256] = {0, };
            SPRINTF(buf, "バストしたので%sの負け", _persons[(int)PersonNo::Player]->getName().c_str());
            printf("------------------------------------------------\n");
            printf("%s\n", buf);
            printf("------------------------------------------------\n");
        }
            break;
        case Result::BustDealer:
        {
            char buf[256] = {0, };
            SPRINTF(buf, "%sがバストしたので%sの勝ち！",
                    _persons[(int)PersonNo::Dealer]->getName().c_str(),
                    _persons[(int)PersonNo::Player]->getName().c_str());
            printf("------------------------------------------------\n");
            printf("%s\n", buf);
            printf("------------------------------------------------\n");
        }
            break;
            
        default:
            break;
    }
    
    printf("もう一度プレイしますか？(y/n)\n");
    if(Util::inputYN()){
        CHANGE_STEP(GameControl::ready);
    }
    else{
        CHANGE_STEP(GameControl::release);
    }
    
    return true;
}

bool GameControl::release()
{
    std::vector<Person*>::iterator itr;
    for(itr = _persons.begin(); itr != _persons.end(); itr++){
        delete (*itr);
    }
    _persons.clear();
    return false;
}

void GameControl::shuffleCard()
{
    _cards.clear();
    std::map<int, int> map;
    map.clear();
    int i;
    for(i = 0; i < CARD_MAX; i++){
        int r = 0;
        do{
            r = Util::getRandom(CARD_MAX - 1);
        }while(map.count(r) > 0);
        map[r] = 1;
        _cards.push_back(r);
    }
}

int GameControl::drawCard(Person* const pPerson, int drawCount)
{
    if(pPerson == NULL){
        return -1;
    }
    
    int card = -1;
    int i;
    for(i = 0; i < drawCount; i++){
        card = drawCard();
        pPerson->addCard(card);
    }
    
    return card;
}

int GameControl::drawCard(Person* const pPerson)
{
    return drawCard(pPerson, 1);
}

int GameControl::drawCard()
{
    // 引くカードが無い 本来はありえないけど念のため
    if(_cards.size() == 0){
        return -1;
    }
    
    int card = _cards.back();
    _cards.pop_back();
    return card;
}

int GameControl::getNextTurn() const
{
    int nextTurn = -1;
    int turn = _turn;
    int i;
    for(i = 0; i < (int)_persons.size(); i++){
        turn = (turn + 1) % (int)_persons.size();
        if(_persons[turn]->getLastAnswer() != Person::Answer::Stand){
            nextTurn = turn;
            break;
        }
    }
    
    return nextTurn;
}

int GameControl::getWinnerNo() const
{
    int no = -1;
    bool tie = true;
    int prevPts = -1;
    int topPts = 0;
    int i;
    for(i = 0; i < (int)_persons.size(); i++){
        const int pts = _persons[i]->getSumPoint(true);
        if(pts > topPts){
            topPts = pts;
            no = i;
        }
        
        if((prevPts >= 0) && (pts != prevPts)){
            tie = false;
        }
        prevPts = pts;
    }
    
    return (!tie) ? no : -1;
}
