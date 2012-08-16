//
//  bigint.h
//  libprem
//
//  Created by Hubert on 04/08/12.
//  Copyright (c) 2012 Hubert. All rights reserved.
//

#ifndef libprem_bigint_h
#define libprem_bigint_h

#include <stdint.h>

//little-endian notation

typedef struct{
    uint8_t*     value;
    int         length;
}bigint;

bigint* newBigint(int size);
   void shrinkBigint(bigint*);
   void terminateBigint(bigint*);
bigint* copyBigInt(bigint*);

    int compare(bigint*, bigint*);
bigint* minimum(bigint*, bigint*);
bigint* maximum(bigint*, bigint*);
bigint* increment(bigint*, bigint*);
bigint* decrement(bigint*, bigint*);
bigint* shl(bigint*);
bigint* addition(bigint*, bigint*);
bigint* additionWithInt(bigint*, uint8_t);
bigint* subtraction(bigint*, bigint*);
bigint* multiply(bigint*, bigint*);
bigint* multiplyWithInt(bigint*, uint8_t);
bigint* divide(bigint*, bigint*);
bigint* modulo(bigint*, bigint*);
bigint* power(bigint* n, bigint* p);
bigint* logarithm(bigint* n, bigint* base);

uint64_t bigint_to_int(bigint* number);
bigint* int_to_bigint(uint64_t n);

#endif
