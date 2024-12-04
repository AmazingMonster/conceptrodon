// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_AMID_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_AMID_H

#include "conceptrodon/descend/varybivore/amid.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif


namespace boost {
namespace mp11 {

template<auto A> using mp_value = std::integral_constant<decltype(A), A>;

}}


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestAmid {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using ShuttleTester = Shuttle<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    boost::mp11::mp_value <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using SupposedMPResult = Capsule<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST





/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedMPResult


template<size_t I>
using MPAt = boost::mp11::mp_at_c<ShuttleTester, I>;

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

#undef SUPPOSED_TYPE
/******************************************************************************************************/



#else





/******************************************************************************************************/
using SupposedResult = ShuttleTester;

#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
constexpr auto At = Amid<SHEEP_SPROUT(240)>::ProtoPage<I>::value;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"


#define SHEEP_PREFIX    \
    At<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Shuttle<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE

#endif

}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif