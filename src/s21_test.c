#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_string.h"

#ifdef __linux
#define ERRORS_COUNT 134
#elif defined(__APPLE__)
#define ERRORS_COUNT 107
#endif

START_TEST(test_s21_strerror) {
  srand(time(NULL));
  int errnum = rand();
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
  int min = 0;
  int max = ERRORS_COUNT;
  int errnum2 = min + rand() % (max - min + 1);
  ck_assert_str_eq(s21_strerror(errnum2), strerror(errnum2));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest1[10] = {0}, dest2[10] = {0};
  const char *src = "hello";
  ck_assert_str_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5));
}
END_TEST

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("hello"), strlen("hello"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
}
END_TEST

START_TEST(test_s21_memchr) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 11), memchr(str, 'o', 11));
}
END_TEST

START_TEST(test_s21_memcmp) {
  ck_assert_int_eq(s21_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));
  ck_assert_int_eq(s21_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char dest1[20] = {0}, dest2[20] = {0};
  const char *src = "hello world";
  ck_assert_mem_eq(s21_memcpy(dest1, src, 11), memcpy(dest2, src, 11), 11);
}
END_TEST

START_TEST(test_s21_memset) {
  char dest1[10] = {0}, dest2[10] = {0};
  ck_assert_mem_eq(s21_memset(dest1, 'a', 5), memset(dest2, 'a', 5), 10);
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest1[20] = "Hello ", dest2[20] = "Hello ";
  const char *src = "world";
  ck_assert_str_eq(s21_strncat(dest1, src, 5), strncat(dest2, src, 5));
}
END_TEST

START_TEST(test_s21_strchr) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
}
END_TEST

START_TEST(test_s21_strncmp) {
  ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
}
END_TEST

START_TEST(test_s21_strcspn) {
  ck_assert_int_eq(s21_strcspn("hello", "eo"), strcspn("hello", "eo"));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  const char *str = "hello world";
  ck_assert_ptr_eq(s21_strpbrk(str, "ow"), strpbrk(str, "ow"));
}
END_TEST

START_TEST(test_s21_strrchr) {
  const char *str = "test.string";
  ck_assert_ptr_eq(s21_strrchr(str, 't'), strrchr(str, 't'));
  ck_assert_ptr_eq(s21_strrchr(str, 'x'), strrchr(str, 'x'));
}
END_TEST

START_TEST(test_s21_strstr) {
  const char *haystack = "hello world";
  ck_assert_ptr_eq(s21_strstr(haystack, "world"), strstr(haystack, "world"));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1[] = "hello world";
  char str2[] = "hello world";
  char *delim = " ";
  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);
  while (token1 && token2) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(NULL, delim);
    token2 = strtok(NULL, delim);
  }
  ck_assert(!token1 && !token2);
}
END_TEST

START_TEST(test_s21_sprintf) {
  char output_f_custom[100];
  s21_sprintf(output_f_custom, "%f", 0.0000123456);
  char output_f_library[100];
  sprintf(output_f_library, "%f", 0.0000123456);
  ck_assert_str_eq(output_f_custom, output_f_library);

  char output_c_custom[100];
  s21_sprintf(output_c_custom, "%c", 't');
  char output_c_library[100];
  sprintf(output_c_library, "%c", 't');
  ck_assert_str_eq(output_c_custom, output_c_library);

  char output_d_custom[100];
  int num1 = 98;
  s21_sprintf(output_d_custom, "%d", num1);
  char output_d_library[100];
  sprintf(output_d_library, "%d", num1);
  ck_assert_str_eq(output_d_custom, output_d_library);

  char output_s_custom[100];
  s21_sprintf(output_s_custom, "%s", "stroke");
  char output_s_library[100];
  sprintf(output_s_library, "%s", "stroke");
  ck_assert_str_eq(output_s_custom, output_s_library);

  unsigned int number = 12345;
  unsigned short hnum = 123;
  unsigned long lnum = 1234567890;

  char output_u_custom[100];
  s21_sprintf(output_u_custom, "%u", number);
  char output_u_library[100];
  sprintf(output_u_library, "%u", number);
  ck_assert_str_eq(output_u_custom, output_u_library);

  char output_plus_u_custom[100];
  s21_sprintf(output_plus_u_custom, "'%-10u'", number);
  char output_plus_u_library[100];
  sprintf(output_plus_u_library, "'%-10u'", number);
  ck_assert_str_eq(output_plus_u_custom, output_plus_u_library);

  char output_ten_u_custom[100];
  s21_sprintf(output_ten_u_custom, "'%10u'", number);
  char output_ten_u_library[100];
  sprintf(output_ten_u_library, "'%10u'", number);
  ck_assert_str_eq(output_ten_u_custom, output_ten_u_library);

  char output_point5_u_custom[100];
  s21_sprintf(output_point5_u_custom, "'%.5u'", number);
  char output_point5_u_library[100];
  sprintf(output_point5_u_library, "'%.5u'", number);
  ck_assert_str_eq(output_point5_u_custom, output_point5_u_library);

  char output_10point5_u_custom[100];
  s21_sprintf(output_10point5_u_custom, "'%10.5u'", number);
  char output_10point5_u_library[100];
  sprintf(output_10point5_u_library, "'%10.5u'", number);
  ck_assert_str_eq(output_10point5_u_custom, output_10point5_u_library);

  char output_hu_custom[100];
  s21_sprintf(output_hu_custom, "'%hu'", hnum);
  char output_hu_library[100];
  sprintf(output_hu_library, "'%hu'", hnum);
  ck_assert_str_eq(output_hu_custom, output_hu_library);

  char output_lu_custom[100];
  s21_sprintf(output_lu_custom, "'%lu'", lnum);
  char output_lu_library[100];
  sprintf(output_lu_library, "'%lu'", lnum);
  ck_assert_str_eq(output_lu_custom, output_lu_library);

  char output_i_custom[100];
  s21_sprintf(output_i_custom, "%i", 52);
  char output_i_library[100];
  sprintf(output_i_library, "%i", 52);
  ck_assert_str_eq(output_i_custom, output_i_library);

  char output_e_custom[100];
  s21_sprintf(output_e_custom, "%e", 0.0000123456);
  char output_e_library[100];
  sprintf(output_e_library, "%e", 0.0000123456);
  ck_assert_str_eq(output_e_custom, output_e_library);

  char output_number_e_custom[100];
  s21_sprintf(output_number_e_custom, "%e", 12345.0);
  char output_number_e_library[100];
  sprintf(output_number_e_library, "%e", 12345.0);
  ck_assert_str_eq(output_number_e_custom, output_number_e_library);

  char output_lnum_e_custom[100];
  s21_sprintf(output_lnum_e_custom, "%e", 123456789.0);
  char output_lnum_e_library[100];
  sprintf(output_lnum_e_library, "%e", 123456789.0);
  ck_assert_str_eq(output_lnum_e_custom, output_lnum_e_library);

  char output_E_custom[100];
  s21_sprintf(output_E_custom, "%E", 0.0000123456);
  char output_E_library[100];
  sprintf(output_E_library, "%E", 0.0000123456);
  ck_assert_str_eq(output_E_custom, output_E_library);

  char output_number_E_custom[100];
  s21_sprintf(output_number_E_custom, "%E", 12345.0);
  char output_number_E_library[100];
  sprintf(output_number_E_library, "%E", 12345.0);
  ck_assert_str_eq(output_number_E_custom, output_number_E_library);

  char output_lnum_E_custom[100];
  s21_sprintf(output_lnum_E_custom, "%E", 123456789.0);
  char output_lnum_E_library[100];
  sprintf(output_lnum_E_library, "%E", 123456789.0);
  ck_assert_str_eq(output_lnum_E_custom, output_lnum_E_library);

  char output_o_custom[100];
  s21_sprintf(output_o_custom, "%o", 100);
  char output_o_library[100];
  sprintf(output_o_library, "%o", 100);
  ck_assert_str_eq(output_o_custom, output_o_library);

  char output_x_custom[100];
  s21_sprintf(output_x_custom, "%x", 100);
  char output_x_library[100];
  sprintf(output_x_library, "%x", 100);
  ck_assert_str_eq(output_x_custom, output_x_library);

  char output_X_custom[100];
  s21_sprintf(output_X_custom, "%X", 100);
  char output_X_library[100];
  sprintf(output_X_library, "%X", 100);
  ck_assert_str_eq(output_X_custom, output_X_library);

  char output_number_n_custom[100];
  char output_number_n_library[100];
  int count_custom = 0;
  s21_sprintf(output_number_n_custom, "%n", &count_custom);
  int count_library = 0;
  sprintf(output_number_n_library, "%n", &count_library);
  ck_assert_int_eq(count_custom, count_library);

  char output_hnum_n_custom[100];
  char output_hnum_n_library[100];
  int count_hnum_n_custom = 0;
  s21_sprintf(output_hnum_n_custom, "%n", &count_hnum_n_custom);
  int count_hnum_n_library = 0;
  sprintf(output_hnum_n_library, "%n", &count_hnum_n_library);
  ck_assert_int_eq(count_hnum_n_custom, count_hnum_n_library);

  char output_lnum_n_custom[100];
  char output_lnum_n_library[100];
  int count_lnum_n_custom = 0;
  s21_sprintf(output_lnum_n_custom, "%n", &count_lnum_n_custom);
  int count_lnum_n_library = 0;
  sprintf(output_lnum_n_library, "%n", &count_lnum_n_library);
  ck_assert_int_eq(count_lnum_n_custom, count_lnum_n_library);

  void *ptr_number = (void *)&number;
  char output_number_p_custom[100];
  s21_sprintf(output_number_p_custom, "%p", ptr_number);
  char output_number_p_library[100];
  sprintf(output_number_p_library, "%p", ptr_number);
  ck_assert_str_eq(output_number_p_custom, output_number_p_library);

  void *ptr_hnum = (void *)&hnum;
  char output_hnum_p_custom[100];
  s21_sprintf(output_hnum_p_custom, "%p", ptr_hnum);
  char output_hnum_p_library[100];
  sprintf(output_hnum_p_library, "%p", ptr_hnum);
  ck_assert_str_eq(output_hnum_p_custom, output_hnum_p_library);

  void *ptr_lnum = (void *)&lnum;
  char output_lnum_p_custom[100];
  s21_sprintf(output_lnum_p_custom, "%p", ptr_lnum);
  char output_lnum_p_library[100];
  sprintf(output_lnum_p_library, "%p", ptr_lnum);
  ck_assert_str_eq(output_lnum_p_custom, output_lnum_p_library);

  char output_number_plus_custom[100];
  s21_sprintf(output_number_plus_custom, "%+d", number);
  char output_number_plus_library[100];
  sprintf(output_number_plus_library, "%+d", number);
  ck_assert_str_eq(output_number_plus_custom, output_number_plus_library);

  char output_hnum_plus_custom[100];
  s21_sprintf(output_hnum_plus_custom, "%+d", hnum);
  char output_hnum_plus_library[100];
  sprintf(output_hnum_plus_library, "%+d", hnum);
  ck_assert_str_eq(output_hnum_plus_custom, output_hnum_plus_library);

  char output_number_g_custom[100];
  s21_sprintf(output_number_g_custom, "%g", 12345.0);
  char output_number_g_library[100];
  sprintf(output_number_g_library, "%g", 12345.0);
  ck_assert_str_eq(output_number_g_custom, output_number_g_library);

  char output_number_G_custom[100];
  s21_sprintf(output_number_G_custom, "%G", 12345.0);
  char output_number_G_library[100];
  sprintf(output_number_G_library, "%G", 12345.0);
  ck_assert_str_eq(output_number_G_custom, output_number_G_library);

  char output_2_g_custom[100];
  s21_sprintf(output_2_g_custom, "%g", 123456789.0);
  char output_2_g_library[100];
  sprintf(output_2_g_library, "%g", 123456789.0);
  ck_assert_str_eq(output_2_g_custom, output_2_g_library);

  char output_2_G_custom[100];
  s21_sprintf(output_2_G_custom, "%G", 123456789.0);
  char output_2_G_library[100];
  sprintf(output_2_G_library, "%G", 123456789.0);
  ck_assert_str_eq(output_2_G_custom, output_2_G_library);

  char output_3_g_custom[100];
  s21_sprintf(output_3_g_custom, "%g", 0.0000123456);
  char output_3_g_library[100];
  sprintf(output_3_g_library, "%g", 0.0000123456);
  ck_assert_str_eq(output_3_g_custom, output_3_g_library);

  char output_3_G_custom[100];
  s21_sprintf(output_3_G_custom, "%G", 0.0000123456);
  char output_3_G_library[100];
  sprintf(output_3_G_library, "%G", 0.0000123456);
  ck_assert_str_eq(output_3_G_custom, output_3_G_library);

  char output_number_g_hash_custom[100];
  s21_sprintf(output_number_g_hash_custom, "%#g", 12345.6789);
  char output_number_g_hash_library[100];
  sprintf(output_number_g_hash_library, "%#g", 12345.6789);
  ck_assert_str_eq(output_number_g_hash_custom, output_number_g_hash_library);
}
END_TEST
START_TEST(test_s21_sscanf) {
  int a, b;
  float c, d;
  int count1, count2;

  // Тест на целые числа
  count1 = s21_sscanf("123 4567", "%d %d", &a, &b);
  count2 = sscanf("123 4567", "%d %d", &a, &b);
  ck_assert_int_eq(count1, count2);
  ck_assert_int_eq(a, 123);
  ck_assert_int_eq(b, 4567);

  // Тест на вещественные числа
  count1 = s21_sscanf("3.14 -42.5e2", "%f %f", &c, &d);
  count2 = sscanf("3.14 -42.5e2", "%f %f", &c, &d);
  ck_assert_int_eq(count1, count2);
  ck_assert(c - 3.14f < 1e-6);
  ck_assert(d - (-4250.0f) < 1e-6);

  // Тест на строки и ширину
  char s1[10], s2[10];
  count1 = s21_sscanf("hello world", "%5s %5s", s1, s2);
  count2 = sscanf("hello world", "%5s %5s", s1, s2);
  ck_assert_int_eq(count1, count2);
  ck_assert_str_eq(s1, "hello");
  ck_assert_str_eq(s2, "world");

  // Тест на подавление присваивания
  count1 = s21_sscanf("skip 42", "%*s %d", &a);
  count2 = sscanf("skip 42", "%*s %d", &a);
  ck_assert_int_eq(count1, count2);
  ck_assert_int_eq(a, 42);

  // Тест на шестнадцатеричные числа
  unsigned int hex;
  count1 = s21_sscanf("1a3f", "%x", &hex);
  count2 = sscanf("1a3f", "%x", &hex);
  ck_assert_int_eq(count1, count2);
  ck_assert_int_eq(hex, 0x1a3f);

  // Тест на модификаторы длины
  short short_val;
  long long_val;
  count1 = s21_sscanf("32767 2147483647", "%hd %ld", &short_val, &long_val);
  count2 = sscanf("32767 2147483647", "%hd %ld", &short_val, &long_val);
  ck_assert_int_eq(count1, count2);
  ck_assert_int_eq(short_val, 32767);
  ck_assert_int_eq(long_val, 2147483647L);

  // Тест на символы
  char c1, c2;
  count1 = s21_sscanf("abc", "%c%c", &c1, &c2);
  count2 = sscanf("abc", "%c%c", &c1, &c2);
  ck_assert_int_eq(count1, count2);
  ck_assert(c1 == 'a');
  ck_assert(c2 == 'b');

  // Тест на %n
  int pos1, pos2;
  s21_sscanf("12345test%n", "%d%n", &a, &pos1);
  sscanf("12345test%n", "%d%n", &a, &pos2);
  ck_assert_int_eq(pos1, pos2);

  // Тест для %p (сравнение адресов указателей)
  const char *input = "random_address";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  s21_sscanf(input, "%p", &ptr1);
  sscanf(input, "%p", &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);

  // Тест для %e
  const char *str = "3.14e2";
  float value1, value2;
  s21_sscanf(str, "%e", &value1);
  sscanf(str, "%e", &value2);
  ck_assert_float_eq(value1, value2);

  // Тест для %i
  const char *str2 = "105";
  int val1, val2;
  s21_sscanf(str2, "%i", &val1);
  sscanf(str2, "%i", &val2);
  ck_assert_int_eq(val1, val2);

  // Тест для %o
  const char *str3 = "125";
  int val3, val4;
  s21_sscanf(str3, "%o", &val3);
  sscanf(str3, "%o", &val4);
  ck_assert_int_eq(val3, val4);

  // Тест для %u
  const char *str4 = "1234";
  int val5, val6;
  s21_sscanf(str4, "%u", &val5);
  sscanf(str4, "%u", &val6);
  ck_assert_int_eq(val5, val6);

  // Тест для %n
  const char *str5 = "123 456 789";
  int num1_1, num2_1, num3_1;
  int count1_1, count2_1;
  int num1_2, num2_2, num3_2;
  int count1_2, count2_2;
  s21_sscanf(str5, "%d%n %d%n %d", &num1_1, &count1_1, &num2_1, &count2_1,
             &num3_1);
  sscanf(str5, "%d%n %d%n %d", &num1_2, &count1_2, &num2_2, &count2_2, &num3_2);
  ck_assert_int_eq(num1_1, num1_2);
  ck_assert_int_eq(count1_1, count1_2);
  ck_assert_int_eq(num2_1, num2_2);
  ck_assert_int_eq(count2_1, count2_2);
  ck_assert_int_eq(num3_1, num3_2);
}
END_TEST

START_TEST(test_to_upper) {
  char test_stroke[] = "Apple_77";
  char expected_stroke[] = "APPLE_77";
  char *result = to_upper(test_stroke);
  ck_assert_str_eq(expected_stroke, result);
  free(result);
}
END_TEST

START_TEST(test_to_lower) {
  char test_stroke[] = "sBER_21";
  char expected_stroke[] = "sber_21";
  char *result = to_lower(test_stroke);
  ck_assert_str_eq(expected_stroke, result);
  free(result);
}
END_TEST

START_TEST(test_insert) {
  char src[] = "U lukomoria  zeleniy";
  char str[] = "dub";
  char expected_stroke[] = "U lukomoria dub zeleniy";
  char *result = insert(src, str, 12);
  ck_assert_str_eq(expected_stroke, result);
  free(result);
}

START_TEST(test_trim) {
  char *stroke = "Predsedatel pravleniaOO";
  char *trim_chars = "POk";
  char expected_stroke[] = "redsedatel pravlenia";
  char *result = trim(stroke, trim_chars);
  ck_assert_str_eq(expected_stroke, result);
  free(result);
}

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_sprintf);
  tcase_add_test(tc_core, test_s21_sscanf);
  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_trim);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite *s = s21_string_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}