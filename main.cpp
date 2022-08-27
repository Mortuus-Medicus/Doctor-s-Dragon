int uni_num = 20;		//To število je število za koliko tailov gre v igralno polje
int uni_img_num = 11;	//To število je število slik za igro (èe se številka spremeni je potrebno tudi spremeniti število imen v Tile_reader-ju)

const int rarity = 1000;
const int ring = 1;
const int emerald = 50;
const int mining = 10;
const int kill_enemy = 100;

const int ATTACK_BASIC = 0x61;			//Osnovni napad (NUMPAD_1 - trenutno)

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;


double cas;
int x_player_pozicija = 1, y_player_pozicija = 1;

#include <time.h>
#include "graphics.h"
#include "Key_Board_Reader.h"
#include "Tile_Reader.h"
#include "non_playing_character.h"
#include "player.h"


double startfps = 0, endfps = 0;


void okno();
void room_loader();


bool map_select = 1;


int main()
{
    okno();
    while(!GetAsyncKeyState(0x20))
    {
        setcolor(COLOR(rand()%256,rand()%256,rand()%256 ));
        moveto((((uni_num*40)/2)-150), 120+((uni_num-10)*30));
        outtext("Use 'WASD' to move and 'NUMPAD_1' to mine!");
        moveto((((uni_num*40)/2)-110), 160+((uni_num-10)*30));
        outtext("Press 'SPACE' to start the game! ");
        swapbuffers();
        delay(25);
    }
    system("color 0a");
    srand(time(0));
    //uni_num = rand()%30+5;
    cout << "Loading: image_to_memory();" <<endl;
    image_to_memory();
    cout << "Loading: tile_draw();" <<endl;
    room_loader();
    cout << "Loading: player_reset();" <<endl;
    player_reset();
    tile_draw();
start:
    money = 0;
    player_health = (rand()%3-1)+5;
    npc_money=1;
    while(true)
    {
        time_t startfps = clock();
        //ZAÈETEK PROGRAMA
        clearviewport();

		if(GetAsyncKeyState(ARROW_UP))
		{
		npc_money+=10;
		}
		else if(GetAsyncKeyState(ARROW_DOWN))
		{
		npc_money-=10;
		}

        tile_draw();
        player();
        draw_npc();
        stats();
        swapbuffers();

        if(player_health <= 0)
        {
            break;
        }

        //KONEC PROGRAMA
        time_t endfps = clock();
        endfps = endfps - startfps;
        cas = endfps / (double) CLOCKS_PER_SEC;
        cas = 1 / cas;
        if(GetAsyncKeyState(0x1B))
            return EXIT_SUCCESS;
    }
    clearviewport();
    swapbuffers();
    clearviewport();
    swapbuffers();
    while(!GetAsyncKeyState(0x1B))
    {
        readimagefile("gameover_splashscreen.gif", 0, 0, uni_num*40, uni_num*30);
        swapbuffers();
        moveto((((uni_num*40)/2)-95), 320+((uni_num-10)*30));
        setcolor(COLOR(rand()%256,rand()%256,rand()%256 ));
        outtext("Press 'SPACE' to play again!");
        if(GetAsyncKeyState(0x20))
            goto start;
    }
    return EXIT_SUCCESS;
}


void okno()
{
    initwindow(uni_num*40, (uni_num+3)*30, "Doctor's Dragon 0.0.0.0", 0, 0);
    clearviewport();
    swapbuffers();
    clearviewport();
}

void room_loader()
{
    //uni_num = rand()%30+5;
    system("cls");
    cout << "Loading..." <<endl;

    cout << "Loading: tile_template();" <<endl;
    tile_template();

    cout << "Loading: room_generator();" <<endl;
    room_generator();

    /*cout << "Loading: gold_generator();" <<endl;
    gold_generator();*/

    cout << "Loading: preferences_npc();" <<endl;
    preferences_npc();

    cout << "Loading done!" <<endl;
}
