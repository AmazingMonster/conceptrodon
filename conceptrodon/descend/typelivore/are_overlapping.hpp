// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ARE_OVERLAPPING_H
#define CONCEPTRODON_TYPELIVORE_ARE_OVERLAPPING_H

#include "conceptrodon/capsule.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...InspectedElements>
struct AreOverlapping
: public std::type_identity<InspectedElements>...
{
    struct Detail
    {
        template<typename...>
        struct ProtoMold { using type = void; };
    };

    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, AreOverlapping>::value, 
            void,
            Capsule<InspectedElements..., InspectingElement>
        >::type;
        
        static constexpr bool value {std::is_same_v<type, void>};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
    
    template<typename...Elements>
    static constexpr bool Mold_v 
    {std::is_same_v<typename ProtoMold<Elements...>::type, void>};;

};

template<>
struct AreOverlapping<>
{
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = AreOverlapping<InspectingElement>::template ProtoMold<RestElements...>
        ::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
    
    template<typename...Elements>
    static constexpr bool Mold_v 
    {std::is_same_v<typename ProtoMold<Elements...>::type, void>};;
};

}}

#endif