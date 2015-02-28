#include <SDL/SDL_image.h>
#include <assert.h>

#include <bomb.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <math.h>

struct bomb {
	int x, y;
	int birth;
	int state;
	int power;
	struct bomb* nxt_bomb;
};

struct bomb* bomb_init(){
	struct bomb* bomb = malloc(sizeof(*bomb));
	if (!bomb)
		error("Memory error");
	bomb->nxt_bomb = NULL;

	return bomb;
}
int bomb_get_x(struct bomb* bomb){
	return bomb->x;
}

int bomb_get_y(struct bomb* bomb){
	return bomb->y;
}

int bomb_get_birth(struct bomb* bomb){
	return bomb->birth;
}

int bomb_get_state(struct bomb* bomb){
	return bomb->state;
}

int bomb_get_power(struct bomb* bomb){
	return bomb->power;
}

struct bomb* bomb_get_nxt_bomb(struct bomb* bomb){
	return bomb->nxt_bomb;
}

void bomb_add(struct bomb* bomb, struct player* player){
	assert(bomb);
	assert(player);

	//Creation of the new bomb
	struct bomb* new_bomb = malloc(sizeof(*bomb));
	new_bomb->x = player_get_x(player);
	new_bomb->y = player_get_y(player);
	new_bomb->birth = SDL_GetTicks();
	new_bomb->state = 3;
	new_bomb->power = player_get_power(player);
	new_bomb->nxt_bomb = bomb;
	//not finished
}

void bomb_update (struct bomb* bomb){
	assert(bomb);
	while (bomb_get_nxt_bomb(bomb) != NULL){
		int age = floor((SDL_GetTicks() - bomb_get_birth(bomb))/1000);
		if (age <=4)
			bomb->state = 3 - age;
		bomb = bomb_get_nxt_bomb(bomb);
	}
};

void bomb_display(struct bomb* bomb, int x, int y){
	assert(bomb);
	while (bomb_get_x(bomb)!=x && bomb_get_y(bomb)!=y)
		bomb = bomb_get_nxt_bomb(bomb);
	window_display_image(sprite_get_bomb(bomb_get_state(bomb)), x*SIZE_BLOC, y*SIZE_BLOC);

};

