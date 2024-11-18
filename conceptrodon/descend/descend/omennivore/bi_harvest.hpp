// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_BI_HARVEST_H
#define CONCEPTRODON_OMENNIVORE_BI_HARVEST_H

#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"
#include "conceptrodon/omennivore/concepts/descend/all_typical.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Crops>
struct BiHarvest {};

template<typename...Crops>
requires AllTypical<Crops...>
struct BiHarvest<Crops...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    template<template<typename...> class Operation>
    using UniRoad = Operation<typename Crops::type...>;
};

template<typename...Crops>
requires AllValuable<Crops...>
struct BiHarvest<Crops...>
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

template<typename...Crops>
requires AllTypical<Crops...> && AllValuable<Crops...>
struct BiHarvest<Crops...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    template<template<typename...> class Operation>
    using UniRoad = Operation<typename Crops::type...>;

    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;

    template<template<auto...> class Operation>
    using UniRail = Operation<Crops::value...>;
};

}}

#endif