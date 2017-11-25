//
//  Person.hpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/15.
//  Copyright  2017�N ���匒��. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <iostream>
#include <vector>

class Person
{
public:
    // ��
    enum class Answer{
        None = -1,
        Hit,       // �J�[�h������
        Stand,     // �~�߂�
        Max
    };
    
public:
    Person();
    virtual ~Person();
    
    void ready();               // ����
    void show(bool open) const;       // ����\������(open = true���ƑS�Ă�\���Afalse����1���ڂ𕚂�����Ԃɂ��A�|�C���g�������ĕ\��)
    void dumpCard();
    int getSumPoint(bool open) const;      // �莝���̍��v�|�C���g���擾���� A�͓s���̗ǂ����l�Ŋ��Z�����
    virtual Answer judge(const Person& rival) = 0;     // �ǂ����邩���f
    
public:
    void setName(const std::string& name){ _name = name; }
    const std::string& getName() const { return _name; }
    bool addCard(int card);
    const Answer getLastAnswer() const { return _lastAnswer; }
    const bool isBust() const { return _bustFlag; }
    virtual const bool isAI() const = 0;
    
private:
    void checkBust();       // �o�X�g�������`�F�b�N
    
protected:
    std::string _name;          // ���O
    std::vector<int> _cards;    // �ێ����Ă�J�[�h
    bool _bustFlag;             // �o�X�g�t���O
    Answer _lastAnswer;         // �Ō�ɑI��������
};

#endif /* Person_hpp */
