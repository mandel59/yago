#include <yago.hxx>

void yago::Oscillator::signal(const yago::time t, const int sample_rate, std::vector<yago::sample>& buffer)
{
    float phase = _phase;
    float rsr = 1.0f / sample_rate;
    float delta_phase = _frequency * rsr;

    if (_freq_f != nullptr)
    {
        for (yago::sample& sample : buffer)
        {
            sample = _wave(phase);
            phase += rsr * _freq_f(t);
            if (phase >= 1.0f) phase -= (int) phase;
        }
    }
    else
    {
        for (yago::sample& sample : buffer)
        {
            sample = _wave(phase);
            phase += delta_phase;
            if (phase >= 1.0f) phase -= (int) phase;
        }
    }

    _phase = phase;
}

void yago::Amplifier::signal(const yago::time t, const int sample_rate, std::vector<yago::sample>& buffer)
{
    for (yago::sample& sample : buffer)
    {
        sample *= _rate;
        if (sample > _limit) sample = _limit;
    }
}

