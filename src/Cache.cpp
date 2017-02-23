//
// Created by maciek on 23.02.17.
//

#include "Cache.h"
#include "YoutubePlanner.h"

Cache::Cache(int id, int size_max) {
    this->id = id;
    this->size_left = size_max;
}

void Cache::AddVideo(int videoId) {
    videos.push_back(videoId);
    this->size_left -= YoutubePlanner::GetInstance().Videos[videoId]->weight;
}


bool Cache::IsEnoughSpace(int videoId)
{
    return this->size_left >= YoutubePlanner::GetInstance().Videos[videoId]->weight;
}