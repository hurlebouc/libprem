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
    int8_t*     value;
    int         length;
}bigint;

bigint* newBigint();
void terminateBigint(bigint*);

bigint* add(bigint*, bigint*);
bigint* mul(bigint*, bigint*);
bigint* div(bigint*, bigint*);
bigint* power(bigint* n, bigint* p);

#endif
