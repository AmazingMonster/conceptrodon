// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZIP_H
#define CONCEPTRODON_OMENNIVORE_ZIP_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/omennivore/concepts/pottery_probe.hpp"
#include "conceptrodon/omennivore/concepts/almanac_probe.hpp"
#include "conceptrodon/omennivore/concepts/freeway_probe.hpp"
#include "conceptrodon/omennivore/concepts/railway_probe.hpp"
#include "conceptrodon/omennivore/among.hpp"
#include "conceptrodon/omennivore/total.hpp"
#include "conceptrodon/varybivore/minimum.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...>
struct Zip {};

template<>
struct Zip<> {};

template<typename...Packages>
requires (... && PotteryProbe<Packages>)
struct Zip<Packages...>
{
    template<size_t I>
    struct ProtoPage
    {
        using type = Capsule
        <typename Omennivore::Among<Packages>::template ProtoPage<I>::type...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<size_t I>
    using UniPage = Capsule
    <typename Omennivore::Among<Packages>::template ProtoPage<I>::type...>;

    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        using type = Capsule
        <typename ProtoPage<I>::type...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;

    using type = ProtoMold
    <
        std::make_index_sequence
        <Varybivore::Minimum<Total<Packages>::value...>::value>
    >
    ::type;
};

template<typename...Packages>
requires (... && AlmanacProbe<Packages>)
struct Zip<Packages...>
{
    template<size_t I>
    struct ProtoPage
    {
        using type = Shuttle
        <Omennivore::Among<Packages>::template ProtoPage<I>::value...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        using type = Capsule
        <typename ProtoPage<I>::type...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;

    using type = ProtoMold
    <
        std::make_index_sequence
        <Varybivore::Minimum<Total<Packages>::value...>::value>
    >
    ::type;
};

template<typename...Packages>
requires (... && FreewayProbe<Packages>)
struct Zip<Packages...>
{
    template<size_t I>
    struct ProtoPage
    {
        using type = Reverie
        <Omennivore::Among<Packages>::template ProtoPage<I>::template Mold...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        using type = Capsule
        <typename Page<I>::type...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;

    using type = ProtoMold
    <
        std::make_index_sequence
        <Varybivore::Minimum<Total<Packages>::value...>::value>
    >
    ::type;
};

template<typename...Packages>
requires (... && RailwayProbe<Packages>)
struct Zip<Packages...>
{
    template<size_t I>
    struct ProtoPage
    {
        using type = Phantom
        <Omennivore::Among<Packages>::template ProtoPage<I>::template Page...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        using type = Capsule
        <typename Page<I>::type...>;
    };
    
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
    
    template<typename...Args>
    using Mold_t = ProtoMold<Args...>::type;

    using type = ProtoMold
    <
        std::make_index_sequence
        <Varybivore::Minimum<Total<Packages>::value...>::value>
    >
    ::type;
};

}}

#endif