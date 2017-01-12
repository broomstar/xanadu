//

#include "player.hpp"

#include "packetcreator.hpp"
#include "mob.hpp"
#include "map.hpp"
#include "session.hpp"

void Player::handle_mob_movement()
{
	int monster_object_id = read<int>();

	Mob *mob = map_->get_mob(monster_object_id);
	if (!mob)
	{
		return;
	}

	short move_id = read<short>();
	signed char nibbles  = read<signed char>();
	signed char action = read<signed char>();
	signed char skill_id = read<signed char>();
	signed char skill_level = read<signed char>();
	short option = read<short>();

	skip_bytes(13);

	short start_position_x = read<short>();
	short start_position_y = read<short>();

	mob->update_position(start_position_x, start_position_y);

	short mob_position_x = 0;
	short mob_position_y = 0;
	short mob_foothold = 0;
	short mob_stance = 0;

	signed char actions_amount = read<signed char>();

	for (signed char i = 0; i < actions_amount; ++i)
	{
		signed char action = read<signed char>();

		switch (action)
		{
		case 0:
		case 5:
		case 17:
			mob_position_x = read<short>();
			mob_position_y = read<short>();
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			mob_stance = read<signed char>();
			mob_foothold = read<short>();
			break;
		case 15:
			mob_position_x = read<short>();
			mob_position_y = read<short>();
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			mob_stance = read<signed char>();
			mob_foothold = read<short>();
			break;
		case 1:
		case 2:
		case 6:
		case 12:
		case 13:
		case 16:
		case 18:
		case 19:
		case 20:
		case 22:
			mob_position_x = read<short>();
			mob_position_y = read<short>();
			mob_stance = read<signed char>();
			mob_foothold = read<short>();
			break;
		case 3:
		case 4:
		case 7:
		case 8:
		case 9:
		case 11:
			mob_position_x = read<short>();
			mob_position_y = read<short>();
			skip_bytes(2);
			mob_foothold = read<short>();
			mob_stance = read<signed char>();
			break;
		case 10:
			skip_bytes(1);
			break;
		case 14:
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			mob_stance = read<signed char>();
			mob_foothold = read<short>();
			break;
		default:
			break;
		}
	}

	if (mob_position_x != 0 || mob_position_y != 0 || mob_foothold != 0)
	{
		mob->update_position(mob_position_x, mob_position_y);
	}
	
	bool next_movement_could_be_skill = (nibbles & 0x0F) != 0;

	// send a packet to the player which is used to make the client continue mob movement for the player
	{
		PacketCreator packet;
		packet.MoveMobResponse(mob, move_id, next_movement_could_be_skill, skill_id, skill_level);
		send_packet(&packet);
	}
	// only send the packet if there are atleast 2 players in the map
	auto map_players = map_->get_players();
	if (map_players->size() >= 2)
	{
		// send a packet to all players in the map except the player to show the movement of the mob
		// exclude some bytes from being sent as that data is not used for the packet
		const int excluded_bytes = (29 + 2);

		PacketCreator packet;
		packet.MoveMob(monster_object_id, next_movement_could_be_skill, action, skill_id, skill_level, option, start_position_x, start_position_y, session_->get_receive_buffer() + excluded_bytes, recv_length_ - excluded_bytes);
		map_->send_packet(&packet, this);
	}
}
