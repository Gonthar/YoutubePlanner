//
// Created by bartek on 23.02.17.
//

#ifndef HASHCODE_YOUTUBEPLANER_H
#define HASHCODE_YOUTUBEPLANER_H

#include <memory>
#include <vector>
#include "Video.h"
#include "Cache.h"
#include "Endpoint.h"


class YoutubePlanner {
public:
    int VideosCount;
    int EndpointsCount;
    int RequestsCount;
    int CacheCount;
    int CacheSize;

    std::vector<std::shared_ptr<Video> > Videos;
    std::vector<std::shared_ptr<Endpoint> > Endpoints;
    std::vector<std::shared_ptr<Cache> > Caches;

    void ReadFromStdin();
    void PrintResult();
    static YoutubePlanner& GetInstance()
    {
        static YoutubePlanner instance;
        return instance;
    }
};

#endif //HASHCODE_YOUTUBEPLANER_H
