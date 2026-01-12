// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_AWAIT_H
#define CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_AWAIT_H

#include "conceptrodon/regularities/clxyosteon/await.hpp"
#include <iostream>
#include <type_traits>

namespace Conceptrodon {
namespace Clxyosteon {
namespace UnitTests {
namespace TestAwait {




/******************************************************************************************************/
inline void test()
{
    {
        std::cout
        << "Is lvalue await rvalue: "
        << std::boolalpha
        << Await<std::is_lvalue_reference>::Road<std::is_rvalue_reference>::Mold<int&>{std::type_identity<int&&>{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Is lvalue await rvalue: "
        << std::boolalpha
        << Await<std::is_lvalue_reference>::Road<std::is_rvalue_reference>::Mold<int&&>{std::type_identity<int&&>{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Call by std::true_type: "
        << std::boolalpha
        << Await<std::is_lvalue_reference>::Road<std::is_rvalue_reference>::Mold<int&>{std::true_type{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Call by std::false_type: "
        << std::boolalpha
        << Await<std::is_lvalue_reference>::Road<std::is_rvalue_reference>::Mold<int&>{std::false_type{}}() << std::endl;
    }
}
/******************************************************************************************************/

}}}}

#endif