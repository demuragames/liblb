#include <iostream>
#include <liblb.hpp>

int main(int argc, char *argv[])
{
    Leaderboard lb("http://localhost:8080", "fasia");
    lb.reportScore(140);
    for (auto player: lb.top())
    {
        std::cout << player.identifier << " - " << player.score << std::endl;
    }
    return 0;
}
