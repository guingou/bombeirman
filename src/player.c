#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <bomb.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>

struct player {
	int x, y;
	enum direction current_direction;
	int power;
	int nb_bomb;
};

struct player* player_init(int bomb_number) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_direction = SOUTH;
	player->nb_bomb = bomb_number;
	player->power = 1;

	return player;
}

void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->current_direction = way;
}

int player_get_power(struct player* player){
	assert(player);
	return player->power;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bomb;
}

void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bomb += 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bomb -= 1;
}

void player_set_bomb(struct player* player, struct map* map, struct bomb* bomb){
	assert(player);
	assert(map);
	assert(bomb);
	if (player_get_nb_bomb(player) > 0){
		int x = player_get_x(player);
		int y = player_get_y(player);
		map_set_cell_type(map, x, y, CELL_BOMB);
		bomb_add(bomb, player);
		player_dec_nb_bomb(player);
	}
}

void player_from_map(struct player* player, struct map* map) {
	assert(player);
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
		for (j = 0; j < map_get_height(map); j++) {
			if (map_get_cell_type(map, i, j) == CELL_PLAYER) {
				player->x = i;
				player->y = j;
			}
		}
	}
}

static int player_move_aux(struct player* player, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_CASE:
		return 1;
		break;

	case CELL_BONUS:
		break;

	case CELL_GOAL:
		break;

	case CELL_MONSTER:
		break;

	case CELL_PLAYER:
		return 0; //ADDED
		break;

	case CELL_BOMB: //ADDED
		return 0;
		break;

	default:
		break;
	}

	// Player has moved
	return 1;
}

int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
			if (map_get_cell_type(map, x, y-1)==CELL_CASE){
				if (map_is_inside(map, x, y-2) && map_get_cell_type(map, x, y-2)==CELL_EMPTY){
					player->y--;
					map_set_cell_type(map, x, y-2, CELL_CASE);
					move = 1;
				}
			}
			else{
				player->y--;
				move = 1;
			}
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			if (map_get_cell_type(map, x, y+1)==CELL_CASE){
				if (map_is_inside(map, x, y+2) && map_get_cell_type(map, x, y+2)==CELL_EMPTY){
					player->y++;
					map_set_cell_type(map, x, y+2, CELL_CASE);
					move = 1;
				}
			}
			else{
				player->y++;
				move = 1;
			}
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			if (map_get_cell_type(map, x-1, y)==CELL_CASE){
				if (map_is_inside(map, x-2, y) && map_get_cell_type(map, x-2, y)==CELL_EMPTY){
					player->x--;
					map_set_cell_type(map, x-2, y, CELL_CASE);
					move = 1;
				}
			}
			else{
				player->x--;
				move = 1;
			}
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)) {
			if (map_get_cell_type(map, x+1, y)==CELL_CASE){
				if (map_is_inside(map, x+2, y) && map_get_cell_type(map, x+2, y)==CELL_EMPTY){
					player->x++;
					map_set_cell_type(map, x+2, y, CELL_CASE);
					move = 1;
				}
			}
			else{
				player->x++;
				move = 1;
			}
		}
		break;
	}

	if (move) {
		if (map_get_cell_type(map, x, y) == CELL_BOMB)
			map_set_cell_type(map, player->x, player->y, CELL_PLAYER);
		else{
			map_set_cell_type(map, x, y, CELL_EMPTY);
			map_set_cell_type(map, player->x, player->y, CELL_PLAYER);
		}
	}
	return move;
}

void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction),
			player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}

