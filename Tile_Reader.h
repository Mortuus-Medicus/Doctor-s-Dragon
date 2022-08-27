#ifndef TILE_READER_H
#define TILE_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>


vector<vector<int> > map;
vector<void*>tile_map_env;
vector<void*>tile_map_player;
vector<void*>tile_map_attack;
vector<void*>tile_map_npc;

int x_creator = 0, y_creator = 0, z_creator = 0;
int x_pozicija = 0, y_pozicija = 0;
int leva_stran = 0, desna_stran = 0, zgornja_stran = 0, spodnja_stran = 0;


void draw_tile(vector<void*>&tiles, int tile_num, int x, int y)
{
    putimage(40*x, 30*y, tiles[tile_num*2+1], AND_PUT);
    putimage(40*x, 30*y, tiles[tile_num*2], OR_PUT);
    //readimagefile(tile, (40*x), (30*y), (40*x+40), (30*y+30));
}

void tile_template()
{
    map = vector<vector<int> >(uni_num,vector<int>(uni_num, 0));

//map = vector<vector<int> >(10,vector<int>(10, 0)); //zbriši za delovanje room generatorja

    /*
    map[0][0] = 1;	//tukaj
    map[1][0] = 1;
    map[2][0] = 1;
    map[3][0] = 1;
    map[4][0] = 1;
    map[5][0] = 1;
    map[6][0] = 1;
    map[7][0] = 1;
    map[8][0] = 1;
    map[9][0] = 1;	//tukaj
    map[0][1] = 1;
    map[9][1] = 1;
    map[0][2] = 1;
    map[9][2] = 1;
    map[0][3] = 1;
    map[9][3] = 1;
    map[0][4] = 1;
    map[9][4] = 1;
    map[0][5] = 1;
    map[9][5] = 1;
    map[0][6] = 1;
    map[9][6] = 1;
    map[0][7] = 1;
    map[9][7] = 1;
    map[0][8] = 1;
    map[9][8] = 1;
    map[0][9] = 1;	//tukaj
    map[1][9] = 1;
    map[2][9] = 1;
    map[3][9] = 1;
    map[4][9] = 1;
    map[5][9] = 1;
    map[6][9] = 1;
    map[7][9] = 1;
    map[8][9] = 1;
    map[9][9] = 1;	//tukaj
    */

    for(int i = 0; i < uni_num; i++)
    {
        map[i][0] = 1;
    }

    for(int i = 0; i < uni_num; i++)
    {
        map[0][i] = 1;
    }

    for(int i = 0; i < uni_num; i++)
    {
        map[i][uni_num-1] = 1;
    }

    for(int i = 0; i < uni_num; i++)
    {
        map[uni_num-1][i] = 1;
    }


    x_creator = 1;
    y_creator = 0;


    if(spodnja_stran != 0)
    {
        map[spodnja_stran][uni_num-1] = 2;
    } else {
        while(spodnja_stran == 0) {
            spodnja_stran = rand()%(uni_num-2)+1;
            map[spodnja_stran][uni_num-1] = 2;
        }
    }

    x_creator = 1;
    y_creator = 0;

    if(zgornja_stran != 0)
    {
        map[zgornja_stran][0] = 2;
    } else {
        while(zgornja_stran == 0) {
            zgornja_stran = rand()%(uni_num-2)+1;
            map[zgornja_stran][0] = 2;
        }
    }

    x_creator = 0;
    y_creator = 1;

    if(leva_stran != 0)
    {
        map[0][leva_stran] = 2;
    } else {
        while(leva_stran == 0) {
            leva_stran = rand()%(uni_num-2)+1;
            map[0][leva_stran] = 2;
        }
    }

    x_creator = 0;
    y_creator = 1;

    if(desna_stran != 0)
    {
        map[uni_num-1][desna_stran] = 2;
    } else {
        while(desna_stran == 0) {
            desna_stran = rand()%(uni_num-2)+1;
            map[uni_num-1][desna_stran] = 2;
        }
    }

}

void gold_generator()
{

    for(int y_creator = 1; y_creator < uni_num-1; y_creator++)
    {
        for(int x_creator = 1; x_creator < uni_num-1; x_creator++)
        {
            if(map[x_creator][y_creator] != 4 ||
                    map[x_creator][y_creator] != 5 ||
                    map[x_creator][y_creator] != 6 ||
                    map[x_creator][y_creator] != 7 ||
                    map[x_creator][y_creator] != 8)
            {
                int selector = rand()%999+1;

                if((selector < (rarity/ ((rand()%999)+1))) && (selector > 0))
                {
                    map[x_creator][y_creator] = 9;
                }
            }
        }
    }
}

void room_generator()
{
    int x_counter, y_counter, z_coumter;
    int counter = 0;
    int counter1 = 0;
    int creating = 0;
    int door_counter;
    int single_side_door;

    for(int y_creator = 1; y_creator < uni_num-1; y_creator++)
    {
        for(int x_creator = 1; x_creator < uni_num-1; x_creator++)
        {
            /*
            map[x_creator][y_creator] = rand()%uni_img_num;
            while((map[x_creator][y_creator] == 2) ||			//Door
            	  (map[x_creator][y_creator] == 1) ||			//Void
            	  (map[x_creator][y_creator] == 9) ||			//Emerald
            	  (map[x_creator][y_creator] == 3))				//Ring
            	map[x_creator][y_creator] = rand()%(uni_img_num-1);
            	*/
            int tile_gen_selector = rand()%uni_img_num;

            //RARITY SISTEM  //----WIP
            int selector = (rand()%rarity)+1;
            switch(tile_gen_selector)
            {

            case 3:
            {
                if((selector < (rarity/(rand()%10+1))) && (selector > 0))
                {
                    map[x_creator][y_creator] = 3;
                }
                break;
            }

            case 4:
            {
                if((selector < (rarity/1.3)) && (selector > 0))
                {
                    map[x_creator][y_creator] = 4;
                }
                break;
            }

            case 5:
            {
                if((selector < (rarity/1.3)) && (selector > 0))
                {
                    map[x_creator][y_creator] = 5;
                }
                break;
            }

            case 6:
            {
                if((selector < (rarity/1.3)) && (selector > 0))
                {
                    map[x_creator][y_creator] = 6;
                }
                break;
            }

            case 7:
            {
                if((selector < (rarity/1.3)) && (selector > 0))
                {
                    map[x_creator][y_creator] = 7;
                }
                break;
            }

            case 8:
            {
                if((selector < (rarity/1.3)) && (selector > 0))
                {
                    map[x_creator][y_creator] = 8;
                }
                break;
            }

            case 9:
            {
                if((selector < (rarity/(rand()%100+1))) && (selector > 0))
                {
                    map[x_creator][y_creator] = 9;
                }
                break;
            }

            case 10:
            {
                if((selector < (rarity/(rand()%5+1))) && (selector > 0))
                {
                    map[x_creator][y_creator] = 10;
                }
                break;
            }


            default:
            {
                map[x_creator][y_creator] = 0;
            }
            }
        }
    }


    /*
    while(counter != 10)
    	{
    	map[x_creator][y_creator] = rand()%2+1;
    		if((map[x_creator][y_creator] == 2) && (zgornja_stran == 0))
    		{
    		door_counter++;
    		zgornja_stran = x_creator;
    		}
    		else
    		{
    		map[x_creator][y_creator] = 1;
    		}
    	x_creator++;
    	counter++;
    	}
    x_creator = 0;
    counter = 0;

    y_creator++;


    while(counter1 != 7)
    {
    		map[x_creator][y_creator] = rand()%1+1;
    	if((map[x_creator][y_creator] == 2) && (leva_stran == 0))
    		{
    		door_counter++;
    		leva_stran = x_creator;
    		}
    	else
    		{
    		map[x_creator][y_creator] = 1;
    		}

    	while(counter != 7)
    		{
    		map[x_creator][y_creator] = rand()%9;
    		while(map[x_creator][y_creator] == 2)
    		{
    		map[x_creator][y_creator] = rand()%9;
    		}
    		x_creator++;
    		counter++;
    		}
    		map[x_creator][y_creator] = rand()%1+1;
    	if((map[x_creator][y_creator] == 2) && (desna_stran == 0))
    		{
    		door_counter++;
    		desna_stran = x_creator;
    		}
    		else
    		{
    		map[x_creator][y_creator] = 1;
    		}
    	x_creator = 0;
    	counter1++;
    	y_creator++;
    	}
    	counter = 0;
    	while(counter != 9)
    	{
    	map[x_creator][y_creator] = rand()%1+1;
    		if((map[x_creator][y_creator] == 2) && (spodnja_stran == 0))
    		{
    		door_counter++;
    		spodnja_stran = x_creator;
    		}
    		else
    		{
    		map[x_creator][y_creator] = 1;
    		}
    	x_creator = 0;
    	x_creator++;
    	counter++;
    	}	*/
}

void tile_reader(int x_map, int y_map)
{
    if(map.size() != 0)
        return;

    int visina_okna = 400;          //x - 10tile; y - 10tile

    char c;
    ifstream is;            //Danijel naj definira
    ofstream save;          //Danijel naj definira



    if((x_map == 0) && (y_map == 0))
    {
        is.open("tile_map_0.txt");
    }

    map = vector<vector<int> >(10,vector<int>(10, 0));

    while(is.good())
    {
        if(x_pozicija > uni_num-1)
        {
            x_pozicija = 0;
            y_pozicija++;
        }
        if(y_pozicija > uni_num-1)
        {
            y_pozicija = 0;
        }
//cout << "X_P >>" << x_pozicija << endl;
//cout << "Y_P >>" << y_pozicija << endl;



        c = is.get();
        if(!is.good())
            break;
        map [x_pozicija][y_pozicija] = c;
        draw_tile(tile_map_env, c, x_pozicija, y_pozicija);//, (1*(1*x_pozicija)), (1*(1*y_pozicija)), (40*x_pozicija)), (30*y_pozicija));
        x_pozicija++;
    }
    is.close();
}

void tile_draw()
{
    using std::string;

    for(int x_pozicija = 0; x_pozicija < map.size(); x_pozicija++) {
        for(int y_pozicija = 0; y_pozicija < map[x_pozicija].size(); y_pozicija++) {
            draw_tile(tile_map_env, map[x_pozicija][y_pozicija], x_pozicija, y_pozicija);//, (1*(1*x_pozicija)), (1*(1*y_pozicija)), (40*x_pozicija)), (30*y_pozicija));

        }
    }
}


void image_to_memory()
{
    int x, y;

    const string tiles[]=
    {
        "textures\\environment\\env_stone_brick_ground_incy.gif",		//0
        "textures\\environment\\env_nullvoid.gif",						//1
        "textures\\environment\\env_door_fantasy_incy.gif",				//2
        "textures\\environment\\env_money_ring.gif",					//3
        "textures\\environment\\env_stone_wall_incy_0.gif",				//4
        "textures\\environment\\env_stone_wall_incy_1.gif",				//5
        "textures\\environment\\env_stone_wall_incy_2.gif",				//6
        "textures\\environment\\env_stone_wall_incy_3.gif",				//7
        "textures\\environment\\env_stone_wall_incy_4.gif",				//8
        "textures\\environment\\env_emerald.gif",						//9
        "textures\\environment\\env_stone_brick_ground_incy.gif",		//10
    };

    const string sprite[]=
    {
        "textures\\sprite\\player\\sprite_player_W.gif",		//0
        "textures\\sprite\\player\\sprite_player_S.gif",		//1
        "textures\\sprite\\player\\sprite_player_A.gif",		//2
        "textures\\sprite\\player\\sprite_player_D.gif",		//3
        "textures\\sprite\\player\\sprite_player.gif",			//4
        "textures\\sprite\\player\\sprite_player.gif",			//5
        "textures\\sprite\\player\\sprite_player.gif",			//6
        "textures\\sprite\\player\\sprite_player.gif",			//7
        "textures\\sprite\\player\\sprite_player.gif",			//8
        "textures\\sprite\\player\\sprite_player.gif",			//9
    };

    const string attack[]=
    {
        "textures\\sprite\\attack\\sprite_player_attack_W.gif",		//0
        "textures\\sprite\\attack\\sprite_player_attack_S.gif",		//1
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//2
        "textures\\sprite\\attack\\sprite_player_attack_D.gif",		//3
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//4
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//5
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//6
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//7
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//8
        "textures\\sprite\\attack\\sprite_player_attack_A.gif",		//9
    };

    const string npc[]=
    {
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
        "textures\\sprite\\npc\\sprite_mob_1.gif",
    };
    for(int i = 0; i < uni_img_num; i++)
    {
        readimagefile(tiles[i].c_str(), 0, 0, 40, 30);
        int velikost_tila = imagesize(0, 0, 40, 30);			//left - x, top - y, right - x, bottom - y
        tile_map_env.push_back(new char[velikost_tila]);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(0,0,0));
            }
        }
        getimage(0, 0, 40, 30, tile_map_env[tile_map_env.size()-1]);		//shraniš sprite
        readimagefile(tiles[i].c_str(), 0, 0, 40, 30);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(255,255,255));
            }
        }
        tile_map_env.push_back(new char[velikost_tila]);
        getimage(0, 0, 40, 30, tile_map_env[tile_map_env.size()-1]);
        clearviewport();
    }

    for(int i = 0; i < uni_img_num; i++)
    {
        readimagefile(sprite[i].c_str(), 0, 0, 40, 30);
        int velikost_tila = imagesize(0, 0, 40, 30);			//left - x, top - y, right - x, bottom - y
        tile_map_player.push_back(new char[velikost_tila]);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(0,0,0));
            }
        }
        getimage(0, 0, 40, 30, tile_map_player[tile_map_player.size()-1]);		//shraniš sprite
        readimagefile(sprite[i].c_str(), 0, 0, 40, 30);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                {
                    putpixel(x, y, COLOR(255,255,255));
                }
                else
                {
                    putpixel(x, y, COLOR(0,0,0));
                }
            }
        }
        tile_map_player.push_back(new char[velikost_tila]);
        getimage(0, 0, 40, 30, tile_map_player[tile_map_player.size()-1]);
        clearviewport();
    }

    for(int i = 0; i < uni_img_num; i++)
    {
        readimagefile(attack[i].c_str(), 0, 0, 40, 30);
        int velikost_tila = imagesize(0, 0, 40, 30);			//left - x, top - y, right - x, bottom - y
        tile_map_attack.push_back(new char[velikost_tila]);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(0,0,0));
            }
        }
        getimage(0, 0, 40, 30, tile_map_attack[tile_map_attack.size()-1]);		//shraniš sprite
        readimagefile(attack[i].c_str(), 0, 0, 40, 30);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(255,255,255));
            }
        }
        tile_map_attack.push_back(new char[velikost_tila]);
        getimage(0, 0, 40, 30, tile_map_attack[tile_map_attack.size()-1]);
        clearviewport();
    }
    for(int i = 0; i < uni_img_num; i++)
    {
        readimagefile(npc[i].c_str(), 0, 0, 40, 30);
        int velikost_tila = imagesize(0, 0, 40, 30);			//left - x, top - y, right - x, bottom - y
        tile_map_npc.push_back(new char[velikost_tila]);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(0,0,0));
            }
        }
        getimage(0, 0, 40, 30, tile_map_npc[tile_map_npc.size()-1]);		//shraniš sprite
        readimagefile(npc[i].c_str(), 0, 0, 40, 30);
        for(y = 0; y <= 30; y++)
        {
            for(x = 0; x <= 40; x++)
            {
                if(getpixel(x, y) == COLOR(255,0 ,255))
                    putpixel(x, y, COLOR(255,255,255));
            }
        }
        tile_map_npc.push_back(new char[velikost_tila]);
        getimage(0, 0, 40, 30, tile_map_npc[tile_map_npc.size()-1]);
        clearviewport();
    }

}

#endif
