// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ARE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_ARE_BOUNDED_BY_LEFT_CLOSED_RIGHT_OPEN_INTERVAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LowerBound, auto UpperBound>
struct AreBoundedByLeftClosedRightOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < LowerBound) && Variables < UpperBound)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(not (Variables < LowerBound) && Variables < UpperBound)) };
};

}}

#endif