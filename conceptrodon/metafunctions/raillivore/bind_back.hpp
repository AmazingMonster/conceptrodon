// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_BIND_BACK_H
#define CONCEPTRODON_RAILLIVORE_BIND_BACK_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct BindBack
{
    template<template<auto...> class...Endings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Sequences..., Endings...>;
    };

    template<template<auto...> class...Endings>
    using Rail = ProtoRail<Endings...>;
};

}}

#endif