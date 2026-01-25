// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SEQUNIVORE_UNIT_TESTS_TEST_PASTE_H
#define CONCEPTRODON_SEQUNIVORE_UNIT_TESTS_TEST_PASTE_H

#include <utility>

#include "conceptrodon/metafunctions/sequnivore/paste.hpp"
#include "conceptrodon/utilities/shuttle.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Sequnivore {
namespace UnitTests {
namespace TestPaste {




/******************************************************************************************************/
template<size_t...>
struct FirstPackedVessel {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = FirstPackedVessel<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/**************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Shuttle<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Paste<FirstPackedVessel<>, SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_1 = std::integer_sequence<size_t, SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/**************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#define SHEEP_PREFIX    \
    std::integer_sequence<int,
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Paste<std::integer_sequence<size_t>, SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_2 = std::integer_sequence<int, SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/**************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#define SHEEP_PREFIX    \
    std::index_sequence<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Paste<std::integer_sequence<int>, SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif