module;
#include <string>

export module player;

export class player
{
public:
    int elo;    
    int team;
    std::string name;

public:
    player()
    {
        clear();
    }

    player(int _elo, std::string _name = "", int _team = 0)
    {
        elo = _elo;
        name = _name;
        team = _team;
    }

    void clear()
    {
        elo = 0;
        name = "";
        team = 0;        
    }
};
