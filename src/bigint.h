//
//  bigint.h
//  libprem
//
//  Created by hurlebouc on 04/08/12.
//  Copyright (c) 2012 hurlebouc. All rights reserved.
//

#ifndef libprem_bigint_h
#define libprem_bigint_h

#include <stdint.h>
extern unsigned long long COMPTEUR;

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

/**
 * add 1 to the parameter
 * @return the new address of the newly incremented bigint
 */
bigint* increment(bigint*);

/**
 * substract 1 to the parameter
 * @return the new address of the newly decremented bigint
 */
bigint* decrement(bigint*);
    int isZero(bigint*);
bigint* shl(bigint*);
bigint* addition(bigint*, bigint*);
bigint* additionWithInt(bigint*, uint8_t);
bigint* substraction(bigint*, bigint*);
bigint* multiply(bigint*, bigint*);
bigint* multiplyWithInt(bigint*, uint8_t);
bigint* divide(bigint*, bigint*);
bigint* power(bigint* n, bigint* p);
bigint* logarithm(bigint* n, bigint* base);

// -------------- MODULO -----------------

bigint* modulo(bigint*, bigint*);
bigint* additionModulo(bigint*, bigint*, bigint* mod);
bigint* substractionModulo(bigint*, bigint*, bigint* mod);
bigint* powerModulo(bigint* n, bigint* p, bigint* mod);

uint64_t bigint_to_int(bigint* number);
bigint* int_to_bigint(uint64_t n);

#endif
