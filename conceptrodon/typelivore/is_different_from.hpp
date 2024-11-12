// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_FROM_H
#define CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_FROM_H

namespace Conceptrodon {
namespace Typelivore {

template<typename RightSide>
struct IsDifferentFrom
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

}}

#endif