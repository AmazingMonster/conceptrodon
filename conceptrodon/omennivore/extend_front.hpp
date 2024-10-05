// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EXTEND_FRONT_H
#define CONCEPTRODON_OMENNIVORE_EXTEND_FRONT_H

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...PreexistingElements>
struct ExtendFront<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { using type = Container<NewElements..., PreexistingElements...>; };
    
    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;

    template<typename...NewElements>
    using Mold_t = Container<NewElements..., PreexistingElements...>;
};

template<template<auto...> class Sequence, auto...PreexistingVariables>
struct ExtendFront<Sequence<PreexistingVariables...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { using type = Sequence<NewVariables..., PreexistingVariables...>; };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;

    template<auto...NewVariables>
    using Page_t = Sequence<NewVariables..., PreexistingVariables...>;
};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...PreexistingContainers>
struct ExtendFront<Warehouse<PreexistingContainers...>>
{
    template<template<typename...> class...NewContainers>
    struct ProtoRoad
    { using type = Warehouse<NewContainers..., PreexistingContainers...>; };

    template<template<typename...> class...NewContainers>
    using Road = ProtoRoad<NewContainers...>;

    template<template<typename...> class...NewContainers>
    using Road_t = Warehouse<NewContainers..., PreexistingContainers...>;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...PreexistingSequences>
struct ExtendFront<Stockroom<PreexistingSequences...>>
{
    template<template<auto...> class...NewSequences>
    struct ProtoRail
    { using type = Stockroom<NewSequences..., PreexistingSequences...>; };

    template<template<auto...> class...NewSequences>
    using Rail = ProtoRail<NewSequences...>;

    template<template<auto...> class...NewSequences>
    using Rail_t = Stockroom<NewSequences..., PreexistingSequences...>;
};

}}

#endif