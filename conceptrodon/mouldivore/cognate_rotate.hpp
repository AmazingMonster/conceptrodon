// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_ROTATE_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_ROTATE_H

#include "conceptrodon/microbiota/typella/swivel.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateRotate
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Typella::Swivel<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif