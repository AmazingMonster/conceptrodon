// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_SEQUNIVORE_TYPICAL_PASTE_H
#define CONCEPTRODON_TESTS_UNIT_SEQUNIVORE_TYPICAL_PASTE_H

#include "conceptrodon/sequnivore/paste.hpp"
#include "conceptrodon/shuttle.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"
#include <utility>


namespace Conceptrodon {
namespace Sequnivore {
namespace UnitTests {
namespace TestTypicalPaste {




/******************************************************************************************************/
template<size_t...>
struct FirstPackedVessel;
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

SAME_TYPE(TypicalPaste<FirstPackedVessel<>, SHEEP_SPROUT(240)>::type);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/

// In this test, we will paste
//  std::integer_sequence<size_t>,
//  std::integer_sequence<int, 0>,
//  ...,
//  std::integer_sequence<int, 239>
// together.

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

SAME_TYPE(TypicalPaste<std::integer_sequence<size_t>, SHEEP_SPROUT(240)>::type);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/

// In this test, we will paste
//  std::integer_sequence<int>,
//  std::index_sequence<0>,
//  ...,
//  std::index_sequence<239>
// together.

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

SAME_TYPE(TypicalPaste<std::integer_sequence<int>, SHEEP_SPROUT(240)>::type);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif