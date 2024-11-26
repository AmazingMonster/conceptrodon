// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_NEGATION_H
#define CONCEPTRODON_MOULDIVORE_NEGATION_H

namespace Conceptrodon {
namespace Mouldivore {

template <template<typename...>  class Predicate>
struct Negation
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {not Predicate<Elements...>::value};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    static constexpr bool Mold_v 
    {not Predicate<Elements...>::value};
};

}}

#endif