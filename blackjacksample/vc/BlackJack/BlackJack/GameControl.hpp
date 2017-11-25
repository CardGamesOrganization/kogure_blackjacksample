//
//  GameControl.hpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
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
        Player,              // �v���C���[
        Dealer,              // �f�B�[���[
        Max
    };
    
    enum class Result{
        None = -1,
        Judge,              // ����
        BustPlayer,         // �v���C���[���o�X�g
        BustDealer,         // �f�B�[���[���o�X�g
        Max
    };
    
public:
    GameControl();
    ~GameControl();
    
    bool update();      // �X�V false��Ԃ��ƏI��
    
private:
    bool init();        // ������
    bool ready();       // ����
    bool game();        // �Q�[����
    bool result();      // ����
    bool release();     // �j��
    
    void shuffleCard();         // �J�[�h���V���b�t������
    int drawCard(Person* const pPerson, int drawCount);      // �J�[�h������
    int drawCard(Person* const pPerson);
    int drawCard();             // �R�D����J�[�h��1������
    int getNextTurn() const;    // ���̃^�[���ԍ����擾�A���̃^�[�����������-1
    int getWinnerNo() const;    // ���҂̔ԍ����擾���� ���������̏ꍇ��-1
    
private:
    std::function<bool()> _stepFunc;
    std::vector<Person*> _persons;      // �Q����
    std::vector<int> _cards;            // �R�D
    int _turn;
    Result _result;
};

#endif /* GameControl_hpp */
