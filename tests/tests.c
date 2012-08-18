//
//  tests.c
//  libprem
//
//  Created by Hubert on 18/08/12.
//  Copyright (c) 2012 Hubert. All rights reserved.
//

#include <stdio.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"

#include "listTests.c"

#include "CUnit/CUCurses.h"

int init_suite_success(void) { return 0; }
int clean_suite_success(void) { return 0; }


int main(int argc, char* argv [])
{
    
    CU_pSuite pSuite = NULL;
    
    /*------------------------ INITIALISATION DU TESTEUR ---------------------*/
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /*---------------------------- CREATION DES TEST -------------------------*/
    printf("initialisation des tests CFG\n");
    pSuite = CU_add_suite("comparaison CFG", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "compare", testCmp))||
        (NULL == CU_add_test(pSuite, "addition", testAddition))||
        (NULL == CU_add_test(pSuite, "addition", testMultiplication))||
        (NULL == CU_add_test(pSuite, "addition", testDivision))||
        (NULL == CU_add_test(pSuite, "substraction", testSubstraction)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /*--------------------------- LANCEMENT DES TESTS ------------------------*/
    
    /* Run all tests using the basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    
    /* Run all tests using the automated interface */
    //CU_automated_run_tests();
    //CU_list_tests_to_file();
    
    /* Run all tests using the console interface */
    //CU_console_run_tests();
    
    /* Run all tests using the curses interface */
    /* (only on systems having curses) */
    //CU_curses_run_tests();
    
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}