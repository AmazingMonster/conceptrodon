// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ERASE_H
#define CONCEPTRODON_TYPELIVORE_ERASE_H

#include "conceptrodon/microbiota/typella/expunge.hpp"
#include "conceptrodon/microbiota/typella/ditch.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif