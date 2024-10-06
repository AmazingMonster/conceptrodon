# Conceptrodon
A C++20 metaprogramming library focusing on composition and continuation.

## Introduction
This library is inspired by pipe syntax and aims to create a similar way to compose metafunctions.  

Both boost::mp11 and kvasir::mpl contain a function called 'compose'. It takes a variadic pack of metafunctions and uses the result from the previous function to invoke the next one.
Namely, mp_compose<F1, F2, …​, Fn>::fn<T…​> is Fn<…​F2<F1<T…​>>…​>. However, since we still don't have a universal template parameter token, signatures of F1... must be specified.
In the case of boost::mp11 and kvasir::mpl, F1... can only take type arguments, which means many functions in both libraries are not composable.  

To resolve this, Conceptrodon expands the idea of 'quoted metafunction'. By using member templates dividing the duty of taking arguments, Conceptrodon groups commonly used functions together based on their signatures, which subsequently creates cleaner call sites and better candidates for compositions:

## Implementation
This library mainly handles four types of signatures:
- Mold, which has signature template<typename...>.
- Page, which has signature template<auto...>.
- Road, which has signature template<template<typename...> class...>.
- Rail, which has signature template<template<auto...> class...>.

These identifiers are deployed inside a metafunction to take corresponding arguments. For example, assuming we plan to pass int, std::tuple, std::index_sequence to function 'Fun':
1. The function itself can always take a kind of argument. we let Fun take types and pass int to Fun: Fun\<int\>.
2. Since the next parameter(std::tuple) is corresponding to Road(template<template<typename...> class...>), we pass it to Road: Fun\<int\>::Road\<std::tuple\>.
3. The last parameter(std::index_sequence) is corresponding to Rail(template<template<auto...> class...>), we pass it to Rail: Fun\<int\>::Road\<std::tuple\>::Rail\<std::index_sequence\>.

Every function in this library is tailored to fit this pattern. Since the inner structures of functions are fixed, composing various signatures is now possible[TODO: Add examples].

## Theory
Let's take another look at Mold. It can be thought of as the set of all metafunctions with the signature template<typename...>. The same is true for Road, while the corresponding signature becomes template<template<typename...> class...>. Function 'Fun' then turns into a map from set Mold to set Road. In other words, by using member templates(for example, 'quoted metafunction' in boost::mp11) to take arguments in steps, we are making maps from functions to functions.

If we reverse the order of Road and Fun, say the new function is called 'FunReversed', we can call it by FunReversed\<std::tuple\>::Mold\<int\>::Rail\<std::index_sequence\> to get the same result as before. FunReversed is then a map from set Road to set Mold. In conclusion, if we collect all the maps from set Mold to set Road and call it A, collect all the maps from set Road to set Mold and call it B, there is a loose correspondence between A and B. This library is structured according to these ideas.

## Structure
This library contains four main namespaces:
- Typelivore. It contains functions that take type arguments and output a function of signature template<template<typename...> class...>.
- Mouldivore. It contains functions of signature template<template<typename...> class...> and output functions that take type arguments.
- Varybivore. It contains functions that take value(non-type) arguments and output a function of signature template<template<auto...> class...>.
- Pagelivore. It contains functions of signature template<template<auto...> class...> and output functions that take value(non-type) arguments.

While there are many exceptions, these rules guide the majority of decision-making. Most functions presented by the library are included in these namespaces. 

A few more namespaces are provided to handle functions that do not naturally fit in one of the above namespaces.
- Roadrivore. It contains functions of signature template<template<template<typename...> class...> class...>.
- Raillivore. It contains functions of signature template<template<template<auto...> class...> class...>.
- Cotanivore. Functions in this namespace take arguments of form Container<Elements...>, where Container has signature template<typename...> and Elements... are types.
- Sequnivore. Functions in this namespace take arguments of form Sequence<Variables...>, where Sequence has signature template<auto...> and Variables... are values.
- Warehivore. Functions in this namespace take arguments of form Warehouse<Containers...>, where Warehouse has signature template<template<typename...> class...> and Containers... have signature template<typename...>.
- Stockivore. Functions in this namespace take arguments of form Stockroom<Sequences...>, where Stockroom has signature template<template<auto...> class...> and Sequences... have signature template<auto...>.
- Omennivore. It contains functions that do not fit in the namespaces above.

The library is further broken down according to dependency. Functions in \Conceptrodon\descend\descend depend on Functions in \Conceptrodon\descend. Functions in \Conceptrodon\descend depend on Functions in \Conceptrodon.

## Speed
Many functions are tested against boost::mp11. If the function being tested is slower than its counterpart, the implementation from boost::mp11 is used. Therefore, This library is generally faster than mp11. Tests can be found in tests/unit. 

## Future
Descriptions will be gradually added to each function. The purpose of this library is to facilitate another project, which is to create a new form of QWidget that can install various features via template parameters. This library will be tested and modified as the other project progresses.

