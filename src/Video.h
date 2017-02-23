//
// Created by bartek on 23.02.17.
//

#ifndef HASHCODE_VIDEO_H
#define HASHCODE_VIDEO_H

#include <unordered_map>

class Video {
public:
    int number;
    int weight;
    int requestsSum = 0;

    Video(int id, int size) : number(id), weight(size) { }

    std::unordered_map<int, int> endpoints;

    void AddEndpointWhichAsksFor(int endpointId, int requests)
    {
        endpoints[endpointId] = requests;
        requestsSum += requests;
    }

    bool operator<(Video const& other) const
    {
        return requestsSum/weight < other.requestsSum/other.weight;
    }
};

#endif //HASHCODE_VIDEO_H
