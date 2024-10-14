// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_SENSIBLE_REFURBISH_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_SENSIBLE_REFURBISH_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/typelivore/sensible_refurbish.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestSensibleRefurbish {




/******************************************************************************************************/
template<typename T>
struct Tester
{
    using type = std::integral_constant<int, 1 + T::value>;
};

template<typename...Args>
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

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(SensibleRefurbish<SHEEP_SPROUT(240)>::Road<Capsule>::Road<Tester_t>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif