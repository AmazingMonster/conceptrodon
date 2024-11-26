// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_FLIP_H
#define CONCEPTRODON_MOULDIVORE_FLIP_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct Flip
{
// Mold -> Mold
    template<typename...Elements>
    struct ProtoMold 
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
    
// Page -> Mold
    template<auto...Variables>
    struct ProtoPage 
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Page<Variables...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

// Road -> Mold
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Road<Containers...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

// Rail -> Mold
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Rail<Sequences...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

// Flow -> Mold
    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Flow<Warehouses...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

// Sail -> Mold
    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

// Snow -> Mold
    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Snow<Sorrow...>;
    };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

// Hail -> Mold
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Hail<Melancholy...>;
    };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

// Cool -> Mold
    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoCool
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Cool<Silence...>;
    };

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;

// Calm -> Mold
    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Calm<Tranquil...>;
    };

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

// Grit -> Mold
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    struct ProtoGrit
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Grit<Consistency...>;
    };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;

// Will -> Mold
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    struct ProtoWill
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Will<Perseverance...>;
    };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

// Glow -> Mold
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Glow<Sunshines...>;
    };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

// Dawn -> Mold
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn
    {
        template<typename...Agreements>
        using Mold = Operation<Agreements...>::template Dawn<Sunshines...>;
    };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;
};

}}

#endif