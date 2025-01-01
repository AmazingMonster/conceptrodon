// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_INJECT_H
#define CONCEPTRODON_TYPELIVORE_INJECT_H

#include "conceptrodon/descend/microbiota/typella/enrich.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            template<template<typename...> class...Agreements>
            using Road = decltype
            (
                Typella::Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif