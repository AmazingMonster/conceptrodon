// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_FLIP_H
#define CONCEPTRODON_ROADRIVORE_FLIP_H

namespace Conceptrodon {
namespace Roadrivore {

template<template<template<typename...> class...> class Operation>
struct Flip
{
// Mold -> Road
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
    
// Page -> Road
    template<auto...Variables>
    struct ProtoPage 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Page<Variables...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

// Road -> Road
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Road<Containers...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

// Rail -> Road
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Rail<Sequences...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

// Flow -> Road
    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Flow<Warehouses...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

// Sail -> Road
    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

// Snow -> Road
    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Snow<Sorrow...>;
    };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = ProtoSnow<Sorrow...>;

// Hail -> Road
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Hail<Melancholy...>;
    };

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = ProtoHail<Melancholy...>;

// Cool -> Road
    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoCool
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Cool<Silence...>;
    };

    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    using Cool = ProtoCool<Silence...>;

// Calm -> Road
    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Calm<Tranquil...>;
    };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = ProtoCalm<Tranquil...>;

// Grit -> Road
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    struct ProtoGrit
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Grit<Consistency...>;
    };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    using Grit = ProtoGrit<Consistency...>;

// Will -> Road
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    struct ProtoWill
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Will<Perseverance...>;
    };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    using Will = ProtoWill<Perseverance...>;

// Glow -> Road
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Glow<Sunshines...>;
    };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    using Glow = ProtoGlow<Sunshines...>;

// Dawn -> Road
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>::template Dawn<Sunshines...>;
    };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    using Dawn = ProtoDawn<Sunshines...>;
};

}}

#endif