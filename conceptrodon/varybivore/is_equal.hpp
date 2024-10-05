// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_EQUAL_H
#define CONCEPTRODON_VARYBIVORE_IS_EQUAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsEqual
{
    static constexpr bool value
    { not (LeftSide < RightSide) && not (RightSide < LeftSide) };
};

template<auto LeftSide, auto RightSide>
constexpr bool IsEqual_v
{ not (LeftSide < RightSide) && not (RightSide < LeftSide) };

template<auto RightSide>
struct IsEqualTo
{
    template<auto LeftSide>
    struct ProtoPage
    {
        static constexpr bool value
        { not (LeftSide < RightSide) && not (RightSide < LeftSide) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<auto LeftSide>
    static constexpr bool Page_v 
    { not (LeftSide < RightSide) && not (RightSide < LeftSide) };
};

}}

#endif