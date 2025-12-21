// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_RISE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_RISE_H

#include "conceptrodon/metafunctions/varybivore/rise.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestRise {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Rise<SHEEP_SPROUT(200, +40), SHEEP_SPROUT(40)>::Rail<Operation>);

#undef SUPPOSED_BASE
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif