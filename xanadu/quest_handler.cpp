//

#include "player.hpp"

void Player::handle_quest_action()
{
	enum k_quest_actions
	{
		kStart = 1,
		kComplete,
		kForfeit,
		kStartScripted,
		kEndScripted
	};

	signed char action = read<signed char>();
	int quest_id = read<unsigned short>();

	switch (action)
	{
	case kStart:
	{
		give_quest(quest_id);
		break;
	}
	case kComplete:
	{
		int npc_id = read<int>();
		complete_quest(quest_id, npc_id);
		break;
	}
	case kForfeit:
	{
		remove_quest(quest_id);
		break;
	}
	case kStartScripted:
	{
		break;
	}
	case kEndScripted:
	{
		break;
	}
	}
}
