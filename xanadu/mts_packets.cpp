//

#include "packetcreator.hpp"

#include "player.hpp"
#include "send_packet_opcodes.hpp"

void PacketCreator::EnterMTS(Player *player)
{
	write<short>(send_headers::kSET_MTS);
	writeCharacterData(player);
	write<std::string>(player->get_user_name());
	write<int>(0); // Register Fee Meso
	write<int>(0); // Commission Rate
	write<int>(0); // Commission Base
	write<int>(0); // Auction Duration Min
	write<int>(0); // Auction Duration Max
	write<long long>(0); // time
}

void PacketCreator::ShowMTSCash()
{
	write<short>(send_headers::kMTS_SHOW_CASH);
	write<int>(0); // nx
	write<int>(0); // maple point
}
