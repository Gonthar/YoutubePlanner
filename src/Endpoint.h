//
// Created by bartek on 23.02.17.
//

#ifndef HASHCODE_ENDPOINT_H
#define HASHCODE_ENDPOINT_H

#include <unordered_map>

class Endpoint {
public:
    int latencyToMainServer;
    std::unordered_map<int, int> requests;
    std::unordered_map<int, int> latency;

    Endpoint(int lat) : latencyToMainServer(lat) { }

    void AddCacheConnection(int id, int lat)
    {
        latency[id] = lat;
    }

    void AddRequest(int videoId, int req)
    {
        requests[videoId] = req;
    }
};


#endif //HASHCODE_ENDPOINT_H
