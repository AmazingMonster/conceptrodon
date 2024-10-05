// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SUBTRACT_H
#define CONCEPTRODON_VARYBIVORE_SUBTRACT_H

namespace Conceptrodon {
namespace Varybivore {

template<auto I, auto J>
struct Subtract
{ 
    static constexpr auto value 
    {I - J}; 
};

template<auto I, auto J>
constexpr auto Subtract_v
{I - J};

template<auto I>
struct SubtractFrom
{
    template<auto J>
    struct ProtoPage
    { 
        static constexpr auto value 
        {I - J}; 
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto J>
    static constexpr auto Page_v
    {I - J};
};

}}

#endif