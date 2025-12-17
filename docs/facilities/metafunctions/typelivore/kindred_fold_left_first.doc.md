<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredFoldLeftFirst` accepts a list of elements and returns a function.

When invoked by an operation, the function left-folds the list using the operation with the first element as the initiator.

<pre><code>   Init, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
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
KindredFoldLeftFirst
 :: typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredFoldLeftFirst
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
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<
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

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredFoldLeftFirst<Initiator, Element>
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

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredFoldLeftFirst<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_fold_left_first.test.hpp)
