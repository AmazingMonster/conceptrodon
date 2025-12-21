// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_OVERLAPPING_H
#define CONCEPTRODON_VARYBIVORE_ARE_OVERLAPPING_H

#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vay.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {

template<auto...InspectedVariables>
struct AreOverlapping: public Vay<InspectedVariables>...
{
    struct Detail
    {
        template<auto...>
        struct ProtoPage { using type = void; };
    };

    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;

        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            void,
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = ProtoPage<Variables...>::type;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    {not std::is_same_v<typename ProtoPage<Variables...>::type, void>};;

};

template<>
struct AreOverlapping<>
{
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = AreOverlapping<InspectingVariable>::template ProtoPage<RestVariables...>
        ::type;

        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    using Page_t = ProtoPage<Variables...>::type;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    {not std::is_same_v<typename ProtoPage<Variables...>::type, void>};;
};



}}

#endif