// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HARVEST_TYPES_H
#define CONCEPTRODON_OMENNIVORE_HARVEST_TYPES_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Crops>
struct HarvestTypes
{ 
    template<template<typename...> class Operation=Capsule>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    template<template<typename...> class Operation=Capsule>
    using UniRoad = Operation<typename Crops::type...>;
};

}}

#endif