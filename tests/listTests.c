//
//  listTests.c
//  libprem
//
//  Created by hurlebouc on 18/08/12.
//  Copyright (c) 2012 hurlebouc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../src/bigint.h"

#define N 1000

void testInitializer(void){
    
}

void testCmp(void){
    CU_ASSERT_EQUAL(-1, compare(int_to_bigint(19283749), int_to_bigint(9928474993)));
    CU_ASSERT_EQUAL(0, compare(int_to_bigint(20284569), int_to_bigint(20284569)));
    CU_ASSERT_EQUAL(1, compare(int_to_bigint(2028453969), int_to_bigint(20284569)));
    CU_ASSERT_EQUAL(0, compare(int_to_bigint(0), int_to_bigint(0)));
    CU_ASSERT_EQUAL(-1, compare(int_to_bigint(0), int_to_bigint(92839898398948)));
    CU_ASSERT_EQUAL(1, compare(int_to_bigint(92839898398948), int_to_bigint(0)));
    CU_ASSERT_EQUAL(0, compare(newBigint(0), int_to_bigint(0)));
    CU_ASSERT_EQUAL(0, compare(int_to_bigint(0), newBigint(0)));
    CU_ASSERT_EQUAL(-1, compare(newBigint(0), int_to_bigint(1)));
    CU_ASSERT_EQUAL(-1, compare(newBigint(0), int_to_bigint(192883)));
    CU_ASSERT_EQUAL(0, compare(int_to_bigint(0), int_to_bigint(0)));
}

void testAddition(void){
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(3142790363),
                               addition(
                                        int_to_bigint(203948130),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(2938842233),
                               addition(
                                        int_to_bigint(0),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(2938842233),
                               addition(
                                        int_to_bigint(2938842233),
                                        int_to_bigint(0)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               addition(
                                        int_to_bigint(0),
                                        int_to_bigint(0)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               addition(
                                        newBigint(0),
                                        int_to_bigint(0)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               addition(
                                        int_to_bigint(0),
                                        newBigint(0)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(102203991),
                               addition(
                                        newBigint(0),
                                        int_to_bigint(102203991)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(1),
                               addition(
                                        newBigint(0),
                                        int_to_bigint(1)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(1),
                               addition(
                                        int_to_bigint(1),
                                        newBigint(0)
                                        )
                               )
                    );
    for (int i = 0; i<N; i++) {
        uint64_t na = rand();
        uint64_t nb = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* c = int_to_bigint(na + nb);
        bigint* res = addition(a, b);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
}

void testSubstraction(void){
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(1),
                               substraction(
                                        int_to_bigint(1),
                                        newBigint(0)
                                        )
                               )
                    );
    
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(1),
                               substraction(
                                           int_to_bigint(1),
                                           int_to_bigint(0)
                                           )
                               )
                    );
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               substraction(
                                           newBigint(0),
                                           newBigint(0)
                                           )
                               )
                    );
    int n = rand();
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               substraction(
                                           int_to_bigint(n),
                                           int_to_bigint(n)
                                           )
                               )
                    );
    for (int i = 0; i<N; i++) {
        uint64_t na = rand();
        uint64_t nb = rand();
        bigint* a = int_to_bigint(fmax(na, nb));
        bigint* b = int_to_bigint(fmin(na, nb));
        bigint* c = int_to_bigint(fmax(na, nb) - fmin(na, nb));
        bigint* res = substraction(a, b);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
}

void testMultiplication(void){
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(599371377785374290),
                               multiply(
                                        int_to_bigint(203948130),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(1, compare(
                               int_to_bigint(599371377785374291),
                               multiply(
                                        int_to_bigint(203948130),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    CU_ASSERT_EQUAL(-1, compare(
                               int_to_bigint(599371377785374289),
                               multiply(
                                        int_to_bigint(203948130),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    
    CU_ASSERT_EQUAL(0, compare(
                                int_to_bigint(0),
                                multiply(
                                         newBigint(0),
                                         int_to_bigint(2938842233)
                                         )
                                )
                    );
    
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               multiply(
                                        int_to_bigint(0),
                                        int_to_bigint(2938842233)
                                        )
                               )
                    );
    
    CU_ASSERT_EQUAL(0, compare(
                               int_to_bigint(0),
                               multiply(
                                        int_to_bigint(29380842233),
                                        int_to_bigint(0)
                                        )
                               )
                    );
    
    for (int i = 0; i<N; i++) {
        uint64_t na = rand();
        uint64_t nb = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* c = int_to_bigint(na * nb);
        bigint* res = multiply(a, b);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
}

void testDivision(void){
    
    for (int i = 0; i<N; i++) {
        uint64_t na = rand();
        uint64_t nb = rand();
        if (nb == 0) {
            continue;
        }
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* c = int_to_bigint(na / nb);
        bigint* res = divide(a, b);
        int cmp = compare(c, res);
        if (cmp != 0) {
            printf("%llu, %llu : ", na, nb);
            printf("%llu\n", bigint_to_int(res));
        }
        CU_ASSERT_EQUAL(0, cmp);
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
}

void testPower(void){
    
    for (int i = 0; i<N; i++) {
        uint64_t na = rand() % (0x10000);
        uint64_t nb = rand() % 4;
        if (nb == 0) {
            continue;
        }
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* c = int_to_bigint(pow(na, nb));
        bigint* res = power(a, b);
        int cmp = compare(c, res);
        if (cmp != 0) {
            printf("%llu, %llu : ", na, nb);
            printf("%llu\n", bigint_to_int(res));
        }
        CU_ASSERT_EQUAL(0, cmp);
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
    
    for (int i = 0; i<N; i++) {
        uint64_t na = 2;
        uint64_t nb = rand() % 64;
        if (nb == 0) {
            continue;
        }
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* c = int_to_bigint(pow(na, nb));
        bigint* res = power(a, b);
        int cmp = compare(c, res);
        if (cmp != 0) {
            printf("%llu, %llu : ", na, nb);
            printf("%llu\n", bigint_to_int(res));
        }
        CU_ASSERT_EQUAL(0, cmp);
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
    }
    
    //power(int_to_bigint(19000000), int_to_bigint(0x10000));
}

void testConst(void){
    bigint* zero1 = BIG_ZERO();
    bigint* zero2 = BIG_ZERO();
    CU_ASSERT_EQUAL(zero1, zero2);
    bigint* one = BIG_ONE();
    CU_ASSERT_NOT_EQUAL(one, zero1);
}

void testModuloAdd(void){
    for (int i = 0; i<N; i++) {
        uint64_t na = rand();
        uint64_t nb = rand();
        uint64_t modulo = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* mod = int_to_bigint(modulo);
        bigint* c = int_to_bigint((na + nb) % modulo);
        bigint* res = additionModulo(a, b, mod);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
        terminateBigint(mod);
    }
}

void testModuloSub(void){
//    printf("   test de modulo : %d\n", (3-9)%5);
    for (int i = 0; i<N; i++) {
        int64_t na = rand();
        int64_t nb = rand();
        int64_t modulo = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* mod = int_to_bigint(modulo);
        int64_t val = (na - nb) % modulo;
        if (val<0) {
            val += modulo;
        }
        bigint* c = int_to_bigint(val);
        bigint* res = substractionModulo(a, b, mod);
        CU_ASSERT_EQUAL(0, compare(c, res));
        if (compare(c, res) != 0) {
            printf("\nc = %llu, res = %llu\n", bigint_to_int(c), bigint_to_int(res));
        }
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
        terminateBigint(mod);
    }
}

void testModuloMult(void){
    for (int i = 0; i<N; i++) {
//        printf("*******************\n");
//        printf("nouveau test %d\n", i);
//        printf("*******************\n");
        uint64_t na = rand();
        uint64_t nb = rand();
        uint64_t modulo = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* mod = int_to_bigint(modulo);
        bigint* c = int_to_bigint((na * nb) % modulo);
        bigint* res = multiplyModulo2(a, b, mod);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
        terminateBigint(mod);
    }
}

static uint64_t puissance(uint64_t n, uint64_t p, uint64_t mod){
    switch (p) {
        case 0:
            return 1;
        case 1:
            return n;
        default:
            if (p % 2 == 1) {
                return (n*puissance(n, p-1, mod)) % mod;
            } else {
                return puissance((n*n) % mod, p/2, mod);
            }
    }
}

void testModuloPow(void){
    for (int i = 0; i<N; i++) {
        printf("(%d) : ",i);
        uint64_t na = rand();
        uint64_t nb = rand();
        printf("%llu\t%llu\n", na, nb);
        uint64_t modulo = rand();
        bigint* a = int_to_bigint(na);
        bigint* b = int_to_bigint(nb);
        bigint* mod = int_to_bigint(modulo);
        bigint* c = int_to_bigint(puissance(na, nb, modulo));
        bigint* res = powerModulo(a, b, mod);
        CU_ASSERT_EQUAL(0, compare(c, res));
        terminateBigint(res);
        terminateBigint(a);
        terminateBigint(b);
        terminateBigint(c);
        terminateBigint(mod);
    }
}













