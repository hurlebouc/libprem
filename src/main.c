//
//  main.c
//  libprem
//
//  Created by Hubert on 04/08/12.
//  Copyright (c) 2012 Hubert. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "bigint.h"

int main(){
    bigint* a = int_to_bigint(2838729873);
    bigint* b = int_to_bigint(2897398729);
    bigint* c = addition(a, b);
    
    
    printf("caca : %llu\n",bigint_to_int(c));
}