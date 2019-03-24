// Copyright 2019 Dave Moore
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include<iostream>

#include "libtcod.hpp"
#include "actor.hpp"
#include "map.hpp"
#include "engine.hpp"

Engine::Engine() : fovRadius(10), computeFov(true) {
	TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GREYSCALE);
	TCODConsole::initRoot(150, 81,"libtcod First Person demo", false);

    player = new Actor(40,25,'@',TCODColor::white, true);
    actors.push(player);
    map = new Map(80,45);
    setup_render();
    facing = 1;
    TCODSystem::setFps(30);
}

void Engine::render() {
	TCODConsole::root->clear();
	// draw the map
	render_3d();
	map->render();
	// draw the actors
	for (Actor **iterator=actors.begin();
	    iterator != actors.end(); iterator++) {
		Actor *actor=*iterator;
		if ( map->isInFov(actor->x,actor->y) ) {
	        actor->render();
	    }
	}
	std::string str;
	if (facing == 1) {
		 str = "Facing: North";
	} else if (facing == 2) {
		 str = "Facing: South";
	} else if (facing == 3) {
		 str = "Facing: West";
	} else if (facing == 4) {
		 str = "Facing: East";
	}

	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->print(2, 70, str);

	TCODConsole::root->setDefaultForeground(TCODColor::yellow);
	TCODConsole::root->print(2, 75, "Libtcod First Person Copyright (C) 2019 Dave Moore");

	TCODConsole::root->setDefaultForeground(TCODColor::orange);
	TCODConsole::root->print(2, 77, "davemoore22@gmail.com");

	TCODConsole::root->setDefaultForeground(TCODColor::red);
	TCODConsole::root->print(2, 79, "Code released under MIT License");

	TCODConsole::root->setDefaultForeground(TCODColor::silver);
	TCODConsole::root->print(70, 75, "Artwork by Clint Bellanger");

	TCODConsole::root->setDefaultForeground(TCODColor::cyan);
	TCODConsole::root->print(70, 77, "http://heroinedusk.com and http://clintbellanger.net");
	TCODConsole::root->print(70, 78, "https://opengameart.org/content/first-person-dungeon-crawl-art-pack");

	TCODConsole::root->setDefaultForeground(TCODColor::silver);
	std::string version = "Powered by Libtcod " + std::to_string(TCOD_MAJOR_VERSION) + "." +
		std::to_string(TCOD_MINOR_VERSION) + "." + std::to_string(TCOD_PATCHLEVEL);
	TCODConsole::root->print(70, 70, version);
}


void Engine:: setup_render()
{
    OffScreenConsole = new TCODConsole(160, 120);

    DungeonWalls = new TCODConsole(640, 240);
    DungeonFloor = new TCODConsole(640, 240);
    DungeonCeiling = new TCODConsole(640, 240);

    TCODImage* WallsImage = new TCODImage("dungeon_wall.png");
    TCODImage* FloorsImage = new TCODImage("dungeon_floor.png");
    TCODImage* CeilingImage = new TCODImage("dungeon_ceiling.png");

    WallsImage->blitRect(DungeonWalls, 0, 0);
    FloorsImage->blitRect(DungeonFloor, 0, 0);
    CeilingImage->blitRect(DungeonCeiling, 0, 0);
    DungeonWalls->setKeyColor(TCODColor::black);
    DungeonFloor->setKeyColor(TCODColor::black);
    DungeonCeiling->setKeyColor(TCODColor::black);
    OffScreenConsole->setKeyColor(TCODColor::black);

	width[0] = 80;
	height[0] = 120;
    src_x[0] = 0;
    src_y[0] = 0;
    dest_x[0] = 0;
    dest_y[0] = 0;

    width[1] = 80;
	height[1] = 120;
    src_x[1] = 80;
    src_y[1] = 0;
    dest_x[1] = 80;
    dest_y[1] = 0;

    width[2] = 80;
	height[2] = 120;
    src_x[2] = 160;
    src_y[2] = 0;
    dest_x[2] = 0;
    dest_y[2] = 0;

    width[3] = 80;
	height[3] = 120;
    src_x[3] = 240;
    src_y[3] = 0;
    dest_x[3] = 80;
    dest_y[3] = 0;

    width[4] = 160;
	height[4] = 120;
    src_x[4] = 320;
    src_y[4] = 0;
    dest_x[4] = 0;
    dest_y[4] = 0;

    width[5] = 80;
	height[5] = 120;
    src_x[5] = 480;
    src_y[5] = 0;
    dest_x[5] = 0;
    dest_y[5] = 0;

    width[6] = 80;
	height[6] = 120;
    src_x[6] = 560;
    src_y[6] = 0;
    dest_x[6] = 80;
    dest_y[6] = 0;

    width[7] = 80;
	height[7] = 120;
    src_x[7] = 0;
    src_y[7] = 120;
    dest_x[7] = 0;
    dest_y[7] = 0;

    width[8] = 80;
	height[8] = 120;
    src_x[8] = 80;
    src_y[8] = 120;
    dest_x[8] = 80;
    dest_y[8] = 0;

	width[9] = 160;
	height[9] = 120;
    src_x[9] = 160;
    src_y[9] = 120;
    dest_x[9] = 0;
    dest_y[9] = 0;

    width[10] = 80;
	height[10] = 120;
    src_x[10] = 320;
    src_y[10] = 120;
    dest_x[10] = 0;
    dest_y[10] = 0;

    width[11] = 80;
	height[11] = 120;
    src_x[11] = 400;
    src_y[11] = 120;
    dest_x[11] = 80;
    dest_y[11] = 0;

    width[12] = 160;
	height[12] = 120;
    src_x[12] = 480;
    src_y[12] = 120;
    dest_x[12] = 0;
    dest_y[12] = 0;
}

Engine::~Engine() {
    actors.clearAndDelete();
    delete map;

}

void Engine::update() {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
    switch(key.vk) {
    	// FORWARD
        case TCODK_UP:
        	// North
			if (facing == 1) {
				if (!map->isWall(player->x, player->y - 1)) {
					player->y--;
					computeFov=true;
				}
			}

			// South
			else if (facing == 2) {
				if (!map->isWall(player->x, player->y + 1)) {
					player->y++;
					computeFov=true;
				}


			// West
			} else if (facing == 3) {
				if (!map->isWall(player->x - 1, player->y)) {
					player->x--;
					computeFov=true;
				}


			// East
			} else if (facing == 4) {
				if (!map->isWall(player->x + 1, player->y)) {
					player->x++;
					computeFov=true;
				}
			}

        break;

        // BACKWARDS
        case TCODK_DOWN:

        	// North
			if (facing == 1) {
				if (!map->isWall(player->x, player->y + 1)) {
					player->y++;
					computeFov=true;
				}
			}

			// South
			else if (facing == 2) {
				if (!map->isWall(player->x, player->y - 1)) {
					player->y--;
					computeFov=true;
				}

			// West
			} else if (facing == 3) {
				if (!map->isWall(player->x + 1, player->y)) {
					player->x++;
					computeFov=true;
				}


			// East
			} else if (facing == 4) {
				if (!map->isWall(player->x - 1, player->y)) {
					player->x--;
					computeFov=true;
				}
			}
        break;
        case TCODK_LEFT :
        	if (facing == 1) {
				facing = 3;
        	} else if (facing == 2) {
				facing = 4;
        	} else if (facing == 3) {
				facing = 2;
			} else if (facing == 4) {
				facing = 1;
			}
        break;
        case TCODK_RIGHT:
        	if (facing == 1) {
				facing = 4;
        	} else if (facing == 2) {
				facing = 3;
        	} else if (facing == 3) {
				facing = 1;
			} else if (facing == 4) {
				facing = 2;
			}
        break;
        default:
        	break;
    }
    if ( computeFov ) {
	    map->computeFov();
	    computeFov=false;
	}
}


void Engine::render_3d()
{
	OffScreenConsole->clear();

	if (facing == 1) {
		// back row
		render_tile(player->x - 2, player->y - 2, 0);
		render_tile(player->x + 2, player->y - 2, 1);
		render_tile(player->x - 1, player->y - 2, 2);
		render_tile(player->x + 1, player->y - 2, 3);
		render_tile(player->x,     player->y - 2, 4);
		// middle row
		render_tile(player->x - 2, player->y - 1, 5);
		render_tile(player->x + 2, player->y - 1 ,6);
		render_tile(player->x - 1, player->y - 1, 7);
		render_tile(player->x + 1, player->y - 1, 8);
		render_tile(player->x,     player->y - 1, 9);
		// front row
		render_tile(player->x - 1, player->y,     10);
		render_tile(player->x + 1, player->y,     11);
		render_tile(player->x,     player->y,     12);
	} else if (facing == 2) {
		// back row
		render_tile(player->x + 2, player->y + 2, 0);
		render_tile(player->x - 2, player->y + 2, 1);
		render_tile(player->x + 1, player->y + 2, 2);
		render_tile(player->x - 1, player->y + 2, 3);
		render_tile(player->x,     player->y + 2, 4);
		// middle row
		render_tile(player->x + 2, player->y + 1, 5);
		render_tile(player->x - 2, player->y + 1, 6);
		render_tile(player->x + 1, player->y + 1, 7);
		render_tile(player->x - 1, player->y + 1, 8);
		render_tile(player->x,     player->y + 1, 9);
		// front row
		render_tile(player->x + 1, player->y,     10);
		render_tile(player->x - 1, player->y,     11);
		render_tile(player->x,     player->y,     12);
	} else if (facing == 3) {
		// back row
		render_tile(player->x - 2, player->y + 2, 0);
		render_tile(player->x - 2, player->y - 2, 1);
		render_tile(player->x - 2, player->y + 1, 2);
		render_tile(player->x - 2, player->y - 1, 3);
		render_tile(player->x - 2, player->y,     4);
		// middle row
		render_tile(player->x - 1, player->y + 2, 5);
		render_tile(player->x - 1, player->y - 2, 6);
		render_tile(player->x - 1, player->y + 1, 7);
		render_tile(player->x - 1, player->y - 1, 8);
		render_tile(player->x - 1, player->y,     9);
		// front row
		render_tile(player->x,     player->y + 1, 10);
		render_tile(player->x,     player->y - 1, 11);
		render_tile(player->x,     player->y,     12);
	} else if (facing == 4) {
		// back row
		render_tile(player->x + 2, player->y - 2, 0);
		render_tile(player->x + 2, player->y + 2, 1);
		render_tile(player->x + 2, player->y - 1, 2);
		render_tile(player->x + 2, player->y + 1, 3);
		render_tile(player->x + 2, player->y,     4);
		// middle row
		render_tile(player->x + 1, player->y - 2, 5);
		render_tile(player->x + 1, player->y + 2, 6);
		render_tile(player->x + 1, player->y - 1, 7);
		render_tile(player->x + 1, player->y + 1, 8);
		render_tile(player->x + 1, player->y,     9);
		// front row
		render_tile(player->x,     player->y - 1, 10);
		render_tile(player->x,     player->y + 1, 11);
		render_tile(player->x,     player->y,     12);
	}

	TCODImage *image_to_render = new TCODImage(OffScreenConsole);
	image_to_render->scale(160, 120);
	image_to_render->blit2x(TCODConsole::root, 1, 1);
}


void Engine::render_tile(int pos_x, int pos_y, int position)
{
	// If inbounds
	if ((pos_x > 0) && (pos_y > 0) && (pos_x <= 80) && (pos_y <= 45)) {

		// If we have a wall
        if (map->isWall(pos_x, pos_y)) {

			// Use the offsets to copy part of the background image
			TCODConsole::blit(DungeonWalls, src_x[position], src_y[position],
				width[position], height[position], OffScreenConsole, dest_x[position],
				dest_y[position]);
        } else {

			TCODConsole::blit(DungeonFloor, src_x[position], src_y[position],
				width[position], height[position], OffScreenConsole, dest_x[position],
				dest_y[position]);
			TCODConsole::blit(DungeonCeiling, src_x[position], src_y[position],
				width[position], height[position], OffScreenConsole, dest_x[position],
				dest_y[position]);
        }
	} else {
		TCODConsole::blit(DungeonWalls, src_x[position], src_y[position],
			width[position], height[position], OffScreenConsole, dest_x[position],
			dest_y[position]);
	}
}

