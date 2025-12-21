// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_BIND_H
#define CONCEPTRODON_PAGELIVORE_BIND_H

#include "conceptrodon/metafunctions/varybivore/among.hpp"
#include "conceptrodon/concepts/omennivore/peg_nonzero.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Bind
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<auto...Replacements>
        struct Detail
        {
            template<auto Variable>
            static constexpr auto Hidden_v {Variable};
            
            template<auto Variable>
            requires Omennivore::PegNonzero<decltype(Variable)>
            static constexpr auto Hidden_v<Variable> 
            {
                Varybivore::Among<Replacements...>
                ::template ProtoPage<Variable.value - 1>
                ::value
            };

            using type = Operation<Hidden_v<Variables>...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif