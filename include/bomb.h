#ifndef BOMB_H_
#define BOMB_H_

#include <map.h>
#include <player.h>
#include <constant.h>

struct bomb;
struct player;

struct bomb* bomb_init();
int bomb_get_x(struct bomb* bomb);
int bomb_get_y(struct bomb* bomb);
int bomb_get_birth(struct bomb* bomb);
int bomb_get_state(struct bomb* bomb);
int bomb_get_power(struct bomb* bomb);
struct bomb* bomb_get_nxt_bomb(struct bomb* bomb);
void bomb_add(struct bomb* bomb, struct player* player);
void bomb_update(struct bomb* bomb);
void bomb_display(struct bomb* bomb, int x, int y);
#endif /* BOMB_H_ */
