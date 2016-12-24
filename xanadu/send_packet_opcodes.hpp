//

#pragma once

namespace send_headers_login
{
	constexpr short kLoginStatus = 0x00;
	constexpr short kSERVER_STATUS = 0x03;
	constexpr short kPIN_CHECK_OPERATION = 0x06;
	constexpr short kSERVER_LIST = 0x0a;
	constexpr short kCHARACTER_LIST = 0x0b;
	constexpr short kSERVER_IP = 0x0c;
	constexpr short kCHECK_CHARACTER_NAME = 0x0d;
	constexpr short kCREATE_NEW_CHARACTER = 0x0e;
	constexpr short kDELETE_CHARACTER = 0x0f;
	constexpr short kCHANGE_CHANNEL = 0x10;
	constexpr short kCHANNEL_SELECTED = 0x14;
	constexpr short kRELOG_RESPONSE = 0x16;
}

namespace send_headers
{
	// all opcodes not updated yet
	constexpr short kMODIFY_INVENTORY_ITEM = 0x1A;
	constexpr short kUPDATE_STATS = 0x1C;
	constexpr short kGIVE_BUFF = 0x1D;
	constexpr short kCANCEL_BUFF = 0x1E;
	constexpr short kUPDATE_SKILLS = 0x21;
	constexpr short kFAME = 0x23;
	constexpr short kSHOW_STATUS_INFO = 0x24;
	constexpr short kSHOW_QUEST_COMPLETION = 0x2E;
	constexpr short kREQUEST_HIRED_MERCHANT = 0x2F;
	constexpr short kUSE_SKILL_BOOK = 0x30;
	constexpr short kGUILD_BBS_OPERATION = 0x38;
	constexpr short kCHAR_INFO = 0x3A;
	constexpr short kPARTY_OPERATION = 0x3B;
	constexpr short kBUDDY_LIST = 0x3C;
	constexpr short kGUILD_OPERATION = 0x3E;
	constexpr short kSPAWN_PORTAL = 0x40;
	constexpr short kSERVERMESSAGE = 0x41;
	constexpr short kYELLOW_TIP = 0x4A;
	constexpr short kSHOW_AVATAR_MEGA = 0x54;
	constexpr short kWARP_TO_MAP = 0x5C;
	constexpr short kOPEN_CASHSHOP = 0x5E;
	constexpr short kMULTICHAT = 0x64;
	constexpr short kWHISPER = 0x65;
	constexpr short kMAP_EFFECT = 0x68;
	constexpr short kCLOCK = 0x6E;
	constexpr short kBOAT_EFFECT = 0x6F;
	constexpr short kSPAWN_PLAYER = 0x78;
	constexpr short kREMOVE_PLAYER_FROM_MAP = 0x79;
	constexpr short kCHATTEXT = 0x7A;
	constexpr short kCHALKBOARD = 0x7B;
	constexpr short kSHOW_SCROLL_EFFECT = 0x7E;
	constexpr short kPET_SPAWN = 0x7F;
	constexpr short kPET_MOVE = 0x81;
	constexpr short kPET_CHAT = 0x82;
	constexpr short kPET_NAMECHANGE = 0x83;
	constexpr short kPET_COMMAND = 0x85;
	constexpr short kSUMMON_SPAWN = 0x86;
	constexpr short kSUMMON_REMOVE = 0x87;
	constexpr short kSUMMON_MOVE = 0x88;
	constexpr short kSUMMON_ATTACK = 0x89;
	constexpr short kDAMAGE_SUMMON = 0x8A;
	constexpr short kMOVE_PLAYER = 0x8D;
	constexpr short kCLOSE_RANGE_ATTACK = 0x8E;
	constexpr short kRANGED_ATTACK = 0x8F;
	constexpr short kMAGIC_ATTACK = 0x90;
	constexpr short kENERGY_ATTACK = 0x91;
	constexpr short kSKILL_EFFECT = 0x92;
	constexpr short kCANCEL_SKILL_EFFECT = 0x93;
	constexpr short kDAMAGE_PLAYER = 0x94;
	constexpr short kFACIAL_EXPRESSION = 0x95;
	constexpr short kSHOW_ITEM_EFFECT = 0x96;
	constexpr short kSHOW_CHAIR = 0x97;
	constexpr short kUPDATE_CHAR_LOOK = 0x98;
	constexpr short kSHOW_FOREIGN_EFFECT = 0x99;
	constexpr short kGIVE_FOREIGN_BUFF = 0x9A;
	constexpr short kCANCEL_FOREIGN_BUFF = 0x9B;
	constexpr short kUPDATE_PARTYMEMBER_HP = 0x9C;
	constexpr short kCANCEL_CHAIR = 0xA0;
	constexpr short kSHOW_ITEM_GAIN_INCHAT = 0xA1;
	constexpr short kUPDATE_QUEST_INFO = 0xA6;
	constexpr short kCOOLDOWN = 0xAD;
	constexpr short kSPAWN_MONSTER = 0xAF;
	constexpr short kKILL_MONSTER = 0xB0;
	constexpr short kSPAWN_MONSTER_CONTROL = 0xB1;
	constexpr short kMOVE_MONSTER = 0xB2;
	constexpr short kMOVE_MONSTER_RESPONSE = 0xB3;
	constexpr short kDAMAGE_MONSTER = 0xB9;
	constexpr short kSHOW_MONSTER_HP = 0xBD;
	constexpr short kSPAWN_NPC = 0xC2;
	constexpr short kSPAWN_NPC_REQUEST_CONTROLLER = 0xC4;
	constexpr short kSPAWN_HIRED_MERCHANT = 0xCA;
	constexpr short kDESTROY_HIRED_MERCHANT = 0xCB;
	constexpr short kDROP_ITEM_FROM_MAPOBJECT = 0xCD;
	constexpr short kREMOVE_ITEM_FROM_MAP = 0xCE;
	constexpr short kSPAWN_MIST = 0xD2;
	constexpr short kREMOVE_MIST = 0xD3;
	constexpr short kSPAWN_DOOR = 0xD4;
	constexpr short kREMOVE_DOOR = 0xD5;
	constexpr short kREACTOR_HIT = 0xD6;
	constexpr short kREACTOR_SPAWN = 0xD8;
	constexpr short kREACTOR_DESTROY = 0xD9;
	constexpr short kMONSTER_CARNIVAL_START = 0xE2;
	constexpr short kMONSTER_CARNIVAL_OBTAINED_CP = 0xE3;
	constexpr short kMONSTER_CARNIVAL_PARTY_CP = 0xE4;
	constexpr short kMONSTER_CARNIVAL_SUMMON = 0xE5;
	constexpr short kMONSTER_CARNIVAL_MESSAGE = 0xE6;
	constexpr short kMONSTER_CARNIVAL_DIED = 0xE7;
	constexpr short kMONSTER_CARNIVAL_LEAVE = 0xE8;
	constexpr short kMONSTER_CARNIVAL_SHOW_GAME_RESULT = 0xE9;
	constexpr short kNPC_TALK = 0xED;
	constexpr short kOPEN_NPC_SHOP = 0xEE;
	constexpr short kCONFIRM_SHOP_TRANSACTION = 0xEF;
	constexpr short kOPEN_STORAGE = 0xF0;
	constexpr short kFREDRICK_MESSAGE = 0xF1;
	constexpr short kFREDRICK_OPERATION = 0xF2;
	constexpr short kMESSENGER = 0xF4;
	constexpr short kPLAYER_INTERACTION = 0xF5;
	constexpr short kSHOW_CASH = 0xFF;
	constexpr short kCASHSHOP_OPERATION = 0x100;
	constexpr short kKEYMAP = 0x107;
}
