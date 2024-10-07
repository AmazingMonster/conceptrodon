// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_SEGMENT_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_SEGMENT_H

#include <concepts>
#include <utility>
#include "conceptrodon/descend/pagelivore/segment.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestSegment {




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    1
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Ark<0, ALKANE_SPROUT(239)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Segment<Shuttle>::Page<SHEEP_SPROUT(240)>);
SAME_TYPE(Segment<Shuttle>::Mold<std::index_sequence<SHEEP_SPROUT(240)>>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/


}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif