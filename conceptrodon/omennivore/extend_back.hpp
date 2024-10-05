// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EXTEND_BACK_H
#define CONCEPTRODON_OMENNIVORE_EXTEND_BACK_H

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct ExtendBack {};

template<template<typename...> class Container, typename...PreexistingElements>
struct ExtendBack<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    struct ProtoMold
    { using type = Container<PreexistingElements..., NewElements...>; };
    
    template<typename...NewElements>
    using Mold = ProtoMold<NewElements...>;

    template<typename...NewElements>
    using Mold_t = Container<PreexistingElements..., NewElements...>;
};

template<template<auto...> class Sequence, auto...PreexistingVariables>
struct ExtendBack<Sequence<PreexistingVariables...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { using type = Sequence<PreexistingVariables..., NewVariables...>; };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;

    template<auto...NewVariables>
    using Page_t = Sequence<PreexistingVariables..., NewVariables...>;
};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...PreexistingContainers>
struct ExtendBack<Warehouse<PreexistingContainers...>>
{
    template<template<typename...> class...NewContainers>
    struct ProtoRoad
    { using type = Warehouse<PreexistingContainers..., NewContainers...>; };

    template<template<typename...> class...NewContainers>
    using Road = ProtoRoad<NewContainers...>;

    template<template<typename...> class...NewContainers>
    using Road_t = Warehouse<PreexistingContainers..., NewContainers...>;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...PreexistingSequences>
struct ExtendBack<Stockroom<PreexistingSequences...>>
{
    template<template<auto...> class...NewSequences>
    struct ProtoRail
    { using type = Stockroom<PreexistingSequences..., NewSequences...>; };

    template<template<auto...> class...NewSequences>
    using Rail = ProtoRail<NewSequences...>;

    template<template<auto...> class...NewSequences>
    using Rail_t = Stockroom<PreexistingSequences..., NewSequences...>;
};

}}

#endif