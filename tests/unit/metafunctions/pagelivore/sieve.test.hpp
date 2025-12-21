// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_SIEVE_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_SIEVE_H

#include <concepts>

#include "conceptrodon/metafunctions/pagelivore/sieve.hpp"
#include "conceptrodon/utilities/shuttle.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestSieve {




/******************************************************************************************************/
template<auto Integer>
struct IsEven
{
    static constexpr bool value = Integer % 2 == 0;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(120, * 2 + 1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Sieve<IsEven>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Integer>
struct IsDivisibleByThirty
{
    static constexpr bool value = Integer % 30 == 0;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_1 = Shuttle
<
    SHEEP_SPROUT(29, +1),
    SHEEP_SPROUT(29, +31),
    SHEEP_SPROUT(29, +61),
    SHEEP_SPROUT(29, +91),
    SHEEP_SPROUT(29, +121),
    SHEEP_SPROUT(29, +151),
    SHEEP_SPROUT(29, +181),
    SHEEP_SPROUT(29, +211)
>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Sieve<IsEven, IsDivisibleByThirty>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif