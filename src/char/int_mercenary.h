// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _INT_MERCENARY_SQL_H_
#define _INT_MERCENARY_SQL_H_

#ifdef __cplusplus
extern "C" {
#endif

struct s_mercenary;

int inter_mercenary_sql_init(void);
void inter_mercenary_sql_final(void);
int inter_mercenary_parse_frommap(int fd);

// Mercenary Owner Database
bool mercenary_owner_fromsql(uint32 char_id, struct mmo_charstatus* status);
bool mercenary_owner_tosql(uint32 char_id, struct mmo_charstatus* status);
bool mercenary_owner_delete(uint32 char_id);

bool mapif_mercenary_delete(int merc_id);

#ifdef __cplusplus
}
#endif

#endif /* _INT_MERCENARY_SQL_H_ */
