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

	/*
	SystemTimeToFileTime(&st, (_FILETIME *)((char *)&ftSecond + 4));
CInPacket::DecodeBuffer(v3, &ftServer, 8u);
v12.dwHighDateTime = ftServer;
v12.dwLowDateTime = (unsigned int)&ftFirst;
v13 = CITC::FileTimeAddition(v2, v12, ftSecond, bSubtract);
v2->m_ftRel.dwLowDateTime = *(_DWORD *)v13.dwLowDateTime;
v2->m_ftRel.dwHighDateTime = *(_DWORD *)(v13.dwLowDateTime + 4);
*/
	write<long long>(0); // time
}

void PacketCreator::ShowMTSCash()
{
	write<short>(send_headers::kMTS_SHOW_CASH);
	write<int>(0); // nx
	write<int>(0); // maple point
}
