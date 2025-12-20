// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TYPICAL_DIVERSITY_H
#define CONCEPTRODON_TYPELIVORE_TYPICAL_DIVERSITY_H

#include "conceptrodon/capsule.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...InspectedElements>
struct TypicalDiversity: public std::type_identity<InspectedElements>...
{
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;
    };

    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, TypicalDiversity>::value, 
            Capsule<InspectedElements...>, 
            Capsule<InspectedElements..., InspectingElement>
        >::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
};

template<>
struct TypicalDiversity<>
{
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = TypicalDiversity<InspectingElement>
        ::template ProtoMold<RestElements...>
        ::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
};

}}

#endif