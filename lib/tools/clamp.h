#ifndef _TOOLS_CLAMP_H_
#define _TOOLS_CLAMP_H_

inline uint16_t clamp_10_bit(uint16_t val)
{
    return val > 1023 ? 1023 : val;
}

#endif // _TOOLS_CLAMP_H_