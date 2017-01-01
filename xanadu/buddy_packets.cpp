//

#include "packetcreator.hpp"

#include "buddy.hpp"
#include "player.hpp"
#include "send_packet_opcodes.hpp"
#include "buddylist_constants.hpp"

void PacketCreator::BuddyList(Player *player)
{
	auto buddylist = player->get_buddylist();
	signed char buddylist_size = static_cast<signed char>(buddylist->size());
	
	write<short>(send_headers::kBUDDY_LIST);
	write<signed char>(BuddylistSendPacketActions::kUpdate);
	write<signed char>(buddylist_size);

	/*
	00000000 GW_Friend       struc ; (sizeof=0x27, copyof_1725)
00000000 dwFriendID      dd ?
00000004 sFriendName     db 13 dup(?)
00000011 nFlag           db ?
00000012 nChannelID      dd ?
00000016 sFriendGroup    db 17 dup(?)
00000027 GW_Friend       ends
*/

	for (auto &it : *buddylist)
	{
		auto buddy = it.second;
		write<int>(buddy->get_player_id());
		write_string(buddy->get_player_name(), 13);
		write<signed char>(buddy->get_opposite_status());
		write<int>(buddy->get_channel_id());
		write_string("test group", 17); // group name
	}

	/*
	CInPacket::DecodeBuffer(v2, v3->m_aInShop.a, 4 * v4);
	it's an array of 4 byte int's, no clue what m_aInShop is supposed to mean/do
	*/
	for (signed char i = 0; i < buddylist_size; ++i)
	{
		write<int>(0);
	}
}

void PacketCreator::BuddyListInvite(Player *player)
{
	write<short>(send_headers::kBUDDY_LIST);
	write<signed char>(BuddylistSendPacketActions::kInvite);
	write<int>(player->get_id());
	write<std::string>(player->get_name());

	/*
	00000000 GW_Friend       struc ; (sizeof=0x27, copyof_1725)
	00000000 dwFriendID      dd ?
	00000004 sFriendName     db 13 dup(?)
	00000011 nFlag           db ?
	00000012 nChannelID      dd ?
	00000016 sFriendGroup    db 17 dup(?)
	00000027 GW_Friend       ends
	*/

	write<int>(player->get_id());
	write_string(player->get_name(), 13);
	write<signed char>(Buddylist::kOppositeStatusRequested);
	write<int>(1); // channel_id?
	write_string("Group Unknown", 17); // group name

	write<signed char>(0);
}

void PacketCreator::UpdateBuddyChannel(int player_id, int channel_id)
{
	write<short>(send_headers::kBUDDY_LIST);
	write<signed char>(BuddylistSendPacketActions::kUpdateChannel);
	write<int>(player_id);
	write<signed char>(0);
	write<int>(channel_id);
}

void PacketCreator::UpdateBuddyListCapacity(Player *player)
{
	write<short>(send_headers::kBUDDY_LIST);
	write<signed char>(BuddylistSendPacketActions::kUpdateCapacity);
	write<signed char>(player->get_buddy_list_capacity());
}
