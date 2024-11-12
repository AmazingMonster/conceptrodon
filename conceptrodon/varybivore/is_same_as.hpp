// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_IS_SAME_AS_H
#define CONCEPTRODON_VARYBIVORE_IS_SAME_AS_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Target>
struct IsSameAs
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {false}; };

    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr bool Page_v 
    {ProtoPage<Args...>::value};
};

}}

#endif