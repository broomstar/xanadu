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

void PacketCreator::SendMTS()
{
	write<short>(send_headers::kMTS_OPERATION);
}

/*
public static byte[] sendMTS(List<MTSItemInfo> items, int tab, int type, int page, int pages) {
final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
mplew.writeShort(SendOpcode.MTS_OPERATION.getValue());
mplew.write(0x15); //operation
mplew.writeInt(pages * 16); //testing, change to 10 if fails
mplew.writeInt(items.size()); //number of items
mplew.writeInt(tab);
mplew.writeInt(type);
mplew.writeInt(page);
mplew.write(1);
mplew.write(1);
for (int i = 0; i < items.size(); i++) {
MTSItemInfo item = items.get(i);
addItemInfo(mplew, item.getItem(), true);
mplew.writeInt(item.getID()); //id
mplew.writeInt(item.getTaxes()); //this + below = price
mplew.writeInt(item.getPrice()); //price
mplew.writeInt(0);
mplew.writeLong(getTime(item.getEndingDate()));
mplew.writeMapleAsciiString(item.getSeller()); //account name (what was nexon thinking?)
mplew.writeMapleAsciiString(item.getSeller()); //char name
for (int j = 0; j < 28; j++) {
mplew.write(0);
}
}
mplew.write(1);
return mplew.getPacket();
}

v4 = CInPacket::Decode4(iPacket);
v5 = CInPacket::Decode4(iPacket);
nCategory = CInPacket::Decode4(iPacket);
nSubCategory = CInPacket::Decode4(iPacket);
nPagea = CInPacket::Decode4(iPacket);
nSortType = (unsigned __int8)CInPacket::Decode1(v3);
nSortColumn = (unsigned __int8)CInPacket::Decode1(v3);
v2->m_nCurCategorySub = nSubCategory;
v2->m_nCurrentCategoryItemCnt = v4;
v2->m_wndList.m_nCurrentCategoryItemCnt = v4;
v2->m_nCurrentPageItemCnt = v5;
v2->m_nCurPage = nPagea;
v2->m_nCurCategory = nCategory;

....

v6->nITCSN = CInPacket::Decode4(iPacket);
v7 = result->p;
v7->nPrice = CInPacket::Decode4(iPacket);
v8 = result->p;
v8->nContractFee = CInPacket::Decode4(iPacket);
v9 = CInPacket::DecodeStr(iPacket, (ZXString<char> *)&v24);
v10 = &result->p->sContractFeeTxId;
v25 = 2;
ZXString<char>::operator=(v10, v9);
LOBYTE(v25) = 0;
if ( *(_DWORD *)&v24.gap0[0] )
ZXString<char>::_Release((ZXString<char>::_ZXStringData *)(*(_DWORD *)&v24.gap0[0] - 12));
v11 = CInPacket::DecodeStr(iPacket, (ZXString<char> *)&v24);
v12 = &result->p->sRollbackUsageID;
v25 = 3;
ZXString<char>::operator=(v12, v11);
LOBYTE(v25) = 0;
if ( *(_DWORD *)&v24.gap0[0] )
ZXString<char>::_Release((ZXString<char>::_ZXStringData *)(*(_DWORD *)&v24.gap0[0] - 12));
CInPacket::DecodeBuffer(iPacket, &result->p->ftITCDateExpired, 8u);
v13 = CInPacket::DecodeStr(iPacket, (ZXString<char> *)&v24);
lstrcpyA(result->p->sUserID, v13->_m_pStr);
if ( *(_DWORD *)&v24.gap0[0] )
ZXString<char>::_Release((ZXString<char>::_ZXStringData *)(*(_DWORD *)&v24.gap0[0] - 12));
v14 = CInPacket::DecodeStr(iPacket, (ZXString<char> *)&v24);
lstrcpyA(result->p->sGameID, v14->_m_pStr);
if ( *(_DWORD *)&v24.gap0[0] )
ZXString<char>::_Release((ZXString<char>::_ZXStringData *)(*(_DWORD *)&v24.gap0[0] - 12));
v15 = CInPacket::DecodeStr(iPacket, (ZXString<char> *)&v24);
lstrcpyA(result->p->sComment, v15->_m_pStr);
if ( *(_DWORD *)&v24.gap0[0] )
ZXString<char>::_Release((ZXString<char>::_ZXStringData *)(*(_DWORD *)&v24.gap0[0] - 12));
v16 = result->p;
v16->nBidCount = CInPacket::Decode4(iPacket);
v17 = result->p;
v17->nBidRange = CInPacket::Decode4(iPacket);
v18 = result->p;
v18->nBidPrice = CInPacket::Decode4(iPacket);
v19 = result->p;
v19->nMinPrice = CInPacket::Decode4(iPacket);
v20 = result->p;
v20->nMaxPrice = CInPacket::Decode4(iPacket);
v21 = result->p;
v21->nUnitPrice = CInPacket::Decode4(iPacket);
v22 = result->p;
v22->nProcessStatus = CInPacket::Decode2(iPacket);
return result;
}

last:

if ( CInPacket::Decode1(v3) )
v2->m_bITCRequestSent = 0;

*/
