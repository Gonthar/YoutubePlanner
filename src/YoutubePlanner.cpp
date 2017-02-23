//
// Created by bartek on 23.02.17.
//

#include "YoutubePlanner.h"

#include <iostream>

void YoutubePlanner::ReadFromStdin()
{
    int size, latency, cacheId, videoId, endpointId, requests;
    std::cin >> VideosCount >> EndpointsCount >> RequestsCount >> CacheCount >> CacheSize;

    for (int i = 0; i < CacheCount; ++i) {
        Caches.push_back(std::shared_ptr<Cache>(new Cache(i, CacheSize)));
    }

    for (int i = 0; i < VideosCount; ++i)
    {
        std::cin >> size;
        Videos.push_back(std::shared_ptr<Video>(new Video(i, size)));
    }

    for (int i = 0; i < EndpointsCount; ++i) {
        std::cin >> latency >> size;
        std::shared_ptr<Endpoint> endpoint(new Endpoint(latency));

        for (int j = 0; j < size; ++j)
        {
            std::cin >> cacheId >> latency;
            endpoint->AddCacheConnection(cacheId, latency);
            Caches[cacheId]->AddEndpoint();
        }
        Endpoints.push_back(std::move(endpoint));
    }

    for (int i = 0; i < RequestsCount; ++i)
    {
        std::cin >> videoId >> endpointId >> requests;
        Endpoints[endpointId]->AddRequest(videoId, requests);
        Videos[videoId]->AddEndpointWhichAsksFor(endpointId, requests);
    }


}

void YoutubePlanner::PrintResult() {
    int count = 0;
    for (int i = 0; i < CacheCount; ++i)
    {
        if (!Caches[i]->videos.empty())
            count++;
    }
    std::cout << count <<"\n";
    for (int i = 0; i < CacheCount; ++i)
    {
        if (Caches[i]->videos.empty())
            continue;
        std::cout << i;
        for (int video : Caches[i]->videos)
            std::cout << " "<<Videos[video]->number;
        std::cout << "\n";
    }
}