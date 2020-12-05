#include "AudioProcessor.h"

audio_t AudioProcessor::Compress(const audio_t &audio, short threshold, float rate) {
    if(threshold < 0 || rate < 1.0) throw std::invalid_argument("invalid threshold or rate");
    audio_t res;
    for(const auto &it : audio)
    {
        bool neg = it < 0;
        if(it < -1*threshold || it > threshold)
        {
            short val = round(((double)(abs(it)-threshold))/rate + threshold);
            if(neg) val*=-1;
            res.push_back(val);
        }
        else res.push_back(it);
    }
    return res;
}

audio_t AudioProcessor::CutOutSilence(const audio_t audio, short level, int silenceLength) {
    if(level < 0 || silenceLength < 1) throw std::invalid_argument("invalid level or silenceLength");
    audio_t res;
    if(audio.size() == 1 && silenceLength == 1 && audio[0] >= -1*level && audio[0] <= level) return res;
    res = audio;
    for(int i = 0; i < audio.size()-1; i++)
    {
        if(res[i] >= -1*level && res[i] <= level)
        {
            int j = i+1;
            while(j < res.size() && res[j] >= -1*level && res[j] <= level) j++;
            if(j-i >= silenceLength) res.erase(res.begin()+i,res.begin()+j);
        }
    }
    return res;
}

audio_t AudioProcessor::StretchTwice(const audio_t &audio) {
    audio_t res;
    for(int i = 0; i < audio.size()-1; i++)
    {
        res.push_back(audio[i]);
        short avg = round(((double)audio[i] + audio[i+1])/2);
        res.push_back(avg);
    }
    res.push_back(audio[audio.size()-1]);
    return res;
}

audio_t AudioProcessor::Normalize(const audio_t audio, short normalizeTarget) {
    if(normalizeTarget < 1) throw std::invalid_argument("invalid normalizeTarget");
    audio_t res;
    if(audio.size() < 1) return res;
    short largestElement = audio[0];
    for(const auto &it : audio)
    {
        short absElement = abs(it);
        largestElement = std::max(largestElement, absElement);
    }
    double x = (double)normalizeTarget/largestElement;
    for(const auto &it : audio) res.push_back(round(x*it));
    return res;
}
