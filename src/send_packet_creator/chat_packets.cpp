//

#include "packetcreator.hpp"

#include "player.hpp"
#include "constants/send_packet_opcodes.hpp"
#include "constants/constants.hpp"

void PacketCreator::ShowChatMessage(Player *player, const std::string &message,
                                    bool bubble_only) {
    write<short>(send_headers::kCHATTEXT);
    write<int>(player->get_id());
    write_bool(player->get_is_gm());
    write_string(message);
    write_bool(bubble_only);
}

enum message_types {
    kNoticeBlue,
    kPopupBox,
    kMegaphone,
    kSuperMegaphone,
    kScrollingMessageAtTop,
    kRedPinkNotice,
    kBlueNotice,
    kItemMegaphone = 8
};

void PacketCreator::ShowMessage(const std::string &message, unsigned char type,
                                unsigned char channel_id, unsigned char whisper,
                                std::shared_ptr<Item> item) {
    write<short>(send_headers::kSERVERMESSAGE);
    write<signed char>(type);

    if (type == kScrollingMessageAtTop) {
        write<signed char>(message != "");
    }

    write_string(message);

    switch (type) {
        case kSuperMegaphone: {
            write<signed char>(channel_id);
            write<signed char>(whisper);
            break;
        }
        case kBlueNotice: {
            write<int>(0);
            break;
        }
        case kItemMegaphone: {
            write<signed char>(channel_id);
            write<signed char>(whisper);
            if (item) {
                write<signed char>(item->get_slot());
                ItemInfo(item.get(), false);
            } else {
                write<signed char>(0);
            }
            break;
        }
    }
}

void PacketCreator::FindPlayerReply(const std::string &name, bool success) {
    write<short>(send_headers::kWHISPER);
    write<signed char>(
            find_player_or_whisper_packet_action_constants::kFindPlayerReply);
    write_string(name);
    write_bool(success);
}

void PacketCreator::FindPlayer(const std::string &name, signed char mode2,
                               int map_id_or_channel_id) {
    write<short>(send_headers::kWHISPER);
    write<signed char>(
            find_player_or_whisper_packet_action_constants::kFindPlayerMapOrChannelOrMtsOrCashshop);
    write_string(name);
    write<signed char>(mode2);
    write<int>(
            map_id_or_channel_id); // mapid or channelid or -1 if mts or cash shop

    if (mode2 == find_player_packet_mode2_constants::kMap) {
        write<long long>(0);
    }
}

void PacketCreator::WhisperPlayer(Player *player, const std::string &message) {
    write<short>(send_headers::kWHISPER);
    write<signed char>(
            find_player_or_whisper_packet_action_constants::kWhisper);
    write_string(player->get_name());
    write<short>(player->get_channel_id());
    write_string(message);
}

void PacketCreator::ShowGroupChat(unsigned char type, const std::string &name,
                                  const std::string &message) {
    write<short>(send_headers::kGROUP_CHAT);
    write<signed char>(type);
    write_string(name);
    write_string(message);
}
