// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_2ND_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_AS_2ND_H

#include <concepts>
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/is_same_as.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsSameAs2nd {



/******************************************************************************************************/
template<size_t I>
using Check_0 = Carrier<IsSameAs<I>::template Page>;
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Check_0 <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using Tester_0 = Capsule<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
template<template<auto...> class>
struct Truth
{
    template<auto...>
    struct ProtoPage
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0>
    struct ProtoPage<A0>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1>
    struct ProtoPage<A0, A1>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2>
    struct ProtoPage<A0, A1, A2>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3>
    struct ProtoPage<A0, A1, A2, A3>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4>
    struct ProtoPage<A0, A1, A2, A3, A4>
    {
        static constexpr bool value 
        {true};
    };

    static constexpr bool value 
    {true};

    template<auto...>
    static constexpr bool Page_v {true};

    template<auto...Args>
    static constexpr bool ProtoPage_v {ProtoPage<Args...>::value};
};
/******************************************************************************************************/




/******************************************************************************************************/
template<size_t I>
constexpr bool Check_1 = Truth<IsSameAs<I>::template Page>::value;
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Check_1 <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using Tester_1 = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
constexpr bool Check_2 = Truth<IsSameAs<I>::template Page>
::template Page_v<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Check_2 <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using Tester_2 = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
constexpr bool Check_3 = Truth<IsSameAs<I>::template Page>
::template ProtoPage_v<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Check_3 <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using Tester_3 = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif