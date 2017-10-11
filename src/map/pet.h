// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _PET_H_
#define _PET_H_

#include "../common_old/cbasetypes.h"
#include "../common_old/mmo.h"

//#include "map.h"
#include "unit.h"
#include "status.h"

//fwd declaration
struct s_map_session_data;
enum e_sc_type : int16;

#define MAX_PET_DB	300
#define MAX_PETLOOT_SIZE	30

/// Pet DB
struct s_pet_db {
	short class_; ///< Monster ID
	char name[NAME_LENGTH], ///< AEGIS name
		jname[NAME_LENGTH]; ///< English name
	unsigned short itemID; ///< Lure ID
	unsigned short EggID; ///< Egg ID
	unsigned short AcceID; ///< Accessory ID
	unsigned short FoodID; ///< Food ID
	int fullness; ///< Amount of hunger decresed each hungry_delay interval
	int hungry_delay; ///< Hunger value decrease each x seconds
	int r_hungry; ///< Intimacy increased after feeding
	int r_full; ///< Intimacy reduced when over-fed
	int intimate; ///< Initial intimacy value
	int die; ///< Intimacy decreased when die
	int capture; ///< Capture success rate 1000 = 100%
	int speed; ///< Walk speed
	char s_perfor; ///< Special performance
	int talk_convert_class; ///< Disables pet talk (instead of talking they emote  with /!.) (?)
	int attack_rate; ///< Rate of which the pet will attack (requires at least pet_support_min_friendly intimacy).
	int defence_attack_rate; ///< Rate of which the pet will retaliate when master is being attacked (requires at least pet_support_min_friendly intimacy).
	int change_target_rate; ///< Rate of which the pet will change its attack target.
	struct s_script_code
		*pet_script, ///< Script since pet hatched
		*pet_loyal_script; ///< Script when pet is loyal
};
extern struct s_pet_db pet_db[MAX_PET_DB];

enum e_pet_itemtype : uint8 { PET_CLASS,PET_CATCH,PET_EGG,PET_EQUIP,PET_FOOD };

struct s_pet_recovery { //Stat recovery
	enum e_sc_type type;	//Status Change id
	unsigned short delay; //How long before curing (secs).
	int timer;
};

struct s_pet_bonus {
	unsigned short type; //bStr, bVit?
	unsigned short val;	//value
	unsigned short duration; //in seconds
	unsigned short delay;	//Time before re-effect the bonus in seconds
	int timer;
};

struct s_pet_skill_attack { //Attack Skill
	unsigned short id;
	unsigned short lv; // Skill level
	unsigned short damage; // Fixed damage value of petskillattack2
	unsigned short div_; //0 = Normal skill. >0 = Fixed damage (lv), fixed div_.
	unsigned short rate; //Base chance of skill ocurrance (10 = 10% of attacks)
	unsigned short bonusrate; //How being 100% loyal affects cast rate (10 = At 1000 intimacy->rate+10%
};

struct s_pet_skill_support { //Support Skill
	unsigned short id;
	unsigned short lv;
	unsigned short hp; //Max HP% for skill to trigger (50 -> 50% for Magnificat)
	unsigned short sp; //Max SP% for skill to trigger (100 = no check)
	unsigned short delay; //Time (secs) between being able to recast.
	int timer;
};

struct s_pet_loot {
	struct s_item *item;
	unsigned short count;
	unsigned short weight;
	unsigned short max;
};

struct s_pet_data {
	struct s_block_list bl;
	struct s_unit_data ud;
	struct s_view_data vd;
	struct s_pet pet;
	struct s_status_data status;
	struct s_mob_db *db;
	struct s_pet_db *petDB;
	int pet_hungry_timer;
	int target_id;
	struct {
		unsigned skillbonus : 1;
	} state;
	int move_fail_count;
	unsigned int next_walktime,last_thinktime;
	unsigned short rate_fix;	//Support rate as modified by intimacy (1000 = 100%) [Skotlex]

	struct s_pet_recovery* recovery;
	struct s_pet_bonus* bonus;
	struct s_pet_skill_attack* a_skill;
	struct s_pet_skill_support* s_skill;
	struct s_pet_loot* loot;

	int masterteleport_timer;
	struct s_map_session_data *master;
};



int pet_create_egg(struct s_map_session_data *sd, unsigned short item_id);
int pet_hungry_val(struct s_pet_data *pd);
void pet_set_intimate(struct s_pet_data *pd, int value);
int pet_target_check(struct s_pet_data *pd,struct s_block_list *bl,int type);
int pet_unlocktarget(struct s_pet_data *pd);
int pet_sc_check(struct s_map_session_data *sd, int type); //Skotlex
int search_petDB_index(int key,int type);
int pet_hungry_timer_delete(struct s_pet_data *pd);
int pet_data_init(struct s_map_session_data *sd, struct s_pet *pet);
int pet_birth_process(struct s_map_session_data *sd, struct s_pet *pet);
int pet_recv_petdata(uint32 account_id,struct s_pet *p,int flag);
int pet_select_egg(struct s_map_session_data *sd,short egg_index);
int pet_catch_process1(struct s_map_session_data *sd,int target_class);
int pet_catch_process2(struct s_map_session_data *sd,int target_id);
bool pet_get_egg(uint32 account_id, short pet_class, int pet_id);
int pet_menu(struct s_map_session_data *sd,int menunum);
int pet_change_name(struct s_map_session_data *sd,char *name);
int pet_change_name_ack(struct s_map_session_data *sd, char* name, int flag);
int pet_equipitem(struct s_map_session_data *sd,int index);
int pet_lootitem_drop(struct s_pet_data *pd,struct s_map_session_data *sd);
int pet_attackskill(struct s_pet_data *pd, int target_id);
int pet_skill_support_timer(int tid, unsigned int tick, int id, intptr_t data); // [Skotlex]
int pet_skill_bonus_timer(int tid, unsigned int tick, int id, intptr_t data); // [Valaris]
int pet_recovery_timer(int tid, unsigned int tick, int id, intptr_t data); // [Valaris]
int pet_heal_timer(int tid, unsigned int tick, int id, intptr_t data); // [Valaris]

#define pet_stop_walking(pd, type) unit_stop_walking(&(pd)->bl, type)
#define pet_stop_attack(pd) unit_stop_attack(&(pd)->bl)

void read_petdb(void);
void do_init_pet(void);
void do_final_pet(void);

#endif /* _PET_H_ */
