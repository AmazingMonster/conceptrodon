// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ADD_TO_H
#define CONCEPTRODON_VARYBIVORE_ADD_TO_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Right>
struct AddTo
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Variables+...+Right)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v 
    {(Variables+...+Right)}; 
};

}}

#endif