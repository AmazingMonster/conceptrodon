// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#define CONCEPTRODON_TEST_COMPARE_WITH_BOOST 0
#define CONCEPTRODON_TEST_ALTERNATIVE_SWITCH 0

#include "tests/unit/regularities/funyosteon/move_rvalue_copy_lvalue.test.hpp"
#include "tests/unit/regularities/clxyosteon/is_prvalue_awaiting_lvalue.test.hpp"
#include "tests/unit/regularities/clxyosteon/left_relate.test.hpp"
#include "tests/unit/regularities/clxyosteon/right_relate.test.hpp"
#include "tests/unit/regularities/clxyosteon/await.test.hpp"

int main()
{
    Conceptrodon::Funyosteon::UnitTests::TestMoveRvalueCopyLvalue::test();
    //Conceptrodon::Clxyosteon::UnitTests::TestIsLvalueAwaitingPrvalue::test();
    //Conceptrodon::Clxyosteon::UnitTests::TestLeftRelate::test();
    //Conceptrodon::Clxyosteon::UnitTests::TestRightRelate::test();
    Conceptrodon::Clxyosteon::UnitTests::TestAwait::test();
}