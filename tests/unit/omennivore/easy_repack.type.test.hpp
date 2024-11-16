// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_REPACK_TYPE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_REPACK_TYPE_H

#include <utility>
#include "conceptrodon/descend/omennivore/easy_repack.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestEasyRepackType {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = std::tuple<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Capsule<std::integral_constant<int,
#define SHEEP_SUFFIX    \
    >>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(EasyRepack<SHEEP_SPROUT(240)>::UniRoad<std::tuple>);
SAME_TYPE(EasyRepack<SHEEP_SPROUT(240)>::Road<std::tuple>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/



}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif