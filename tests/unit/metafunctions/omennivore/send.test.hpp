// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H

#include <concepts>

#include "conceptrodon/omennivore/send.hpp"

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
namespace TestSend {




/******************************************************************************************************/
template
<
    typename,
    typename
>
struct Operation_0 {};

template
<
    auto,
    auto
>
struct Operation_1 {};

template
<
    template<typename...> class,
    template<typename...> class
>
struct Operation_2 {};

template
<
    template<auto...> class,
    template<auto...> class
>
struct Operation_3 {};

template
<
    template<template<typename...> class...> class,
    template<template<typename...> class...> class
>
struct Operation_4 {};

template
<
    template<template<auto...> class...> class,
    template<template<auto...> class...> class
>
struct Operation_5 {};

template
<
    template<template<template<typename...> class...> class...> class,
    template<template<template<typename...> class...> class...> class
>
struct Operation_6 {};

template
<
    template<template<template<auto...> class...> class...> class,
    template<template<template<auto...> class...> class...> class
>
struct Operation_7 {};

template
<
    template<template<template<template<typename...> class...> class...> class...> class,
    template<template<template<template<typename...> class...> class...> class...> class
>
struct Operation_8 {};

template
<
    template<template<template<template<auto...> class...> class...> class...> class,
    template<template<template<template<auto...> class...> class...> class...> class
>
struct Operation_9 {};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class
>
struct Operation_10 {};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class
>
struct Operation_11 {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_0<int, int>

SAME_TYPE(Send<Capsule<int, int>>::Road<Operation_0>);
SAME_TYPE(Send<Capsule<int, int>>::UniRoad<Operation_0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_1<0, 0>

SAME_TYPE(Send<Shuttle<0, 0>>::Rail<Operation_1>);
SAME_TYPE(Send<Shuttle<0, 0>>::UniRail<Operation_1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_2<Capsule, Capsule>

SAME_TYPE(Send<Vehicle<Capsule, Capsule>>::Flow<Operation_2>);
SAME_TYPE(Send<Vehicle<Capsule, Capsule>>::UniFlow<Operation_2>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_3<Shuttle, Shuttle>

SAME_TYPE(Send<Carrier<Shuttle, Shuttle>>::Sail<Operation_3>);
SAME_TYPE(Send<Carrier<Shuttle, Shuttle>>::UniSail<Operation_3>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_4<Vehicle, Vehicle>

SAME_TYPE(Send<Reverie<Vehicle, Vehicle>>::Snow<Operation_4>);
SAME_TYPE(Send<Reverie<Vehicle, Vehicle>>::UniSnow<Operation_4>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_5<Carrier, Carrier>

SAME_TYPE(Send<Phantom<Carrier, Carrier>>::Hail<Operation_5>);
SAME_TYPE(Send<Phantom<Carrier, Carrier>>::UniHail<Operation_5>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_6<Reverie, Reverie>

SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::Cool<Operation_6>);
SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::UniCool<Operation_6>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_7<Phantom, Phantom>

SAME_TYPE(Send<Travail<Phantom, Phantom>>::Calm<Operation_7>);
SAME_TYPE(Send<Travail<Phantom, Phantom>>::UniCalm<Operation_7>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_8<Forlorn, Forlorn>

SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::Grit<Operation_8>);
SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::UniGrit<Operation_8>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_9<Travail, Travail>

SAME_TYPE(Send<Halcyon<Travail, Travail>>::Will<Operation_9>);
SAME_TYPE(Send<Halcyon<Travail, Travail>>::UniWill<Operation_9>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_10<Lullaby, Lullaby>

SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::Glow<Operation_10>);
SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::UniGlow<Operation_10>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation_11<Halcyon, Halcyon>

SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::Dawn<Operation_11>);
SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::UniDawn<Operation_11>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif