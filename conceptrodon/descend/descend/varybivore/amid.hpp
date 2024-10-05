// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_AMID_H
#define CONCEPTRODON_VARYBIVORE_AMID_H

#include "conceptrodon/descend/stamp.hpp"
#include <type_traits>
#include <utility>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    : public Stamp<Elements, I>...
    { using Stamp<Elements, I>::idyl...; };

    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            Detail<std::make_index_sequence<sizeof...(Elements)>>
            ::idyl(std::integral_constant<size_t, I>{})
        };
    };

    template<size_t I>
    static constexpr auto Page_v
    {
        Detail<std::make_index_sequence<sizeof...(Elements)>>
        ::idyl(std::integral_constant<size_t, I>{})
    };
};

}}

#endif