#ifndef BOMB_H_
#define BOMB_H_

#include <map.h>
#include <player.h>
#include <constant.h>

struct bomb;

int bomb_get_power(struct bomb* bomb);
struct bomb* bomb_get_nxt_bomb(struct bomb* bomb);
struct bomb* bomb_add(struct bomb* bomb, struct player* player);

#endif /* BOMB_H_ */
