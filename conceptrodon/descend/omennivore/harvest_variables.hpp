// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HARVEST_VARIABLES_H
#define CONCEPTRODON_OMENNIVORE_HARVEST_VARIABLES_H

namespace Conceptrodon {
namespace Omennivore {

template<typename...Crops>
struct HarvestVariables
{ 
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;

    template<template<auto...> class Operation>
    using UniRail = Operation<Crops::value...>; 
};

}}

#endif