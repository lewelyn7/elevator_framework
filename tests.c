
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "elevator_framework/elevator_framework.c"


START_TEST(test_elevator1){
    struct elevator_state elevator1 = elevator_init(0);
    request req;
    req.from = 8;
    req.to = 1;
    enqueue(&elevator1.queue, &req);
    calc_next_move(&elevator1);
    ck_assert_int_eq(elevator1.status.current_floor, 0);
    ck_assert_int_eq(elevator1.status.target_floor, 1);
    move_one_step(&elevator1);
    move_one_step(&elevator1);
    move_one_step(&elevator1);

}
END_TEST




void setup(void)
{
}

void teardown(void)
{
}





Suite * money_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_limits;

    s = suite_create("Money");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_elevator1);
    suite_add_tcase(s, tc_core);


    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
