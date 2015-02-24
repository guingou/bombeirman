#include <SDL/SDL_image.h>
#include <assert.h>

#include <bomb.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>

struct bomb {
	int x, y;
	int birth;
	int state;
	int power;
	struct bomb* nxt_bomb;
};

struct bomb* bomb_init(int bomb_power){
	struct bomb* bomb = malloc(sizeof(*bomb));
	if (!bomb)
		error("Memory error");

	bomb->birth = SDL_GetTicks();
	bomb->state = 3;
	bomb->power = bomb_power;
	bomb->nxt_bomb = NULL;

	return bomb;
}

int bomb_get_power(struct bomb* bomb){
	return bomb->power;
}

struct bomb* bomb_bet_nxt_bomb(struct bomb* bomb){
	return bomb->nxt_bomb;
}

struct bomb* bomb_add(struct bomb* bomb, struct player* player){
	struct bomb* new_bomb = bomb_init(player_get_power(player));
	new_bomb->x = player_get_x(player);
	new_bomb->y = player_get_y(player);

	struct bomb* end_of_bomb = bomb;
	while (end_of_bomb->nxt_bomb != NULL)
		end_of_bomb = end_of_bomb->nxt_bomb;

	end_of_bomb->nxt_bomb = new_bomb;

	return bomb;
	//not finished
}
