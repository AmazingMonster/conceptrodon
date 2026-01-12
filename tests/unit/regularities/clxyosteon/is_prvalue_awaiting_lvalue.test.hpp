// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_IS_PRVALUE_AWAITING_LVALUE_H
#define CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_IS_PRVALUE_AWAITING_LVALUE_H

#include "conceptrodon/regularities/clxyosteon/is_prvalue_awaiting_lvalue.hpp"
#include <iostream>

namespace Conceptrodon {
namespace Clxyosteon {
namespace UnitTests {
namespace TestIsLvalueAwaitingPrvalue {




/******************************************************************************************************/
struct Argument {};

template<typename Target, typename Arg>
void check(Arg&& arg)
{
    std::cout
    << "Is Lvalue to Prvalue: "
    << std::boolalpha
    << IsPrvalueAwaitingLvalue<Target>{std::type_identity<Arg>{}}() << std::endl;
}

template<typename Target>
void check()
{
    std::cout
    << "Is Lvalue to Prvalue: "
    << std::boolalpha
    << IsPrvalueAwaitingLvalue<Target>{std::true_type{}}() << std::endl;
}
/******************************************************************************************************/




/******************************************************************************************************/
inline void test()
{
    {
        Argument argument{};
        check<Argument>(argument);
    }

    std::cout << std::endl;

    {
        check<Argument>();
    }

    std::cout << std::endl;

    {
        check<Argument>(Argument{});
    }

    std::cout << std::endl;

    {
        Argument argument{};
        check<Argument>(std::move(argument));
    }

    std::cout << std::endl;
    {
        Argument argument{};
        check<Argument&>(argument);
    }

    std::cout << std::endl;

    {
        check<Argument&>(Argument{});
    }

    std::cout << std::endl;

    {
        Argument argument{};
        check<Argument&>(std::move(argument));
    }
}
/******************************************************************************************************/




}}}}

#endif