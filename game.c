#include <gb/gb.h>
#include <gb/hardware.h>
#include "graphics/red.c"
#include "graphics/newTilesc.c"

void start_game();
void update_player();
void move_player_sprite(int direction, int reversed);
void walk(int direction);

UINT8 player_x, player_y;
UINT8 last_keys;

unsigned char bkgtilea[] = {0};
unsigned char bkgtileb[] = {2};


void main()
{
	start_game();

	while(1){

		update_player();

		last_keys = joypad();
		wait_vbl_done();
	}
}

void move_player_sprite(int direction, int reversed)
{
	// Function to move all 4 quadrants of sprite at the same time


	// TO DO:
	// WALKING ANIMATION
	// FUNCTIONALISE DIFFERENT ACTIONS FOR OTHER SPRITES

	int tile;

	for(tile=0;tile<4;tile++)
	{
		set_sprite_tile(tile,tile + direction);

		if (!reversed)
		{
			// i.e. don't flip the sprite
			set_sprite_prop(tile,get_sprite_prop(0) & ~S_FLIPX);
			move_sprite(0,player_x,player_y);
			move_sprite(1,player_x+8,player_y);
			move_sprite(2,player_x,player_y+8);
			move_sprite(3,player_x+8,player_y+8);
			} 
		else
		{
			set_sprite_prop(tile,S_FLIPX);
			move_sprite(0,player_x+8,player_y);
			move_sprite(1,player_x,player_y);
			move_sprite(2,player_x+8,player_y+8);
			move_sprite(3,player_x,player_y+8);
			}
	}

}


void walk(int direction) {
	// Slow because of delays, need to find a way around this
	
	int tile;
	int time = 100;
	delay(time);
	for(tile=0;tile<4;tile++)
		{
			set_sprite_tile(tile,tile + direction + 12);
		}
	delay(time);

}

void start_game()
{
	int i, j, k;
	int base = 75;

	DISPLAY_ON;
	NR52_REG = 0x8F;
	NR51_REG = 0x11;
	NR50_REG = 0x1F;

	player_x = 80;
	player_y = 80;

	SPRITES_8x8;

	set_sprite_data(0, 47, red_tile_data);
	move_player_sprite(0,0);

	SHOW_SPRITES;


	set_bkg_data(0,3,newTiles);

	// Box around the screen
	for(i=0 ; i<20 ; i++)
	 {
	 // top	
	 set_bkg_tiles(i,0,1,1,bkgtilea);    /*  x,y,w,h,tilenumber */
	 //left
	 set_bkg_tiles(0,i,1,1,bkgtilea);
	 //bottom
	 set_bkg_tiles(i,17,1,1,bkgtilea);
	 //right
	 set_bkg_tiles(19,i,1,1,bkgtilea);
	}

	// Interior
	for (k=1;k<17;k++){
		for (j=1;j<19;j++)
			{
				set_bkg_tiles(j,k,1,1,bkgtileb);
			}
	}

	SHOW_BKG;

}

void update_player()
{

	// UP
	if (joypad() & J_UP) {
	 		player_y--;
	 		move_player_sprite(4,0);
	 		walk(4);
			if (player_y == 15) {
				player_y = 16;
			}
	}

	// DOWN
	if (joypad() & J_DOWN) {
		player_y++;
		move_player_sprite(0,0);
		walk(0);
			if (player_y == 153) {
				player_y = 152;
			}
	}

	// LEFT
	if (joypad() & J_LEFT) {
		player_x--;
		move_player_sprite(8,0);
		walk(8);
			if (player_x == 7) {
				player_x = 8;
			}
	}

	// RIGHT
	if (joypad() & J_RIGHT) {
		player_x++;
		move_player_sprite(8,1);
		walk(8);
			if (player_x == 161) {
				player_x = 160;
			}
	}


}


