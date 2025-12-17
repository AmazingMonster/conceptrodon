<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeft` accepts a list of elements.
Its first layer accepts an initiator and returns a function.

When invoked by an operation, the function left-folds the list using the operation and the initiator.
The type result of the operation is used for continuation.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
      &vellip;
   &gt;::type, E<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
KindredClassicFoldLeft
 :: typename...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= KindredClassicFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredClassicFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredClassicFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              typename Operation<
                Initiator, First
              >::type, Second
              >::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct KindredClassicFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredClassicFoldLeft<Others...>
            ::template Mold<
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_classic_fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left.test.hpp)
