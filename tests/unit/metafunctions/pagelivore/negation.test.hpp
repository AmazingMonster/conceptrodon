// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_NEGATION_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_NEGATION_H

#include <utility>

#include "conceptrodon/metafunctions/pagelivore/negation.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestNegation {




/******************************************************************************************************/
template<auto First, auto Second>
struct IsLess
{
    static constexpr bool value
    {First < Second};
};

template<auto...Args>
using IsNoLess = Negation<IsLess>::Page<Args...>;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(IsNoLess<1, 1>::value);
VALID(IsNoLess<1, 0>::value);
INVALID(IsNoLess<1, 2>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif