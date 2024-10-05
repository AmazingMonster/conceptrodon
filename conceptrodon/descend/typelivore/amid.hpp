// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_AMID_H
#define CONCEPTRODON_TYPELIVORE_AMID_H

#include "conceptrodon/label.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    : public Label<Elements, I>...
    { using Label<Elements, I>::idyl...; };

    template<size_t I>
    struct ProtoPage
    {
        using type = decltype
        (Detail<std::make_index_sequence<sizeof...(Elements)>>::idyl(std::integral_constant<size_t, I>{}));
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<size_t I>
    using UniPage = decltype
    (Detail<std::make_index_sequence<sizeof...(Elements)>>::idyl(std::integral_constant<size_t, I>{}));
};

}}

#endif