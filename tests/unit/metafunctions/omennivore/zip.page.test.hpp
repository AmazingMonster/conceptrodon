// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_PAGE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ZIP_PAGE_H

#include <utility>

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/omennivore/zip.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestZipPage {




/******************************************************************************************************/
template<template<auto...> class...>
struct ArgArgVessel {};

template<size_t>
struct Tester_0 
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};


template<size_t>
struct Tester_1
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<auto...> class A,
    template<auto...> class B
>
struct CrossSectionHelper
{ using type = Capsule<A<0>, B<0>>; };

template
<
    template<auto...> class A,
    template<auto...> class B
>
using CrossSection = CrossSectionHelper<A, B>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Capsule<Tester_0<
#define DOUBLE_SHEEP_MIDDLE \
    >::Page<0>, Tester_1<
#define DOUBLE_SHEEP_SUFFIX \
    >::Page<0>>
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
    >::Page
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
    >::Page
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

SAME_TYPE(Zip<Arg_0, Arg_1>::Sail<CrossSection>::Road<Capsule>);

#define SHEEP_PREFIX \
    Zip<Arg_0, Arg_1>::Sail<CrossSection>::Page<
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