// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SEND_H
#define CONCEPTRODON_OMENNIVORE_SEND_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Pack>
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

    template<template<auto...> class...Args>
    using Rail_t = Detail<Args...>::type;

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

template<template<template<template<typename...> class...> class...> class Foolishness, template<template<typename...> class...> class...Warehouses>
struct Send<Foolishness<Warehouses...>>
{
    template<template<template<template<typename...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = Detail<Agreements...>::type;

    template<template<template<template<typename...> class...> class...> class Operation>
    using UniSnow = Operation<Warehouses...>;
};

template<template<template<template<auto...> class...> class...> class Foolishness, template<template<auto...> class...> class...Stockrooms>
struct Send<Foolishness<Stockrooms...>>
{
    template<template<template<template<auto...> class...> class...> class Operation>
    struct Detail 
    { using type = Operation<Stockrooms...>; };

    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = Detail<Agreements...>::type;

    template<template<template<template<auto...> class...> class...> class Operation>
    using UniHail = Operation<Stockrooms...>;
};

}}

#endif