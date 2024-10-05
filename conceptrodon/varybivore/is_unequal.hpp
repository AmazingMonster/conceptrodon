// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_UNEQUAL_H
#define CONCEPTRODON_VARYBIVORE_IS_UNEQUAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsUnequal
{
    static constexpr auto value
    { LeftSide < RightSide || RightSide < LeftSide };
};

template<auto LeftSide, auto RightSide>
constexpr bool IsUnequal_v
{ LeftSide < RightSide || RightSide < LeftSide };

template<auto RightSide>
struct IsUnequalTo
{
    template<auto LeftSide>
    struct ProtoPage
    {
        static constexpr auto value
        { LeftSide < RightSide || RightSide < LeftSide };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto LeftSide>
    static constexpr bool Page_v 
    { LeftSide < RightSide || RightSide < LeftSide };
};

}}

#endif