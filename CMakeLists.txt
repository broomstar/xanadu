cmake_minimum_required(VERSION 3.8)
project(xanadu)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        xanadu/scriptarray/scriptarray.cpp
#        xanadu/scriptarray/scriptarray.h
#        xanadu/scripts/npcs/el_nath_magic_spot_npc.cpp
#        xanadu/scripts/npcs/female_stylist_nimakin.cpp
#        xanadu/scripts/npcs/first_eos_rock_npc.cpp
#        xanadu/scripts/npcs/fourth_eos_rock_npc.cpp
#        xanadu/scripts/npcs/gachapon_npc_handler.cpp
#        xanadu/scripts/npcs/guild_creator_npc.cpp
#        xanadu/scripts/npcs/guild_emblem_npc.cpp
#        xanadu/scripts/npcs/handle_bowman_job_advancer.cpp
#        xanadu/scripts/npcs/handle_mage_job_advancer.cpp
#        xanadu/scripts/npcs/handle_npc_sera.cpp
#        xanadu/scripts/npcs/handle_npc_spinel.cpp
#        xanadu/scripts/npcs/handle_pirate_job_advancer.cpp
#        xanadu/scripts/npcs/handle_thief_job_advancer.cpp
#        xanadu/scripts/npcs/handle_warrior_job_advancer.cpp
#        xanadu/scripts/npcs/handle_zakum_npcs.cpp
#        xanadu/scripts/npcs/horntail_entrance_npc.cpp
#        xanadu/scripts/npcs/jeff_elnath_npc.cpp
#        xanadu/scripts/npcs/male_stylist_kin.cpp
#        xanadu/scripts/npcs/maple_leaf_exchanger_npc.cpp
#        xanadu/scripts/npcs/npcs_pq_henesys.cpp
#        xanadu/scripts/npcs/npcs_pq_kerning.cpp
#        xanadu/scripts/npcs/npcs_pq_ludi_maze.cpp
#        xanadu/scripts/npcs/npcs_pq_ludibrium.cpp
#        xanadu/scripts/npcs/npcs_ship_plane_subway.cpp
#        xanadu/scripts/npcs/orbis_magic_spot_npc.cpp
#        xanadu/scripts/npcs/papulatus_npc.cpp
#        xanadu/scripts/npcs/second_eos_rock_npc.cpp
#        xanadu/scripts/npcs/third_eos_rock_npc.cpp
#        xanadu/scriptstdstring/scriptstdstring.cpp
#        xanadu/scriptstdstring/scriptstdstring.h
#        xanadu/scriptstdstring/scriptstdstring_utils.cpp
        xanadu/attackinfo.hpp
        xanadu/buddy.cpp
        xanadu/buddy.hpp
        xanadu/buddy_packets.cpp
        xanadu/buddylist_constants.hpp
        xanadu/buff_packets.cpp
        xanadu/buffstat_constants.hpp
        xanadu/buffvalue.cpp
        xanadu/buffvalue.hpp
        xanadu/buffvalues.cpp
        xanadu/buffvalues.hpp
        xanadu/cash_item_data.hpp
        xanadu/cash_shop_item_data_provider.cpp
        xanadu/cash_shop_item_data_provider.hpp
        xanadu/cash_shop_package_data_provider.cpp
        xanadu/cash_shop_package_data_provider.hpp
        xanadu/cash_shop_packets.cpp
        xanadu/cashshop_constants.hpp
        xanadu/cashshop_handler.cpp
        xanadu/channel.cpp
        xanadu/channel.hpp
        xanadu/character.cpp
        xanadu/character.hpp
        xanadu/chat_handler.cpp
        xanadu/chat_packets.cpp
        xanadu/constants.hpp
        xanadu/crypto.cpp
        xanadu/crypto.hpp
        xanadu/crypto_constants.hpp
        xanadu/drop.cpp
        xanadu/drop.hpp
        xanadu/drop_constants.hpp
        xanadu/drop_data.hpp
        xanadu/drop_handler.cpp
        xanadu/drop_packets.cpp
        xanadu/effect.cpp
        xanadu/effect.hpp
        xanadu/equip_data.hpp
        xanadu/equip_data_provider.cpp
        xanadu/equip_data_provider.hpp
        xanadu/fame_handler.cpp
        xanadu/game_constants.hpp
        xanadu/guild.cpp
        xanadu/guild.hpp
        xanadu/guild_constants.hpp
        xanadu/guild_handler.cpp
        xanadu/guild_member.cpp
        xanadu/guild_member.hpp
        xanadu/guild_packets.cpp
        xanadu/hiredmerchant.cpp
        xanadu/hiredmerchant.hpp
        xanadu/hiredmerchant_item.cpp
        xanadu/hiredmerchant_item.hpp
        xanadu/inventory.cpp
        xanadu/inventory.hpp
        xanadu/inventory_handler.cpp
        xanadu/inventory_packets.cpp
        xanadu/item.cpp
        xanadu/item.hpp
        xanadu/item_data.hpp
        xanadu/item_data_provider.cpp
        xanadu/item_data_provider.hpp
        xanadu/job_constants.hpp
        xanadu/key.hpp
        xanadu/logger.cpp
        xanadu/logger.hpp
        xanadu/login_handler.cpp
        xanadu/login_packets.cpp
        xanadu/map.cpp
        xanadu/map.hpp
        xanadu/map_data.cpp
        xanadu/map_data.hpp
        xanadu/map_data_provider.cpp
        xanadu/map_data_provider.hpp
        xanadu/map_foothold_data.hpp
        xanadu/map_mob_data.hpp
        xanadu/map_portal_data.cpp
        xanadu/map_portal_data.hpp
        xanadu/map_reactor_data.hpp
        xanadu/mapnpc.cpp
        xanadu/mapnpc.hpp
        xanadu/messenger.cpp
        xanadu/messenger.hpp
        xanadu/messenger_constants.hpp
        xanadu/messenger_handler.cpp
        xanadu/messenger_packet.cpp
        xanadu/mob.cpp
        xanadu/mob.hpp
        xanadu/mob_constants.hpp
        xanadu/mob_data.hpp
        xanadu/mob_data_provider.cpp
        xanadu/mob_data_provider.hpp
        xanadu/mob_drops_data_provider.cpp
        xanadu/mob_drops_data_provider.hpp
        xanadu/mob_handler.cpp
        xanadu/mob_packets.cpp
        xanadu/movement_handler.cpp
        xanadu/mts_handler.cpp
        xanadu/npc_handler.cpp
        xanadu/npc_packets.cpp
        xanadu/other_packets.cpp
        xanadu/packet_constants.hpp
        xanadu/packetcreator.cpp
        xanadu/packetcreator.hpp
        xanadu/party.cpp
        xanadu/party.hpp
        xanadu/party_constants.hpp
        xanadu/party_handler.cpp
        xanadu/party_member.cpp
        xanadu/party_member.hpp
        xanadu/party_packets.cpp
        xanadu/pet_command_data.hpp
        xanadu/pet_data.cpp
        xanadu/pet_data.hpp
        xanadu/pet_data_provider.cpp
        xanadu/pet_data_provider.hpp
        xanadu/pet_handler.cpp
        xanadu/pet_packets.cpp
        xanadu/player.cpp
        xanadu/player.hpp
        xanadu/player_attack_handler.cpp
        xanadu/player_handler.cpp
        xanadu/player_interaction_handler.cpp
        xanadu/player_interation_packets.cpp
        xanadu/player_movement_handler.cpp
        xanadu/player_trade.cpp
        xanadu/playerbuddylist.cpp
        xanadu/playerbuffs.cpp
        xanadu/playernpc.cpp
        xanadu/playernpc.hpp
        xanadu/playerquests.cpp
        xanadu/playersummons.cpp
        xanadu/portal_script_handler.cpp
        xanadu/pq_constants.hpp
        xanadu/pq_packets.cpp
        xanadu/quest.cpp
        xanadu/quest.hpp
        xanadu/quest_constants.hpp
        xanadu/quest_data.cpp
        xanadu/quest_data.hpp
        xanadu/quest_data_provider.cpp
        xanadu/quest_data_provider.hpp
        xanadu/quest_handler.cpp
        xanadu/quest_reward_data.hpp
        xanadu/reactor_handler.cpp
        xanadu/reactor_packets.cpp
        xanadu/receive_packet_opcodes.hpp
        xanadu/script_handler.cpp
        xanadu/script_handler.h
        xanadu/send_packet_opcodes.hpp
        xanadu/server_constants.hpp
        xanadu/session.cpp
        xanadu/session.hpp
        xanadu/shop_data.cpp
        xanadu/shop_data.hpp
        xanadu/shop_data_provider.cpp
        xanadu/shop_data_provider.hpp
        xanadu/shop_item_data.hpp
        xanadu/skill.hpp
        xanadu/skill_data.cpp
        xanadu/skill_data.hpp
        xanadu/skill_data_provider.cpp
        xanadu/skill_data_provider.hpp
        xanadu/skill_level_data.hpp
        xanadu/skill_packets.cpp
        xanadu/skills_handler.cpp
        xanadu/stat_packets.cpp
        xanadu/stats_handler.cpp
        xanadu/storage_handler.cpp
        xanadu/summon.cpp
        xanadu/summon.hpp
        xanadu/summon_handler.cpp
        xanadu/summon_packets.cpp
        xanadu/timer.cpp
        xanadu/timer.hpp
        xanadu/timer_id.hpp
        xanadu/tools.cpp
        xanadu/tools.hpp
        xanadu/valid_char_data_provider.cpp
        xanadu/valid_char_data_provider.hpp
        xanadu/world.cpp
        xanadu/world.hpp
        xanadu/wz/wzcrypto.cpp
        xanadu/wz/wzcrypto.hpp
        xanadu/wz/wzdata.hpp
        xanadu/wz/wzdata_constants.hpp
        xanadu/wz/wzfile.cpp
        xanadu/wz/wzfile.hpp
        xanadu/wz/wzimg.cpp
        xanadu/wz/wzimg.hpp
        xanadu/wz/wzmain.cpp
        xanadu/wz/wzmain.hpp
        xanadu/wz/wznode.cpp
        xanadu/wz/wznode.hpp
        xanadu/xanadu.cpp)

include_directories(/usr/local/Cellar/cryptopp/5.6.5/include/cryptopp)
link_directories(/usr/local/Cellar/cryptopp/5.6.5/lib)
add_executable(xanadu ${SOURCE_FILES})
target_link_libraries(xanadu cryptopp fmt)