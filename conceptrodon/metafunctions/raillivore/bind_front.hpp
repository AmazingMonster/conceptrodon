// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_BIND_FRONT_H
#define CONCEPTRODON_RAILLIVORE_BIND_FRONT_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct BindFront
{
    template<template<auto...> class...Beginnings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Beginnings..., Sequences...>;
    };

    template<template<auto...> class...Beginnings>
    using Rail = ProtoRail<Beginnings...>;
};

}}

#endif