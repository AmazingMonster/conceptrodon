// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LowerBound, auto UpperBound>
struct IsBoundedByLeftOpenRightClosedInterval
{
    template<auto Variable>
    struct ProtoPage
    { 
        static constexpr bool value
        { LowerBound < Variable && not (UpperBound < Variable) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto Variable>
    static constexpr bool Page_v
    { LowerBound < Variable && not (UpperBound < Variable) };
};

}}

#endif