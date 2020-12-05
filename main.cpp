#include "AudioProcessor.h"

using namespace std;
using audio = vector<short>;
int main() {
    AudioProcessor p;
    audio a = {1,1,1,1};
    for(const auto &it : p.CutOutSilence(a,1,4))
    {
        cout<<it<<" ";
    }
    audio b = {1};
    p.CutOutSilence(a,1,1);
    p.StretchTwice(b);
    return 0;
}
