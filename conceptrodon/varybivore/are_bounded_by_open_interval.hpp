// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_OPEN_INTERVAL_H
#define CONCEPTRODON_VARYBIVORE_IS_BOUNDED_BY_OPEN_INTERVAL_H

namespace Conceptrodon {
namespace Varybivore {

template<auto LowerBound, auto UpperBound>
struct IsBoundedByOpenInterval
{
    template<auto Variable>
    struct ProtoPage
    {
        static constexpr bool value
        { LowerBound < Variable && Variable < UpperBound };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto Variable>
    static constexpr bool Page_v 
    { LowerBound < Variable && Variable < UpperBound };
};

}}

#endif