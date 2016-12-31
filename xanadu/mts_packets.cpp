//

#include "packetcreator.hpp"

#include "player.hpp"
#include "send_packet_opcodes.hpp"

/*
MTS enter packet probably like this:

got it from v0.95 GMS, but verified that it's very likely the same for v0.83 GMS

opcode
writeCharacterData(player);
write<std::string>(player->get_user_name());
write<int>(0); // m_nRegisterFeeMeso
write<int>(0); // m_nCommissionRate
write<int>(0); // m_nCommissionBase
write<int>(0); // m_nAuctionDurationMin
write<int>(0); // m_nAuctionDurationMax
write<long long>(0); // time

v2->m_nRegisterFeeMeso = CInPacket::Decode4(v3);
v2->m_nCommissionRate = CInPacket::Decode4(v3);
v2->m_nCommissionBase = CInPacket::Decode4(v3);
v2->m_nAuctionDurationMin = CInPacket::Decode4(v3);
v2->m_nAuctionDurationMax = CInPacket::Decode4(v3);
v757BDB98(&st);
SystemTimeToFileTime(&st, (_FILETIME *)((char *)&ftSecond + 4));
CInPacket::DecodeBuffer(v3, &ftServer, 8u);
v12.dwHighDateTime = ftServer;
v12.dwLowDateTime = (unsigned int)&ftFirst;
v13 = CITC::FileTimeAddition(v2, v12, ftSecond, bSubtract);
v2->m_ftRel.dwLowDateTime = *(_DWORD *)v13.dwLowDateTime;
v2->m_ftRel.dwHighDateTime = *(_DWORD *)(v13.dwLowDateTime + 4);
*/

void PacketCreator::EnterMTS(Player *player)
{
	write<short>(send_headers::kSET_MTS);
	writeCharacterData(player);
	write<std::string>(player->get_user_name());
	write<int>(0); // m_nRegisterFeeMeso
	write<int>(0); // m_nCommissionRate
	write<int>(0); // m_nCommissionBase
	write<int>(0); // m_nAuctionDurationMin
	write<int>(0); // m_nAuctionDurationMax
	write<long long>(0); // time
}
