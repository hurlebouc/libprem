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
    bigint* a = int_to_bigint(283743);
    bigint* b = int_to_bigint(27);
    
    printf("substraction : %llx\n",bigint_to_int(subtraction(a, b)));
    printf("division : %llx\n",bigint_to_int(divide(a, b)));
    
}