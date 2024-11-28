// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_TYPICAL_AMONG_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_TYPICAL_AMONG_H

#include "conceptrodon/typelivore/among.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestAmong {

// In this test,
// we will collect every element of list
//  std::integral_constant<0>,
//  ...,
//  std::integral_constant<239>
// using their indices and collect the result in Capsule.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult
/******************************************************************************************************/




#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST




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
using At = TypicalAmong<SHEEP_SPROUT(240)>::Page<I>::type;
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