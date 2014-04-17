#pragma once
#include <list>
#include <string>

struct Player
{
    std::string identifier;
    int score;
};

class Leaderboard
{
public:
    Leaderboard(const char *url, const char *identifier) :
        _url(url), _identifier(identifier) {}

    std::list<Player> top();
    void reportScore(int score);

private:
    std::string _url;
    std::string _identifier;

};
