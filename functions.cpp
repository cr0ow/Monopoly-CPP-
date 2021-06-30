#include <iostream>
#include <windows.h>
#include "headers.h"

//City
City::City(int nm, std::string n, int v, int h, int p[], std::string c)
{
    nr = nm;
    name = n;
    value = v;
    house_value = h;
    for (int i = 0; i < 6; i++) pay[i] = p[i];
    owner = NULL;
    buildings = 0;
    country = c;
    pledged = false;
}
int City::how_much_for_it()
{
    switch (this->buildings)
    {
        case 0:
            return this->pay[0];
        case 1:
            return this->pay[1];
        case 2:
            return this->pay[2];
        case 3:
            return this->pay[3];
        case 4:
            return this->pay[4];
        case 5:
            return this->pay[5];
        default:
            return 0;
    }
}
void City::at_visit(Player* player, int* no)
{
    if (this->owner == player)
    {
        std::cout << " You are visiting Your own city" << std::endl; //visitor's city
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (pledged == true)) //someone's else field, but field is pledged
    {
        std::cout << " This city belongs to someone else, but it is pledged at the moment. You don't have to pay this time!" << std::endl;
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (this->owner->imprisoned > 0)) //someone's else field, but owner is in jail
    {
        std::cout << " This city belongs to someone else, but it's owner is in jail. Lucky You!" << std::endl;
        Sleep(2000);
    }
    else if (this->owner != NULL) //paying
    {
        int cost = this->how_much_for_it();
        std::cout << " You have to pay " << cost << "$ to the owner: Player " << this->owner->get_id();
        Sleep(2000);
        std::cout << std::endl;
        if (player->cash >= cost)
        {
            player->cash -= cost;
            this->owner->cash += cost;
        }
        else lack_of_cash(player, this->owner, cost);
    }
    else if (this->owner == NULL) //can buy
    {
        system("cls");
        std::cout << " Cash: " << player->cash << "$" << std::endl << std::endl;
        char choice = 'y';
        std::cout << " You can buy this property:" << std::endl;
        this->draw_property();
        while (choice != 'n')
        {
            std::cout << " Do You want to buy? [y/n] ";
            std::cin >> choice;
            switch (choice)
            {
            case 'n':
                break;
            case 'y':
                if (player->cash < this->value)
                {
                    std::cout << " You don't have enough money!" << std::endl;
                    Sleep(2000);
                    choice = 'n';
                    break;
                }
                player->cash -= this->value;
                this->owner = player;
                player->city[player->num_cities] = this;
                player->num_cities++;
                std::cout << " Bought! Cash left: " << player->cash << "$" << std::endl;
                Sleep(2000);
                choice = 'n';
                break;
            default:
                std::cout << " Invalid action! Try again..." << std::endl;
                break;
            }
        }

    }
}
void City::draw_property()
{
    using namespace std;
    int val = this->get_value();
    cout << endl;
    cout << "  + " << this->name << endl;
    cout << "  |" << endl;
    cout << "  | Purchase price: " << val << "$" << endl;
    cout << "  |" << endl;
    cout << "  | Payment for visiting:" << endl;
    cout << "  | - undeveloped area:     " << this->pay[0] << "$" << endl;
    cout << "  | - with 1 house:         " << this->pay[1] << "$" << endl;
    cout << "  | - with 2 houses:        " << this->pay[2] << "$" << endl;
    cout << "  | - with 3 houses:        " << this->pay[3] << "$" << endl;
    cout << "  | - with 4 houses:        " << this->pay[4] << "$" << endl;
    cout << "  | - with hotel:           " << this->pay[5] << "$" << endl;
    cout << "  |" << endl;
    cout << "  | House value:            " << this->house_value << "$" << endl;
    cout << "  + Pledge value:           " << val/2 << "$" << endl << endl;
}

//Special
Special::Special(int n, std::string na)
{
    nr = n;
    name = na;
    value = 300;
    owner = NULL;
    pledged = false;
}
void Special::at_visit(Player* player, int* sum)
{
    std::cout << " " << this->get_name() << std::endl;
    if (this->owner == player) //visiting owned field
    {
        std::cout << " You are visiting Your own property" << std::endl;
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (pledged == true)) //someone's else field, but field is pledged
    {
        std::cout << " This property belongs to someone else, but it is pledged at the moment. You don't have to pay this time!" << std::endl;
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (this->owner->imprisoned > 0)) //someone's else field, but owner is in jail
    {
        std::cout << " This property belongs to someone else, but it's owner is in jail. Lucky You!" << std::endl;
        Sleep(2000);
    }
    else if (this->owner != NULL) //paying
    { 
        int cost = 0;
        int s = *sum;
        if (this->owner->num_specials == 1) int cost = s * 10;
        else if (this->owner->num_specials == 2) int cost = s * 20;
        std::cout << " You have to pay " << cost << "$ to the owner: Player " << this->owner->get_id();
        std::cout << std::endl;
        if (player->cash < cost) lack_of_cash(player, this->owner, cost);
        player->cash -= cost;
        this->owner->cash += cost;
        Sleep(3000);
    }
    else if (this->owner == NULL) //can buy
    {
        system("cls");
        std::cout << " Cash: " << player->cash << "$" << std::endl << std::endl;
        char choice = 'y';
        std::cout << " You can buy this property:" << std::endl;
        this->draw_property();
        while (choice != 'n')
        {
            std::cout << " Do You want to buy? [y/n] ";
            std::cin >> choice;
            switch (choice)
            {
            case 'n':
                break;
            case 'y':
                if (player->cash < this->value)
                {
                    std::cout << " You don't have enough money!" << std::endl;
                    Sleep(2000);
                    choice = 'n';
                    break;
                }
                player->cash -= this->value;
                this->owner = player;
                player->special[player->num_specials] = this;
                player->num_specials++;
                std::cout << " Bought! Cash left: " << player->cash << "$" << std::endl;
                Sleep(2000);
                choice = 'n';
                break;
            default:
                std::cout << " Invalid action! Try again..." << std::endl;
                break;
            }
        }
    }
}
void Special::draw_property()
{
    using namespace std;
    cout << endl;
    cout << "  + " << this->name << endl;
    cout << "  |" << endl;
    cout << "  | Purchase price: 300$" << endl;
    cout << "  |" << endl;
    cout << "  | Payment for visiting:" << endl;
    cout << "  | Number of pips thrown * 2." << endl;
    cout << "  | When You own also "; this->what_do_i_own(); cout << endl;
    cout << "  | a payment is doubled!" << endl;
    cout << "  | You cannot build here any buildings." << endl;
    cout << "  |" << endl;
    cout << "  + Pledge value:               150$" << endl << endl;
}
void Special::what_do_i_own()
{
    if (this->nr == 13) std::cout << "Waterworks";
    else std::cout << "Power station";
}

//Neutral
void Neutral::at_visit(Player* player, int* jackpot, int position)
{
    if (position == 1) { std::cout << " You are visiting START" << std::endl; }
    else if (position == 5)
    {
        std::cout << " Guarded parking! You have to pay 400$!" << std::endl;
        if (player->cash < 400) lack_of_cash(player, NULL, 400);
        player->cash -= 400;
        *jackpot += 400;
    }
    else if (position == 11 && player->imprisoned == 0) { std::cout << " You are visiting JAIL" << std::endl; }
    else if (position == 21)
    {
        std::cout << " Free parking! The jackpot is Yours. You get: " << *jackpot << "$!" << std::endl;
        player->cash += *jackpot;
        *jackpot = 0;
    }
    else if (position == 31)
    {
        std::cout << " Hold on!";
        player->go_to_jail();
    }
    else if (position == 39)
    {
        std::cout << " Luxury tax! You have to pay 200$!" << std::endl;
        if (player->cash < 200) lack_of_cash(player, NULL, 200);
        player->cash -= 200;
        *jackpot += 200;
    }
    if(position != 31) Sleep(3000);
}

//Railway
Railway::Railway(int n, std::string na, int p[])
{
    nr = n;
    name = na;
    owner = NULL;
    value = 400;
    for (int i = 0; i < 4; i++) pay[i] = p[i];
    pledged = false;
}
void Railway::at_visit(Player* player, int* no)
{
    std::cout << " " << this->get_name() << std::endl;
    if (this->owner == player) //visiting owned field
    {
        std::cout << " You are visiting Your own railway" << std::endl;
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (pledged == true)) //someone's else field, but field is pledged
    {
        std::cout << " This railway belongs to someone else, but it is pledged at the moment. You don't have to pay this time!" << std::endl;
        Sleep(2000);
    }
    else if ((this->owner != NULL) && (this->owner->imprisoned > 0)) //someone's else field, but owner is in jail
    {
        std::cout << " This railway belongs to someone else, but it's owner is in jail. Lucky You!" << std::endl;
        Sleep(2000);
    }
    else if (this->owner != NULL) //paying
    {
        int cost = this->how_much_for_it(player->num_railways);
        std::cout << " You have to pay " << this->pay[this->owner->num_railways-1] <<"$ to the owner: Player " << this->owner->get_id();
        std::cout << std::endl;
        if (player->cash >= cost)
        {
            player->cash -= cost;
            this->owner->cash += cost;
        }
        else lack_of_cash(player, this->owner, cost);
        Sleep(4000);
    }
    else if (this->owner == NULL) //can buy
    {
        system("cls");
        std::cout << " Cash: " << player->cash << "$" << std::endl << std::endl;
        char choice = 'y';
        std::cout << " You can buy this property:" << std::endl;
        this->draw_property();
        while (choice != 'n')
        {
            std::cout << " Do You want to buy? [y/n] ";
            std::cin >> choice;
            switch (choice)
            {
                case 'n':
                    break;
                case 'y':
                    if (player->cash < this->value)
                    {
                        std::cout << " You don't have enough money!" << std::endl;
                        Sleep(2000);
                        choice = 'n';
                        break;
                    }
                    player->cash -= this->value;
                    this->owner = player;
                    player->railway[player->num_railways] = this;
                    player->num_railways++;
                    std::cout << " Bought! Cash left: " << player->cash << "$" << std::endl;
                    Sleep(2000);
                    choice = 'n';
                    break;
                default:
                    std::cout << " Invalid action! Try again..." << std::endl;
                    break;
            }
        }
        
    }
}
int Railway::how_much_for_it(int num)
{
    switch (num)
    {
        case 1:
            return 50;
        case 2:
            return 100;
        case 3:
            return 200;
        case 4:
            return 400;
        default:
            return -1;
    }
}
void Railway::draw_property()
{
    using namespace std;
    cout << endl;
    cout << "  + " << this->name << endl;
    cout << "  |" << endl;
    cout << "  | Purchase price: 400$" << endl;
    cout << "  |" << endl;
    cout << "  | Payment for visiting:" << endl;
    cout << "  | - with 1 railway owned:      50$" << endl;
    cout << "  | - with 2 railways owned:    100$" << endl;
    cout << "  | - with 3 railways owned:    200$" << endl;
    cout << "  | - with 4 railways owned:    400$" << endl;
    cout << "  |" << endl;
    cout << "  + Pledge value:               200$" << endl << endl;
}

//Chance
void Chance::at_visit(Player* player, int* jackpot)
{
    int draw = rand() % 20;
    switch (draw)
    {
        case 0: //getting 100$
            std::cout << " Bank gives You 100$!" << std::endl;
            player->cash += 100;
            break;
        case 1: //getting 200$
            std::cout << " Bank gives You 200$!" << std::endl;
            player->cash += 200;
            break;
        case 2: //getting 300$
            std::cout << " Bank gives You 300$!" << std::endl;
            player->cash += 300;
            break;
        case 3: //getting 20$
            std::cout << " Bank gives You 20$!" << std::endl;
            player->cash += 20;
            break;
        case 4: //getting 40$
            std::cout << " Bank gives You 40$!" << std::endl;
            player->cash += 400;
            break;
        case 5: //getting 50$
            std::cout << " Bank gives You 50$!" << std::endl;
            player->cash += 50;
            break;
        case 6: //paying 20$
            std::cout << " You have to pay 20$!" << std::endl;
            if (player->cash < 20) lack_of_cash(player, NULL, 20);
            player->cash -= 20;
            *jackpot += 20;
            break;
        case 7: //paying 30$
            std::cout << " You have to pay 30$!" << std::endl;
            if (player->cash < 30) lack_of_cash(player, NULL, 30);
            player->cash -= 30;
            *jackpot += 30;
            break;
        case 8: //paying 40$
            std::cout << " You have to pay 40$!" << std::endl;
            if (player->cash < 40) lack_of_cash(player, NULL, 40);
            player->cash -= 40;
            *jackpot += 40;
            break;
        case 9: //paying 300$
            std::cout << " You have to pay 300$!" << std::endl;
            if (player->cash < 300) lack_of_cash(player, NULL, 300);
            player->cash -= 300;
            *jackpot += 300;
            break;
        case 10: //paying 400$
            std::cout << " You have to pay 400$!" << std::endl;
            if (player->cash < 400) lack_of_cash(player, NULL, 400);
            player->cash -= 400;
            *jackpot += 400;
            break;
        case 11: //go to jail
            player->go_to_jail();
            break;
        case 12: //go to jail
            player->go_to_jail();
            break;
        case 13: //free from jail
            std::cout << " You can get out from jail one time for free!" << std::endl;
            player->lucker++;
            break;
        case 14: //free from jail
            std::cout << " You can get out from jail one time for free!" << std::endl;
            player->lucker++;
            break;
        case 15: //go to Naples
            std::cout << " You are going to the NAPLES!" << std::endl;
            player->position = 7;
            break;
        case 16: //go to Brussels
            std::cout << " You are going to the BRUSSELS!" << std::endl;
            player->position = 24;
            break;
        case 17: //go to Vienna
            std::cout << " You are going to the VIENNA!" << std::endl;
            player->position = 40;
            break;
        case 18: //go to Start
            std::cout << " You are coming back to START!" << std::endl;
            player->position = 1;
            break;
        case 19: //by 3 fields
            std::cout << " You are coming back by 3 fields!" << std::endl;
            player->position -= 3;
            break;
        default:
            std::cout << " Something went wrong..." << std::endl;
            break;
    }
    Sleep(3000);
}

//Player
Player::Player(int i)
{
    id = i;
    cash = 2000;
    num_cities = 0;
    num_railways = 0;
    num_specials = 0;
    num_buildings = 0;
    for(int i=0; i<22; i++) city[i] = NULL;
    for(int i=0; i<4; i++) railway[i] = NULL;
    for(int i=0; i<2; i++) special[i] = NULL;
    position = 1;
    imprisoned = 0;
    lucker = 0;
}
Player::~Player()
{
    int i = 0;
    while (city[i] != NULL)
    {
        city[i]->owner = NULL;
        city[i]->pledged = false;
        i++;
    }
    i = 0;
    while (railway[i] != NULL)
    {
        railway[i]->owner = NULL;
        railway[i]->pledged = false;
        i++;
    }
    i = 0;
    while (special[i] != NULL)
    {
        special[i]->owner = NULL;
        special[i]->pledged = false;
        i++;
    }
}
Player::Player(Player& p)
{
    id = p.id+1;
    cash = p.cash;
    num_cities = p.num_cities;
    num_railways = p.num_railways;
    num_specials = p.num_specials;
    num_buildings = p.num_buildings;
    for (int i = 0; i < 22; i++) city[i] = p.city[i];
    for (int i = 0; i < 4; i++) railway[i] = p.railway[i];
    for (int i = 0; i < 2; i++) special[i] = p.special[i];
    position = p.position;
    imprisoned = p.imprisoned;
    lucker = p.lucker;
}
int Player::move()
{
    int dice1 = 0, dice2 = 0;
    int rolls = 0;
    int sum = 0;
    while(dice1 == dice2 && rolls < 2)
    {
        dice1 = rand() % 5 + 1;
        dice2 = rand() % 5 + 1;
        sum += (dice1 + dice2);
        rolls++;
        std::cout << " " << dice1 << " " << dice2 << std::endl;
    }
    if (dice1 == dice2) this->go_to_jail();
    else
    {
        this->position = (this->position + sum) % 41;
        if ((sum >= this->position) && (this->imprisoned == 0))
        {
            std::cout << " You walked through the START, You get 400$!" << std::endl;
            this->cash += 400; 
        }
        std::cout << " Dices: " << sum << std::endl;
        Sleep(1000);
    }
    return sum;
}
void Player::go_to_jail()
{
    if (this->lucker > 0)
    {
        std::cout << " You have a card that allows You to avoid punishment! (but still you must visit the jail)" << std::endl;
        this->position = 11;
        this->lucker--;
        Sleep(2000);
    }
    else
    {
        std::cout << " You are going to the jail!" << std::endl;
        this->position = 11;
        this->imprisoned = 2;
        Sleep(2000);
    }
}
bool Player::sell_buildings(int cost)
{
    int num, var;
    City* p[22];
    while (this->cash < cost && this->num_buildings > 0) //selling
    {
        do
        {
            system("cls");
            for (int i = 0; i < 22; i++) p[i] = NULL;
            var = 0;
            std::cout << " You need " << cost - this->cash << "$ more" << std::endl;
            std::cout << " Your buildings [number of buildings] (selling value per house):" << std::endl;
            for (int i = 0; i < this->num_cities; i++)
            {
                if ((this->city[i]->buildings > 0) && (this->city[i]->pledged == false))
                {
                    p[var] = this->city[i];
                    var++;  
                    std::cout << " " << var << ". " << this->city[i]->get_name() << " [" << this->city[i]->buildings;
                    std::cout << "] (" << (this->city[i]->house_value) / 2 << "$)" << std::endl;
                }
            }
            std::cout << " Which one You want to sell? ";
            std::cin >> num;
            if (num < 1 || num > var)
            {
                std::cout << " Choose valid number!" << std::endl;
                Sleep(2000);
            }
        } while (num < 1 || num > var);
        this->num_buildings--;
        p[num - 1]->buildings--;
        this->cash += (p[num - 1]->house_value) / 2;
    }
    if (this->cash >= cost) return true; //can pay
    //sill not enough
    std::cout << " You have no more buildings to sell!" << std::endl;
    Sleep(2000);
    return false;
}
void Player::buy_buildings()
{
    if (this->num_cities == 0)
    {
        std::cout << "You have no cities to expand!" << std::endl;
        Sleep(2000);
    }
    else
    {
        int i = 0;
        int choice = 1;
        while (choice != 0)
        {
            i = 0;
            system("cls");
            std::cout << " Your cash: " << this->cash << "$" << std::endl;
            std::cout << " Your cities [number of buildings] (upgrade cost):" << std::endl;
            while (this->city[i] != NULL)
            {
                std::cout << " " << i + 1 << ". " << this->city[i]->get_name() << " [" << this->city[i]->buildings << "] ";
                std::cout << " (" << this->city[i]->house_value << "$)" << std::endl;
                i++;
            }
            std::cout << " Where do You want to buy buildings? (insert valid number or 0 to exit this menu) ";
            std::cin >> choice;
            if (choice == 0) break;
            if (choice < 1 || choice > i+1) std::cout << " Insert valid number!" << std::endl;
            else if ((this->cash) < (this->city[choice-1]->house_value)) std::cout << " You have not enough cash!" << std::endl;
            else if (this->city[choice-1]->buildings == 5) std::cout << " You can't build more buildings in this city!" << std::endl;
            else
            {
                this->cash -= this->city[choice-1]->house_value;
                this->num_buildings++;
                this->city[choice-1]->buildings++;
                std::cout << " Built!" << std::endl;
            }
            Sleep(2000);
        }
    }
}
void Player::draw_stats()
{
    std::cout << " Current player: " << this->id << std::endl;
    std::cout << " Cash: " << this->cash << "$" << std::endl;
    std::cout << " Properties: ";
    int i = 0;
    while (this->city[i] != NULL)
    {
        std::cout << this->city[i]->get_name();
        std::cout << ", ";
        i++;
    }
    i = 0;
    while (this->railway[i] != NULL)
    {
        std::cout << this->railway[i]->get_name();
        std::cout << ", ";
        i++;
    }
    i = 0;
    while (this->special[i] != NULL)
    {
        std::cout << this->special[i]->get_name();
        std::cout << ", ";
        i++;
    }
    std::cout << std::endl;
}
bool Player::operator==(Player* p1)
{
    if (this->id == p1->id) return true;
    else return false;
}

//functions
void draw_board(Player* players[], City* cities[], int num_players, int current, int jack)
{
    using namespace std;
    players[current]->draw_stats();
    cout << endl;
    cout << "  +----+--------------------------------+----------+-----------+       +----+--------------------------------+----------+-----------+" << endl;
    cout << "  | NR | NAME                           | VISITORS | BUILDINGS |       | NR | NAME                           | VISITORS | BUILDINGS |" << endl;
    cout << "  +----+--------------------------------+----------+-----------+       +----+--------------------------------+----------+-----------+" << endl;
    cout << "  |  1 | Start (+400$)                  | "; visitors(players, 1, num_players); cout << " | " << "          |       | 21 | Free parking "; jackpot(jack); cout << "        | "; visitors(players, 21, num_players); cout << " |           |" << endl;
    cout << "  |  2 | Thessaloniki            YELLOW | "; visitors(players, 2, num_players); cout << " |    "; buildings(cities[0]); cout << "   |       | 22 | Rotterdam                GREEN | "; visitors(players, 22, num_players); cout << " |    "; buildings(cities[11]); cout << "   |" << endl;
    cout << "  |  3 | Chance (?)                     | "; visitors(players, 3, num_players); cout << " | " << "          |       | 23 | Chance (?)                     | "; visitors(players, 23, num_players); cout << " |           |" << endl;
    cout << "  |  4 | Athens                  YELLOW | "; visitors(players, 4, num_players); cout << " |    "; buildings(cities[1]); cout << "   |       | 24 | Brussels                 GREEN | "; visitors(players, 24, num_players); cout << " |    "; buildings(cities[12]); cout << "   |" << endl;
    cout << "  |  5 | Guarded parking (-400$)        | "; visitors(players, 5, num_players); cout << " | " << "          |       | 25 | Amsterdam                GREEN | "; visitors(players, 25, num_players); cout << " |    "; buildings(cities[13]); cout << "   |" << endl;
    cout << "  |  6 | Southern railway               | "; visitors(players, 6, num_players); cout << " | " << "          |       | 26 | Northern railway               | "; visitors(players, 26, num_players); cout << " |           |" << endl;
    cout << "  |  7 | Naples                     RED | "; visitors(players, 7, num_players); cout << " |    "; buildings(cities[2]); cout << "   |       | 27 | Malmo                   PURPLE | "; visitors(players, 27, num_players); cout << " |    "; buildings(cities[14]); cout << "   |" << endl;
    cout << "  |  8 | Chance (?)                     | "; visitors(players, 8, num_players); cout << " | " << "          |       | 28 | Gotteborg               PURPLE | "; visitors(players, 28, num_players); cout << " |    "; buildings(cities[15]); cout << "   |" << endl;
    cout << "  |  9 | Milan                      RED | "; visitors(players, 9, num_players); cout << " |    "; buildings(cities[3]); cout << "   |       | 29 | Waterworks                     | "; visitors(players, 29, num_players); cout << " |           |" << endl;
    cout << "  | 10 | Roma                       RED | "; visitors(players, 10, num_players); cout << " |    "; buildings(cities[4]); cout << "   |       | 30 | Stockholm               PURPLE | "; visitors(players, 30, num_players); cout << " |    "; buildings(cities[16]); cout << "   |" << endl;
    cout << "  | 11 | Jail                           | "; visitors(players, 11, num_players); cout << " | " << "          |       | 31 | Go to jail                     | "; visitors(players, 31, num_players); cout << " |           |" << endl;
    cout << "  | 12 | Barcelona                 BLUE | "; visitors(players, 12, num_players); cout << " |    "; buildings(cities[5]); cout << "   |       | 32 | Frankfurt                BROWN | "; visitors(players, 32, num_players); cout << " |    "; buildings(cities[17]); cout << "   |" << endl;
    cout << "  | 13 | Power Station                  | "; visitors(players, 13, num_players); cout << " | " << "          |       | 33 | Cologne                  BROWN | "; visitors(players, 33, num_players); cout << " |    "; buildings(cities[18]); cout << "   |" << endl;
    cout << "  | 14 | Sevilla                   BLUE | "; visitors(players, 14, num_players); cout << " |    "; buildings(cities[6]); cout << "   |       | 34 | Chance (?)                     | "; visitors(players, 34, num_players); cout << " |           |" << endl;
    cout << "  | 15 | Madrid                    BLUE | "; visitors(players, 15, num_players); cout << " |    "; buildings(cities[7]); cout << "   |       | 35 | Bonn                     BROWN | "; visitors(players, 35, num_players); cout << " |    "; buildings(cities[19]); cout << "   |" << endl;
    cout << "  | 16 | Eastern railway                | "; visitors(players, 16, num_players); cout << " | " << "          |       | 36 | Western railway                | "; visitors(players, 36, num_players); cout << " |           |" << endl;
    cout << "  | 17 | Liverpool               ORANGE | "; visitors(players, 17, num_players); cout << " |    "; buildings(cities[8]); cout << "   |       | 37 | Chance (?)                     | "; visitors(players, 37, num_players); cout << " |           |" << endl;
    cout << "  | 18 | Chance (?)                     | "; visitors(players, 18, num_players); cout << " | " << "          |       | 38 | Innsbruck                BLACK | "; visitors(players, 38, num_players); cout << " |    "; buildings(cities[20]); cout << "   |" << endl;
    cout << "  | 19 | Glasgow                 ORANGE | "; visitors(players, 19, num_players); cout << " |    "; buildings(cities[9]); cout << "   |       | 39 | Luxury tax                     | "; visitors(players, 39, num_players); cout << " |           |" << endl;
    cout << "  | 20 | London                  ORANGE | "; visitors(players, 20, num_players); cout << " |    "; buildings(cities[10]); cout << "   |       | 40 | Vienna                   BLACK | "; visitors(players, 40, num_players); cout << " |    "; buildings(cities[21]); cout << "   |" << endl;
    cout << "  +----+--------------------------------+----------+-----------+       +----+--------------------------------+----------+-----------+" << endl << endl;
}
void visitors(Player* players[], int field, int num_players)
{
    std::cout << "  ";
    for (int i = 0; i < num_players; i++)
    {
        if (players[i]->get_position() == field) std::cout << players[i]->get_id();
        else std::cout << " ";
    }
    std::cout << "  ";
}
void buildings(City* city)
{
    switch (city->get_buildings())
    {
        case 0:
            std::cout << "    ";
            break;
        case 1:
            std::cout << " h  ";
            break;
        case 2:
            std::cout << " hh ";
            break;
        case 3:
            std::cout << "hhh ";
            break;
        case 4:
            std::cout << "hhhh";
            break;
        case 5:
            std::cout << " H  ";
            break;
        default:
            std::cout << "    ";
            break;
    }
}
void jackpot(int jackpot)
{
    std::cout << "(+" << jackpot << "$)";
    if (jackpot < 10) std::cout << "     ";
    else if (jackpot < 100) std::cout << "    ";
    else if (jackpot < 1000) std::cout << "   ";
    else if (jackpot < 10000) std::cout << "  ";
    
}
void fill_array(int* p, int p1, int p2, int p3, int p4, int p5, int p6)
{
    *p = p1;
    *(p + 1) = p2;
    *(p + 2) = p3;
    *(p + 3) = p4;
    *(p + 4) = p5;
    *(p + 5) = p6;
}
void lack_of_cash(Player* player, Player* owner, int cost)
{
    bool a = false, b = false;
    std::cout << " You need " << cost - player->cash << "$ more! Try to sell buildings or pledge some of Your's properties." << std::endl;
    Sleep(3000);
    for (int i = 0; i < player->num_cities; i++) if (player->city[i]->buildings > 0) a = true; //if player owns any building
    if (a) b = player->sell_buildings(cost); //selling buildings
    if(!b) //pledging properties
    {
        int var1, var2, var3, choice;
        while (player->cash < cost)
        {
            system("cls");
            var1 = 0;
            a = false;
            std::cout << " You need " << cost - player->cash << "$ more." << std::endl;
            std::cout << " Your properties: [pledge value]" << std::endl;
            for (int i = 0; i < player->num_cities; i++) //if player owns cities
            {
                if (player->city[i]->pledged == false)
                {
                    a = true;
                    var1++;
                    std::cout << " " << var1 << ". " << player->city[i]->get_name();
                    std::cout << " [" << player->city[i]->get_value() / 2;
                    std::cout << "$]" << std::endl;
                }
            }
            var2 = var1;
            for (int i = 0; i < player->num_railways; i++) //if player owns railways
            {
                if (player->railway[i]->pledged == false)
                {
                    a = true;
                    var2++;
                    std::cout << " " << var2 << ". " << player->railway[i]->get_name();
                    std::cout << " [" << player->railway[i]->get_value() / 2;
                    std::cout << "$]" << std::endl;
                }
            }
            var3 = var2;
            for (int i = 0; i < player->num_specials; i++) //if player owns specials
            {
                if (player->special[i]->pledged == false)
                {
                    a = true;
                    var3++;
                    std::cout << " " << var3 << ". " << player->special[i]->get_name();
                    std::cout << " [" << player->special[i]->get_value() / 2;
                    std::cout << "$]" << std::endl;
                }
            }
            if (!a) //nothing to pledge
            {
                std::cout << " You have nothing more to plegde and You can't afford to pay full price!" << std::endl;
                std::cout << " You LOST!" << std::endl;
                if (owner != NULL)
                {
                    std::cout << " Owner gets Your whole cash: " << player->cash << "$" << std::endl;
                    owner->cash += player->cash;
                }
                Sleep(4000);
                player = NULL;
            }
            else //pledge
            {
                std::cout << std::endl;
                do
                {
                    std::cout << " Which property You would like to pledge? ";
                    std::cin >> choice;
                    if (choice < 1 || choice > var3) std::cout << " Choose valid property!" << std::endl;
                } while (choice < 1 || choice > var3);
                if (choice <= var1) //city
                {
                    player->city[choice - 1]->pledged = true;
                    player->cash += (player->city[choice - 1]->get_value()) / 2;
                }
                else if (choice <= var2) //railway
                {
                    player->railway[choice - var1 - 1]->pledged = true;
                    player->cash += (player->railway[choice - var1 - 1]->get_value()) / 2;
                }
                else //special
                {
                    player->special[choice - var2 - 1]->pledged = true;
                    player->cash += (player->special[choice - var2 - 1]->get_value()) / 2;
                }
                std::cout << " Pledged! " << std::endl;
                Sleep(2000);
            }
        }
    }
    if (player != NULL) //can pay only if player is "alive"
    {
        std::cout << " Now You afford to pay" << std::endl;
        player->cash -= cost;
        if (owner != NULL) owner->cash += cost;
        Sleep(2000);
    }
    else delete player;
}
int next_player(Player* players[], int previous_player, int num_players)
{
    if (players[previous_player] == NULL) return -1;
    else if (players[previous_player]->get_imprisoned() > 0) 
    {
        std::cout << " Player " << previous_player + 1 << " is in jail!" << std::endl;
        Sleep(2000);
        system("cls");
        return -1;
    }
    else return previous_player;
}
void turns_in_jail(Player* players[], int turn)
{
    for (int i = 0; i < 4; i++)
    {
        if (i == turn)
        {
            if (players[turn]->imprisoned > 0) players[turn]->imprisoned--;
        }
    }
}
int choose()
{
    char c;
    int choice = 1;
    bool znak = false;
    std::cout << " Choose an action:" << std::endl;
    std::cout << " 1. Roll the dices" << std::endl;
    std::cout << " 2. Expand Your cities" << std::endl;
    do
    {
        if (!(choice == 1 || choice == 2)) std::cout << " Choose valid option!" << std::endl;
        while (!znak || atoi(&c) > 9)
        {
            std::cout << " Choice: ";
            std::cin >> c;
            for (int i = 49; i < 51; i++) if (c == char(i)) znak = true;
            if(!znak || atoi(&c) > 9) std::cout << " Choose valid option!" << std::endl;
        }
        choice = atoi(&c);
        if (!(choice == 1 || choice == 2)) choice = 3;
    } while (choice == 3);
    return choice;
}