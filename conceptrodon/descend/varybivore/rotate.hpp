// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ROTATE_H
#define CONCEPTRODON_VARYBIVORE_ROTATE_H

#include "conceptrodon/descend/microbiota/varbola/swivel.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif