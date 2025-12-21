// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_AMID_H
#define CONCEPTRODON_TYPELIVORE_AMID_H

#include <cstddef>
#include <utility>
#include "conceptrodon/utilities/label.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    : public Label<Elements, std::integral_constant<size_t, I>>...
    { using Label<Elements, std::integral_constant<size_t, I>>::idyl...; };

    template<size_t I>
    struct Hidden
    {
        using type = decltype
        (
            Detail<std::make_index_sequence<sizeof...(Elements)>>
            ::idyl(std::integral_constant<size_t, I>{})
        );
    };

    template<auto...Agreements>
    using Page = Hidden<Agreements...>::type;

    template<size_t I>
    using UniPage = decltype
    (
        Detail<std::make_index_sequence<sizeof...(Elements)>>
        ::idyl(std::integral_constant<size_t, I>{})
    );
};

}}

#endif