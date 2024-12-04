// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_GENERAL_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_5_H
#define CONCEPTRODON_TESTS_GENERAL_VARIABLE_TEMPLATE_MEMBER_SPECIALIZATION_5_H

#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace GeneralTests {
namespace VariableTemplateMemberSpecialization5 {




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