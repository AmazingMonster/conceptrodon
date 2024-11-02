// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_LABORIOUS_PRESS_H
#define CONCEPTRODON_OMENNIVORE_LABORIOUS_PRESS_H

namespace Conceptrodon {
namespace Omennivore {

template<typename Operation>
struct LaboriousPress
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
    { using type = Operation::template Lull<Contents...>; };

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
        using type = LaboriousPress<typename Operation::template Mold<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Page<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Road<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Rail<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Flow<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Sail<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Snow<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Hail<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Lull<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Calm<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Grit<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Will<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Glow<Contents...>>
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
        using type = LaboriousPress<typename Operation::template Dawn<Contents...>>
        ::template Detail<Others...>::type;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Mold at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Page at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Road at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Mold at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Page at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Road at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/



/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
    >
    struct Detail<
        A<as...>
        , B<bs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Mold at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ;
    };
/******************************************************************************************************/





/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Page at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Road at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ;
    };
/******************************************************************************************************/




/******************************************************************************************************/
/* Rail at index 0 */
/******************************************************************************************************/
/* Rail at index 1 */
/******************************************************************************************************/
/* Rail at index 2 */
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ;
    };
/******************************************************************************************************/



    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif