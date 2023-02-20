/*
   (c) Rafael González (astrorafael@gmail.com), LICA, Ftad. CC. Fisicas, UCM

   See project's LICENSE file.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    static inline uint min(uint x, uint y)
    {
        return (x < y) ? x : y;
    }

    static inline uint max(uint x, uint y)
    {
        return (x > y) ? x : y;
    }

    static inline uint clip(uint x, uint lo, uint hi)
    {
        return min(max(lo, x), hi);
    }

#ifdef __cplusplus
}
#endif