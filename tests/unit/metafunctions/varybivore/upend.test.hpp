// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_UPEND_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_UPEND_H

#include "conceptrodon/metafunctions/varybivore/upend.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestUpend {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep_reversed.hpp"
using SupposedResult = Operation<SHEEP_REVERSED_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep_reversed.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Upend<SHEEP_SPROUT(240)>::Rail<Operation>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif