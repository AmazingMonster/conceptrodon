// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_BI_HARVEST_H
#define CONCEPTRODON_OMENNIVORE_BI_HARVEST_H

namespace Conceptrodon {
namespace Omennivore {

template<typename...Crops>
struct BiHarvest
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;
};

}}

#endif