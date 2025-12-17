<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left">To Index</a></p>

## Description

`Typelivore::KindredFoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
KindredFoldLeft
 :: typename...
 -> typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeft
{
    template<typename>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will left-fold 2, 3, 4 and 3 using subtraction.
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
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= KindredFoldLeft<
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

We will implement `KindredFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              Operation<
                Initiator, First
              >, Second
              >;
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
struct KindredFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredFoldLeft<Others...>
            ::template Mold<
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
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

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left.test.hpp)
