#ifndef _YAGO_ENVELOP_HXX
#define _YAGO_ENVELOP_HXX

namespace yago
{

template <typename Range>
class Envelop : public FunctionalElement<Range>
{
private:
    float _attack;
    float _decay;
    float _sustain;
    float _release;
    float _velocity;
    yago::time _note_off_t;
    float _envelop(yago::time t, float sample)
    {
        if (t - _note_off_t >= _release)
            return 0.0f;

        float envelop;
        yago::time t_end = (t < _note_off_t) ? t : _note_off_t;
        if (t_end < _attack)
            envelop = t_end / _attack;
        else if (t_end - _attack < _decay)
            envelop = 1.0f + (_sustain - 1.0f) * ((t_end - _attack) / _decay);
        else
            envelop = _sustain;

        if (t - _note_off_t >= 0.0f)
            envelop *= 1.0f - (float)(t - _note_off_t) / _release;

        return sample * _velocity * envelop;
    }
public:
    Envelop(float attack, float decay, float sustain, float release, float velocity = 1.0f, float note_off_t = std::numeric_limits<float>::infinity()) : FunctionalElement<Range>([this](yago::time t, float s){ return _envelop(t,s); }), _attack(attack), _decay(decay), _sustain(sustain), _release(release), _velocity(velocity), _note_off_t(note_off_t) {}
    void note_off(yago::time t)
    {
        _note_off_t = t;
    }
};

}
/* namespace yago */

#endif

