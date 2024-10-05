// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H

namespace Conceptrodon {
namespace Typelivore {

template<typename LeftSide, typename RightSide>
struct IsDifferent
{ static constexpr bool value {true}; };

template<typename Element>
struct IsDifferent<Element, Element>
{ static constexpr bool value {false}; };

template<typename RightSide>
struct IsDifferentAs
{
    template<typename LeftSide>
    struct ProtoMold
    { static constexpr bool value {true}; };

    template<>
    struct ProtoMold<RightSide>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};

template<typename LeftSide, typename RightSide>
constexpr auto IsDifferent_v 
{IsDifferent<LeftSide, RightSide>::value};

}}

#endif