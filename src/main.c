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
    bigint* a = int_to_bigint(1000);
    bigint* b = int_to_bigint(190000000);
    bigint* c = addition(b, a);
    
    
    printf("caca : %llu\n",bigint_to_int(c));
}