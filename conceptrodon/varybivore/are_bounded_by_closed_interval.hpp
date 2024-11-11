// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_CLOSED_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_CLOSED_INTERVAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LowerBound, auto UpperBound>
struct IsBoundedByClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < LowerBound) && not (UpperBound < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < LowerBound) && not (UpperBound < Variables))) };
};

}}

#endif