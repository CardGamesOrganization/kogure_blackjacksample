//
//  GameControl.cpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
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

// ��ʑJ�ڃ}�N��
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
                printf("���Ȃ��̖��O�����:");
                std::cin >> name;
                printf("�u%s�v�ł�낵���ł����H(y/n)\n", name.c_str());
            }while(!Util::inputYN());
            pPlayer->setName(name);
            _persons.push_back(pPlayer);
        }
        else{
            Dealer* pDealer = new Dealer();
            pDealer->setName(std::string("�f�B�[���["));        // �����l���Q���̏ꍇ��"�f�B�[���[" + �ԍ���ݒ肷�邪�A����͌Œ�
            _persons.push_back(pDealer);
        }
    }
    
    CHANGE_STEP(GameControl::ready);
    return true;
}

bool GameControl::ready()
{
    printf("�Q�[���X�^�[�g!\n");
    shuffleCard();
    
    // �܂��͑S��2�����J�[�h������
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
        printf("\n>>>%s�̃^�[��<<<\n", pPerson->getName().c_str());
        
        int nextTurn = (_turn + 1) % (int)_persons.size();
        const Person::Answer ans = pPerson->judge(*_persons[nextTurn]);
        switch (ans) {
            case Person::Answer::Hit:
            {
                printf("%s�̓q�b�g���܂���\n", pPerson->getName().c_str());
                const int card = drawCard(pPerson);
                std::string format = CardUtil::getCardFormat(card);
                if(!format.empty()){
                    printf("�J�[�h��[%s]�ł���\n", format.c_str());
                }
            }
                break;
            case Person::Answer::Stand:
                printf("%s�̓X�^���h���܂���\n", pPerson->getName().c_str());
                break;
                
            default:
                break;
        }
#ifdef MODE_XCODE
        sleep(3);           // �ҋ@
#else
        Sleep(3000);        // �ҋ@
#endif
        
        int turn = getNextTurn();
        
        const bool bust = pPerson->isBust();
        // �S�����X�^���h�������o�X�g�����ꍇ�A���ʂ�
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
    printf("\n>>>>>>>>>>���ʔ��\<<<<<<<<<<\n");
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
                SPRINTF(buf, "��������");
            }
            else{
                SPRINTF(buf, "%s��", _persons[(int)PersonNo::Player]->getName().c_str());
                switch ((PersonNo)winner) {
                    case PersonNo::Player:
                        SPRINTF(buf, "%s�����I", buf);
                        break;
                    case PersonNo::Dealer:
                        SPRINTF(buf, "%s����", buf);
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
            SPRINTF(buf, "�o�X�g�����̂�%s�̕���", _persons[(int)PersonNo::Player]->getName().c_str());
            printf("------------------------------------------------\n");
            printf("%s\n", buf);
            printf("------------------------------------------------\n");
        }
            break;
        case Result::BustDealer:
        {
            char buf[256] = {0, };
            SPRINTF(buf, "%s���o�X�g�����̂�%s�̏����I",
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
    
    printf("������x�v���C���܂����H(y/n)\n");
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
    // �����J�[�h������ �{���͂��肦�Ȃ����ǔO�̂���
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
