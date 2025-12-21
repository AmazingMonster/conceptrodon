// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_TYPICAL_AMONG_RAIL_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_TYPICAL_AMONG_RAIL_H

#include "conceptrodon/metafunctions/omennivore/among.hpp"

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vehicle.hpp"
#include "conceptrodon/utilities/carrier.hpp"
#include "conceptrodon/utilities/reverie.hpp"
#include "conceptrodon/utilities/phantom.hpp"
#include "conceptrodon/utilities/forlorn.hpp"
#include "conceptrodon/utilities/travail.hpp"
#include "conceptrodon/utilities/lullaby.hpp"
#include "conceptrodon/utilities/halcyon.hpp"
#include "conceptrodon/utilities/pursuit.hpp"
#include "conceptrodon/utilities/persist.hpp"
#include "conceptrodon/utilities/sunrise.hpp"
#include "conceptrodon/utilities/morning.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAmongRail {




/******************************************************************************************************/
template<size_t>
struct Tester
{
    template<template<auto...> class>
    struct ProtoRail {};

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Rail<Shuttle>
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Capsule<SHEEP_SPROUT(80)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult
/******************************************************************************************************/



/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Rail
#define SHEEP_SEPARATOR \
    ,

using Amongus = TypicalAmong<Phantom<SHEEP_SPROUT(80)>>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR


#define SHEEP_PREFIX    \
    Amongus::Page<
#define SHEEP_SUFFIX    \
    >::Rail<Shuttle>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(80)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif