// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SEND_H
#define CONCEPTRODON_OMENNIVORE_SEND_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail 
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    template<template<typename...> class Operation>
    using UniRoad = Operation<Elements...>;
};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail 
    { using type = Operation<Variables...>; };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;

    template<template<auto...> class Operation>
    using UniRail = Operation<Variables...>;
};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct Send<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail 
    { using type = Operation<Containers...>; };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;

    template<template<template<typename...> class...> class Operation>
    using UniFlow = Operation<Containers...>;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Send<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail 
    { using type = Operation<Sequences...>; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;

    template<template<template<auto...> class...> class Operation>
    using UniSail = Operation<Sequences...>;
};

template<template<template<template<typename...> class...> class...> class Sorrow, template<template<typename...> class...> class...Warehouses>
struct Send<Sorrow<Warehouses...>>
{
    template<template<template<template<typename...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = Detail<Agreements...>::type;

    template<template<template<template<typename...> class...> class...> class Operation>
    using UniSnow = Operation<Warehouses...>;
};

template<template<template<template<auto...> class...> class...> class Melancholy, template<template<auto...> class...> class...Stockrooms>
struct Send<Melancholy<Stockrooms...>>
{
    template<template<template<template<auto...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Stockrooms...>; };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = Detail<Agreements...>::type;

    template<template<template<template<auto...> class...> class...> class Operation>
    using UniHail = Operation<Stockrooms...>;
};

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct Send<Silence<Sorrow...>>
{
    template<template<template<template<template<typename...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Sorrow...>; };

    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = Detail<Agreements...>::type;

    template<template<template<template<template<typename...> class...> class...> class...> class Operation>
    using UniCool = Operation<Sorrow...>;
};

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct Send<Tranquil<Melancholy...>>
{
    template<template<template<template<template<auto...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Melancholy...>; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = Detail<Agreements...>::type;

    template<template<template<template<template<auto...> class...> class...> class...> class Operation>
    using UniCalm = Operation<Melancholy...>;
};

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct Send<Consistency<Silence...>>
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Silence...>; };

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = Detail<Agreements...>::type;

    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
    using UniGrit = Operation<Silence...>;
};

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct Send<Perseverance<Tranquil...>>
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Tranquil...>; };

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = Detail<Agreements...>::type;

    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
    using UniWill = Operation<Tranquil...>;
};

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct Send<Sunshine<Consistency...>>
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Consistency...>; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = Detail<Agreements...>::type;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
    using UniGlow = Operation<Consistency...>;
};

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct Send<Sunshine<Perseverance...>>
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Perseverance...>; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = Detail<Agreements...>::type;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
    using UniDawn = Operation<Perseverance...>;
};

}}

#endif