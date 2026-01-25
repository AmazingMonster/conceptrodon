// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#define CONCEPTRODON_TEST_COMPARE_WITH_BOOST 0
#define CONCEPTRODON_TEST_ALTERNATIVE_SWITCH 0

#include "tests/unit/regularities/funyosteon/move_rvalue_while_copy_lvalue.test.hpp"
#include "tests/unit/regularities/funyosteon/copy_lvalue_to_prvalue_while_forward_others.test.hpp"
#include "tests/unit/regularities/clxyosteon/copy_lvalue_to_prvalue_while_forward_others.test.hpp"

int main()
{
    //Conceptrodon::Funyosteon::UnitTests::TestMoveRvalueWhileCopyLvalue::test();
    //Conceptrodon::Funyosteon::UnitTests::TestCopyLvalueToRvalueWhileForwardOthers::test();
    Conceptrodon::Clxyosteon::UnitTests::TestCopyLvalueToRvalueWhileForwardOthers::test();
}