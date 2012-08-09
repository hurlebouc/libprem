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

bigint* newBigint(int size){
    bigint* res = malloc(sizeof(bigint));
    res->value = malloc(sizeof(uint8_t)*size);
    res->length = size;
    return res;
}

void terminateBigint(bigint* n){
    free(n->value);
    free(n);
}

static int minint(int a, int b){
    if (a<b) {
        return a;
    } else {
        return b;
    }
}

static int maxint(int a, int b){
    if (a<b) {
        return b;
    } else {
        return a;
    }
}

static int log(uint64_t n, int base){
    int res = 0;
    while (n!= 0) {
        res++;
        n = n / base;
    }
    return res - 1;
}

uint64_t bigint_to_int(bigint* number){
    uint64_t* res = (uint64_t*) number->value;
    return *res;
}

bigint* int_to_bigint(uint64_t n){
    int size = log(n, 256) + 1;
    bigint* res = newBigint(size);
    for (int i = 0; i<size; i++) {
        res->value[i] = n % 256;
        n = n / 256;
    }
    return res;
}

bigint* addition(bigint* a, bigint* b){
    uint8_t retenu = 0;
    int sa = a->length;
    int sb = b->length;
    int min = minint(sa, sb);
    int max = maxint(sa, sb);
    bigint* res = newBigint(max);
    for (int i = 0; i<min; i++) {
        uint8_t n1 = a->value[i];
        uint8_t n2 = b->value[i];
        int n = n1 + n2 + retenu;
        printf("%x %x ", n1, n2);
        retenu = n / 256;
        printf("retenue : %x\n", retenu);
        res->value[i] = (char) n;
    }
    bigint* bigger;
    if (sa == max) {
        bigger = a;
    } else {
        bigger = b;
    }
    for (int i = min; i<max; i++) {
        int n = bigger->value[i] + retenu;
        res->value[i] = (char) n;
        retenu = n / 256;
    }
    if (retenu != 0) {
        res->value = realloc(res->value, res->length + 1);
        res->value[res->length] = retenu;
        res->length++;
    }
    return res;
}















