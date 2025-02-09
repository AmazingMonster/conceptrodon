// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EXTEND_FRONT_H
#define CONCEPTRODON_OMENNIVORE_EXTEND_FRONT_H

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct ExtendFront {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendFront<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., PreexistingElements...>;
};

template
<
    template<auto...> class Sequence,
    auto...PreexistingVariables
>
struct ExtendFront<Sequence<PreexistingVariables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., PreexistingVariables...>;
};

template
<
    template<typename, auto...> class Sequence,
    typename Type,
    auto...PreexistingVariables
>
struct ExtendFront<Sequence<Type, PreexistingVariables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<Type, static_cast<Type>(NewVariables)..., PreexistingVariables...>;
};

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...PreexistingContainers
>
struct ExtendFront<Warehouse<PreexistingContainers...>>
{
    template<template<typename...> class...NewContainers>
    using Road = Warehouse<NewContainers..., PreexistingContainers...>;
};

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...PreexistingSequences
>
struct ExtendFront<Stockroom<PreexistingSequences...>>
{
    template<template<auto...> class...NewSequences>
    using Rail = Stockroom<NewSequences..., PreexistingSequences...>;
};

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...PreexistingWarehouses
>
struct ExtendFront<Sorrow<PreexistingWarehouses...>>
{
    template<template<template<typename...> class...> class...NewWarehouses>
    using Flow = Sorrow<NewWarehouses..., PreexistingWarehouses...>;
};

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...PreexistingStockrooms
>
struct ExtendFront<Melancholy<PreexistingStockrooms...>>
{
    template<template<template<auto...> class...> class...NewStockrooms>
    using Sail = Melancholy<NewStockrooms..., PreexistingStockrooms...>;
};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...PreexistingSorrow
>
struct ExtendFront<Silence<PreexistingSorrow...>>
{
    template<template<template<template<typename...> class...> class...> class...NewSorrow>
    using Snow = Silence<NewSorrow..., PreexistingSorrow...>;
};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...PreexistingMelancholy
>
struct ExtendFront<Tranquil<PreexistingMelancholy...>>
{
    template<template<template<template<auto...> class...> class...> class...NewMelancholy>
    using Hail = Tranquil<NewMelancholy..., PreexistingMelancholy...>;
};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...PreexistingSilence
>
struct ExtendFront<Consistency<PreexistingSilence...>>
{
    template<template<template<template<template<typename...> class...> class...> class...> class...NewSilence>
    using Cool = Consistency<NewSilence..., PreexistingSilence...>;
};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...PreexistingTranquil
>
struct ExtendFront<Perseverance<PreexistingTranquil...>>
{
    template<template<template<template<template<auto...> class...> class...> class...> class...NewTranquil>
    using Calm = Perseverance<NewTranquil..., PreexistingTranquil...>;
};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...PreexistingConsistency
>
struct ExtendFront<Sunshine<PreexistingConsistency...>>
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...NewConsistency>
    using Grit = Sunshine<NewConsistency..., PreexistingConsistency...>;
};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...PreexistingPerseverance
>
struct ExtendFront<Sunshine<PreexistingPerseverance...>>
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...NewPerseverance>
    using Will = Sunshine<NewPerseverance..., PreexistingPerseverance...>;
};

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendFront<Sunlight<PreexistingSunshines...>>
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...NewSunshines>
    using Glow = Sunlight<NewSunshines..., PreexistingSunshines...>;
};

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendFront<Sunlight<PreexistingSunshines...>>
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...NewSunshines>
    using Dawn = Sunlight<NewSunshines..., PreexistingSunshines...>;
};


}}

#endif