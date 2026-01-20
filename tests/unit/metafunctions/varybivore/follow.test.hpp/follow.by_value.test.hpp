// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_FOLLOW_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_FOLLOW_H

#include "conceptrodon/metafunctions/varybivore/follow.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"
#include <utility>




namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestFollowByValue {
    
    


/******************************************************************************************************/
template<auto...Args>
struct Operation {};

template<auto...Args>
using Tester = Operation<Follow<Args>::template Page<0>::value...>;
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    0
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Operation<ALKANE_SPROUT(40)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Tester<SHEEP_SPROUT(40)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif