// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PRESS_H
#define CONCEPTRODON_OMENNIVORE_PRESS_H

namespace Conceptrodon {
namespace Omennivore {

template<typename Operation>
struct Press
{
    template<typename...>
    struct Detail {};

/******************************************************************************************************/
    template
    <
        template<typename...> class Container,
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    { using type = Operation::template Mold<Contents...>; };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

    template
    <
        template<template<typename...> class...> class Warehouse,
        template<typename...> class...Contents
    >
    struct Detail<Warehouse<Contents...>>
    { using type = Operation::template Road<Contents...>; };

    template
    <
        template<template<auto...> class...> class Stockroom,
        template<auto...> class...Contents
    >
    struct Detail<Stockroom<Contents...>>
    { using type = Operation::template Rail<Contents...>; };

    template
    <
        template<template<template<typename...> class...> class...> class Sorrow,
        template<template<typename...> class...> class...Contents
    >
    struct Detail<Sorrow<Contents...>>
    { using type = Operation::template Flow<Contents...>; };

    template
    <
        template<template<template<auto...> class...> class...> class Melancholy,
        template<template<auto...> class...> class...Contents
    >
    struct Detail<Melancholy<Contents...>>
    { using type = Operation::template Sail<Contents...>; };

    template
    <
        template<template<template<template<typename...> class...> class...> class...> class Silence,
        template<template<template<typename...> class...> class...> class...Contents
    >
    struct Detail<Silence<Contents...>>
    { using type = Operation::template Snow<Contents...>; };

    template
    <
        template<template<template<template<auto...> class...> class...> class...> class Tranquil,
        template<template<template<auto...> class...> class...> class...Contents
    >
    struct Detail<Tranquil<Contents...>>
    { using type = Operation::template Hail<Contents...>; };

    template
    <
        template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<typename...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Cool<Contents...>; };

    template
    <
        template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<auto...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Calm<Contents...>; };

    template
    <
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<typename...> class...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Grit<Contents...>; };

    template
    <
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<auto...> class...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Will<Contents...>; };

    template
    <
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Glow<Contents...>; };

    template
    <
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Contents
    >
    struct Detail<Sunshines<Contents...>>
    { using type = Operation::template Dawn<Contents...>; };
/******************************************************************************************************/




/******************************************************************************************************/
    template
    <
        template<typename...> class Container,
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Mold<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<typename...> class...> class Warehouse,
        template<typename...> class...Contents,
        typename...Others
    >
    struct Detail<Warehouse<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Road<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<auto...> class...> class Stockroom,
        template<auto...> class...Contents,
        typename...Others
    >
    struct Detail<Stockroom<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Rail<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<typename...> class...> class...> class Sorrow,
        template<template<typename...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sorrow<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Flow<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<auto...> class...> class...> class Melancholy,
        template<template<auto...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Melancholy<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Sail<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<typename...> class...> class...> class...> class Silence,
        template<template<template<typename...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Silence<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Snow<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<auto...> class...> class...> class...> class Tranquil,
        template<template<template<auto...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Tranquil<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Hail<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<typename...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Cool<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<auto...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Calm<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<typename...> class...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Grit<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<auto...> class...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Will<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Glow<Contents...>>
        ::template Detail<Others...>::type;
    };

    template
    <
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunshines,
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Contents,
        typename...Others
    >
    struct Detail<Sunshines<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Dawn<Contents...>>
        ::template Detail<Others...>::type;
    };
/******************************************************************************************************/


    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif