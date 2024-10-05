// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_NO_GREATER_H
#define CONCEPTRODON_VARYBIVORE_IS_NO_GREATER_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsNoGreater
{
    static constexpr bool value
    { not (RightSide < LeftSide) };
};

template<auto LeftSide, auto RightSide>
constexpr bool IsNoGreater_v
{ not (RightSide < LeftSide) };

template<auto RightSide>
struct IsNoGreaterThan
{
    template<auto LeftSide>
    struct ProtoPage
    {
        static constexpr bool value
        { not (RightSide < LeftSide) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto LeftSide>
    static constexpr bool Page_v 
    = not (RightSide < LeftSide);
};

}}

#endif