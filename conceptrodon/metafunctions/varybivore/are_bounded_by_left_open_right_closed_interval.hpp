// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_ARE_BOUNDED_BY_LEFT_OPEN_RIGHT_CLOSED_INTERVAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LowerBound, auto UpperBound>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr bool value
        { (...&&(LowerBound < Variables && not (UpperBound < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(LowerBound < Variables && not (UpperBound < Variables))) };
};

}}

#endif