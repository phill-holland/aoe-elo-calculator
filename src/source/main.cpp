#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "kdpoint.h"
#include <math.h>

using namespace std;

/*
auto is_dominant = [](int *a, int *b) 
	{ 
		const int dimensions = 2;
		bool any = false;
		for (int i = 0; i < dimensions; ++i)
		{
			//Log << a[i];
			// modify kdtree for this condition, between left and right insert
			if(a[i] > b[i]) return false;
			any |= (a[i] < b[i]);
			//if((*epochs)[i]->results.score > (*source.epochs)[i]->results.score) return false;
			//any |= ((*epochs)[i]->results.score < (*source.epochs)[i]->results.score);
		}

		return any;
	};

*/

class player
{
public:
    int elo;
    std::string name;
    int team;

public:
    player()
    {
        clear();
    }

    player(int _elo, std::string _name, int _team = 0)
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


class team
{
public:
    std::vector<int> members; // player index
    float eol;

public:
    team() { clear(); }

    void clear()
    {
        eol = 0.0f;
        members.clear();
    }
};


class permutation
{
public:
    std::unordered_map<int,team> map;
};

void calculate(std::vector<player> players, int total_teams)
{    
    //std::vector<int> teams;
    //teams.resize(total_teams);
    
    std::vector<int> play;
    play.resize(players.size());

    float average = 0.0f;    
    int counter = 0;
    for(auto &it: players)
    {    
        average += (float)it.elo;     
        play[counter] = counter;
        ++counter;
    }

    average /= (float)total_teams;

/*
    int counter = 0;
    for(auto &it: play)
    {
        play[counter] = counter;
        ++counter;
    } 
*/
    //int best_index = 0;
    //float closest = 5000.0f;



float max_team_elo = 0.0f;
int players_per_team = players.size() / total_teams;

    std::vector<permutation> data;

    do
    {
        std::unordered_map<int,team> map;
        permutation permutate;
     
        int previous_team_idx = 0;
        int counter = 0;
        for(auto &it:play)
        {
            //std::cout << it << " ";            
            float value = (float)players[it].elo;

            //int team_idx = counter % players_per_team;//(int)(counter / total_teams);
            int team_idx = (int)std::floor((float)counter / (float)(players_per_team));
            if(map.find(team_idx) == map.end()) 
            {
                team t1;
                t1.eol = value;
                t1.members.push_back(it);
                map[team_idx] = t1;
            }
            else 
            {
                map[team_idx].members.push_back(it);
                map[team_idx].eol += value;
            }

            ++counter;
        }
        //std::cout << "(" << total << ")\n";
        //std::cout << "\n";

        permutate.map = map;
        for(auto &it:map)
        {
            if(it.second.eol>max_team_elo) max_team_elo = it.second.eol;
        }
        data.push_back(permutate);

    } while(std::next_permutation(play.begin(), play.end()));

    int count = data.size();
    bool result[count];
    for(int i = 0; i < count; ++i)
    {
        result[i] = true;
    }

// compute pareto front
    organisation::kdpoint a(total_teams);
    organisation::kdpoint b(total_teams);

    for(int i =  0; i < count; ++i)
    {
        int counter = 0;
        for(auto &it:data[i].map)
        {
            float distance = abs(it.second.eol - average);
            distance = ((distance/max_team_elo) * -1.0f) + 1.0f;
            a.set((long)(distance * 1000.0f), counter++);

            //std::cout << "elo/distance=" << it.second.eol << "/" << distance << ",";
        }
        //std::cout << "\n";

        for(int j  = 0; j < count; ++j)        
        {
            if(i != j)
            {
                int counter = 0;
                for(auto &it:data[j].map)
                {
                    float distance = abs(it.second.eol - average);
                    distance = ((distance/max_team_elo) * -1.0f) + 1.0f;
                    b.set((long)(distance * 1000.0f), counter++);
                }

                if(b.dominates(a))
                {
                    result[i] = false;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < count; ++i)
    {
        if(result[i])
        {
            for(auto&it:data[i].map)
            {
                std::cout << "team" << it.first << " elo=" << it.second.eol << "("; 
                for(auto &jt:it.second.members) 
                {
                    std::cout << jt << "[" << players[jt].name << "] ";
                }
                std::cout << ") ";

                for(auto &jt:it.second.members)
                {

                }
            }

            // ***
            for(int player = 0; player < players.size(); ++player)
            {
                for(auto&it:data[i].map)
                {
                    for(auto &jt:it.second.members) 
                    {
                        if(jt == player)
                        {
                            std::cout << (it.first + 1);
                        }
                    }
                }
            }
            // ***

            std::cout << "\n";

            return;
        }
    }

    //std::cout << "muppet\n";    
}

int main(int argc, char *argv[])
{        
/*
    std::vector<player> players = {
        player(500, "dave"),
        player(500, "susan"),
        player(1000, "bob"),
        player(1000, "mary")
    };
*/
    std::vector<player> players = {
        player(600, "dave"),
        player(600, "susan"),
        player(1200, "bob"),
        player(2000, "mary"),
        player(700, "woof"),
        player(1200, "baa")
    };

// teams need to be divisable by two
    calculate(players, 2);

    return 0;
}