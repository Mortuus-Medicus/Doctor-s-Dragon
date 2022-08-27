#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "Tile_Reader.h"
#include "graphics.h"


int temp_x, temp_y, temp_facing;
int player_facing_1 = 1, player_facing_2;
double fade, fade1, fade2;

void room_loader();

double money = 0;
int player_health = 1;
void player()
{

    bool allowed, allowed1, allowed2;
    temp_x = x_player_pozicija;
    temp_y = y_player_pozicija;
    temp_facing = player_facing_1;



    if((clock() - fade) > (CLOCKS_PER_SEC/7))
    {
        allowed = true;
    }
    else
    {
        allowed = false;
    }

    if(allowed == true)
    {
        if(GetAsyncKeyState(0x57))
        {
            y_player_pozicija-=1;
            player_facing_1 = 1;
        }

        if(GetAsyncKeyState(0x53))
        {
            y_player_pozicija+=1;
            player_facing_1 = 2;
        }

        if(GetAsyncKeyState(0x41))
        {
            x_player_pozicija-=1;
            player_facing_1 = 3;
        }

        if(GetAsyncKeyState(0x44))
        {
            x_player_pozicija+=1;
            player_facing_1 = 4;
        }
        fade = clock();
    }



    if((map[x_player_pozicija][y_player_pozicija] == 1) ||
            (map[x_player_pozicija][y_player_pozicija] == 4) ||
            (map[x_player_pozicija][y_player_pozicija] == 5) ||
            (map[x_player_pozicija][y_player_pozicija] == 6) ||
            (map[x_player_pozicija][y_player_pozicija] == 7) ||
            (map[x_player_pozicija][y_player_pozicija] == 8))
    {
        x_player_pozicija = temp_x;
        y_player_pozicija = temp_y;
    }
    /*else
    {
    draw_tile(tile_map_env, map[temp_x][temp_y], temp_x, temp_y);
    }*/

    if((map[x_player_pozicija][y_player_pozicija] == 2)&& (x_player_pozicija == 0))
    {
        desna_stran = leva_stran;
        leva_stran = 0;
        spodnja_stran = 0;
        zgornja_stran = 0;
        room_loader();
        x_player_pozicija = uni_num-2;
        for(int i = 1; i < uni_img_num; i++) {
            if(map[x_player_pozicija][y_player_pozicija] == i)
                map[x_player_pozicija][y_player_pozicija] = 0;
        }
    }


    if((map[x_player_pozicija][y_player_pozicija] == 2)&& (x_player_pozicija == (uni_num-1)))
    {
        leva_stran = desna_stran;
        desna_stran = 0;
        spodnja_stran = 0;
        zgornja_stran = 0;
        room_loader();
        x_player_pozicija = 1;
        for(int i = 1; i < uni_img_num; i++) {
            if(map[x_player_pozicija][y_player_pozicija] == i)
                map[x_player_pozicija][y_player_pozicija] = 0;
        }
    }

    if((map[x_player_pozicija][y_player_pozicija] == 2)&& (y_player_pozicija == 0))
    {
        spodnja_stran = zgornja_stran;
        zgornja_stran = 0;
        leva_stran = 0;
        desna_stran = 0;
        room_loader();
        y_player_pozicija = uni_num-2;
        for(int i = 1; i < uni_img_num; i++) {
            if(map[x_player_pozicija][y_player_pozicija] == i)
                map[x_player_pozicija][y_player_pozicija] = 0;
        }
    }

    if((map[x_player_pozicija][y_player_pozicija] == 2)&& (y_player_pozicija == (uni_num-1) ))
    {
        zgornja_stran = spodnja_stran;
        spodnja_stran = 0;
        leva_stran = 0;
        desna_stran = 0;
        room_loader();
        y_player_pozicija = 1;
        for(int i = 1; i < uni_img_num; i++) {
            if(map[x_player_pozicija][y_player_pozicija] == i)
                map[x_player_pozicija][y_player_pozicija] = 0;
        }
    }

    if(map[x_player_pozicija][y_player_pozicija] == 3)
    {
        map[x_player_pozicija][y_player_pozicija] = 0; // Kako narediti to za nocja oziroma da ima npz collision z playerjom
        money+=ring;
    }

    if(map[x_player_pozicija][y_player_pozicija] == 9)
    {
        map[x_player_pozicija][y_player_pozicija] = 0; // Kako narediti to za nocja oziroma da ima npz collision z playerjom
        money+=emerald;
    }

    if((x_npc == x_player_pozicija) && (y_npc == y_player_pozicija))
    {
        preferences_npc();

        if((money <= 0))
        {
			
            money = 0;
            player_health--;
            Beep( 5000, 60 );
            Beep( 4000, 60 );
            Beep( 3000, 60 );
            Beep( 2000, 60 );
            Beep( 1000, 60 );
		}else{
            //money = money - (1-exp(-money/2));			//vpraðaj danijela, za boljše uravnavanje odbitka denarja ko se dotakneš npcja
			double temp_money = money;
            money -= rand()%(int)money+1;
			npc_money+=temp_money-money;
		}
    }

    draw_tile(tile_map_player, player_facing_1-1, x_player_pozicija, y_player_pozicija);

    int zamik_sprita [][2] =
    {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
    };
    if(GetAsyncKeyState(ATTACK_BASIC))
    {
        if(money >= mining)
            if(
                (map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 8)||
                (map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 7)||
                (map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 6)||
                (map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 5)||
                (map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 4)||
                ((x_player_pozicija+zamik_sprita[player_facing_1-1][0] == x_npc) && (y_player_pozicija+zamik_sprita[player_facing_1-1][1] == y_npc))
            )
                draw_tile (tile_map_attack, player_facing_1-1, x_player_pozicija+zamik_sprita[player_facing_1-1][0],
                           y_player_pozicija+zamik_sprita[player_facing_1-1][1]);


        if((clock() - fade1) > (CLOCKS_PER_SEC/3))
        {
            allowed1 = true;
        }
        else
        {
            allowed1 = false;
        }
        if(money >= mining) {
            if(allowed1 == true)
            {

                if(map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 8)
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 0;
                    money-=mining;
                }
                if(map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 7)
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 8;
                    money-=mining;
                }
                if(map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 6)
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 7;
                    money-=mining;
                }
                if(map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 5)
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 6;
                    money-=mining;
                }
                if(map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] == 4)
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 5;
                    money-=mining;
                }

                fade1 = clock();
            }
        }
        if((clock() - fade2) > (CLOCKS_PER_SEC/3))
        {
            allowed2 = true;
        }
        else
        {
            allowed2 = false;
        }
        if(money >= mining)
            if(allowed2 == true)
            {
                if((x_player_pozicija+zamik_sprita[player_facing_1-1][0] == x_npc) && (y_player_pozicija+zamik_sprita[player_facing_1-1][1] == y_npc))
                {
                    map[x_player_pozicija+zamik_sprita[player_facing_1-1][0]][y_player_pozicija+zamik_sprita[player_facing_1-1][1]] = 0;
                    money-=mining;
                    money+=kill_enemy;
                    x_npc = rand()%(uni_num-2)+1;
                    y_npc = rand()%(uni_num-2)+1;
                    if(npc_money > 0)
                        npc_money -= rand()%(int)npc_money+1;
                    else
                        npc_money = 0;
                }
                fade2 = clock();
            }
    }




}

string mymoney;
string myfps;
string npcmoney;
string npcspeed;

void stats()
{
    std::string;
    stringstream temp_money;
    stringstream temp_fps;
    stringstream temp_npcmoney;
    stringstream temp_npc_speed;

    temp_money << (int)money;
    mymoney=temp_money.str();

    temp_npcmoney << npc_money;
    npcmoney=temp_npcmoney.str();

    temp_fps << cas;
    myfps=temp_fps.str();

    temp_npc_speed << clock()-fade_npc;
    npcspeed=temp_npc_speed.str();

    setcolor(YELLOW);
    moveto(8, 300+((uni_num-10)*30));
    outtext("Money:  ");
    outtext((char*) mymoney.c_str());

    setcolor(YELLOW);
    moveto(202, 300+((uni_num-10)*30));
    outtext("NPC Money:  ");
    outtext((char*) npcmoney.c_str());

    setcolor(LIGHTRED);
    moveto(2, 340+((uni_num-10)*30));
    for(int i = 0; i < player_health; i++)
    {
        outtext(" <3 ");
    }

    setcolor(LIGHTGREEN);
    moveto(2, 370+((uni_num-10)*30));
    outtext("FPS:  ");
    outtext((char*) myfps.c_str());

    setcolor(LIGHTGREEN);
    moveto(202, 370+((uni_num-10)*30));
    outtext("Speed:  ");
    outtext((char*) npcspeed.c_str());
}

void player_reset()
{

    x_player_pozicija = (rand()%(uni_num-2))+1;
    y_player_pozicija = (rand()%(uni_num-2))+1;

    map[x_player_pozicija][y_player_pozicija] = 0;
}

#endif

