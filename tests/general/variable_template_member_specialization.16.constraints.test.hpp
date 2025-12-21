// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_16_CONSTRAINTS_H
#define CONCEPTRODON_GENERAL_TESTS_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_16_CONSTRAINTS_H

#include <cstddef>
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace GeneralTests {
namespace VariableTemplateMemberSpecialization16Constraints {




/******************************************************************************************************/
template<size_t>
struct Tester
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

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<typename...>
struct Vessel {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester <
#define SHEEP_SUFFIX    \
    >::Page<0>
#define SHEEP_SEPARATOR \
    ,

using Dummy = Vessel<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif