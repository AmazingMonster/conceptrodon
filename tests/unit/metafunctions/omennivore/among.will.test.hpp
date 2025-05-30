// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_AMONG_WILL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_AMONG_WILL_H

#include "conceptrodon/omennivore/among.hpp"

#include <utility>

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAmongWill {




/******************************************************************************************************/
template<size_t>
struct Tester
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    struct ProtoWill {};

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Will<Halcyon>
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
    >::Will
#define SHEEP_SEPARATOR \
    ,

using Amongus = Among<Morning<SHEEP_SPROUT(80)>>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR


#define SHEEP_PREFIX    \
    Amongus::Page<
#define SHEEP_SUFFIX    \
    >::Will<Halcyon>
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