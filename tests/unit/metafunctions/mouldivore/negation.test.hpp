// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_NEGATION_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_NEGATION_H

#include <utility>

#include "conceptrodon/mouldivore/negation.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestNegation {




/******************************************************************************************************/
template<typename First, typename Second>
struct IsLess
{
    static constexpr bool value
    {First::value < Second::value};
};

template<typename...Args>
using IsNoLess = Negation<IsLess>::Mold<Args...>;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 1>>::value);
VALID(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 0>>::value);
INVALID(IsNoLess<std::integral_constant<int, 1>, std::integral_constant<int, 2>>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif