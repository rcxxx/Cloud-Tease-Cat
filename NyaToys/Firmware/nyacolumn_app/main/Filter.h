#ifndef __FILTER_H
#define __FILTER_H

#include <stdint.h>


void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);

#endif /* __FILTER_H */



