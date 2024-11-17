// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_FLIP_H
#define CONCEPTRODON_RAILLIVORE_FLIP_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct Flip
{
// Mold -> Rail
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
    
// Page -> Rail
    template<auto...Variables>
    struct ProtoPage 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Page<Variables...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

// Road -> Rail
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Road<Containers...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

// Rail -> Rail
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Rail<Sequences...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

// Flow -> Rail
    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Flow<Warehouses...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

// Sail -> Rail
    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

// Snow -> Rail
    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Snow<Sorrow...>;
    };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = ProtoSnow<Sorrow...>;

// Hail -> Rail
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Hail<Melancholy...>;
    };

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = ProtoHail<Melancholy...>;

// Cool -> Rail
    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoCool
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Cool<Silence...>;
    };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = ProtoCool<Silence...>;

// Calm -> Rail
    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Calm<Tranquil...>;
    };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = ProtoCalm<Tranquil...>;

// Grit -> Rail
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    struct ProtoGrit
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Grit<Consistency...>;
    };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    using Grit = ProtoGrit<Consistency...>;

// Will -> Rail
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    struct ProtoWill
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Will<Perseverance...>;
    };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    using Will = ProtoWill<Perseverance...>;

// Glow -> Rail
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Glow<Sunshines...>;
    };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = ProtoGlow<Sunshines...>;

// Dawn -> Rail
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>::template Dawn<Sunshines...>;
    };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = ProtoDawn<Sunshines...>;
};

}}

#endif