// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_FRONT_H

#include <concepts>
#include <tuple>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_front.hpp"
#include "macaron/judgmental/same_type.hpp"

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

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestExtendFront {




/******************************************************************************************************/
template<typename...>
struct TesterA {};

template<auto...>
struct TesterB {};

template<template<typename...> class...>
struct TesterC {};

template<template<auto...> class...>
struct TesterD {};

template<template<template<typename...> class...> class...>
struct TesterE {};

template<template<template<auto...> class...> class...>
struct TesterF {};

template<template<template<template<typename...> class...> class...> class...>
struct TesterG {};

template<template<template<template<auto...> class...> class...> class...>
struct TesterH {};

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct TesterI {};

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct TesterJ {};

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct TesterK {};

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct TesterL {};
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
    Vehicle<Capsule, TesterA>

SAME_TYPE(ExtendFront<Vehicle<TesterA>>::Road<Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier<Shuttle, TesterB>

SAME_TYPE(ExtendFront<Carrier<TesterB>>::Rail<Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Reverie<Vehicle, TesterC>

SAME_TYPE(ExtendFront<Reverie<TesterC>>::Flow<Vehicle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Phantom<Carrier, TesterD>

SAME_TYPE(ExtendFront<Phantom<TesterD>>::Sail<Carrier>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Forlorn<Reverie, TesterE>

SAME_TYPE(ExtendFront<Forlorn<TesterE>>::Snow<Reverie>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Travail<Phantom, TesterF>

SAME_TYPE(ExtendFront<Travail<TesterF>>::Hail<Phantom>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Lullaby<Forlorn, TesterG>

SAME_TYPE(ExtendFront<Lullaby<TesterG>>::Cool<Forlorn>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Halcyon<Travail, TesterH>

SAME_TYPE(ExtendFront<Halcyon<TesterH>>::Calm<Travail>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Pursuit<Lullaby, TesterI>

SAME_TYPE(ExtendFront<Pursuit<TesterI>>::Grit<Lullaby>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Persist<Halcyon, TesterJ>

SAME_TYPE(ExtendFront<Persist<TesterJ>>::Will<Halcyon>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Sunrise<Pursuit, TesterK>

SAME_TYPE(ExtendFront<Sunrise<TesterK>>::Glow<Pursuit>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Morning<Persist, TesterL>

SAME_TYPE(ExtendFront<Morning<TesterL>>::Dawn<Persist>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif