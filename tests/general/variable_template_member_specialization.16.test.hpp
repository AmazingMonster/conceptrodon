// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_GENERAL_TESTS_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_16_H
#define CONCEPTRODON_GENERAL_TESTS_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_16_H

#include <cstddef>
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace GeneralTests {
namespace VariableTemplateMemberSpecialization16 {




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

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10, auto A11>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10, auto A11, auto A12>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10, auto A11, auto A12, auto A13>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10, auto A11, auto A12, auto A13, auto A14>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14>
    {
        static constexpr bool value 
        {true};
    };

    template<auto A0, auto A1, auto A2, auto A3, auto A4, auto A5, auto A6, auto A7, auto A8, auto A9, auto A10, auto A11, auto A12, auto A13, auto A14, auto A15>
    struct ProtoPage<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15>
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