// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_FOLLOW_H
#define CONCEPTRODON_TYPELIVORE_FOLLOW_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Leader>
struct Follow
{
    template<typename Follower>
    struct Detail
    {
        using type = Follower;
    };

    template<auto Follower>
    struct ProtoPage
    {
        static constexpr auto value {Follower};
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif