// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_AMID_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_AMID_H

#include <utility>

#include "conceptrodon/metafunctions/typelivore/amid.hpp"
#include "conceptrodon/utilities/capsule.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestAmid {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult
/******************************************************************************************************/




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
template<size_t I>
using MPAt = boost::mp11::mp_at_c<SupposedResult, I>;

#define SHEEP_PREFIX    \
    MPAt <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,    
SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




#else




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<size_t I>
using At = Amid<SHEEP_SPROUT(240)>::UniPage<I>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#define SHEEP_PREFIX    \
    At<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




#endif




/******************************************************************************************************/
#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif