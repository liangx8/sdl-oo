#include <stdint.h>


#define  sqr1       0b1
#define  bar2       0b11
#define  bar3       0b111
#define  bar4       0b1111

/**
 * -----
 */
#define  l4       0b11111
/**
 * -+
 *  +--
 */
#define  z1         0b11+(0b00001110<<8)
/**
 * -+
 *  +--
 */
#define  z2          0b111+(0b11100<<8)
#define  longL       0b111111111
#define  c3          0b111+(0b0101<<8)
#define  c4          0b1111+(0b1001<<8)
#define  square      0b11+(0b11 << 8)

const uint16_t blpu_block[]={sqr1,bar2,bar3,bar4,l4,z1,z2,longL,c3,c4,square};

