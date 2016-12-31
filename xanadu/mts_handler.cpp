//

#include "player.hpp"

#include "map.hpp"
#include "packetcreator.hpp"

void Player::handle_enter_mts()
{
	in_mts_ = true;
	map_->remove_player(this);

	{
		PacketCreator packet;
		packet.EnterMTS(this);
		send_packet(&packet);
	}

	// warp the player to the free market
	//set_map(910000000);
}

void Player::handle_leave_mts()
{
	in_mts_ = false;

	{
		// send a packet
		PacketCreator packet;
		packet.change_map(this, true);
		send_packet(&packet);
	}

	map_->add_player(this);
}
