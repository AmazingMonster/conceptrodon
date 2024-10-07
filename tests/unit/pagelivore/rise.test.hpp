// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_RISE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_RISE_H

#include "conceptrodon/descend/pagelivore/rise.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <type_traits>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestRise {





/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Tester<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Rise<Tester>::Page<SHEEP_SPROUT(200, +40), SHEEP_SPROUT(40)>);

#undef SUPPOSED_BASE
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif