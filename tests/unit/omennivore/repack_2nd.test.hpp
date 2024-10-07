// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_REPACK_2ND_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_REPACK_2ND_H

#include "conceptrodon/descend/omennivore/repack.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestRepack2nd {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedIndexSequence = std::index_sequence<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/**************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedIndexSequence

#define SHEEP_PREFIX    \
    Shuttle<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Repack<SHEEP_SPROUT(240)>::UniRail<std::index_sequence>);
SAME_TYPE(Repack<SHEEP_SPROUT(240)>::Rail<std::index_sequence>::type);
SAME_TYPE(Repack<SHEEP_SPROUT(240)>::Rail_t<std::index_sequence>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    static_cast<std::make_signed_t<size_t>>(
#define SHEEP_SUFFIX    \
    )
#define SHEEP_SEPARATOR \
    ,

using SupposedShuttle = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/**************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedShuttle

#define SHEEP_PREFIX    \
    std::integer_sequence<int,
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Repack<SHEEP_SPROUT(240)>::UniRail<Shuttle>);
SAME_TYPE(Repack<SHEEP_SPROUT(240)>::Rail<Shuttle>::type);
SAME_TYPE(Repack<SHEEP_SPROUT(240)>::Rail_t<Shuttle>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif