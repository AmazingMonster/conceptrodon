// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EXTEND_BACK_H
#define CONCEPTRODON_OMENNIVORE_EXTEND_BACK_H

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct ExtendBack {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendBack<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<PreexistingElements..., NewElements...>;
};

template
<
    template<auto...> class Sequence,
    auto...PreexistingVariables
>
struct ExtendBack<Sequence<PreexistingVariables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<PreexistingVariables..., NewVariables...>;
};

template
<
    template<typename, auto...> class Sequence,
    typename Type,
    auto...PreexistingVariables
>
struct ExtendBack<Sequence<Type, PreexistingVariables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<Type, PreexistingVariables..., static_cast<Type>(NewVariables)...>;
};

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...PreexistingContainers
>
struct ExtendBack<Warehouse<PreexistingContainers...>>
{
    template<template<typename...> class...NewContainers>
    using Road = Warehouse<PreexistingContainers..., NewContainers...>;
};

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...PreexistingSequences
>
struct ExtendBack<Stockroom<PreexistingSequences...>>
{
    template<template<auto...> class...NewSequences>
    using Rail = Stockroom<PreexistingSequences..., NewSequences...>;
};

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...PreexistingWarehouses
>
struct ExtendBack<Sorrow<PreexistingWarehouses...>>
{
    template<template<template<typename...> class...> class...NewWarehouses>
    using Flow = Sorrow<PreexistingWarehouses..., NewWarehouses...>;
};

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...PreexistingStockrooms
>
struct ExtendBack<Melancholy<PreexistingStockrooms...>>
{
    template<template<template<auto...> class...> class...NewStockrooms>
    using Sail = Melancholy<PreexistingStockrooms..., NewStockrooms...>;
};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...PreexistingSorrow
>
struct ExtendBack<Silence<PreexistingSorrow...>>
{
    template<template<template<template<typename...> class...> class...> class...NewSorrow>
    using Snow = Silence<PreexistingSorrow..., NewSorrow...>;
};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...PreexistingMelancholy
>
struct ExtendBack<Tranquil<PreexistingMelancholy...>>
{
    template<template<template<template<auto...> class...> class...> class...NewMelancholy>
    using Hail = Tranquil<PreexistingMelancholy..., NewMelancholy...>;
};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<typename...> class...> class...> class...> class...PreexistingSilence
>
struct ExtendBack<Sunshine<PreexistingSilence...>>
{
    template<template<template<template<template<typename...> class...> class...> class...> class...NewSilence>
    using Cool = Sunshine<PreexistingSilence..., NewSilence...>;
};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<auto...> class...> class...> class...> class...PreexistingTranquil
>
struct ExtendBack<Sunshine<PreexistingTranquil...>>
{
    template<template<template<template<template<auto...> class...> class...> class...> class...NewTranquil>
    using Calm = Sunshine<PreexistingTranquil..., NewTranquil...>;
};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendBack<Sunshine<PreexistingSunshines...>>
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...NewSunshines>
    using Grit = Sunshine<PreexistingSunshines..., NewSunshines...>;
};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendBack<Sunshine<PreexistingSunshines...>>
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...NewSunshines>
    using Will = Sunshine<PreexistingSunshines..., NewSunshines...>;
};

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendBack<Sunshine<PreexistingSunshines...>>
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...NewSunshines>
    using Glow = Sunshine<PreexistingSunshines..., NewSunshines...>;
};

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...PreexistingSunshines
>
struct ExtendBack<Sunshine<PreexistingSunshines...>>
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...NewSunshines>
    using Dawn = Sunshine<PreexistingSunshines..., NewSunshines...>;
};


}}

#endif