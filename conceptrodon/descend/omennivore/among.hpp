// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_AMONG_H
#define CONCEPTRODON_OMENNIVORE_AMONG_H

#include "conceptrodon/microbiota/typella/typical_among.hpp"
#include "conceptrodon/microbiota/varbola/among.hpp"
#include "conceptrodon/microbiota/moldiae/among.hpp"
#include "conceptrodon/microbiota/pagelis/among.hpp"

#include "conceptrodon/delegacy.hpp"
#include "conceptrodon/legation.hpp"
#include "conceptrodon/florican.hpp"
#include "conceptrodon/sailfish.hpp"
#include "conceptrodon/snowfall.hpp"
#include "conceptrodon/halfmoon.hpp"
#include "conceptrodon/lungfish.hpp"
#include "conceptrodon/camellia.hpp"
#include "conceptrodon/graphite.hpp"
#include "conceptrodon/wildfire.hpp"
#include "conceptrodon/glowworm.hpp"
#include "conceptrodon/daydream.hpp"

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
        using Road = Typella::TypicalAmong<Delegacy<Warehouses>...>
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
        using Rail = Typella::TypicalAmong<Legation<Stockrooms>...>
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
        using Flow = Typella::TypicalAmong<Florican<Sorrow>...>
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
        using Sail = Typella::TypicalAmong<Sailfish<Melancholy>...>
        ::template Page<I>::type::template Sail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct TypicalAmong<Sunshine<Silence...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<typename...> class...> class...> class...Agreements>
        using Snow = Typella::TypicalAmong<Snowfall<Silence>...>
        ::template Page<I>::type::template Snow<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct TypicalAmong<Sunshine<Tranquil...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<auto...> class...> class...> class...Agreements>
        using Hail = Typella::TypicalAmong<Halfmoon<Tranquil>...>
        ::template Page<I>::type::template Hail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
        using Lull = Typella::TypicalAmong<Lungfish<Sunshines>...>
        ::template Page<I>::type::template Lull<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
        using Calm = Typella::TypicalAmong<Camellia<Sunshines>...>
        ::template Page<I>::type::template Calm<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
        using Grit = Typella::TypicalAmong<Graphite<Sunshines>...>
        ::template Page<I>::type::template Grit<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
        using Will = Typella::TypicalAmong<Wildfire<Sunshines>...>
        ::template Page<I>::type::template Will<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
        using Glow = Typella::TypicalAmong<Glowworm<Sunshines>...>
        ::template Page<I>::type::template Glow<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template
<
    template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Sunshines
>
struct TypicalAmong<Sunshine<Sunshines...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
        using Dawn = Typella::TypicalAmong<Daydream<Sunshines>...>
        ::template Page<I>::type::template Dawn<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename...PackedHolders>
struct Among
: public TypicalAmong<PackedHolders...>
{};

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