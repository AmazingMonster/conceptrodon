// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SLICE_H
#define CONCEPTRODON_TYPELIVORE_SLICE_H

#include "conceptrodon/descend/microbiota/typella/incise.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Slice
{
    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage
    {   
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif