// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_FLIP_H
#define CONCEPTRODON_PAGELIVORE_FLIP_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct Flip
{
// Mold -> Page
    template<typename...Elements>
    struct ProtoMold 
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
    
// Page -> Page
    template<auto...Variables>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Page<Variables...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

// Road -> Page
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Road<Containers...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;

// Rail -> Page
    template<template<auto...> class...Sequences>
    struct ProtoRail
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Rail<Sequences...>;
    };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;

// Flow -> Page
    template<template<template<typename...> class...> class...Warehouses>
    struct ProtoFlow
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Flow<Warehouses...>;
    };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>;

// Sail -> Page
    template<template<template<auto...> class...> class...Stockrooms>
    struct ProtoSail
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Sail<Stockrooms...>;
    };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = ProtoSail<Stockrooms...>;

// Snow -> Page
    template<template<template<template<typename...> class...> class...> class...Sorrow>
    struct ProtoSnow
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Snow<Sorrow...>;
    };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;

// Hail -> Page
    template<template<template<template<auto...> class...> class...> class...Melancholy>
    struct ProtoHail
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Hail<Melancholy...>;
    };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;

// Cool -> Page
    template<template<template<template<template<typename...> class...> class...> class...> class...Silence>
    struct ProtoCool
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Cool<Silence...>;
    };

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;

// Calm -> Page
    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    struct ProtoCalm
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Calm<Tranquil...>;
    };

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;

// Grit -> Page
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency>
    struct ProtoGrit
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Grit<Consistency...>;
    };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;

// Will -> Page
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance>
    struct ProtoWill
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Will<Perseverance...>;
    };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;

// Glow -> Page
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoGlow
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Glow<Sunshines...>;
    };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;

// Dawn -> Page
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines>
    struct ProtoDawn
    {
        template<auto...Agreements>
        using Page = Operation<Agreements...>::template Dawn<Sunshines...>;
    };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;
};

}}

#endif