// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_NO_GREATER_THAN_H
#define CONCEPTRODON_VARYBIVORE_ARE_NO_GREATER_THAN_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target>
struct AreNoGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Target < Variables))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Target < Variables))) };
};

}}

#endif