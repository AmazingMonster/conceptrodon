// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_SWAP_H
#define CONCEPTRODON_RAILLIVORE_SWAP_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct Swap
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
    
    template<auto...Variables>
    struct ProtoPage 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Page<Variables...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Road<Containers...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Rail<Sequences...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Flow<Warehouses...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;
};

}}

#endif