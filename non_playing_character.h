#ifndef NON_PLAYING_CHARACTER_H
#define NON_PLAYING_CHARACTER_H

#include "Tile_Reader.h"
#include <math.h>

int x_npc, y_npc;
int fade_npc;
double npc_money;
bool npc_move = false;

void preferences_npc()
{
    do {
        x_npc = rand()%(uni_num-2)+1;
        y_npc = rand()%(uni_num-2)+1;
    } while((map[x_npc][y_npc] == 1) ||
            (map[x_npc][y_npc] == 2) ||
            (map[x_npc][y_npc] == 3) ||
            (map[x_npc][y_npc] == 4) ||
            (map[x_npc][y_npc] == 5) ||
            (map[x_npc][y_npc] == 6) ||
            (map[x_npc][y_npc] == 7) ||
            (map[x_npc][y_npc] == 8) ||
            (map[x_npc][y_npc] == 9) ||
            ((x_npc == x_player_pozicija)&&(y_npc == y_player_pozicija)));
}

void draw_npc()
{
    draw_tile(tile_map_npc, 1, x_npc, y_npc);
	if((clock() - fade_npc) < 60000/npc_money)//(CLOCKS_PER_SEC*(2.0-exp(-npc_money/2.0)/2.0)))
        return;
    else
        npc_move=false;
    int vsi_premiki = 0;
    while((npc_move == false) && (vsi_premiki != 255))
    {
        int temp = rand()%8+1;
        switch (temp)
        {

        case 1:
        {
            if((map[x_npc][y_npc-1] == 0) || (map[x_npc][y_npc-1] == 3) || (map[x_npc][y_npc-1] == 9))
            {
                if(map[x_npc][y_npc-1] == 3)
                    npc_money+=ring;
                if(map[x_npc][y_npc-1] == 9)
                    npc_money+=emerald;
                y_npc--;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 1;
            }
            break;
        }
        case 2:
        {
            if((map[x_npc][y_npc+1] == 0) || (map[x_npc][y_npc+1] == 3) || (map[x_npc][y_npc+1] == 9))
            {
                if(map[x_npc][y_npc+1] == 3)
                    npc_money+=ring;
                if(map[x_npc][y_npc+1] == 9)
                    npc_money+=emerald;
                y_npc++;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 2;
            }
            break;
        }
        case 3:
        {
            if((map[x_npc-1][y_npc] == 0) || (map[x_npc-1][y_npc] == 3) || (map[x_npc-1][y_npc] == 9 ))
            {
                if(map[x_npc-1][y_npc] == 3)
                    npc_money+=ring;
                if(map[x_npc-1][y_npc] == 9)
                    npc_money+=emerald;
                x_npc--;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 4;
            }
            break;
        }
        case 4:
        {
            if((map[x_npc+1][y_npc] == 0) || (map[x_npc+1][y_npc] == 3) || (map[x_npc+1][y_npc] == 9))
            {
                if(map[x_npc+1][y_npc] == 3)
                    npc_money+=ring;
                if(map[x_npc+1][y_npc] == 9)
                    npc_money+=emerald;
                x_npc++;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 8;
            }
            break;
        }
        case 5:
        {
            if((map[x_npc+1][y_npc-1] == 0) || (map[x_npc+1][y_npc-1] == 3)  || (map[x_npc+1][y_npc-1] == 9))
            {
                if(map[x_npc+1][y_npc-1] == 3)
                    npc_money+=ring;
                if(map[x_npc+1][y_npc-1] == 9)
                    npc_money+=emerald;
                y_npc--;
                x_npc++;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 16;
            }
            break;
        }
        case 6:
        {
            if((map[x_npc-1][y_npc-1] == 0) || (map[x_npc-1][y_npc-1] == 3) || (map[x_npc-1][y_npc-1] == 9))
            {
                if(map[x_npc-1][y_npc-1] == 3)
                    npc_money+=ring;
                if(map[x_npc-1][y_npc-1] == 9)
                    npc_money+=emerald;
                y_npc--;
                x_npc--;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 32;
            }
            break;
        }
        case 7:
        {
            if((map[x_npc-1][y_npc+1] == 0) || (map[x_npc-1][y_npc+1] == 3) || (map[x_npc-1][y_npc+1] == 3))
            {
                if(map[x_npc-1][y_npc+1] == 3)
                    npc_money+=ring;
                if(map[x_npc-1][y_npc+1] == 9)
                    npc_money+=emerald;
                y_npc++;
                x_npc--;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 64;
            }
            break;
        }
        case 8:
        {
            if((map[x_npc+1][y_npc+1] == 0) || (map[x_npc+1][y_npc+1] == 3) || (map[x_npc+1][y_npc+1] == 9))
            {
                if(map[x_npc+1][y_npc+1] == 3)
                    npc_money+=ring;
                if(map[x_npc+1][y_npc+1] == 9)
                    npc_money+=emerald;
                y_npc++;
                x_npc++;
                npc_move = true;
                map[x_npc][y_npc] = 0;
            }
            else
            {
                npc_move = false;
                vsi_premiki = vsi_premiki | 128;
            }
        }
        }
        fade_npc = clock();
    }
}


#include "player.h"

#endif
