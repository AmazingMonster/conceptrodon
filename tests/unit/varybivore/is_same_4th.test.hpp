// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_4TH_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_4TH_H

#include <concepts>
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/is_same.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace TestIsSame4th {



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

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5>
    struct ProtoPage<A0, A1, A2, A3, A4, A5>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7>
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
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
constexpr bool Check = Truth<IsSameAs<I>::template Page>
::template ProtoPage_v<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Check <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using Tester = Shuttle<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif