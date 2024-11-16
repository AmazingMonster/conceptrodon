// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_RAIL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_RAIL_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/reverie.hpp"

#include "conceptrodon/descend/descend/omennivore/zip.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/travail.hpp"
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
namespace TestZipRail {




/******************************************************************************************************/
template<size_t>
struct TesterA 
{
    template<template<auto...> class...>
    struct ProtoRail {};

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};


template<size_t>
struct TesterB 
{
    template<template<auto...> class...>
    struct ProtoRail {};

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename>
struct TesterC {};

template
<
    template<template<template<auto...> class...> class...> class Holder,
    template<template<auto...> class...> class A,
    template<template<auto...> class...> class B
>
struct TesterC<Holder<A, B>>
{ using type = Capsule<A<Shuttle>, B<Shuttle>>; };

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
    >::Rail<Shuttle>, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >::Rail<Shuttle>>
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
    >::Rail
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Travail<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >::Rail
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Travail<SHEEP_SPROUT(300)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(TesterD<Zip<ArgA, ArgB>::Hail<Travail>::Road<Capsule>>::type);

#define SHEEP_PREFIX \
    TesterC<Zip<ArgA, ArgB>::Hail<Travail>::Page<
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