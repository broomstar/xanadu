cmake_minimum_required(VERSION 3.8)
project(xanadu)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/connection_handling/session.cpp
        src/connection_handling/session.hpp
        src/constants/buddylist_constants.hpp
        src/constants/buffstat_constants.hpp
        src/constants/cashshop_constants.hpp
        src/constants/constants.hpp
        src/constants/crypto_constants.hpp
        src/constants/drop_constants.hpp
        src/constants/game_constants.hpp
        src/constants/guild_constants.hpp
        src/constants/job_constants.hpp
        src/constants/messenger_constants.hpp
        src/constants/mob_constants.hpp
        src/constants/packet_constants.hpp
        src/constants/party_constants.hpp
        src/constants/pq_constants.hpp
        src/constants/quest_constants.hpp
        src/constants/receive_packet_opcodes.hpp
        src/constants/send_packet_opcodes.hpp
        src/constants/server_constants.hpp
        src/crypto/crypto.cpp
        src/crypto/crypto.hpp
        src/database/cash_shop_item_data_provider.cpp
        src/database/cash_shop_item_data_provider.hpp
        src/database/cash_shop_package_data_provider.cpp
        src/database/cash_shop_package_data_provider.hpp
        src/database/equip_data_provider.cpp
        src/database/equip_data_provider.hpp
        src/database/item_data_provider.cpp
        src/database/item_data_provider.hpp
        src/database/map_data_provider.cpp
        src/database/map_data_provider.hpp
        src/database/mob_data_provider.cpp
        src/database/mob_data_provider.hpp
        src/database/mob_drops_data_provider.cpp
        src/database/mob_drops_data_provider.hpp
        src/database/pet_data_provider.cpp
        src/database/pet_data_provider.hpp
        src/database/quest_data_provider.cpp
        src/database/quest_data_provider.hpp
        src/database/shop_data_provider.cpp
        src/database/shop_data_provider.hpp
        src/database/skill_data_provider.cpp
        src/database/skill_data_provider.hpp
        src/database/valid_char_data_provider.cpp
        src/database/valid_char_data_provider.hpp
        src/receive_packet_handler/cashshop_handler.cpp
        src/receive_packet_handler/chat_handler.cpp
        src/receive_packet_handler/drop_handler.cpp
        src/receive_packet_handler/fame_handler.cpp
        src/receive_packet_handler/guild_handler.cpp
        src/receive_packet_handler/inventory_handler.cpp
        src/receive_packet_handler/login_handler.cpp
        src/receive_packet_handler/messenger_handler.cpp
        src/receive_packet_handler/mob_handler.cpp
        src/receive_packet_handler/movement_handler.cpp
        src/receive_packet_handler/mts_handler.cpp
        src/receive_packet_handler/npc_handler.cpp
        src/receive_packet_handler/party_handler.cpp
        src/receive_packet_handler/pet_handler.cpp
        src/receive_packet_handler/player_attack_handler.cpp
        src/receive_packet_handler/player_handler.cpp
        src/receive_packet_handler/player_interaction_handler.cpp
        src/receive_packet_handler/player_movement_handler.cpp
        src/receive_packet_handler/portal_script_handler.cpp
        src/receive_packet_handler/quest_handler.cpp
        src/receive_packet_handler/reactor_handler.cpp
        #        src/receive_packet_handler/script_handler.cpp
        src/receive_packet_handler/skills_handler.cpp
        src/receive_packet_handler/stats_handler.cpp
        src/receive_packet_handler/storage_handler.cpp
        src/receive_packet_handler/summon_handler.cpp
        #        src/script_engine/scriptarray/scriptarray.cpp
        #        src/script_engine/scriptarray/scriptarray.h
        #        src/script_engine/scriptstdstring/scriptstdstring.cpp
        #        src/script_engine/scriptstdstring/scriptstdstring.h
        #        src/script_engine/scriptstdstring/scriptstdstring_utils.cpp
        #        src/script_engine/script_handler.h
        #        src/scripts/npcs/1012000.as
        #        src/scripts/npcs/1022001.as
        #        src/scripts/npcs/1032000.as
        #        src/scripts/npcs/1052016.as
        #        src/scripts/npcs/9201056.as
        #        src/scripts/npcs/el_nath_magic_spot_npc.cpp
        #        src/scripts/npcs/female_stylist_nimakin.cpp
        #        src/scripts/npcs/first_eos_rock_npc.cpp
        #        src/scripts/npcs/fourth_eos_rock_npc.cpp
        #        src/scripts/npcs/gachapon_npc_handler.cpp
        #        src/scripts/npcs/guild_creator_npc.cpp
        #        src/scripts/npcs/guild_emblem_npc.cpp
        #        src/scripts/npcs/handle_bowman_job_advancer.cpp
        #        src/scripts/npcs/handle_mage_job_advancer.cpp
        #        src/scripts/npcs/handle_npc_sera.cpp
        #        src/scripts/npcs/handle_npc_spinel.cpp
        #        src/scripts/npcs/handle_pirate_job_advancer.cpp
        #        src/scripts/npcs/handle_thief_job_advancer.cpp
        #        src/scripts/npcs/handle_warrior_job_advancer.cpp
        #        src/scripts/npcs/handle_zakum_npcs.cpp
        #        src/scripts/npcs/horntail_entrance_npc.cpp
        #        "src/scripts/npcs/info ids.txt"
        #        src/scripts/npcs/jeff_elnath_npc.cpp
        #        src/scripts/npcs/male_stylist_kin.cpp
        #        src/scripts/npcs/maple_leaf_exchanger_npc.cpp
        #        src/scripts/npcs/npcs_pq_henesys.cpp
        #        src/scripts/npcs/npcs_pq_kerning.cpp
        #        src/scripts/npcs/npcs_pq_ludi_maze.cpp
        #        src/scripts/npcs/npcs_pq_ludibrium.cpp
        #        src/scripts/npcs/npcs_ship_plane_subway.cpp
        #        src/scripts/npcs/orbis_magic_spot_npc.cpp
        #        src/scripts/npcs/papulatus_npc.cpp
        #        src/scripts/npcs/second_eos_rock_npc.cpp
        #        src/scripts/npcs/third_eos_rock_npc.cpp
        src/send_packet_creator/buddy_packets.cpp
        src/send_packet_creator/buff_packets.cpp
        src/send_packet_creator/cash_shop_packets.cpp
        src/send_packet_creator/chat_packets.cpp
        src/send_packet_creator/drop_packets.cpp
        src/send_packet_creator/guild_packets.cpp
        src/send_packet_creator/inventory_packets.cpp
        src/send_packet_creator/login_packets.cpp
        src/send_packet_creator/mob_packets.cpp
        src/send_packet_creator/npc_packets.cpp
        src/send_packet_creator/other_packets.cpp
        src/send_packet_creator/party_packets.cpp
        src/send_packet_creator/pet_packets.cpp
        src/send_packet_creator/player_interation_packets.cpp
        src/send_packet_creator/pq_packets.cpp
        src/send_packet_creator/reactor_packets.cpp
        src/send_packet_creator/skill_packets.cpp
        src/send_packet_creator/stat_packets.cpp
        src/send_packet_creator/summon_packets.cpp
        src/timer/timer.cpp
        src/timer/timer.hpp
        src/timer/timer_id.hpp
        src/utilities/tools.cpp
        src/utilities/tools.hpp
        src/world_server/attackinfo.hpp
        src/world_server/buddy.cpp
        src/world_server/buddy.hpp
        src/world_server/buffvalue.cpp
        src/world_server/buffvalue.hpp
        src/world_server/buffvalues.cpp
        src/world_server/buffvalues.hpp
        src/world_server/cash_item_data.hpp
        src/world_server/channel.cpp
        src/world_server/channel.hpp
        src/world_server/character.cpp
        src/world_server/character.hpp
        src/world_server/drop.cpp
        src/world_server/drop.hpp
        src/world_server/drop_data.hpp
        src/world_server/effect.cpp
        src/world_server/effect.hpp
        src/world_server/equip_data.hpp
        src/world_server/guild.cpp
        src/world_server/guild.hpp
        src/world_server/guild_member.cpp
        src/world_server/guild_member.hpp
        src/world_server/hiredmerchant.cpp
        src/world_server/hiredmerchant.hpp
        src/world_server/hiredmerchant_item.cpp
        src/world_server/hiredmerchant_item.hpp
        src/world_server/inventory.cpp
        src/world_server/inventory.hpp
        src/world_server/item.cpp
        src/world_server/item.hpp
        src/world_server/item_data.hpp
        src/world_server/key.hpp
        src/world_server/logger.cpp
        src/world_server/logger.hpp
        src/world_server/map.cpp
        src/world_server/map.hpp
        src/world_server/map_data.cpp
        src/world_server/map_data.hpp
        src/world_server/map_foothold_data.hpp
        src/world_server/map_mob_data.hpp
        src/world_server/map_portal_data.cpp
        src/world_server/map_portal_data.hpp
        src/world_server/map_reactor_data.hpp
        src/world_server/mapnpc.cpp
        src/world_server/mapnpc.hpp
        src/world_server/messenger.cpp
        src/world_server/messenger.hpp
        src/world_server/messenger_packet.cpp
        src/world_server/mob.cpp
        src/world_server/mob.hpp
        src/world_server/mob_data.hpp
        src/world_server/packetcreator.cpp
        src/world_server/packetcreator.hpp
        src/world_server/party.cpp
        src/world_server/party.hpp
        src/world_server/party_member.cpp
        src/world_server/party_member.hpp
        src/world_server/pet_command_data.hpp
        src/world_server/pet_data.cpp
        src/world_server/pet_data.hpp
        src/world_server/player.cpp
        src/world_server/player.hpp
        src/world_server/player_trade.cpp
        src/world_server/playerbuddylist.cpp
        src/world_server/playerbuffs.cpp
        src/world_server/playernpc.cpp
        src/world_server/playernpc.hpp
        src/world_server/playerquests.cpp
        src/world_server/playersummons.cpp
        src/world_server/quest.cpp
        src/world_server/quest.hpp
        src/world_server/quest_data.cpp
        src/world_server/quest_data.hpp
        src/world_server/quest_reward_data.hpp
        src/world_server/shop_data.cpp
        src/world_server/shop_data.hpp
        src/world_server/shop_item_data.hpp
        src/world_server/skill.hpp
        src/world_server/skill_data.cpp
        src/world_server/skill_data.hpp
        src/world_server/skill_level_data.hpp
        src/world_server/summon.cpp
        src/world_server/summon.hpp
        src/world_server/world.cpp
        src/world_server/world.hpp
        src/wz_reader/wzcrypto.cpp
        src/wz_reader/wzcrypto.hpp
        src/wz_reader/wzdata.hpp
        src/wz_reader/wzdata_constants.hpp
        src/wz_reader/wzfile.cpp
        src/wz_reader/wzfile.hpp
        src/wz_reader/wzimg.cpp
        src/wz_reader/wzimg.hpp
        src/wz_reader/wzmain.cpp
        src/wz_reader/wzmain.hpp
        src/wz_reader/wznode.cpp
        src/wz_reader/wznode.hpp
        src/xanadu.cpp)

include_directories(src/
        src/database
        src/world_server
        src/wz_reader
        src/constants
        /usr/local/Cellar/cryptopp/5.6.5/include/cryptopp
        /Users/linjian/Cpp/User/local/include)
link_directories(
        /usr/local/Cellar/cryptopp/5.6.5/lib
        /Users/linjian/Cpp/User/local/lib)
add_executable(xanadu ${SOURCE_FILES})
target_link_libraries(xanadu cryptopp fmt PocoDataMySQL PocoData PocoFoundation)