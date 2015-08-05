#pragma once
#include "cocos2d.h"

#if _MSC_VER>=1900
#  define STDC99
#endif

//enum COLOR { RED, GREEN, BLUE, YELLOW };

// BLOCK_COL의 값은 2 이상이어야 함
#define BLOCK_ROW (4)

// BLOCK_ROW의 값은 2 이상이어야 함
#define BLOCK_COL (4)

//#define BLOCK_WIDTH (640 / BLOCK_COL)
//#define BLOCK_HEIGHT (BLOCK_WIDTH)

const cocos2d::Color3B cBlockColor[5] = { cocos2d::Color3B(196, 219, 160),
										cocos2d::Color3B(242, 120, 134),
										cocos2d::Color3B(255, 216, 155),
										cocos2d::Color3B(230, 171, 237),
										cocos2d::Color3B(137, 206, 232)};
