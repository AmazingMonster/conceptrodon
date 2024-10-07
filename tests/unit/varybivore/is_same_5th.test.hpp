// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_5TH_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_IS_SAME_5TH_H

#include <concepts>
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/varybivore/is_same.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestIsSame5th {



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

    template<auto...Args>
    requires (sizeof...(Args) == 1)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 2)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 3)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 4)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 5)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 6)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 7)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 8)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 9)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 10)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 11)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 12)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 13)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 14)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 15)
    struct ProtoPage<Args...>
    {
        static constexpr bool value 
        {true};
    };

    template<auto...Args>
    requires (sizeof...(Args) == 16)
    struct ProtoPage<Args...>
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




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif