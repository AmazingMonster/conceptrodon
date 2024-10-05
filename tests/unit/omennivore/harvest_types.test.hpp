// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TEST_HARVEST_TYPES_H
#define CONCEPTRODON_OMENNIVORE_TEST_HARVEST_TYPES_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/omennivore/harvest_types.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestHarvestTypes {




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements)==240)
struct TesterA {};

template<auto I>
struct TesterB
{using type = std::integral_constant<int, I>; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = TesterA<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    TesterB<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(HarvestTypes<SHEEP_SPROUT(240)>::UniRoad<TesterA>);
SAME_TYPE(HarvestTypes<SHEEP_SPROUT(240)>::Road<TesterA>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif