//
//  common.h
//  BlackJack
//
//  Created by ���匒�� on 2017/08/11.
//  Copyright  2017�N ���匒��. All rights reserved.
//

#ifndef common_h
#define common_h

// �J�[�h�ő喇��
#define CARD_MAX        (52)

// �f�B�[���[���X�^���h���鍇�v�l
#define AI_STAND_PTS    (17)

// �f�o�b�O
// �f�B�[���[�̎�D���J
//#define DEBUG_DEALER_CARD_OPEN

#ifdef MODE_XCODE
#define SPRINTF sprintf
#else
#define SPRINTF sprintf_s
#endif

#endif /* common_h */
