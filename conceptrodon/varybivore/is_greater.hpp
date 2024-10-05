// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_GREATER_H
#define CONCEPTRODON_VARYBIVORE_IS_GREATER_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsGreater
{
    static constexpr bool value
    { RightSide < LeftSide };
};

template<auto LeftSide, auto RightSide>
constexpr bool IsGreater_v
{ RightSide < LeftSide };

template<auto RightSide>
struct IsGreaterThan
{
    template<auto LeftSide>
    struct ProtoPage
    {
        static constexpr bool value
        { RightSide < LeftSide };   
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto LeftSide>
    static constexpr bool Page_v
    { RightSide < LeftSide };
};

}}

#endif