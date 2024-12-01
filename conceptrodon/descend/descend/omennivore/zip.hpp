// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZIP_H
#define CONCEPTRODON_OMENNIVORE_ZIP_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_willful.hpp"

#include "conceptrodon/descend/omennivore/among.hpp"
#include "conceptrodon/omennivore/total.hpp"
#include "conceptrodon/varybivore/minimum.hpp"

namespace Conceptrodon {
namespace Omennivore {



// value
/******************************************************************************************************/
template<typename...Packages>
struct Zip
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::value...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
/******************************************************************************************************/



// type
/******************************************************************************************************/
template<typename...Packages>
requires AllMoldful<Packages...>
struct Zip<Packages...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <typename TypicalAmong<Packages>::template ProtoPage<I>::type...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <typename TypicalAmong<Packages>::template ProtoPage<I>::type...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
/******************************************************************************************************/



// Mold
/******************************************************************************************************/
template<typename...Packages>
requires AllRoadful<Packages...>
struct Zip<Packages...>
{
    template<template<template<typename...> class...> class Operation>
    struct ProtoFlow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Mold...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Mold...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;
};
/******************************************************************************************************/



// Page
/******************************************************************************************************/
template<typename...Packages>
requires AllRailful<Packages...>
struct Zip<Packages...>
{
    template<template<template<auto...> class...> class Operation>
    struct ProtoSail
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Page...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Page...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};
/******************************************************************************************************/



// Road
/******************************************************************************************************/
template<typename...Packages>
requires AllFlowful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<typename...> class...> class...> class Operation>
    struct ProtoSnow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Road...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Road...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<typename...> class...> class...> class...Agreements>
    using Snow = ProtoSnow<Agreements...>;
};
/******************************************************************************************************/



// Rail
/******************************************************************************************************/
template<typename...Packages>
requires AllSailful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<auto...> class...> class...> class Operation>
    struct ProtoHail
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Rail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Rail...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<auto...> class...> class...> class...Agreements>
    using Hail = ProtoHail<Agreements...>;
};
/******************************************************************************************************/



// Flow
/******************************************************************************************************/
template<typename...Packages>
requires AllSnowful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<typename...> class...> class...> class...> class Operation>
    struct ProtoCool
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Flow...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Flow...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
    using Cool = ProtoCool<Agreements...>;
};
/******************************************************************************************************/



// Sail
/******************************************************************************************************/
template<typename...Packages>
requires AllHailful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<auto...> class...> class...> class...> class Operation>
    struct ProtoCalm
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Sail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Sail...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
    using Calm = ProtoCalm<Agreements...>;
};
/******************************************************************************************************/



// Snow
/******************************************************************************************************/
template<typename...Packages>
requires AllCoolful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
    struct ProtoGrit
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Snow...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Snow...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
    using Grit = ProtoGrit<Agreements...>;
};
/******************************************************************************************************/



// Hail
/******************************************************************************************************/
template<typename...Packages>
requires AllCalmful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
    struct ProtoWill
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Hail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Hail...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
    using Will = ProtoWill<Agreements...>;
};
/******************************************************************************************************/



// Cool
/******************************************************************************************************/
template<typename...Packages>
requires AllGritful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
    struct ProtoGlow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Cool...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Cool...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
    using Glow = ProtoGlow<Agreements...>;
};
/******************************************************************************************************/



// Calm
/******************************************************************************************************/
template<typename...Packages>
requires AllWillful<Packages...>
struct Zip<Packages...>
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
    struct ProtoDawn
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <TypicalAmong<Packages>::template ProtoPage<I>::template Calm...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <TypicalAmong<Packages>::template ProtoPage<I>::template Calm...>;

/**********/
        template<template<typename...> class OuterOperation>
        struct Hidden
        {
            template<typename...>
            struct Secret {};

            template<size_t...I>
            struct Secret<std::index_sequence<I...>>
            { using type = OuterOperation<typename Detail<I>::type...>; };

            using type = Secret
            <
                std::make_index_sequence
                <Varybivore::Minimum<Total<Packages>::value...>::value>
            >
            ::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Hidden<Agreements...>::type;
/**********/

    };
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
    using Dawn = ProtoDawn<Agreements...>;
};
/******************************************************************************************************/




}}

#endif