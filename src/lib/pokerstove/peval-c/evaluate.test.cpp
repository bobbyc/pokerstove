#include <gtest/gtest.h>
#include "evaluate.h"

TEST(Evaluator, holdem_evaluation) {

    int rc = 0;
    double equity[10];
    size_t size = sizeof(equity)/sizeof(double);

    rc = evaluate_holdem("KsKhKc", "Qc3s", equity, &size);
    EXPECT_NE(0, rc);
    EXPECT_EQ(2, size);

    size = sizeof(equity)/sizeof(double);
    rc = evaluate_holdem("", "Qc3s AsAh", equity, &size);
    EXPECT_NE(0, rc);
    EXPECT_EQ(2, size);

    size = sizeof(equity)/sizeof(double);
    rc = evaluate_holdem("", "AsKh 3s5h", equity, &size);
    EXPECT_NE(0, rc);
    EXPECT_EQ(2, size);
    for ( size_t i = 0 ; i < size; i++)
        printf("Equity %d = %f \n", i, equity[i]);
}
