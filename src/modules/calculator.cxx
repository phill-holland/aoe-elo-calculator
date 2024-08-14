module;

#include <vector>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <algorithm>

import team;
import player;
import point;

export module calculator;

class permutation
{
public:
    std::unordered_map<int,team> map;
};

export class calculator
{
public:
    static void calculate(std::vector<player> players, int total_teams);

private:
    static void permutations(std::vector<permutation> &data, std::vector<player> &players, float &max_team_elo, int total_teams);
    static void front(std::vector<permutation> &data, std::vector<player> &players, int total_teams, float average, float max_team_elo);
};

void calculator::calculate(std::vector<player> players, int total_teams)
{
    float average = 0.0f;    
    for(auto &it: players)
    {    
        average += (float)it.elo;     
    }

    average /= (float)total_teams;

    float max_team_elo = 0.0f;

    std::vector<permutation> data;

    permutations(data, players, max_team_elo, total_teams);
    front(data, players, total_teams, average, max_team_elo); 
}

void calculator::permutations(std::vector<permutation> &data, std::vector<player> &players, float &max_team_elo, int total_teams)
{
    std::vector<int> play;
    play.resize(players.size());

    int counter = 0;
    for(auto &it: players)
    {    
        play[counter] = counter;
        ++counter;
    }

    int players_per_team = players.size() / total_teams;

    do
    {
        std::unordered_map<int,team> map;
        permutation permutate;
     
        int previous_team_idx = 0;
        int counter = 0;
        for(auto &it:play)
        {
            float value = (float)players[it].elo;

            int team_idx = (int)std::floor((float)counter / (float)(players_per_team));
            if(map.find(team_idx) == map.end()) 
            {
                team t1;
                t1.elo = value;
                t1.members.push_back(it);
                map[team_idx] = t1;
            }
            else 
            {
                map[team_idx].members.push_back(it);
                map[team_idx].elo += value;
            }

            ++counter;
        }

        permutate.map = map;
        for(auto &it:map)
        {
            if(it.second.elo>max_team_elo) max_team_elo = it.second.elo;
        }
        data.push_back(permutate);

    } while(std::next_permutation(play.begin(), play.end()));
}

void calculator::front(std::vector<permutation> &data, std::vector<player> &players, int total_teams, float average, float max_team_elo)
{
    int count = data.size();
    bool result[count];
    for(int i = 0; i < count; ++i)
    {
        result[i] = true;
    }

    point a(total_teams);
    point b(total_teams);

    for(int i =  0; i < count; ++i)
    {
        int counter = 0;
        for(auto &it:data[i].map)
        {
            float distance = abs(it.second.elo - average);
            distance = ((distance/max_team_elo) * -1.0f) + 1.0f;
            a.set((long)(distance * 1000.0f), counter++);
        }

        for(int j  = 0; j < count; ++j)        
        {
            if(i != j)
            {
                int counter = 0;
                for(auto &it:data[j].map)
                {
                    float distance = abs(it.second.elo - average);
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

    int output_count = 0;

    for(int i = 0; i < count; ++i)
    {
        if(result[i])
        {
            for(auto&it:data[i].map)
            {
                std::cout << "team" << it.first << " elo=" << it.second.elo << "("; 
                for(auto &jt:it.second.members) 
                {
                    std::cout << jt << "[" << players[jt].name << "] ";
                }
                std::cout << ") ";
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
            ++output_count;
            if(output_count >= 5) return;
        }
    }
}