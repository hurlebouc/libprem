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
    for (int i = 0; i<1000; i++) {
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
    for (int i = 0; i<1000; i++) {
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
    
    for (int i = 0; i<1000; i++) {
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
    
    for (int i = 0; i<1000; i++) {
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
    
    for (int i = 0; i<1000; i++) {
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
    
    for (int i = 0; i<1000; i++) {
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














