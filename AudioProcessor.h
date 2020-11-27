#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <cmath>
#include <iostream>
#include <vector>

using audio_t = std::vector<short>;

class AudioProcessor {
public:
    audio_t Compress(const audio_t &audio, short threshold, float rate);
    audio_t CutOutSilence(const audio_t audio, short level, int silenceLength);
    audio_t StretchTwice(const audio_t &audio);
    audio_t Normalize(const audio_t audio, short normalizeTarget);
};


#endif
