#include <vector>
#include <string>

import calculator;
import player;

using namespace std;

int main(int argc, char *argv[])
{ 
    std::vector<player> players = {
        player(600, "dave"),
        player(600, "susan"),
        player(1200, "bob"),
        player(2000, "mary"),
        player(700, "woof"),
        player(1200, "baa")
    };

    int total_teams = 2;

    if(argc > 2)
    {
        total_teams = atoi(argv[1]);
        std::vector<player> temp;
        for(int i = 2; i < argc; ++i)
        {
            std::string name = "player" + std::to_string(i);
            temp.push_back(player(atoi(argv[i]), name));
        }

        players = temp;
    }
    
    // teams need to be divisable by two
    calculator::calculate(players, total_teams);

    return 0;
}