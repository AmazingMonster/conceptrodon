// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_ROTATE_H
#define CONCEPTRODON_MOULDIVORE_ROTATE_H

#include "conceptrodon/descend/microbiota/typella/swivel.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Rotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (Typella::Swivel<std::make_index_sequence<Amount>>::template idyl<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif