// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_ARE_UNIQUE_3RD_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_ARE_UNIQUE_3RD_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/typelivore/are_unique.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestAreUnique3rd {




#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using Tester = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
VALID(boost::mp11::mp_is_set<Tester>::value);
/******************************************************************************************************/




#else




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(AreUnique<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/


#endif

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif