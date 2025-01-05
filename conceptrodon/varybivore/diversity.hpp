// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TYPICAL_DIVERSITY_H
#define CONCEPTRODON_VARYBIVORE_TYPICAL_DIVERSITY_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vay.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {

template<auto...InspectedVariables>
struct TypicalDiversity: public Vay<InspectedVariables>...
{
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            Shuttle<InspectedVariables...>, 
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = ProtoPage<Variables...>::type;
};

template<>
struct TypicalDiversity<>
{
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = TypicalDiversity<InspectingVariable>::template ProtoPage<RestVariables...>
        ::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = ProtoPage<Variables...>::type;
};

template<auto...Variables>
struct Diversity
{
    template<auto...Agreements>
    using Page = TypicalDiversity<Variables...>
    ::template ProtoPage<Agreements...>
    ::type;
};

}}

#endif