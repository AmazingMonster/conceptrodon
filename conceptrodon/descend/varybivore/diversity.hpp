// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DIVERSITY_H
#define CONCEPTRODON_VARYBIVORE_DIVERSITY_H

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/monotony.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {

template<auto...InspectedVariables>
struct Diversity: public Monotony<InspectedVariables>...
{
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Monotony<InspectingVariable>, Diversity>::value, 
            Diversity, 
            Diversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Monotony<InspectingVariable>, Diversity>::value, 
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
struct Diversity<>
{
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = Diversity<InspectingVariable>::template ProtoPage<RestVariables...>
        ::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = ProtoPage<Variables...>::type;
};


}}

#endif