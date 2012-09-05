//
//  bigint.c
//  libprem
//
//  Created by hurlebouc on 04/08/12.
//  Copyright (c) 2012 hurlebouc. All rights reserved.
//

// TODO think about implementing maximal sharing

#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

unsigned long long COMPTEUR = 0;

static bigint* _zero = NULL;
static bigint* _one = NULL;
static bigint* _two = NULL;

bigint* BIG_ZERO(){
    if (_zero == NULL) {
        _zero = int_to_bigint(0);
    }
    return _zero;
}

bigint* BIG_ONE(){
    if (_one == NULL) {
        _one = int_to_bigint(1);
    }
    return _one;
}

bigint* BIG_TWO(){
    if (_two == NULL) {
        _two = int_to_bigint(2);
    }
    return _two;
}

static void sout(bigint* number){
    printf("%llu\n", bigint_to_int(number));
}

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

bigint* copyBigInt(bigint* number){
    bigint* res = newBigint(number->length);
    for (int i = 0; i<number->length; i++) {
        res->value[i] = number->value[i];
    }
    return res;
}

bigint* shl(bigint* number){
    bigint* res = newBigint(number->length + 1);
    res->value[0] = 0;
    for (int i = 0; i<number->length; i++) {
        res->value[i + 1] = number->value[i];
    }
    return res;
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

int compare(bigint* a, bigint*b){
    if (a->length > b->length) {
        return 1;
    }
    if (a->length < b->length) {
        return -1;
    }
    for (int i = a->length - 1; i>=0; i--) {
        if (a->value[i] > b->value[i]) {
            return 1;
        }
        if (a->value[i] < b->value[i]) {
            return -1;
        }
    }
    return 0;
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
        uint16_t n = n1 + n2 + retenue;
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
        uint16_t n = bigger->value[i] + retenue;
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

bigint* substraction(bigint* a, bigint* b){
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
    for (int i = b->length; i<a->length; i++) {
        int na = a->value[i];
        int n = na - retenue;
        if (n < 0) {
            retenue = 1;
            n = n + 256;
        } else {
            retenue = 0;
        }
        res->value[i] = n;
    }
    int i = a->length - 1;
    while (i>=0 && res->value[i] == 0) {
        i--;
    }
    res->length = i + 1;
    return res;
}

static bigint* mult_aux(bigint* a, uint8_t b, int offset){
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
        terminateBigint(former);
        terminateBigint(tmp);
    }
    return res;
}

static bigint* getHead(bigint* number, int size){
    if (size > number->length) {
        printf("This number has not a head of size %d.\n", size);
        exit(EXIT_FAILURE);
    }
    bigint* res = newBigint(size);
    for (int i = 0; i<size; i++) {
        res->value[i] = number->value[number->length - size + i];
    }
    return res;
}

/**
 * can be improved
 */
static uint8_t divide_weak(bigint* a, bigint*b){
    bigint* mult = copyBigInt(b);
    uint8_t q = 0;
    while (compare(a, mult) >= 0) {
        bigint* tmp = addition(mult, b);
        terminateBigint(mult);
        mult = tmp;
        q++;
    }
    terminateBigint(mult);
    return q;
}

bigint* divide(bigint* a, bigint* b){
    if (compare(a, b) < 0) {
        // to avoit error in getHead();
        return newBigint(0);
    }
    uint8_t* tab = malloc(sizeof(uint8_t)*a->length);
    int offset = b->length;
    bigint* head = getHead(a, offset);
    while (offset < a->length) {
        uint8_t div = divide_weak(head, b);
        tab[offset - b->length] = div;
        bigint* mult = multiplyWithInt(b, div);
        bigint* tmp = substraction(head, mult);
        terminateBigint(mult);
        terminateBigint(head);
        head = tmp;
        tmp = shl(head);
        terminateBigint(head);
        head = tmp;
        tmp = additionWithInt(head, a->value[a->length - (offset + 1)]);
        terminateBigint(head);
        head = tmp;
        offset++;
    }
    uint8_t div = divide_weak(head, b);
    terminateBigint(head);
    tab[offset - b->length] = div;
    
    bigint* res = newBigint(offset - b->length + 1);
    for (int i = 0; i<= offset - b->length; i++) {
        res->value[i] = tab[offset - b->length - i];
    }
    free(tab);
    if (res->value[res->length - 1] == 0) {
        res->length--;
    }
    return res;
}

/**
 * maybe to improve!
 */
bigint* additionWithInt(bigint* number, uint8_t n){
    bigint* tmp = int_to_bigint(n);
    bigint* res = addition(number, tmp);
    terminateBigint(tmp);
    return res;
}

/**
 * maybe to improve!
 */
bigint* multiplyWithInt(bigint* number, uint8_t n){
    bigint* tmp = int_to_bigint(n);
    bigint* res = multiply(number, tmp);
    terminateBigint(tmp);
    return res;
}

bigint* increment(bigint* number){
    bigint* tmp = int_to_bigint(1);
    bigint* res = addition(number, tmp);
    terminateBigint(tmp);
    terminateBigint(number);
    return res;
}

bigint* decrement(bigint* number){
    bigint* tmp = int_to_bigint(1);
    bigint* res = substraction(number, tmp);
    terminateBigint(tmp);
    terminateBigint(number);
    return res;
}

bigint* modulo(bigint* a, bigint* b){
    bigint* quotient = divide(a, b);
    bigint* mult = multiply(b, quotient);
    bigint* res = substraction(a, mult);
    terminateBigint(quotient);
    terminateBigint(mult);
    return res;
}

int isZero(bigint* number){
    return number->length == 0 ||(number->length == 1 && number->value[0] == 0);
}


bigint* power(bigint* n, bigint* p){
    if (isZero(p)) {
        return int_to_bigint(1);
    }
//    bigint* two = int_to_bigint(2);
    bigint* pdiv2 = divide(p, BIG_TWO());
//    terminateBigint(two);
    bigint* tmp = power(n, pdiv2);
    bigint* cmp = multiply(pdiv2, BIG_TWO());
    terminateBigint(pdiv2);
    bigint* res = multiply(tmp, tmp);
    terminateBigint(tmp);
    if (compare(p, cmp) == 0) {
        terminateBigint(cmp);
        return res;
    } else {
        terminateBigint(cmp);
        bigint* tmp = multiply(n, res);
        terminateBigint(res);
        return tmp;
    }
}


// -------------------------- MODULO ----------------------------

// Maybe to improve!
bigint* additionModulo(bigint* a, bigint* b, bigint* mod){
    bigint* tmp = addition(a, b);
    if (compare(tmp, mod) < 0) {
        return tmp;
    }
    bigint* res = modulo(tmp, mod);
    terminateBigint(tmp);
    return res;
}

bigint* substractionModulo(bigint* a, bigint* b, bigint* mod){
    bigint* reste;
    int isStrictlyNeg;
    if (compare(a, b) >= 0) {
        reste = substraction(a, b);
        isStrictlyNeg = 0;
    } else {
        reste = substraction(b, a);
        isStrictlyNeg = 1;
    }
    bigint* res = modulo(reste, mod);
    terminateBigint(reste);
    if (!isStrictlyNeg) {
        return res;
    }
    bigint* res2 = substraction(mod, res);
    terminateBigint(res);
    return res2;
}

bigint* multiplyModulo(bigint* a, bigint* b, bigint* mod){
    bigint* max = maximum(a, b);
    bigint* min;
    if (max == a) {
        min = b;
    } else {
        min = a;
    }
    bigint* res = newBigint(0); // useless
    for (int i = 0; i<min->length; i++) {
        bigint* former;
        bigint* tmp = mult_aux(max, min->value[i], i);
        if (tmp->length >= mod->length) {
            former = tmp;
            tmp = modulo(tmp, mod);
            terminateBigint(former);
        }
        former = res;
        res = addition(res, tmp);
        terminateBigint(former);
        if (res->length >= mod->length) {
            former = res;
            res = modulo(res, mod);
            terminateBigint(former);
        }
        terminateBigint(tmp);
    }
    return res;
}

bigint* powerModulo(bigint* n, bigint* p, bigint* mod){
    if (isZero(p)) {
        return int_to_bigint(1);
    }
    bigint* two = int_to_bigint(2);
    bigint* pdiv2 = divide(p, two);
    bigint* cmp = multiply(pdiv2, two);
    terminateBigint(two);
    bigint* tmp = power(n, pdiv2);
    terminateBigint(pdiv2);
    bigint* res = multiply(tmp, tmp);
    terminateBigint(tmp);
    if (compare(p, cmp) == 0) {
        terminateBigint(cmp);
        return res;
    } else {
        terminateBigint(cmp);
        bigint* tmp = multiply(n, res);
        terminateBigint(res);
        return tmp;
    }
}










