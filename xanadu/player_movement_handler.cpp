//

#include "player.hpp"

#include "map.hpp"
#include "session.hpp"
#include "packetcreator.hpp"

void Player::handle_player_movement()
{
	skip_bytes(1);
	skip_bytes(4);

	short start_position_x = read<short>();
	short start_position_y = read<short>();

	signed char actions_amount = read<signed char>();

	for (signed char i = 0; i < actions_amount; ++i)
	{
		signed char action = read<signed char>();

		switch (action)
		{
		case 0:
		case 5:
		case 17:
			position_x_ = read<short>();
			position_y_ = read<short>();
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			stance_ = read<signed char>();
			foothold_ = read<short>();
			break;
		case 15:
			position_x_ = read<short>();
			position_y_ = read<short>();
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			stance_ = read<signed char>();
			foothold_ = read<short>();
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
			position_x_ = read<short>();
			position_y_ = read<short>();
			stance_ = read<signed char>();
			foothold_ = read<short>();
			break;
		case 3:
		case 4:
		case 7:
		case 8:
		case 9:
		case 11:
			position_x_ = read<short>();
			position_y_ = read<short>();
			skip_bytes(2);
			foothold_ = read<short>();
			stance_ = read<signed char>();
			break;
		case 10:
			skip_bytes(1);
			break;
		case 14:
			skip_bytes(2);
			skip_bytes(2);
			skip_bytes(2);
			stance_ = read<signed char>();
			foothold_ = read<short>();
			break;
		default:
			break;
		}
	}

	// only send the packet if there are atleast 2 players in the map

	auto map_players = map_->get_players();
	if (map_players->size() >= 2)
	{
		// send a packet to all players in the map except the player to show the movement of the player
		// exclude some bytes from being sent as that data is not used for the packet

		constexpr int excluded_bytes = (9 + 2);
		int size = (recv_length_ - excluded_bytes);

		if (size < 1)
		{
			return;
		}
		{
			PacketCreator packet;
			packet.ShowPlayerMovement(id_, session_->get_receive_buffer() + excluded_bytes, size);
			map_->send_packet(&packet, this);
		}
	}
}
