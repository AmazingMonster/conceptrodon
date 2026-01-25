// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_SEQUNIVORE_UNIT_TESTS_TEST_KINDRED_REPACK_H
#define CONCEPTRODON_SEQUNIVORE_UNIT_TESTS_TEST_KINDRED_REPACK_H

#include "conceptrodon/metafunctions/sequnivore/kindred_repack.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Sequnivore {
namespace UnitTests {
namespace TestKindredRepack {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Operation;
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(240)>;
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

SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::UniRail<Operation>);
SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::Rail<Operation>);

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

using SupposedResult_1 = Operation<SHEEP_SPROUT(240)>;

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

SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::UniRail<Operation>);
SAME_TYPE(KindredRepack<SHEEP_SPROUT(240)>::Rail<Operation>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif