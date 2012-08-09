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
    bigint* a = int_to_bigint(0xa9E6);
    bigint* b = int_to_bigint(0x273);
    bigint* c = multiply(a, b);
    
    
    printf("caca : %llx\n",bigint_to_int(c));
}