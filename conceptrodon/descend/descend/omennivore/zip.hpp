// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ZIP_H
#define CONCEPTRODON_OMENNIVORE_ZIP_H

#include "conceptrodon/descend/omennivore/concepts/moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/lullful.hpp"
#include "conceptrodon/descend/omennivore/concepts/calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/willful.hpp"

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
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::value...>;

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
requires (... && Moldful<Packages>)
struct Zip<Packages...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <typename Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::type...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <typename Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::type...>;

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
requires (... && Roadful<Packages>)
struct Zip<Packages...>
{
    template<template<template<typename...> class...> class Operation>
    struct ProtoFlow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Mold...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Mold...>;

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
requires (... && Railful<Packages>)
struct Zip<Packages...>
{
    template<template<template<auto...> class...> class Operation>
    struct ProtoSail
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Page...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Page...>;

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
requires (... && Flowful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<typename...> class...> class...> class Operation>
    struct ProtoSnow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Road...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Road...>;

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
requires (... && Sailful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<auto...> class...> class...> class Operation>
    struct ProtoHail
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Rail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Rail...>;

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
requires (... && Snowful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<typename...> class...> class...> class...> class Operation>
    struct ProtoLull
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Flow...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Flow...>;

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
    using Lull = ProtoLull<Agreements...>;
};
/******************************************************************************************************/



// Sail
/******************************************************************************************************/
template<typename...Packages>
requires (... && Hailful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<auto...> class...> class...> class...> class Operation>
    struct ProtoCalm
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Sail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Sail...>;

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
requires (... && Lullful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class Operation>
    struct ProtoGrit
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Snow...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Snow...>;

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
requires (... && Calmful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class Operation>
    struct ProtoWill
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Hail...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Hail...>;

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



// Lull
/******************************************************************************************************/
template<typename...Packages>
requires (... && Gritful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Operation>
    struct ProtoGlow
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Lull...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Lull...>;

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
requires (... && Willful<Packages>)
struct Zip<Packages...>
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
    struct ProtoDawn
    {
        template<size_t I>
        struct Detail
        {
            using type = Operation
            <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Calm...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;

        template<size_t I>
        using UniPage = Operation
        <Omennivore::TypicalAmong<Packages>::template ProtoPage<I>::template Calm...>;

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