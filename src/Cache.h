//
// Created by maciek on 23.02.17.
//

#ifndef YOUTUBE_CACHE_H
#define YOUTUBE_CACHE_H

#include <vector>

class Cache {
public:
    int id;
    int size_left;
    int howManyEndpoints = 0;
    std::vector<int> videos;
    // ::vector<int> _endpoints;

    Cache(int, int);

    void AddVideo(int id);
    bool IsEnoughSpace(int videoId);
    void AddEndpoint() {
        howManyEndpoints++;
    }
};


#endif //YOUTUBE_CACHE_H
