//     _     _                       _   
//    | |__ (_) __ _        ___ __ _| |_ 
//    | '_ \| |/ _` |_____ / __/ _` | __|
//    | |_) | | (_| |_____| (_| (_| | |_ 
//    |_.__/|_|\__, |      \___\__,_|\__|
//                |_|                      nya-nya software team.
//                                                    Dev:
//                                                       Catgirllover
//                                                    Artist:
//                                                       Catgirllover


#include <gb/gb.h>
#include "../tilesets-maps/wonderleafTileSet.c"
#include "../tilesets-maps/wonderleaf.c"
#include "../tilesets-maps/char.c"

void init();
void updateSwitches();
void checkinput();

UINT8 player[2];
UINT8 legWalkCheck = 0;
UINT8 directionCheck = 0;
UINT8 animationCheck = 0;
UINT8 animationCountDown = 10;

//_______________________________________
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//_______________________________________

void main()
{                                                                                                              
	init();
	
	while(1) 
    {
		updateSwitches();
		checkinput();
		CollisionCheck();
		wait_vbl_done();
	}
}

//_______________________________________
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//_______________________________________

void init()
{
	DISPLAY_ON;

	set_bkg_data(0, 23, wonderleafTileSet);
	set_bkg_tiles(0, 0, wonderleafWidth, wonderleafHeight, wonderleaf);

	set_sprite_data(0,30, mainchar);
	set_sprite_tile(0,0); // head
	set_sprite_tile(1,1); // body
	set_sprite_tile(2,4); // additional right hand
	set_sprite_tile(3,5); // additional left hand

	player[0] = 80;
	player[1] = 72;

}

//_______________________________________
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//_______________________________________

void updateSwitches()
{
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}

//_______________________________________
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//_______________________________________

void checkinput()
{
	//               compass
	//                /___\ 
	//             /  | 1 |  \ 
	//            /--/     \--\ 
	//            |  4     3  |
	//            \--\     /--/
	//             \  | 2 |  /
	//                \---/

	// UP
	if (joypad() & J_UP)
	{	
		player[1] = player[1] - 1/2;
		scroll_bkg(0,-1);
		directionCheck = 1;
		if (animationCheck == 0)
		{
			if (legWalkCheck == 0)
			{
				set_sprite_tile(0, 12);
				set_sprite_tile(1, 14);
				legWalkCheck = 1;
			}
			else
			{
				set_sprite_tile(0, 12);
				set_sprite_tile(1, 15);
				legWalkCheck = 0;
			}
			animationCheck = 1;
		}
		
	}

	// DOWN
	if (joypad() & J_DOWN) 
	{
		player[1] = player[1] + 1/2;
		scroll_bkg(0,1);
		directionCheck = 2;
		if (animationCheck == 0)
		{
			if (legWalkCheck == 0)
			{
				set_sprite_tile(0, 0);
				set_sprite_tile(1, 2);
				legWalkCheck = 1;
			}
			else
			{
				set_sprite_tile(0, 0);
				set_sprite_tile(1, 3);
				legWalkCheck = 0;
			}
			animationCheck = 1;
		}
		
	}

	// LEFT
	if (joypad() & J_LEFT) 
	{
		player[0] = player[0] - 1/2;
		scroll_bkg(-1,0);
		directionCheck = 4;
		if (animationCheck == 0)
		{
			if (legWalkCheck == 0)
			{
				set_sprite_tile(0, 9);
				set_sprite_tile(1, 11);
				legWalkCheck = 1;
			}
			else
			{
				set_sprite_tile(0, 9);
				set_sprite_tile(1, 10);
				legWalkCheck = 0;
			}
			animationCheck = 1;
		}
		
	}
	
	// RIGHT
	if (joypad() & J_RIGHT) 
	{
		player[0] = player[0] + 1/2;
		scroll_bkg(1,0);
		directionCheck = 3;
		if (animationCheck == 0)
		{
			if (legWalkCheck == 0)
			{
				set_sprite_tile(0, 6);
				set_sprite_tile(1, 7);
				legWalkCheck = 1;
			}
			else
			{
				set_sprite_tile(0, 6);
				set_sprite_tile(1, 8);
				legWalkCheck = 0;
			}
			animationCheck = 1;
		}
		
	}
//_______________________________________
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//_______________________________________

	move_sprite(0, player[0], player[1]);            // head
	move_sprite(1, player[0], player[1] + 8);        // body
	move_sprite(2, player[0] + 8, player[1] + 8);    // additional right hand
	move_sprite(3, player[0] - 8, player[1] + 8);    // additional left hand 
	if (directionCheck < 3)
	{
		set_sprite_tile(2, 4);
		set_sprite_tile(3, 5);
	}
	if (directionCheck > 2)
	{
		set_sprite_tile(2, 32);
		set_sprite_tile(3, 32);
	}
	if (animationCheck == 1)
	{
		animationCountDown = animationCountDown - 1;
	}
	if (animationCountDown == 0)
	{
		animationCountDown = 10;
		animationCheck = 0;

		switch (directionCheck)
		{
			case 1:
				set_sprite_tile(1, 13);
				break;
			case 2:
				set_sprite_tile(1, 1);
				break;
			case 3:
				set_sprite_tile(1, 7);
				break;
			case 4:
				set_sprite_tile(1, 10);
				break;

		}
	}
	

}
void CollisionCheck()
{ 
	if(player[0] > 64 && player[0] < 80)
	{
		player[0] = player[0] - 1;
	}
	if((player[1]+8) < 72 && (player[1]+8) > 88)
	{
		player[1] = player[0] + 1;
	}
}



