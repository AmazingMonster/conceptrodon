// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_KINDRED_FIND_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_KINDRED_FIND_H

#include <utility>

#include "conceptrodon/varybivore/kindred_find.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/is_same_as.hpp"

#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestKindredFind {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto Found = KindredFind<SHEEP_SPROUT(80)>
::Rail_v<IsSameAs<I>::template Page>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(80), ALKANE_SPROUT(40)>;
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