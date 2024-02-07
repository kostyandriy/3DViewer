#include <check.h>

#include "../C_part/back.h"

START_TEST(test_check_parser_1) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
    Parse_file(&Data, str);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_2) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0};
    Parse_file(&Data, str);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_3) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0};
    Parse_file(&Data, str);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_4) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    int result = 8;
    Parse_file(&Data, str);
    ck_assert_double_eq_tol(result, Data.v->amount_vert, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_5) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[2] = {-1.0, 1.0};
    Parse_file(&Data, str);
    for (int i = 0; i < 2; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->MinMax_x[i], 1e-06);
      ck_assert_double_eq_tol(result[i], Data.v->MinMax_y[i], 1e-06);
      ck_assert_double_eq_tol(result[i], Data.v->MinMax_z[i], 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_6) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0};
    Parse_file(&Data, str);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_7) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    int result = 6;
    Parse_file(&Data, str);
    ck_assert_double_eq_tol(result, Data.amount_polygons, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_8) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    int result = 4;
    Parse_file(&Data, str);
    for (int i = 0; i < Data.amount_polygons; i++) {
      ck_assert_double_eq_tol(result, Data.p[i].amount_p, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_parser_9) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    int result[4] = {2, 3, 4, 1};
    Parse_file(&Data, str);
    for (int i = 0; i < Data.p[0].amount_p; i++) {
      ck_assert_double_eq_tol(result[i], Data.p[0].p[i], 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_1) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {0.8, 0.8, -0.8, -0.8, 0.8, 0.8, -0.8, -0.8};
    Parse_file(&Data, str);
    scale_start(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_2) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-0.8, -0.8, -0.8, -0.8, 0.8, 0.8, 0.8, 0.8};
    Parse_file(&Data, str);
    scale_start(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_3) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-0.8, 0.8, 0.8, -0.8, -0.8, 0.8, 0.8, -0.8};
    Parse_file(&Data, str);
    scale_start(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_4) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
    Parse_file(&Data, str);
    center(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_5) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0};
    Parse_file(&Data, str);
    center(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_6) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0};
    Parse_file(&Data, str);
    center(&Data);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_7) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {5.0, 5.0, -5.0, -5.0, 5.0, 5.0, -5.0, -5.0};
    Parse_file(&Data, str);
    scale_cords(&Data, 5);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_8) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-8.0, -8.0, -8.0, -8.0, 8.0, 8.0, 8.0, 8.0};
    Parse_file(&Data, str);
    scale_cords(&Data, 8);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_9) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-0.1, 0.1, 0.1, -0.1, -0.1, 0.1, 0.1, -0.1};
    Parse_file(&Data, str);
    scale_cords(&Data, 0.1);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_10) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {5.0, 5.0, 3.0, 3.0, 5.0, 5.0, 3.0, 3.0};
    Parse_file(&Data, str);
    motion(&Data, 4.0, 0, 0);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_11) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-8.0, -8.0, -8.0, -8.0, -6.0, -6.0, -6.0, -6.0};
    Parse_file(&Data, str);
    motion(&Data, 0, -7.0, 0);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_12) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-0.1, 1.9, 1.9, -0.1, -0.1, 1.9, 1.9, -0.1};
    Parse_file(&Data, str);
    motion(&Data, 0, 0, 0.9);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_13) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
    Parse_file(&Data, str);
    turn(&Data, 30, 0);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].x, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_14) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = -0.366025404;
    Parse_file(&Data, str);
    turn(&Data, 30, 0);
    ck_assert_double_eq_tol(result, Data.v->cord[0].y, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_15) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = -1.3660254;
    Parse_file(&Data, str);
    turn(&Data, 60, 0);
    ck_assert_double_eq_tol(result, Data.v->cord[0].z, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_16) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = 0.366025404;
    Parse_file(&Data, str);
    turn(&Data, 30, 1);
    ck_assert_double_eq_tol(result, Data.v->cord[0].x, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_17) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result[8] = {-1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0};
    Parse_file(&Data, str);
    turn(&Data, 30, 1);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].y, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_18) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = -1.40883205;
    Parse_file(&Data, str);
    turn(&Data, 50, 1);
    ck_assert_double_eq_tol(result, Data.v->cord[0].z, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_19) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = -0.597672477;
    Parse_file(&Data, str);
    turn(&Data, 70, 2);
    ck_assert_double_eq_tol(result, Data.v->cord[0].x, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_20) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    double result = -0.529773725;
    Parse_file(&Data, str);
    turn(&Data, -23, 2);
    ck_assert_double_eq_tol(result, Data.v->cord[0].y, 1e-06);
    free_data(&Data);
  }
}
END_TEST

START_TEST(test_check_afinn_21) {
  Model_data_t Data;
  Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
  if (Data.v != NULL) {
    Data.p = NULL;
    Data.v->amount_vert = 0;
    Data.amount_polygons = 0;
    Data.v->cord = NULL;
    char str[20] = "../Models/cube.obj";
    Parse_file(&Data, str);
    double result[8] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0};  // z
    turn(&Data, -23, 2);
    for (int i = 0; i < 8; i++) {
      ck_assert_double_eq_tol(result[i], Data.v->cord[i].z, 1e-06);
    }
    free_data(&Data);
  }
}
END_TEST

int main(void) {
  Suite *s;
  TCase *tc;
  SRunner *sr;

  s = suite_create("tests");
  tc = tcase_create("test");

  tcase_add_test(tc, test_check_parser_1);
  tcase_add_test(tc, test_check_parser_2);
  tcase_add_test(tc, test_check_parser_3);
  tcase_add_test(tc, test_check_parser_4);
  tcase_add_test(tc, test_check_parser_5);
  tcase_add_test(tc, test_check_parser_6);
  tcase_add_test(tc, test_check_parser_7);
  tcase_add_test(tc, test_check_parser_8);
  tcase_add_test(tc, test_check_parser_9);

  tcase_add_test(tc, test_check_afinn_1);
  tcase_add_test(tc, test_check_afinn_2);
  tcase_add_test(tc, test_check_afinn_3);
  tcase_add_test(tc, test_check_afinn_4);
  tcase_add_test(tc, test_check_afinn_5);
  tcase_add_test(tc, test_check_afinn_6);
  tcase_add_test(tc, test_check_afinn_7);
  tcase_add_test(tc, test_check_afinn_8);
  tcase_add_test(tc, test_check_afinn_9);
  tcase_add_test(tc, test_check_afinn_10);
  tcase_add_test(tc, test_check_afinn_11);
  tcase_add_test(tc, test_check_afinn_12);
  tcase_add_test(tc, test_check_afinn_13);
  tcase_add_test(tc, test_check_afinn_14);
  tcase_add_test(tc, test_check_afinn_15);
  tcase_add_test(tc, test_check_afinn_16);
  tcase_add_test(tc, test_check_afinn_17);
  tcase_add_test(tc, test_check_afinn_18);
  tcase_add_test(tc, test_check_afinn_19);
  tcase_add_test(tc, test_check_afinn_20);
  tcase_add_test(tc, test_check_afinn_21);

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
