<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeftFirst` accepts a list of elements and produces a function.

When invoked by an operation, the function left-folds the list with the first element as the initiator.
The type result of the operation is used for continuation.

<pre><code>   Init, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
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
KindredClassicFoldLeftFirst
 ::  typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
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
template<template<typename...> class...Args>
using Metafunction 
= KindredClassicFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredClassicFoldLeftFirst<Initiator, Element>
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

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredClassicFoldLeftFirst<Initiator, First, Second>
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredClassicFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredClassicFoldLeftFirst<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_classic_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left_first.test.hpp)
