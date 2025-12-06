// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TYPICAL_AMONG_H
#define CONCEPTRODON_OMENNIVORE_TYPICAL_AMONG_H

#include "conceptrodon/microbiota/typella/typical_among.hpp"
#include "conceptrodon/microbiota/varbola/among.hpp"
#include "conceptrodon/microbiota/moldiae/among.hpp"
#include "conceptrodon/microbiota/pagelis/among.hpp"

#include "conceptrodon/roy.hpp"
#include "conceptrodon/ray.hpp"
#include "conceptrodon/fly.hpp"
#include "conceptrodon/say.hpp"
#include "conceptrodon/sny.hpp"
#include "conceptrodon/hay.hpp"
#include "conceptrodon/coy.hpp"
#include "conceptrodon/cay.hpp"
#include "conceptrodon/gry.hpp"
#include "conceptrodon/wiy.hpp"
#include "conceptrodon/gly.hpp"
#include "conceptrodon/day.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typella::TypicalAmong<Elements...>
{};

template<template<auto...> class Sequence, auto...Variables>
struct TypicalAmong<Sequence<Variables...>>
: public Varbola::Among<Variables...>
{};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct TypicalAmong<Warehouse<Containers...>>
: public Moldiae::Among<Containers...>
{};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct TypicalAmong<Stockroom<Sequences...>>
: public Pagelis::Among<Sequences...>
{};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct TypicalAmong<Sequence<Type, Variables...>>
: public Varbola::Among<Variables...>
{};

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct TypicalAmong<Sorrow<Warehouses...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = Typella::TypicalAmong<Roy<Warehouses>...>
        ::template Page<I>::type::template Road<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct TypicalAmong<Melancholy<Stockrooms...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = Typella::TypicalAmong<Ray<Stockrooms>...>
        ::template Page<I>::type::template Rail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct TypicalAmong<Silence<Sorrow...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<typename...> class...> class...Agreements>
        using Flow = Typella::TypicalAmong<Fly<Sorrow>...>
        ::template Page<I>::type::template Flow<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct TypicalAmong<Tranquil<Melancholy...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<auto...> class...> class...Agreements>
        using Sail = Typella::TypicalAmong<Say<Melancholy>...>
        ::template Page<I>::type::template Sail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct TypicalAmong<Consistency<Silence...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<typename...> class...> class...> class...Agreements>
        using Snow = Typella::TypicalAmong<Sny<Silence>...>
        ::template Page<I>::type::template Snow<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct TypicalAmong<Perseverance<Tranquil...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<auto...> class...> class...> class...Agreements>
        using Hail = Typella::TypicalAmong<Hay<Tranquil>...>
        ::template Page<I>::type::template Hail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct TypicalAmong<Sunshine<Consistency...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
        using Cool = Typella::TypicalAmong<Coy<Consistency>...>
        ::template Page<I>::type::template Cool<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct TypicalAmong<Sunshine<Perseverance...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
        using Calm = Typella::TypicalAmong<Cay<Perseverance>...>
        ::template Page<I>::type::template Calm<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunlight<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
        using Grit = Typella::TypicalAmong<Gry<Sunshines>...>
        ::template Page<I>::type::template Grit<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunlight<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
        using Will = Typella::TypicalAmong<Wiy<Sunshines>...>
        ::template Page<I>::type::template Will<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Sunlights
>
struct TypicalAmong<Sunlight<Sunlights...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
        using Glow = Typella::TypicalAmong<Gly<Sunlights>...>
        ::template Page<I>::type::template Glow<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Sunlights
>
struct TypicalAmong<Sunlight<Sunlights...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
        using Dawn = Typella::TypicalAmong<Day<Sunlights>...>
        ::template Page<I>::type::template Dawn<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename...PackedVessels>
struct Among
: public TypicalAmong<PackedVessels...>
{

};

template<template<typename...> class Container, typename...Elements>
struct Among<Container<Elements...>>
{
    template<auto I>
    struct Detail
    {
        using type = Typella::TypicalAmong<Elements...>
        ::template ProtoPage<I>
        ::type;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

}}

#endif