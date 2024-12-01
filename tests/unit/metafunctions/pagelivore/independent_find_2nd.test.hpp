// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_INDEPENDENT_FIND_2ND_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_INDEPENDENT_FIND_2ND_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/independent_find.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/are_no_greater_than.hpp"
#include "conceptrodon/varybivore/are_no_less_than.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestIndependentFind2nd {



/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto FailFound = IndependentFind
<
    Varybivore::AreNoGreaterThan<-1>::template Page,
    Varybivore::AreNoLessThan<-1>::template Page
>
::Page_v<SHEEP_SPROUT(40), I>;

#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedFailedResult = SignedArk<ALKANE_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_negative_one_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedFailedResult

#define SHEEP_PREFIX    \
    FailFound <
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




}}}}

#include "macaron/fragmental/amenity/undef_alkane.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif