#ifndef headers_h
#define headers_h

class Player;
class City;
class Special;
class Railway;
class Chance;
class Neutral;

class Field {
	int nr;
	std::string name;
	Player* owner;
	int value;
	friend class City;
	friend class Railway;
	friend class Chance;
	friend class Special;
	friend class Player;
public:
	virtual void at_visit(Player*, int*) = 0;
	virtual void draw_property() = 0;
	int get_value() { return this->value; }
	int get_nr() { return this->nr; }
	std::string get_name() { return this->name; }
};

class City : public Field {
	int house_value;
	int pay[6];
	int buildings;
	std::string country;
	bool pledged;
	friend class Player;
	friend void lack_of_cash(Player*, Player*, int);
public:
	City(int, std::string, int, int, int [], std::string);
	int get_buildings() { return this->buildings; }
	int how_much_for_it();
	void at_visit(Player*, int*) override;
	void draw_property() override;
	
};

class Railway : public Field {
	int pay[4];
	bool pledged;
	friend class City;
	friend class Player;
	friend void lack_of_cash(Player*, Player*, int);
public:
	Railway(int, std::string, int[]);
	void at_visit(Player*, int*) override;
	void draw_property() override;
	int how_much_for_it(int);
};

class Chance : public Field {
public:
	Chance() { name = "chance"; }
	void at_visit(Player*, int*) override;
	void draw_property() override { ; }
};

class Neutral {
public:
	void at_visit(Player*, int*, int);
};

class Special : public Field {
	bool pledged;
	friend class Player;
	friend void lack_of_cash(Player*, Player*, int);
public:
	Special(int, std::string);
	void at_visit(Player*, int*) override;
	void draw_property() override;
	void what_do_i_own();
};

class Player {
	int id;
	int cash;
	int num_cities;
	int num_railways;
	int num_specials;
	int num_buildings;
	City* city[22];
	Railway* railway[4];
	Special* special[2];
	int position;
	int imprisoned;
	int lucker;
	friend class City;
	friend class Special;
	friend class Neutral;
	friend class Railway;
	friend class Chance;
	friend void lack_of_cash(Player*, Player*, int);
	friend void turns_in_jail(Player*[], int);
public:
	Player(int);
	~Player();
	Player(Player&);
	int get_id() { return this->id; }
	int get_position() { return this->position; }
	int get_cash() { return this->cash; }
	int get_imprisoned() { return this->imprisoned; }
	int move();
	void go_to_jail();
	bool sell_buildings(int);
	void buy_buildings();
	void draw_stats();
	bool operator==(Player* p1);
};

void draw_board(Player*[], City*[], int, int, int);
void visitors(Player*[], int, int);
void buildings(City*);
void jackpot(int);
void fill_array(int*, int, int, int, int, int, int);
void lack_of_cash(Player*, Player*, int);
int next_player(Player* [], int, int);
void turns_in_jail(Player*[],int);
int choose();

#endif