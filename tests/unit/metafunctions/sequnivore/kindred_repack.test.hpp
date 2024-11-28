// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_SEQUNIVORE_KINDRED_REPACK_H
#define CONCEPTRODON_TESTS_UNIT_SEQUNIVORE_KINDRED_REPACK_H

#include "conceptrodon/descend/sequnivore/kindred_repack.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Sequnivore {
namespace UnitTests {
namespace TestKindredRepack {

// In this test, we will paste
//  Shuttle<0>,
//  ...,
//  Shuttle<239>
// together and place the result in Tester.

/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Tester;
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Tester<SHEEP_SPROUT(240)>;
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

SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::UniRail<Tester>);
SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::Rail<Tester>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/

// In this test, we will paste
//  Shuttle<0>,
//  ...,
//  Shuttle<239>
// together and place the result in Tester.

/******************************************************************************************************/
#define SHEEP_PREFIX    \
    static_cast<std::make_signed_t<size_t>>(
#define SHEEP_SUFFIX    \
    )
#define SHEEP_SEPARATOR \
    ,

using SupposedResult_1 = Tester<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
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

SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::UniRail<Tester>);
SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::Rail<Tester>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif