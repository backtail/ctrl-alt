#ifndef _TOOLS_CLAMP_H_
#define _TOOLS_CLAMP_H_

/// @brief Clamp a value to a 10-bit range
/// @param val The value to clamp
/// @return The clamped value, which will be between 0 and 1023
inline uint16_t clamp_10_bit(uint16_t val)
{
    return val > 1023 ? 1023 : val;
}

#endif // _TOOLS_CLAMP_H_