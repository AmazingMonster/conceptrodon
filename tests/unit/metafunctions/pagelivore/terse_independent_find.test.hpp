// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_TERSE_INDEPENDENT_FIND_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_TERSE_INDEPENDENT_FIND_H

#include <utility>

#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/metafunctions/pagelivore/terse_independent_find.hpp"
#include "conceptrodon/metafunctions/varybivore/are_no_greater_than.hpp"
#include "conceptrodon/metafunctions/varybivore/are_no_less_than.hpp"

#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestTerseIndependentFind {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto Found = TerseIndependentFind
<
    Varybivore::AreNoGreaterThan<I>::template Page,
    Varybivore::AreNoLessThan<I>::template Page
>
::template Page_v<SHEEP_SPROUT(40)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(40), ALKANE_SPROUT(80)>;
#include "macaron/fragmental/amenity/instances/undef_integer_negative_one_alkane.hpp"
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define SHEEP_PREFIX    \
    Found <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
SAME_TYPE(Shuttle<SHEEP_SPROUT(120)>);

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