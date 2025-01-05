// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_BIND_H
#define CONCEPTRODON_MOULDIVORE_BIND_H

#include "conceptrodon/typelivore/among.hpp"
#include "conceptrodon/omennivore/concepts/peg_nonzero.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Bind
{
    template<typename...Elements>
    struct ProtoMold
    {
        template<typename...Replacements>
        struct Detail
        {
            template<typename Element>
            struct Hidden 
            { using type = Element; };

            template<typename Element>
            requires Omennivore::PegNonzero<Element>
            struct Hidden<Element>
            { 
                using type = Typelivore::TypicalAmong<Replacements...>
                ::template ProtoPage<Element::value - 1>
                ::type; 
            };

            using type = Operation<typename Hidden<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif