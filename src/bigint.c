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

void shrinkBigint(bigint* number){
    number->value = realloc(number->value, number->length);
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
    uint64_t res = 0;
    uint64_t p = 1;
    for (int i = 0; i<number->length; i++) {
        res += p * number->value[i];
        p *= 256;
    }
    return res;
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

int equality(bigint* a, bigint*b){
    if (a->length != b->length) {
        return 0;
    }
    for (int i = 0; i<a->length; i++) {
        if (a->value[i] != b->value[i]) {
            return 0;
        }
    }
    return 1;
}

bigint* maximum(bigint* a, bigint* b){
    if (a->length > b->length) {
        return a;
    }
    if (b->length > a->length) {
        return b;
    }
    for (int i = a->length - 1; i>=0; i--) {
        if (a->value[i] > b->value[i]) {
            return a;
        }
        if (b->value[i] > a->value[i]) {
            return b;
        }
    }
    return a;
}

bigint* minimum(bigint* a, bigint* b){
    bigint* max = maximum(a, b);
    if (max == a) {
        return b;
    } else {
        return a;
    }
}

bigint* addition(bigint* a, bigint* b){
    uint8_t retenue = 0;
    int sa = a->length;
    int sb = b->length;
    int min = minint(sa, sb);
    int max = maxint(sa, sb);
    bigint* res = newBigint(max + 1);
    for (int i = 0; i<min; i++) {
        uint8_t n1 = a->value[i];
        uint8_t n2 = b->value[i];
        int n = n1 + n2 + retenue;
        retenue = n / 256;
        res->value[i] = (char) n;
    }
    bigint* bigger;
    if (sa == max) {
        bigger = a;
    } else {
        bigger = b;
    }
    for (int i = min; i<max; i++) {
        int n = bigger->value[i] + retenue;
        res->value[i] = (char) n;
        retenue = n / 256;
    }
    if (retenue == 0) {
        res->length--;
    } else {
        res->value[res->length - 1] = retenue;
    }
    return res;
}

/**
 * This function work only with a >= b
 */

bigint* subtraction(bigint* a, bigint* b){
    bigint* res = newBigint(a->length);
    int retenue = 0;
    for (int i = 0; i<b->length; i++) {
        int na = a->value[i];
        int nb = b->value[i];
        int n = na - (nb + retenue);
        if (n < 0) {
            retenue = 1;
            n = n + 256;
        } else {
            retenue = 0;
        }
        res->value[i] = n;
    }
    int i = b->length;
    while (retenue != 0) {
        int n = a->value[i] - retenue;
        if (n < 0) {
            retenue = 1;
            n = n + 256;
        } else {
            retenue = 0;
        }
        res->value[i] = n;
        i++;
    }
    res->length = i;
    return res;
}

bigint* mult_aux(bigint* a, uint8_t b, int offset){
    bigint* res = newBigint(a->length + offset + 1);
    uint8_t retenue = 0;
    for (int i = 0; i<offset; i++) {
        res->value[i] = 0;
    }
    for (int i = 0; i<a->length; i++) {
        int n = a->value[i] * b + retenue;
        res->value[i + offset] = (uint8_t) n;
        retenue = n / 256;
    }
    if (retenue == 0) {
        res->length--;
    } else {
        res->value[res->length - 1] = retenue;
    }
    return res;
}

bigint* multiply(bigint* a, bigint* b){
    bigint* max = maximum(a, b);
    bigint* min;
    if (max == a) {
        min = b;
    } else {
        min = a;
    }
    bigint* res = newBigint(0); // useless
    for (int i = 0; i<min->length; i++) {
        bigint* tmp = mult_aux(max, min->value[i], i);
        bigint* former = res;
        res = addition(res, tmp);
        free(former);
        free(tmp);
    }
    return res;
}

static bigint* getHead(bigint* number, int size){
    bigint* res = newBigint(size);
    for (int i = 0; i<size; i++) {
        res->value[i] = number->value[number->length - size + i];
    }
    return res;
}

bigint* divide(bigint* a, bigint* b){
    uint8_t* tab = malloc(sizeof(uint8_t)*a->length);
    int bookmark = 0;
    
}











