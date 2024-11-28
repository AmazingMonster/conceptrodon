// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_UNEQUAL_TO_H
#define CONCEPTRODON_VARYBIVORE_ARE_UNEQUAL_TO_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target>
struct AreUnequalTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        { (...&&(Variables < Target || Target < Variables)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Variables < Target || Target < Variables)) };
};

}}

#endif