// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_PREEN_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_PREEN_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/typelivore/preen.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestPreen {




/******************************************************************************************************/
template<typename T>
struct Tester
{
    using type = std::integral_constant<int, 1 + T::value>;
};
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
SAME_TYPE(Preen<SHEEP_SPROUT(240)>::Road_t<Tester>);
SAME_TYPE(Preen<SHEEP_SPROUT(240)>::UniRoad<Tester>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif