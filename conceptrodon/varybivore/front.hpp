// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_FRONT_H
#define CONCEPTRODON_VARYBIVORE_FRONT_H

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/microbiota/varbola/fore.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif