// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FRONT_H
#define CONCEPTRODON_PAGELIVORE_FRONT_H

#include "conceptrodon/descend/microbiota/varbola/fore.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (
            Varbola::Fore<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Monotony<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif