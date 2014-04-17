#include <curl/curl.h>
#include "liblb.hpp"
#include <stdio.h>

static size_t lb_cb(void *ptr, size_t size, size_t nmemb, std::string *result)
{
    *result += (const char *)ptr;
}

std::list<Player> Leaderboard::top()
{
    std::string result;

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, (_url + "/top").c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, lb_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::list<Player> players;

    char identifier[1024];
    const char *string = result.c_str();
    int score = 0, shift = 0;
    const char *current_position = string;
    while (sscanf(current_position, "%s %d%n", identifier, &score, &shift) == 2)
    {
        Player player;
        player.score = score;
        player.identifier = identifier;
        players.push_back(player);

        current_position += shift;
    }

    return players;
}

void Leaderboard::reportScore(int score)
{
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, (_url + "/report?id=" + _identifier + "&score=" + std::to_string(score)).c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
