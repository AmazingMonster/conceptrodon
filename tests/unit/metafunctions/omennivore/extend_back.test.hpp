// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/omennivore/extend_back.hpp"

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

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestExtendBack {




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
    Capsule<int, double>

SAME_TYPE(ExtendBack<Capsule<int>>::Mold<double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<0, 1>

SAME_TYPE(ExtendBack<Shuttle<0>>::Page<1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Vehicle<Vessel_0, Capsule>

SAME_TYPE(ExtendBack<Vehicle<Vessel_0>>::Road<Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier<Vessel_1, Shuttle>

SAME_TYPE(ExtendBack<Carrier<Vessel_1>>::Rail<Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Reverie<Vessel_2, Vehicle>

SAME_TYPE(ExtendBack<Reverie<Vessel_2>>::Flow<Vehicle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Phantom<Vessel_3, Carrier>

SAME_TYPE(ExtendBack<Phantom<Vessel_3>>::Sail<Carrier>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Forlorn<Vessel_4, Reverie>

SAME_TYPE(ExtendBack<Forlorn<Vessel_4>>::Snow<Reverie>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Travail<Vessel_5, Phantom>

SAME_TYPE(ExtendBack<Travail<Vessel_5>>::Hail<Phantom>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Lullaby<Vessel_6, Forlorn>

SAME_TYPE(ExtendBack<Lullaby<Vessel_6>>::Cool<Forlorn>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Halcyon<Vessel_7, Travail>

SAME_TYPE(ExtendBack<Halcyon<Vessel_7>>::Calm<Travail>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Pursuit<Vessel_8, Lullaby>

SAME_TYPE(ExtendBack<Pursuit<Vessel_8>>::Grit<Lullaby>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Persist<Vessel_9, Halcyon>

SAME_TYPE(ExtendBack<Persist<Vessel_9>>::Will<Halcyon>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Sunrise<Vessel_10, Pursuit>

SAME_TYPE(ExtendBack<Sunrise<Vessel_10>>::Glow<Pursuit>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Morning<Vessel_11, Persist>

SAME_TYPE(ExtendBack<Morning<Vessel_11>>::Dawn<Persist>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif