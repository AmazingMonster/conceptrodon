// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EXTEND_BACK_H

#include <concepts>
#include <tuple>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/extend_back.hpp"
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
namespace TestExtendBack {




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
    Vehicle<TesterA, Capsule>

SAME_TYPE(ExtendBack<Vehicle<TesterA>>::Road<Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Carrier<TesterB, Shuttle>

SAME_TYPE(ExtendBack<Carrier<TesterB>>::Rail<Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Reverie<TesterC, Vehicle>

SAME_TYPE(ExtendBack<Reverie<TesterC>>::Flow<Vehicle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Phantom<TesterD, Carrier>

SAME_TYPE(ExtendBack<Phantom<TesterD>>::Sail<Carrier>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Forlorn<TesterE, Reverie>

SAME_TYPE(ExtendBack<Forlorn<TesterE>>::Snow<Reverie>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Travail<TesterF, Phantom>

SAME_TYPE(ExtendBack<Travail<TesterF>>::Hail<Phantom>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Lullaby<TesterG, Forlorn>

SAME_TYPE(ExtendBack<Lullaby<TesterG>>::Cool<Forlorn>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Halcyon<TesterH, Travail>

SAME_TYPE(ExtendBack<Halcyon<TesterH>>::Calm<Travail>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Pursuit<TesterI, Lullaby>

SAME_TYPE(ExtendBack<Pursuit<TesterI>>::Grit<Lullaby>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Persist<TesterJ, Halcyon>

SAME_TYPE(ExtendBack<Persist<TesterJ>>::Will<Halcyon>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Sunrise<TesterK, Pursuit>

SAME_TYPE(ExtendBack<Sunrise<TesterK>>::Glow<Pursuit>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Morning<TesterL, Persist>

SAME_TYPE(ExtendBack<Morning<TesterL>>::Dawn<Persist>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif