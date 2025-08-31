// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_HAS_H
#define CONCEPTRODON_TYPELIVORE_HAS_H

#include <cstddef>
#include "conceptrodon/label.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Has
{
    template<typename...InspectingElements>
    struct ProtoMold
    {
        template<typename, typename>
        struct Detail {};

        template<size_t...I, size_t...J>
        struct Detail<std::index_sequence<I...>, std::index_sequence<J...>>
        : public Label<Elements*, std::integral_constant<size_t, I>>..., public Label<InspectingElements*, std::integral_constant<size_t, sizeof...(Elements) + J>>...
        {
            using Label<Elements*, std::integral_constant<size_t, I>>::lark...;
            using Label<InspectingElements*, std::integral_constant<size_t, sizeof...(Elements) + J>>::lark...;

            template<typename, typename=void>
            struct Hidden
            { static constexpr bool value {true}; };

            template<typename Element>
            struct Hidden<Element, std::void_t<decltype(lark(std::declval<Element*>()))>>
            { static constexpr bool value {false}; };

            static constexpr bool value {(...&&(Hidden<InspectingElements>::value))};
        };
        
        static constexpr bool value 
        {Detail<std::index_sequence_for<Elements...>, std::index_sequence_for<InspectingElements...>>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v {ProtoMold<Args...>::value};
};

}}

#endif