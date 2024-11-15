// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SEND_H

#include <concepts>
#include "conceptrodon/omennivore/send.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
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
#include "conceptrodon/arcadia.hpp"
#include "conceptrodon/nirvana.hpp"

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

SAME_TYPE(Send<Reverie<Capsule, Capsule>>::Flow<TesterC>);
SAME_TYPE(Send<Reverie<Capsule, Capsule>>::UniFlow<TesterC>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterD<Shuttle, Shuttle>

SAME_TYPE(Send<Phantom<Shuttle, Shuttle>>::Sail<TesterD>);
SAME_TYPE(Send<Phantom<Shuttle, Shuttle>>::UniSail<TesterD>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterE<Reverie, Reverie>

SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::Snow<TesterE>);
SAME_TYPE(Send<Forlorn<Reverie, Reverie>>::UniSnow<TesterE>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterF<Phantom, Phantom>

SAME_TYPE(Send<Travail<Phantom, Phantom>>::Hail<TesterF>);
SAME_TYPE(Send<Travail<Phantom, Phantom>>::UniHail<TesterF>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterG<Forlorn, Forlorn>

SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::Lull<TesterG>);
SAME_TYPE(Send<Lullaby<Forlorn, Forlorn>>::UniLull<TesterG>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterH<Travail, Travail>

SAME_TYPE(Send<Halcyon<Travail, Travail>>::Calm<TesterH>);
SAME_TYPE(Send<Halcyon<Travail, Travail>>::UniCalm<TesterH>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterI<Lullaby, Lullaby>

SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::Grit<TesterI>);
SAME_TYPE(Send<Pursuit<Lullaby, Lullaby>>::UniGrit<TesterI>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterJ<Halcyon, Halcyon>

SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::Will<TesterJ>);
SAME_TYPE(Send<Persist<Halcyon, Halcyon>>::UniWill<TesterJ>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterK<Pursuit, Pursuit>

SAME_TYPE(Send<Sunrise<Pursuit, Pursuit>>::Glow<TesterK>);
SAME_TYPE(Send<Sunrise<Pursuit, Pursuit>>::UniGlow<TesterK>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterL<Persist, Persist>

SAME_TYPE(Send<Morning<Persist, Persist>>::Dawn<TesterL>);
SAME_TYPE(Send<Morning<Persist, Persist>>::UniDawn<TesterL>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif