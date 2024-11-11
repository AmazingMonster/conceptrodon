// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ADD_H
#define CONCEPTRODON_VARYBIVORE_ADD_H

namespace Conceptrodon {
namespace Varybivore {

template<auto First, auto...Variables>
struct Add
{ 
    static constexpr auto value 
    {(First+...+Variables)}; 
};

template<auto First, auto...Variables>
constexpr auto Add_v 
{(First+...+Variables)}; 

template<auto J>
struct AddTo
{
    template<auto I>
    struct ProtoPage
    { 
        static constexpr auto value 
        {I + J}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto I>
    static constexpr auto Page_v 
    {I + J};
};

}}

#endif