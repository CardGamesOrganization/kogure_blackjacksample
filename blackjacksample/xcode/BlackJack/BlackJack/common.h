//
//  common.h
//  BlackJack
//
//  Created by 小槫健太 on 2017/08/11.
//  Copyright © 2017年 小槫健太. All rights reserved.
//

#ifndef common_h
#define common_h

// カード最大枚数
#define CARD_MAX        (52)

// ディーラーがスタンドする合計値
#define AI_STAND_PTS    (17)

// デバッグ
// ディーラーの手札公開
//#define DEBUG_DEALER_CARD_OPEN

#ifdef MODE_XCODE
#define SPRINTF sprintf
#else
#define SPRINTF sprintf_s
#endif

#endif /* common_h */
