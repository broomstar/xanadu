
#include "player.hpp"
#include "map.hpp"
#include "playernpc.hpp"
#include "session.hpp"
#include "constants.hpp"

#include <angelscript.h>
#include "scriptstdstring\scriptstdstring.h"
#include "scriptarray\scriptarray.h"

// Implement a simple message callback function for as
void MessageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

static bool first_npc = true;

static asIScriptEngine *engine = nullptr;

void as_function_dummy()
{

}

// constants for as

const int as_YES_CONSTANT = kNpcConstantsYes;
const int as_NO_CONSTANT = kNpcConstantsNo;

const int as_EQUIP = kInventoryConstantsTypesEquip;
const int as_USE = kInventoryConstantsTypesUse;
const int as_SETUP = kInventoryConstantsTypesSetup;
const int as_ETC = kInventoryConstantsTypesEtc;
const int as_CASH = kInventoryConstantsTypesCash;

void Player::npc_script_handler()
{
	int npc_id = npc_->id_;

	std::string npc_id_string = std::to_string(npc_id);

	// init it
	// to-do do initialization at server start
	if (first_npc)
	{
		int r;

		// Set the message callback when creating the engine
		engine = asCreateScriptEngine();
		r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

		// Register the string type
		RegisterStdString(engine);

		// Register arrays
		RegisterScriptArray(engine, true);

		r = engine->RegisterGlobalProperty("const int YES", (void*)&as_YES_CONSTANT); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int NO", (void*)&as_NO_CONSTANT); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int EQUIP", (void*)&as_EQUIP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int USE", (void*)&as_USE); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int SETUP", (void*)&as_SETUP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int ETC", (void*)&as_ETC); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const int CASH", (void*)&as_CASH); assert(r >= 0);

		// Player
		r = engine->RegisterObjectType("Player", sizeof(Player), asOBJ_REF); assert(r >= 0);

		r = engine->RegisterObjectBehaviour("Player", asBEHAVE_ADDREF, "void f()", asFUNCTION(as_function_dummy), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour("Player", asBEHAVE_RELEASE, "void f()", asFUNCTION(as_function_dummy), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Map
		r = engine->RegisterObjectType("Map", sizeof(Map), asOBJ_REF); assert(r >= 0);

		r = engine->RegisterObjectBehaviour("Map", asBEHAVE_ADDREF, "void f()", asFUNCTION(as_function_dummy), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour("Map", asBEHAVE_RELEASE, "void f()", asFUNCTION(as_function_dummy), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// functions
		r = engine->RegisterObjectMethod("Player", "int get_selected()", asMETHOD(Player, get_selected), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void set_selected(int)", asMETHOD(Player, set_selected), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void send_simple(string)", asMETHOD(Player, send_simple), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void send_ok(string)", asMETHOD(Player, send_ok), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void set_npc_variable(string, int)", asMETHOD(Player, set_npc_variable), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "int get_npc_variable(string)", asMETHOD(Player, get_npc_variable), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "int get_mesos()", asMETHOD(Player, get_mesos), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "bool add_mesos(int)", asMETHOD(Player, add_mesos), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void set_state(int)", asMETHOD(Player, set_state), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "int get_state()", asMETHOD(Player, get_state), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void send_yes_no(string)", asMETHOD(Player, send_yes_no), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "void set_map(int)", asMETHOD(Player, set_map), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Player", "Map @get_map()", asMETHOD(Player, get_map), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod("Map", "int get_id()", asMETHOD(Map, get_id), asCALL_THISCALL); assert(r >= 0);
	}

	// START OF LOADING AND BUILDING

	std::string file_name_string = "npc scripts\\" + npc_id_string + ".as";

	// Load the entire script file into a string buffer

	// Open the file in binary mode
	FILE *f = fopen(file_name_string.c_str(), "rb");

	if (!f)
	{
		return;
	}

	// Create a new script module
	asIScriptModule *mod = engine->GetModule(file_name_string.c_str(), asGM_ALWAYS_CREATE);

	// Load and add the script sections to the module
	std::string script;

	// Determine the size of the file
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);

	// Load the entire file in one call
	script.resize(len);
	fread(&script[0], len, 1, f);

	fclose(f);
	mod->AddScriptSection(file_name_string.c_str(), script.c_str());

	// Build the module
	int r = mod->Build();
	if (r < 0)
	{
		// The build failed. The message stream will have received
		// compiler errors that shows what needs to be fixed
	}

	// END OF LOADING AND BUILDING

	// START OF PREPARING AND EXECUTING

	// Get a script context instance. Usually you'll want to reuse a previously
	// created instance to avoid the overhead of allocating the instance with
	// each call.
	asIScriptContext *ctx = engine->CreateContext();
	// Obtain the function from the module. This should preferrably  
	// be cached if the same function is called multiple times.
	asIScriptFunction *func = engine->GetModule(file_name_string.c_str())->GetFunctionByName("main");
	// Prepare() must be called to allow the context to prepare the stack
	ctx->Prepare(func);
	// Set the function arguments
	ctx->SetArgObject(0, this);
	r = ctx->Execute();
	/*if (r == asEXECUTION_FINISHED)
	{
		// The return value is only valid if the execution finished successfully
		asDWORD ret = ctx->GetReturnDWord();
	}*/
	// Release the context when you're done with it
	ctx->Release();

	// END OF PREPARING AND EXECUTING

	/*switch (npc_->id_)
	{
	switch (npc_->id_)
	{
		// custom Free Market npcs
	case 9100117: // Nautilus Gachapon
	case 9100100: //Spa (Female)
	case 9100101: //Ellinia
	case 9100102: //Perion
	case 9100103: //Kerning City
	case 9100104: //Sleepywood
	case 9100105: //Mushroom Shrine
	case 9100106: //Spa (Male)
	case 9100107: //Spa (Female)
	case 9100109: //NLC
	case 9100110: //Henesys
	case 9100111: //Singapore
	case 9100112: //EXP Gachapon
				  //get these gachapon IDs in V62 npc wz, but not sure where they located
	case 9100108:
	case 9110011:
	case 9110012:
	case 9110013:
	case 9110014:
	case 9270043:
		handle_gachapon_npc();
		break;
	case 9001000: // Donator Npc
		handle_donator_npc();
		break;
	case 9001001: // Maple Leaf Exchanger
		handle_maple_leaf_exchanger_npc();
		break;

		// job advancer npcs
	case 1032001: // Mage job advancer
		handle_mage_job_advancer();
		break;
	case 1052001: // Thief job advancer
		handle_thief_job_advancer();
		break;
	case 1012100: // Bowman job advancer
		handle_bowman_job_advancer();
		break;
	case 1022000: // Warrior job advancer
		handle_warrior_job_advancer();
		break;
	case 1072008: // Pirate job advancer
		handle_pirate_job_advancer();
		break;

	// PQ Npcs

	case 1012112: // Tory, warps into Henesys PQ
		handle_hpq_tory_npc();
		break;
	case 1012113: // Tommy, warps out of Henesys PQ
		handle_hpq_tommy_npc();
		break;
	case 1012114: // Growlie, warps to shortcut map after finishing HPQ main stage
		handle_hpq_growlie_npc();
		break;
	case 9020000: // Lakelis, brings party into Kerning PQ
		handle_kpq_lakelis_npc();
		break;
	case 9020001: // Cloto, KPQ Stage 1, 2, 3, 4, Last Stage
		handle_kpq_cloto_npc();
		break;
	case 9020002: // Nella, Exit for KPQ
		handle_kpq_nella_npc();
		break;
	case 2040034: // Red Sign, brings party into Ludibrium PQ
		handle_lpq_red_sign_npc();
		break;
	case 2013000: // Wonky the fairy, brings party into Orbis PQ
		handle_npc_opq_wonky();
		break;
	case 2094000: // Guon, brings party into Pirate PQ
		handle_npc_ppq_guon();
		break;
	case 2094002: // Guon2, handles pirate pq inside
		handle_npc_ppq_guon2();
		break;
	case 9103000: // Pietri, at Ludibrium Maze PQ room 16
		handle_npc_lmpq_pietri();
		break;
	case 9103001: // Rolly, brings party into Ludi Maze PQ
		handle_npc_lmpq_rolly();
		break;
	case 9103002: // Rolly2, warps out of Ludi Maze PQ
		handle_npc_lmpq_rolly2();
		break;
	case 9103003: // Rolly3, warps out of Ludi Maze PQ and gives rewards
		handle_npc_lmpq_rolly3();
		break;
	case 2042000: // Spiegelmann, warps into Carnival PQ
		handle_npc_cpq_spiegelmann();
		break;

		// boss npcs
	case 2041025: // Machine Apparatus, Origin of Clocktower(220080001)
		handle_papulatus_npc();
		break;
	case 2030010: // Amon @ Last Mission: Zakum's Altar
		handle_amon_zakum_npc();
		break;
	case 2030013: // Adobis @ El Nath: Entrance to Zakum Altar
		handle_adobis_zakum_npc();
		break;
	case 2081005: // Horntail entrance
		handle_horntail_entrance_npc();
		break;

		// misc npcs
	case 9201056: // NLC Taxi
		handle_nlc_taxi_npc();
		break;
	case 2012014: // Orbis Magic Spot
		handle_orbis_magic_spot_npc();
		break;
	case 2012015: // EL Nath Magic Spot
		handle_el_nath_magic_spot_npc();
		break;
	case 2040024: // First eos rock
		handle_first_eos_rock_npc();
		break;
	case 2040025: // Second eos rock
		handle_second_eos_rock_npc();
		break;
	case 2040026: // Third eos rock
		handle_third_eos_rock_npc();
		break;
	case 2040027: // Fourth eos rock
		handle_fourth_eos_rock_npc();
		break;
	case 2030000: // Jeff - El Nath : Ice Valley II (211040200)
		handle_jeff_npc();
		break;
	case 2010007: // Heracle guild creator
		handle_heracle_guild_creator_npc();
		break;
	case 2010008: // Lea guild emblem creator
		handle_lea_guild_emblem_npc();
		break;
	case 9900000: // KIN
		handle_kin_npc();
		break;
	case 9900001: // NimaKIN
		handle_nimakin_npc();
		break;

		// maple camp npcs
	case 2100: // Sera
		handle_npc_sera();
		break;

		// ship, subway and plane npcs
	case 1032008: // Ellinia Station Ticket Npc
		set_map(200000100);
		break;
	case 2012001: // Orbis Station<To Ellinia>
		set_map(101000300);
		break;
	case 2012013: // Orbis Station<Ludibrium>
		set_map(220000100);
		break;
	case 2041000: // Ludubrium Station<Orbis>
		set_map(200000100);
		break;
	case 2012006: // Orbis Platform Usher
		handle_orbis_platform_usher();
		break;
	case 9270038: // Changi Airport Shalon
		set_map(103000000);
		break;
	case 9270041: // Kerning City Irene
		set_map(540010000);
		break;
	case 1052007: // The Ticket Gate (Kerning)
		set_map(600010001);
		break;
	case 2102000: // Asesson (Ariant)
		set_map(200000100);
		break;
	case 2082001: // Tommie (Leafre)
		set_map(200000100);
		break;

		// misc npcs

	case 9000020: // Spinel
		handle_npc_spinel();
		break;
	case 9201022: // Thomas Swift
		set_map(680000000);
		break;

	default:
		break;
	}*/
}
