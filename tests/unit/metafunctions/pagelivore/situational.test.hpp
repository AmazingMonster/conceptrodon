// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_SITUATIONAL_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_SITUATIONAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/situational.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestSituational {




/******************************************************************************************************/
template<auto A, auto B>
struct Predicate 
{ 
    static constexpr bool value 
    {static_cast<bool>(A())}; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE   \
    std::true_type{}

EQUAL_VALUE(Situational<Predicate>::Page_v<std::true_type{}, std::false_type{}>);
EQUAL_VALUE(Situational<Predicate>::Page_v<std::false_type{}, std::true_type{}>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif