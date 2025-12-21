// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ZIP_ROAD_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_ZIP_ROAD_H

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/metafunctions/omennivore/zip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestZipRoad {




/******************************************************************************************************/
template<typename...Nothingness>
struct ArgArg {};

template<template<template<typename...> class...> class...>
struct ArgArgVessel {};

template<size_t>
struct Tester_0 
{
    template<template<typename...> class...>
    struct ProtoRoad {};

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<size_t>
struct Tester_1
{
    template<template<typename...> class...>
    struct ProtoRoad {};

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template
<
    template<template<typename...> class...> class A,
    template<template<typename...> class...> class B
>
struct CrossSectionHelper
{ using type = Capsule<A<ArgArg>, B<ArgArg>>; };

template
<
    template<template<typename...> class...> class A,
    template<template<typename...> class...> class B
>
using CrossSection = CrossSectionHelper<A, B>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Capsule<Tester_0<
#define DOUBLE_SHEEP_MIDDLE \
    >::Road<ArgArg>, Tester_1<
#define DOUBLE_SHEEP_SUFFIX \
    >::Road<ArgArg>>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Capsule<DOUBLE_SHEEP_SPROUT(80)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    Tester_0<
#define SHEEP_SUFFIX \
    >::Road
#define SHEEP_SEPARATOR  \
    ,

using Arg_0 = ArgArgVessel<SHEEP_SPROUT(80)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    Tester_1<
#define SHEEP_SUFFIX \
    >::Road
#define SHEEP_SEPARATOR  \
    ,

using Arg_1 = ArgArgVessel<SHEEP_SPROUT(80)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(Zip<Arg_0, Arg_1>::Snow<CrossSection>::Road<Capsule>);

#define SHEEP_PREFIX \
    Zip<Arg_0, Arg_1>::Snow<CrossSection>::Page<
#define SHEEP_SUFFIX \
    >
#define SHEEP_SEPARATOR  \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(80)>);

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