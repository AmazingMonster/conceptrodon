// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_4TH_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_4TH_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/phantom.hpp"

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
namespace TestZip4th {




/******************************************************************************************************/
template<size_t>
struct TesterA 
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};


template<size_t>
struct TesterB 
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};


template<typename>
struct TesterC {};

template
<
    template<template<auto...> class...> class Holder,
    template<auto...> class A,
    template<auto...> class B
>
struct TesterC<Holder<A, B>>
{ using type = Capsule<A<0>, B<0>>; };

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
    >::Page<0>, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >::Page<0>>
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
    >::Page
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Phantom<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >::Page
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Phantom<SHEEP_SPROUT(300)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(TesterD<Zip<ArgA, ArgB>::Sail<Phantom>::Road<Capsule>>::type);

#define SHEEP_PREFIX \
    TesterC<Zip<ArgA, ArgB>::Sail<Phantom>::Page<
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