// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ERASE_H
#define CONCEPTRODON_MOULDIVORE_ERASE_H

#include "conceptrodon/descend/microbiota/typella/expunge.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Erase
{
    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Typella::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif