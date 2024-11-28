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
struct TesterA {};

template
<
    auto,
    auto
>
struct TesterB {};

template
<
    template<typename...> class,
    template<typename...> class
>
struct TesterC {};

template
<
    template<auto...> class,
    template<auto...> class
>
struct TesterD {};

template
<
    template<template<typename...> class...> class,
    template<template<typename...> class...> class
>
struct TesterE {};

template
<
    template<template<auto...> class...> class,
    template<template<auto...> class...> class
>
struct TesterF {};

template
<
    template<template<template<typename...> class...> class...> class,
    template<template<template<typename...> class...> class...> class
>
struct TesterG {};

template
<
    template<template<template<auto...> class...> class...> class,
    template<template<template<auto...> class...> class...> class
>
struct TesterH {};

template
<
    template<template<template<template<typename...> class...> class...> class...> class,
    template<template<template<template<typename...> class...> class...> class...> class
>
struct TesterI {};

template
<
    template<template<template<template<auto...> class...> class...> class...> class,
    template<template<template<template<auto...> class...> class...> class...> class
>
struct TesterJ {};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class
>
struct TesterK {};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class
>
struct TesterL {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterA<int, int>

SAME_TYPE(Send<Capsule<int, int>>::Road<TesterA>);
SAME_TYPE(Send<Capsule<int, int>>::UniRoad<TesterA>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterB<0, 0>

SAME_TYPE(Send<Shuttle<0, 0>>::Rail<TesterB>);
SAME_TYPE(Send<Shuttle<0, 0>>::UniRail<TesterB>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterC<Capsule, Capsule>

SAME_TYPE(Send<Vehicle<Capsule, Capsule>>::Flow<TesterC>);
SAME_TYPE(Send<Vehicle<Capsule, Capsule>>::UniFlow<TesterC>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterD<Shuttle, Shuttle>

SAME_TYPE(Send<Carrier<Shuttle, Shuttle>>::Sail<TesterD>);
SAME_TYPE(Send<Carrier<Shuttle, Shuttle>>::UniSail<TesterD>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterE<Vehicle, Vehicle>

SAME_TYPE(Send<Reverie<Vehicle, Vehicle>>::Snow<TesterE>);
SAME_TYPE(Send<Reverie<Vehicle, Vehicle>>::UniSnow<TesterE>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterF<Carrier, Carrier>

SAME_TYPE(Send<Phantom<Carrier, Carrier>>::Hail<TesterF>);
SAME_TYPE(Send<Phantom<Carrier, Carrier>>::UniHail<TesterF>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterG<Reverie, Reverie>

SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::Cool<TesterG>);
SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::UniCool<TesterG>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterH<Phantom, Phantom>

SAME_TYPE(Send<Travail<Phantom, Phantom>>::Calm<TesterH>);
SAME_TYPE(Send<Travail<Phantom, Phantom>>::UniCalm<TesterH>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterI<Forlorn, Forlorn>

SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::Grit<TesterI>);
SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::UniGrit<TesterI>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterJ<Travail, Travail>

SAME_TYPE(Send<Halcyon<Travail, Travail>>::Will<TesterJ>);
SAME_TYPE(Send<Halcyon<Travail, Travail>>::UniWill<TesterJ>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterK<Lullaby, Lullaby>

SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::Glow<TesterK>);
SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::UniGlow<TesterK>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterL<Halcyon, Halcyon>

SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::Dawn<TesterL>);
SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::UniDawn<TesterL>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif