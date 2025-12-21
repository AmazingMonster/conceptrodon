// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_CONJUNCTION_H
#define CONCEPTRODON_MOULDIVORE_CONJUNCTION_H

namespace Conceptrodon {
namespace Mouldivore {

template <template<typename...> class...Predicates>
struct Conjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value 
        {(...&&Predicates<Elements...>::value)};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    static constexpr bool Mold_v
    {(...&&Predicates<Elements...>::value)};
};


}}

#endif