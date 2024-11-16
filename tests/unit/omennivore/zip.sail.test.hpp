// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_SAIL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_SAIL_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/reverie.hpp"

#include "conceptrodon/descend/descend/omennivore/zip.hpp"
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
namespace TestZipSail {




/******************************************************************************************************/
template<size_t>
struct TesterA 
{
    template<template<template<auto...> class...> class...>
    struct ProtoSail {};

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};


template<size_t>
struct TesterB 
{
    template<template<template<auto...> class...> class...>
    struct ProtoSail {};

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};

template<typename>
struct TesterC {};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Holder,
    template<template<template<auto...> class...> class...> class A,
    template<template<template<auto...> class...> class...> class B
>
struct TesterC<Holder<A, B>>
{ using type = Capsule<A<Phantom>, B<Phantom>>; };

template<typename>
struct TesterD {};

template<template<typename...> class Holder, typename...Args>
struct TesterD<Holder<Args...>>
{
    using type = Capsule<typename TesterC<Args>::type...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Capsule<TesterA<
#define DOUBLE_SHEEP_MIDDLE \
    >::Sail<Phantom>, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >::Sail<Phantom>>
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
    >::Sail
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Halcyon<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >::Sail
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Halcyon<SHEEP_SPROUT(300)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(TesterD<Zip<ArgA, ArgB>::Calm<Halcyon>::Road<Capsule>>::type);

#define SHEEP_PREFIX \
    TesterC<Zip<ArgA, ArgB>::Calm<Halcyon>::Page<
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