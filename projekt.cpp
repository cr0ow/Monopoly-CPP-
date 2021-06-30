#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include "headers.h"

int main()
{
    system("mode con:cols=135 lines=40");
    srand(time(NULL));
    int num_players = 4;
    int active_player = 3, test_player = 0;
    int position;
    int jackpot = 0;
    int turn = 0;
    int i, sum;
    int temp;

    Player* player1 = new Player(1);
    Player* player2 = new Player(*player1);
    Player* player3 = new Player(*player2);
    Player* player4 = new Player(*player3);
    Player* players[4] = { player1, player2, player3, player4 };

    Neutral neutral;
    Chance chance;

    Special* special1 = new Special(13,"Power station");
    Special* special2 = new Special(29,"Waterworks");

    int r[4] = { 50,100,200,400 };
    Railway* railway1 = new Railway(6, "Southern railway", r);
    Railway* railway2 = new Railway(16, "Eastern railway", r);
    Railway* railway3 = new Railway(26, "Northern railway", r);
    Railway* railway4 = new Railway(36, "Western railway", r);

    int p[6] = { 10,40,120,360,640,900 };
    City* city1 = new City(2, "Thessaloniki", 120, 100, p, "Greece");
    City* city2 = new City(4, "Athens", 120, 100, p, "Greece");
    fill_array(p, 15, 60, 180, 540, 800, 1100);
    City* city3 = new City(7, "Naples", 200, 100, p, "Italy");
    City* city4 = new City(9, "Milan", 200, 100, p, "Italy");
    fill_array(p, 20, 80, 200, 600, 900, 1200);
    City* city5 = new City(10, "Roma", 240, 100, p, "Italy");
    fill_array(p, 20, 100, 300, 900, 1250, 1500);
    City* city6 = new City(12, "Barcelona", 280, 200, p, "Spain");
    City* city7 = new City(14, "Sevilla", 280, 200, p, "Spain");
    fill_array(p, 25, 120, 360, 1000, 1400, 1800);
    City* city8 = new City(15, "Madrid", 320, 200, p, "Spain");
    fill_array(p, 30, 140, 400, 1100, 1500, 1900);
    City* city9 = new City(17, "Liverpool", 360, 200, p, "England");
    City* city10 = new City(19, "Glasgow", 360, 200, p, "England");
    fill_array(p, 35, 160, 440, 1200, 1600, 2000);
    City* city11 = new City(20,"London", 400, 200, p, "England");
    fill_array(p, 35, 180, 500, 1400, 1750, 2100);
    City* city12 = new City(22, "Rotterdam", 440, 300, p, "Benelux");
    City* city13 = new City(24, "Brussels", 440, 300, p, "Benelux");
    fill_array(p, 40, 200, 600, 1500, 1850, 2200);
    City* city14 = new City(25,"Amsterdam", 480, 300, p, "Benelux");
    fill_array(p, 45, 220, 660, 1600, 1950, 2300);
    City* city15 = new City(27, "Malmo", 520, 300, p, "Sweden");
    City* city16 = new City(28, "Gotteborg", 520, 300, p, "Sweden");
    fill_array(p, 50, 240, 720, 1700, 2050, 2400);
    City* city17 = new City(30, "Stockholm", 560, 300, p, "Sweden");
    fill_array(p, 55, 260, 780, 1900, 220, 2550);
    City* city18 = new City(32, "Frankfurt", 600, 400, p, "RFN");
    City* city19 = new City(33, "Cologne", 600, 400, p, "RFN");
    fill_array(p, 60, 300, 900, 2000, 2400, 2800);
    City* city20 = new City(35, "Bonn", 640, 400, p, "RFN");
    fill_array(p, 70, 350, 1000, 2200, 2600, 3000);
    City* city21 = new City(38, "Innsbruck", 700, 400, p, "Austria");
    fill_array(p, 100, 400, 1200, 2800, 3400, 4000);
    City* city22 = new City(40, "Vienna", 800, 400, p, "Austria");
    City* cities[22] = { city1, city2, city3, city4, city5, city6, city7, city8, city9, city10, city11, city12,
    city13, city14, city15, city16, city17, city18, city19, city20, city21, city22 };

    while (num_players > 1) //end-of-game condition
    {
        system("cls");
        turns_in_jail(players,turn);
        //switching players
        do 
        {
            if (test_player == -1) active_player = (active_player + 1) % 4;
            if (active_player == 3) test_player = next_player(players, 0, num_players);
            else test_player = next_player(players, active_player + 1, num_players);
        }  while (test_player == -1);
        active_player = test_player;

        //choosing an action
        draw_board(players, cities, num_players, active_player, jackpot);
        while (choose() == 2)
        {
            players[active_player]->buy_buildings();
            system("cls");
            draw_board(players, cities, num_players, active_player, jackpot);
        }
        sum = players[active_player]->move();
        system("cls");
        draw_board(players, cities, num_players, active_player, jackpot);
        position = players[active_player]->get_position();
        Sleep(1000);

        //checking field and taking an action
        if (position == 1 || position == 5 || position == 11 || position == 21 || position == 31 || position == 39)
        {
            neutral.at_visit(players[active_player], &jackpot, position);
        }
        else if (position == 6) railway1->at_visit(players[active_player], 0);
        else if (position == 16) railway2->at_visit(players[active_player], 0);
        else if (position == 26) railway3->at_visit(players[active_player], 0);
        else if (position == 36) railway4->at_visit(players[active_player], 0);
        else if (position == 3 || position == 8 || position == 18 || position == 23 || position == 34 || position == 37)
        {
            chance.at_visit(players[active_player], &jackpot);
        }
        else if (position == 13) special1->at_visit(players[active_player], &sum);
        else if (position == 29) special2->at_visit(players[active_player], &sum);
        else
        {
            i = 0;
            do
            {
                temp = cities[i]->get_nr();
                i++;
            } while ( temp != position);
            cities[i-1]->at_visit(players[active_player], 0);
        }
        turn = (turn + 1) % 4;
    }
    return 0;
}
