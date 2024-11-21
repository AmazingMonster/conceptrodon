// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_COOL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_COOL_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/vehicle.hpp"

#include "conceptrodon/descend/descend/omennivore/zip.hpp"
#include "conceptrodon/pursuit.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestZipCool {




/******************************************************************************************************/
template<size_t>
struct TesterA 
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    struct ProtoCool {};

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;
};


template<size_t>
struct TesterB 
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    struct ProtoCool {};

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;
};

template<typename>
struct TesterC {};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Vessel,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class A,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class B
>
struct TesterC<Vessel<A, B>>
{ using type = Capsule<A<Forlorn>, B<Forlorn>>; };

template<typename>
struct TesterD {};

template<template<typename...> class Vessel, typename...Args>
struct TesterD<Vessel<Args...>>
{
    using type = Capsule<typename TesterC<Args>::type...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Capsule<TesterA<
#define DOUBLE_SHEEP_MIDDLE \
    >::Cool<Forlorn>, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >::Cool<Forlorn>>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Capsule<DOUBLE_SHEEP_SPROUT(240)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterA<
#define SHEEP_SUFFIX \
    >::Cool
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Pursuit<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >::Cool
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Pursuit<SHEEP_SPROUT(300)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(TesterD<Zip<ArgA, ArgB>::Glow<Pursuit>::Road<Capsule>>::type);

#define SHEEP_PREFIX \
    TesterC<Zip<ArgA, ArgB>::Glow<Pursuit>::Page<
#define SHEEP_SUFFIX \
    >>::type
#define SHEEP_SEPARATOR  \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR


#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif