//
//  bigint.c
//  libprem
//
//  Created by Hubert on 04/08/12.
//  Copyright (c) 2012 Hubert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

bigint* newBigint(){
    return malloc(sizeof(bigint));
}

void terminateBigint(bigint* n){
    free(n);
}

bigint* addition(bigint* a, bigint* b){
    int8_t retenu = 0;
}