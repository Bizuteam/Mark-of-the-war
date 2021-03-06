#ifndef HEADER_H
#define HEADER_H
#define VITESSE 4
//Must be odd: 2k+1
#define MAP_SIZE (2*10+1)
#define SETS_ROW ((MAP_SIZE-1)/2)
#define SETS_NUMBER (SETS_ROW*SETS_ROW)
#define EDGES_DOUBLE_ROW (MAP_SIZE-2)
#define EDGES_NUMBER (2*SETS_NUMBER - 2*((MAP_SIZE-1)/2))
#define ROBOTS_NUMBER (MAP_SIZE/4)
#define CARDS_NUMBER ROBOTS_NUMBER

typedef struct player_struct {
	int x;
	int y;
	int direction;
	int lifes;
	int papers;
	int keys;
} Player;

typedef struct robot_struct {
	int x;
	int y;
	int direction;
	int rotation_direction;
	int alive;
} Robot;

typedef struct card_struct {
	int x;
	int y;
	int still_on_map;
} Card;

typedef struct exit_struct {
	int x;
	int y;
} Exit;

typedef struct game_struct {
	Player player;
	Robot robots[ROBOTS_NUMBER];
	Card cards[CARDS_NUMBER];
	int map[MAP_SIZE][MAP_SIZE];
	int quit_game;
	Exit exit;
}* Game;

#endif
