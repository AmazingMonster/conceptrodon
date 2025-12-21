// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_CONJURE_SET_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_CONJURE_SET_H

#include <concepts>
#include "conceptrodon/metafunctions/typelivore/conjure_set.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestConjureSet {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(boost::mp11::mp_set_push_back<Capsule<>, SHEEP_SPROUT(240), std::integral_constant<int, 39>>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(ConjureSet<SHEEP_SPROUT(240), std::integral_constant<int, 39>>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/


#endif


}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif