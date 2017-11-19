//

#include "packetcreator.hpp"

#include "send_packet_opcodes.hpp"
#include "buffvalues.hpp"
#include "buffstat_constants.hpp"

void PacketCreator::GiveEnergyCharge(int player_id, int bar, int time) {
    if (player_id > 0) {
        write<short>(send_headers::kGIVE_FOREIGN_BUFF);
        write<int>(player_id);
    } else {
        write<short>(send_headers::kGIVE_BUFF);
    }

    write<long long>(0);
    write<long long>(buffstat_constants::kEnergyCharge);

    write_null(13);

    if (player_id > 0) {
        write_null(14);
    }

    if (bar < 10000) {
        write<int>(bar);
    } else {
        write<int>(10000);
    }

    write<long long>(0);
    write<signed char>(0);
    write<int>(bar >= 10000 ? time : 0);
    write<short>(0);
    write<signed char>(6);
}

/*
public static byte[] giveInfusion(int buffid, int bufflength, int speed) {//This ain't correct
final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
mplew.writeShort(SendOpcode.GIVE_BUFF.getValue());
mplew.writeLong(MapleBuffStat.SPEED_INFUSION.getValue());
mplew.writeLong(0);
mplew.writeShort(speed);
mplew.writeInt(buffid);
mplew.write(0);
mplew.writeShort(bufflength);
mplew.writeShort(0);
mplew.writeShort(0);
mplew.writeShort(0);
return mplew.getPacket();
}

public static byte[] givePirateBuff(List<Pair<MapleBuffStat, Integer>> statups, int buffid, int duration) {
final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
mplew.writeShort(SendOpcode.GIVE_BUFF.getValue());
writeLongMask(mplew, statups);
mplew.writeShort(0);
for (Pair<MapleBuffStat, Integer> stat : statups) {
mplew.writeInt(stat.getRight().shortValue());
mplew.writeInt(buffid);
mplew.skip(5);
mplew.writeShort(duration);
}
mplew.skip(3);
return mplew.getPacket();
}

public static byte[] giveForeignDash(int cid, int buffid, int time, List<Pair<MapleBuffStat, Integer>> statups) {
final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
mplew.writeShort(SendOpcode.GIVE_FOREIGN_BUFF.getValue());
mplew.writeInt(cid);
writeLongMask(mplew, statups);
mplew.writeShort(0);
for (Pair<MapleBuffStat, Integer> statup : statups) {
mplew.writeInt(statup.getRight().shortValue());
mplew.writeInt(buffid);
mplew.skip(5);
mplew.writeShort(time);
}
mplew.writeShort(0);
mplew.write(2);
return mplew.getPacket();
}

public static byte[] giveForeignInfusion(int cid, int speed, int duration) {
final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
mplew.writeShort(SendOpcode.GIVE_FOREIGN_BUFF.getValue());
mplew.writeInt(cid);
mplew.writeLong(MapleBuffStat.SPEED_INFUSION.getValue());
mplew.writeLong(0);
mplew.writeShort(0);
mplew.writeInt(speed);
mplew.writeInt(5121009);
mplew.writeLong(0);
mplew.writeInt(duration);
mplew.writeShort(0);
return mplew.getPacket();
}
*/

void
PacketCreator::ShowMonsterRiding(int player_id, int item_id, int skill_id) {
    if (player_id > 0) {
        write<short>(send_headers::kGIVE_FOREIGN_BUFF);
        write<int>(player_id);
    } else {
        write<short>(send_headers::kGIVE_BUFF);
    }

    write<long long>(buffstat_constants_position_1::kMonsterRiding);
    write<long long>(0);

    write<short>(0);
    write<int>(item_id);
    write<int>(skill_id);
    write<int>(0);
    write<short>(0);
    write<signed char>(0);
}

void PacketCreator::ShowPlayerBuff(Values *values, int skill_id, int time) {
    write<short>(send_headers::kGIVE_BUFF);

    values->sort();

    WriteBuffMask(values);

    auto values2 = values->get_values();

    for (auto &value : *values2) {
        write<short>(value.get_value());
        write<int>(skill_id);
        write<int>(time);
    }

    write<signed char>(0);
    write<signed char>(0);
    write<short>(0);
    write<long long>(0);
}

void PacketCreator::CancelPlayerBuff(Values *values) {
    write<short>(send_headers::kCANCEL_BUFF);

    WriteBuffMask(values);

    write<signed char>(1);
}

void PacketCreator::ShowMapBuff(int player_id, Values *values) {
    write<short>(send_headers::kGIVE_FOREIGN_BUFF);
    write<int>(player_id);

    values->sort();

    WriteBuffMask(values);

    auto values2 = values->get_values();

    for (Value &value : *values2) {
        // morph is 8 bit here except for pirate morph?
        write<short>(value.get_value());
    }

    write<int>(0);
    write<short>(0);
}

void PacketCreator::CancelMapBuff(int player_id, Values *values) {
    write<short>(send_headers::kCANCEL_FOREIGN_BUFF);
    write<int>(player_id);

    WriteBuffMask(values);
}

void PacketCreator::WriteBuffMask(Values *values) {
    unsigned long long mask = 0;
    auto values2 = values->get_values();

    for (Value &value : *values2) {
        mask |= value.get_stat();
    }

    write<unsigned long long>(0);
    write<unsigned long long>(mask);
}
