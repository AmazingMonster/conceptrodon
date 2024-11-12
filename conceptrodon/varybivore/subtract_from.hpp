// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SUBTRACT_FROM_H
#define CONCEPTRODON_VARYBIVORE_SUBTRACT_FROM_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target>
struct SubtractFrom
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Target -...- Variables)}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v
    {(Target -...- Variables)};
};

}}

#endif