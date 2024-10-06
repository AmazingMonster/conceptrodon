# Conceptrodon
A metaprogramming library focusing on continuation.

## Introduction
This library is inspired by pipe syntax and aims to create a similar way to compose metafunctions.  
Both boost::mp11 and kvasir::mpl contain a function called 'compose'. It takes a variadic pack of metafunctions and uses the result from the previous function to invoke the next one.
Namely, mp_compose<F1, F2, …​, Fn>::fn<T…​> is Fn<…​F2<F1<T…​>>…​>. However, since we still don't have a universal template parameter token, signatures of F1... must be specified.
In the case of boost::mp11 and kvasir::mpl, F1... can only take type arguments, which means many functions in both libraries are not composable.  
To resolve this, Conceptrodon expands the idea of 'quoted metafunction'. By using member templates dividing the duty of taking arguments, Conceptrodon groups commonly used functions together based on their signatures, which subsequently creates cleaner call sites and better candidates for compositions:

## Implementation
This library mainly handles four types of metafunctions:
- Mold, which has signature template<typename...>.
- Page, which has signature template<auto...>.
- Road, which has signature template<template<typename...> class...>.
- Rail, which has signature template<template<auto...> class...>.

