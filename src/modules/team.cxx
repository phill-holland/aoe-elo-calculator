module;
#include <vector>

export module team;

export class team
{
public:
    std::vector<int> members;
    float elo;

public:
    team() { clear(); }

    void clear()
    {
        elo = 0.0f;
        members.clear();
    }
};
