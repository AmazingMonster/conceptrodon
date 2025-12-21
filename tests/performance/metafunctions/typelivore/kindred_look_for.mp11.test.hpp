// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_KINDRED_LOOK_FOR_2ND_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_KINDRED_LOOK_FOR_2ND_H

#include <concepts>
#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/typelivore/kindred_look_for.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/metafunctions/typelivore/is_same_as.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestKindredLookFor2nd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using CapsuleTester = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    boost::mp11::mp_size_t<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using SupposedMPResult = Capsule<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR


#define SUPPOSED_TYPE \
    SupposedMPResult

template<int I>
using MP11_Found = boost::mp11::mp_find_if
<CapsuleTester, IsSameAs<std::integral_constant<int, I>>::template Mold>;

#define SHEEP_PREFIX    \
    MP11_Found <
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
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<int I>
constexpr auto Found = KindredLookFor<SHEEP_SPROUT(240)>
::Road_v<IsSameAs<std::integral_constant<int, I>>::template Mold>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#define SUPPOSED_TYPE \
    SupposedResult

#define SHEEP_PREFIX    \
    Found <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
    
SAME_TYPE(Shuttle<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#endif

}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif