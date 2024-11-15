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
    Reverie<Capsule, TesterA>

SAME_TYPE(ExtendFront<Reverie<TesterA>>::Road<Capsule>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Phantom<Shuttle, TesterB>

SAME_TYPE(ExtendFront<Phantom<TesterB>>::Rail<Shuttle>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Forlorn<Reverie, TesterC>

SAME_TYPE(ExtendFront<Forlorn<TesterC>>::Flow<Reverie>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Travail<Phantom, TesterD>

SAME_TYPE(ExtendFront<Travail<TesterD>>::Sail<Phantom>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Lullaby<Forlorn, TesterE>

SAME_TYPE(ExtendFront<Lullaby<TesterE>>::Snow<Forlorn>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Halcyon<Travail, TesterF>

SAME_TYPE(ExtendFront<Halcyon<TesterF>>::Hail<Travail>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Pursuit<Lullaby, TesterG>

SAME_TYPE(ExtendFront<Pursuit<TesterG>>::Lull<Lullaby>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Persist<Halcyon, TesterH>

SAME_TYPE(ExtendFront<Persist<TesterH>>::Calm<Halcyon>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Sunrise<Pursuit, TesterI>

SAME_TYPE(ExtendFront<Sunrise<TesterI>>::Grit<Pursuit>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Morning<Persist, TesterJ>

SAME_TYPE(ExtendFront<Morning<TesterJ>>::Will<Persist>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Arcadia<Sunrise, TesterK>

SAME_TYPE(ExtendFront<Arcadia<TesterK>>::Glow<Sunrise>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Nirvana<Morning, TesterL>

SAME_TYPE(ExtendFront<Nirvana<TesterL>>::Dawn<Morning>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif