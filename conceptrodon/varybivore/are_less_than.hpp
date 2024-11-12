// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_LESS_THAN_H
#define CONCEPTRODON_VARYBIVORE_ARE_LESS_THAN_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target>
struct AreLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Variables < Target)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Variables < Target)) };
};

}}

#endif