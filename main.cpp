#include "AudioProcessor.h"

using namespace std;
using audio = vector<short>;
int main() {
    AudioProcessor p;
    audio a = {};
    for(const auto &it : p.Compress(a,1,1))
    {
        cout<<it<<" ";
    }
    for(const auto &it : p.Normalize(a,1))
    {
        cout<<it<<" ";
    }
    for(const auto &it : p.StretchTwice(a))
    {
        cout<<it<<" ";
    }
    for(const auto &it : p.CutOutSilence(a,1,1))
    {
        cout<<it<<" ";
    }
//    audio b = {1};
//    p.CutOutSilence(a,1,1);
//    p.StretchTwice(b);
    return 0;
}
