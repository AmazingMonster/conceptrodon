// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLATTEN_H
#define CONCEPTRODON_OMENNIVORE_FLATTEN_H

namespace Conceptrodon {
namespace Omennivore {

template<typename Operation>
struct Flatten
{
    template<typename...>
    struct Detail {};

/*0*/
/******************************************************************************************************/
    template<template<typename...> class A, typename...as>
    struct Detail<A<as...>>
    { using type = Operation::template Mold<as...>; };
/******************************************************************************************************/




/*1*/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





















/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<typename...> class A, typename...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Mold<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/



























/*0*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
    template<template<auto...> class A, auto...as>
    struct Detail<A<as...>>
    { using type = Operation::template Page<as...>; };
/******************************************************************************************************/




/*1*/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





















/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<auto...> class A, auto...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Page<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/



























/*0*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
    template<template<template<typename...> class...> class A, template<typename...> class...as>
    struct Detail<A<as...>>
    { using type = Operation::template Road<as...>; };
/******************************************************************************************************/




/*1*/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





















/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<typename...> class...> class A, template<typename...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Road<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/



























/*0*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
    template<template<template<auto...> class...> class A, template<auto...> class...as>
    struct Detail<A<as...>>
    { using type = Operation::template Rail<as...>; };
/******************************************************************************************************/




/*1*/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<typename...> class B, typename...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Mold<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<auto...> class B, auto...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Page<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





























/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<typename...> class...> class B, template<typename...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Road<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/





















/*1*/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
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




/*2*/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<typename...> class C, typename...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Mold<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/















/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<auto...> class C, auto...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Page<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<typename...> class...> class C, template<typename...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Road<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/













/*2*/
/******************************************************************************************************/
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




/*3*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<typename...> class D, typename...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Mold<ds...>
        ;
    };
/******************************************************************************************************/




/*4*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<auto...> class D, auto...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Page<ds...>
        ;
    };
/******************************************************************************************************/




/*5*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<typename...> class...> class D, template<typename...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Road<ds...>
        ;
    };
/******************************************************************************************************/




/*6*/
/******************************************************************************************************/
    template<
        template<template<auto...> class...> class A, template<auto...> class...as
        , template<template<auto...> class...> class B, template<auto...> class...bs
        , template<template<auto...> class...> class C, template<auto...> class...cs
        , template<template<auto...> class...> class D, template<auto...> class...ds
    >
    struct Detail<
        A<as...>
        , B<bs...>
        , C<cs...>
        , D<ds...>
    >
    { 
        using type = Operation::template Rail<as...>
        ::template Rail<bs...>
        ::template Rail<cs...>
        ::template Rail<ds...>
        ;
    };
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/
/******************************************************************************************************/











    template<typename A, typename B, typename C, typename D, typename...RestPacks>
    struct Detail<A, B, C, D, RestPacks...>
    :public Flatten<typename Detail<A, B, C, D>::type>::template Detail<RestPacks...>
    {};

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif