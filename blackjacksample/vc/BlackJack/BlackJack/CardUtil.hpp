//
//  CardUtil.hpp
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
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
    static bool getMarkNumber(int card, char* pMark, int* pNum);      // �J�[�h�ԍ�����}�[�N�Ɣԍ����擾����
    static char getNumberToWord(int num);     // �ԍ����烏�[�h���擾���� ���[�h�������ꍇ��0��Ԃ�
    static int getNumberToPoint(int num);     // �ԍ�������ۂ̓_�����擾����(A = -1, J Q K = 10, ����ȊO�͂��̐����̂܂ܕԂ�)
    static std::string getCardFormat(int card); // �J�[�h�ԍ�����A���߂�ꂽ�t�H�[�}�b�g�ŕ�����Ƃ��ĕԂ�
    
private:
    static const char _marks[4];
    static const int _markSize;
    static std::map<int, char> _words;
    static std::map<int, int> _points;
};

#endif /* CardUtil_hpp */
