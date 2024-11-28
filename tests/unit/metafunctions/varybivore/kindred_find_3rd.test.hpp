// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_KINDRED_FIND_3RD_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_KINDRED_FIND_3RD_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/varybivore/kindred_find.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/are_no_greater_than.hpp"
#include "conceptrodon/varybivore/are_no_less_than.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestKindredFind3rd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto Found = KindredFind<SHEEP_SPROUT(240)>
::Rail_v<AreNoLessThan<I>::template Page, AreNoGreaterThan<I>::template Page>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(240)>;
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
SAME_TYPE(Shuttle<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif