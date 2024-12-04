// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H

#include <utility>

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_front.hpp"

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

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestExtendFront {




/******************************************************************************************************/
template<typename...>
struct Vessel_0 {};

template<auto...>
struct Vessel_1 {};

template<template<typename...> class...>
struct Vessel_2 {};

template<template<auto...> class...>
struct Vessel_3 {};

template<template<template<typename...> class...> class...>
struct Vessel_4 {};

template<template<template<auto...> class...> class...>
struct Vessel_5 {};

template<template<template<template<typename...> class...> class...> class...>
struct Vessel_6 {};

template<template<template<template<auto...> class...> class...> class...>
struct Vessel_7 {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Vessel_8 {};

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Vessel_9 {};

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Vessel_10 {};

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Vessel_11 {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<double, int>

SAME_TYPE(ExtendFront<Capsule<int>>::Mold<double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<1, 0>

SAME_TYPE(ExtendFront<Shuttle<0>>::Page<1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Vehicle<Capsule, Vessel_0>

SAME_TYPE(ExtendFront<Vehicle<Vessel_0>>::Road<Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier<Shuttle, Vessel_1>

SAME_TYPE(ExtendFront<Carrier<Vessel_1>>::Rail<Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Reverie<Vehicle, Vessel_2>

SAME_TYPE(ExtendFront<Reverie<Vessel_2>>::Flow<Vehicle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Phantom<Carrier, Vessel_3>

SAME_TYPE(ExtendFront<Phantom<Vessel_3>>::Sail<Carrier>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Forlorn<Reverie, Vessel_4>

SAME_TYPE(ExtendFront<Forlorn<Vessel_4>>::Snow<Reverie>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Travail<Phantom, Vessel_5>

SAME_TYPE(ExtendFront<Travail<Vessel_5>>::Hail<Phantom>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Lullaby<Forlorn, Vessel_6>

SAME_TYPE(ExtendFront<Lullaby<Vessel_6>>::Cool<Forlorn>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Halcyon<Travail, Vessel_7>

SAME_TYPE(ExtendFront<Halcyon<Vessel_7>>::Calm<Travail>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Pursuit<Lullaby, Vessel_8>

SAME_TYPE(ExtendFront<Pursuit<Vessel_8>>::Grit<Lullaby>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Persist<Halcyon, Vessel_9>

SAME_TYPE(ExtendFront<Persist<Vessel_9>>::Will<Halcyon>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Sunrise<Pursuit, Vessel_10>

SAME_TYPE(ExtendFront<Sunrise<Vessel_10>>::Glow<Pursuit>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Morning<Persist, Vessel_11>

SAME_TYPE(ExtendFront<Morning<Vessel_11>>::Dawn<Persist>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif