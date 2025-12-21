// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_ARE_DISTINCT_3RD_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_ARE_DISTINCT_3RD_H

#include <concepts>
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/typelivore/are_distinct.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp" 
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestAreDistinct3rd {




#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using Tester = Capsule<SHEEP_SPROUT(160)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"




#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
VALID(boost::mp11::mp_is_set<Tester>::value);
/******************************************************************************************************/




#else




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
VALID(AreDistinct<SHEEP_SPROUT(160)>::value);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/


#endif

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif