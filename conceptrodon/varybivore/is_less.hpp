// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_LESS_H
#define CONCEPTRODON_VARYBIVORE_IS_LESS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsLess
{
    static constexpr bool value
    { LeftSide < RightSide };
};

template<auto LeftSide, auto RightSide>
constexpr bool IsLess_v
{ LeftSide < RightSide };

template<auto RightSide>
struct IsLessThan
{
    template<auto LeftSide>
    struct ProtoPage
    {
        static constexpr bool value
        { LeftSide < RightSide };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto LeftSide>
    static constexpr bool Page_v
    { LeftSide < RightSide };
};

}}

#endif