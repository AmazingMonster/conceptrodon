// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_VARYBIVORE_IS_DIFFERENT_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LeftSide, auto RightSide>
struct IsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct IsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };

template<auto RightSide>
struct IsDifferentAs
{
    template<auto LeftSide>
    struct ProtoPage
    { static constexpr bool value {true}; };

    template<>
    struct ProtoPage<RightSide>
    { static constexpr bool value {false}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};

template<auto LeftSide, auto RightSide>
constexpr auto IsDifferent_v 
{IsDifferent<LeftSide, RightSide>::value};

}}

#endif