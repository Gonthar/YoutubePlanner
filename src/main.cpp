#include <iostream>
#include <limits>
#include <algorithm>
#include "YoutubePlanner.h"

using namespace std;

int main(int argc, char** argv) {

    int count = atoi(argv[1]);

    YoutubePlanner::GetInstance().ReadFromStdin();



    YoutubePlanner& yt = YoutubePlanner::GetInstance();

    int db[yt.VideosCount][yt.CacheCount];
    // KITtENS
    /*int** db = new int*[yt.VideosCount+2];
    for (int i = 0; i < yt.VideosCount+2; ++i)
    {
        db[i] = new int[yt.CacheCount+2];
    }*/

    int datacenter_dist = 0;
    int gain = 0;


    for (int i = 0; i < yt.VideosCount; ++i)
        for (int j = 0; j < yt.CacheCount; ++j)
            db[i][j] = 0;

    for (auto& e : yt.Endpoints) {
        //datacenter_dist
        for (auto& v : yt.Videos) {
            if (e->requests.find(v->number) != e->requests.end())
            {
                for (auto& c : e->latency) {
                    gain = e->latencyToMainServer - c.second;
                    db[v->number][c.first] += (gain) * e->requests[v->number];


                }
            }
        }
    }

    for (int iter = 0; iter < count; ++iter)
    {
        int maxVideo = std::numeric_limits<int>::min();
        int maxCache = std::numeric_limits<int>::min();
        int max = std::numeric_limits<int>::min();
        for (int i = 0; i < yt.VideosCount; ++i)
        {
            for (int j = 0; j < yt.CacheCount; ++j)
            {
                //std::cout << db[i][j] <<" ";
                if (db[i][j] > max)
                {
                    max = db[i][j];
                    maxVideo = i;
                    maxCache = j;
                }
            }
            //std::cout <<"\n";
        }

        db[maxVideo][maxCache] = -1;

        if (yt.Caches[maxCache]->IsEnoughSpace(maxVideo))
            yt.Caches[maxCache]->AddVideo(maxVideo);

        for (int i = 0; i < yt.CacheCount; ++i)
            if (db[maxVideo][i] != -1)
                db[maxVideo][i] = 0;

        for (auto& e : yt.Endpoints) {
            if (e->requests.find(maxVideo) != e->requests.end())
            {
                for (auto& c : e->latency) {
                    if (db[maxVideo][c.first] > -1)
                    {
                        int g = e->latencyToMainServer;
                        if (e->latency.find(maxCache) != e->latency.end())
                            g =  e->latency[maxCache];
                        gain = g - e->latency[c.second];
                        db[maxVideo][c.first] += gain * e->requests[maxVideo];
                    }
                }
            }
        }
    }

    /*
     * TRENDINGS :)
     * int currCache = 0;
    int currVideo = 0;

    std::sort(yt.Videos.begin(), yt.Videos.end(), [](std::shared_ptr<Video> const& a, std::shared_ptr<Video> const& b){
        return a->requestsSum/a->weight > b->requestsSum/b->weight;
    });

    //for (int i = 0; i < 10; ++i)
   // {
    //    std::cout << i << " " << yt.Videos[i]->number << " "<<yt.Videos[i]->requestsSum << " "<<yt.Videos[i]->weight
    //    <<" "<< (yt.Videos[i]->requestsSum / yt.Videos[i]->weight) <<"\n";
    //}
    //return 0;
    while (currVideo < yt.VideosCount && currCache < yt.CacheCount) {
        if (yt.Caches[currCache]->IsEnoughSpace(currVideo)) {
            yt.Caches[currCache]->AddVideo(currVideo);
            ++currVideo;
        } else {
            ++currCache;
        }
    }*/


    yt.PrintResult();

    return 0;
}