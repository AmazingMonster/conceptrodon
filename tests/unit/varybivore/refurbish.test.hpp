// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_REFURBISH_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_REFURBISH_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/varybivore/refurbish.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestRefurbish {




/******************************************************************************************************/
template<auto I>
struct Tester
{
    using type = std::integral_constant<int, 1 + I>;
};

template<auto...Args>
using Tester_t = Tester<Args...>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Refurbish<SHEEP_SPROUT(240)>::Rail_t<Tester_t>);
SAME_TYPE(Refurbish<SHEEP_SPROUT(240)>::UniRail<Tester_t>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif