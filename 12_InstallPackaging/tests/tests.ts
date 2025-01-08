#include <check.h>
#include "guess_number.h"


#tcase read_int2roman_file
#test test_arabic_numbers
    Int2Roman pairs[100];
    readInt2RomanFile("../src/int2roman.csv", pairs);
    ck_assert_uint_eq(pairs[0].arabic, 1);
    ck_assert_uint_eq(pairs[1].arabic, 2);
    ck_assert_uint_eq(pairs[19].arabic, 20);
    ck_assert_uint_eq(pairs[50].arabic, 51);
    ck_assert_uint_eq(pairs[98].arabic, 99);


#test test_roman_numbers
    Int2Roman pairs[100];
    readInt2RomanFile("../src/int2roman.csv", pairs);
    ck_assert_str_eq(pairs[0].roman, "I");
    ck_assert_str_eq(pairs[1].roman, "II");
    ck_assert_str_eq(pairs[19].roman, "XX");
    ck_assert_str_eq(pairs[50].roman, "LI");
    ck_assert_str_eq(pairs[98].roman, "XCIX");


#tcase tr_functions_test
#test arabic2Roman_test
    Int2Roman pairs[100];
    readInt2RomanFile("../src/int2roman.csv", pairs);
    ck_assert_str_eq(arabic2Roman(3, pairs), "III");
    ck_assert_str_eq(arabic2Roman(17, pairs), "XVII");
    ck_assert_str_eq(arabic2Roman(34, pairs), "XXXIV");
    ck_assert_str_eq(arabic2Roman(51, pairs), "LI");


#test roman2Arabic_test
    Int2Roman pairs[100];
    readInt2RomanFile("../src/int2roman.csv", pairs);
    ck_assert_uint_eq(roman2Arabic("III", pairs), 3);
    ck_assert_uint_eq(roman2Arabic("XVII", pairs), 17);
    ck_assert_uint_eq(roman2Arabic("XXXIV", pairs), 34);
    ck_assert_uint_eq(roman2Arabic("LI", pairs), 51);