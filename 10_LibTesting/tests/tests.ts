#include <check.h>
#include "buf.h"


#tcase size_tests
#test test_zero_capacity_size
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);

#test test
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    ck_assert_float_eq(a[0], (float)1.3f);
    buf_clear(a);

    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_ne(a, 0);
    buf_free(a);
    ck_assert_ptr_eq(a, 0);

    

#test test_zero_ptr
    float *a = 0;
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_eq(a, 0);


    
#tcase push_and_indexing
#test test_push_and_indexing
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_uint_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_uint_eq(match, 10000);
    buf_free(ai);


#tcase grow_trunc
#test test_grow
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);
    buf_free(ai);



#tcase pop
#test test_pop
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_uint_eq(buf_size(a), 4);
    ck_assert_float_eq(buf_pop(a), (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3);
    ck_assert_float_eq(buf_pop(a), (float)1.3f);
    ck_assert_float_eq(buf_pop(a), (float)1.2f);
    ck_assert_float_eq(buf_pop(a), (float)1.1f);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);