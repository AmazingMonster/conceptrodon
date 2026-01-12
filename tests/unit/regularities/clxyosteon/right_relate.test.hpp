// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_RIGHT_RELATE_H
#define CONCEPTRODON_CLXYOSTEON_UNIT_TESTS_TEST_RIGHT_RELATE_H

#include "conceptrodon/regularities/clxyosteon/right_relate.hpp"
#include "conceptrodon/utilities/vay.hpp"
#include <ios>
#include <iostream>
#include <type_traits>

namespace Conceptrodon {
namespace Clxyosteon {
namespace UnitTests {
namespace TestRightRelate {




/******************************************************************************************************/
template<typename Left, typename Right>
struct Less
{
    static constexpr bool value {Left::value < Right::value};
};
/******************************************************************************************************/




/******************************************************************************************************/
inline void test()
{
    {
        std::cout
        << "Is Vay<1> right related to Vay<0> by Less: "
        << std::boolalpha
        << RightRelate<Less>::Mold<Vay<0>>{std::type_identity<Vay<1>>{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Is Vay<0> right related to Vay<1> by Less: "
        << std::boolalpha
        << RightRelate<Less>::Mold<Vay<1>>{std::type_identity<Vay<0>>{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Call by std::true_type: "
        << std::boolalpha
        << RightRelate<Less>::Mold<Vay<1>>{std::true_type{}}() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout
        << "Call by std::false_type: "
        << std::boolalpha
        << RightRelate<Less>::Mold<Vay<1>>{std::false_type{}}() << std::endl;
    }
}
/******************************************************************************************************/




}}}}

#endif