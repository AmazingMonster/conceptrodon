<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::KindredFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-kindred-fold-left-first">To Index</a></p>

## Description

`Varybivore::KindredFoldLeftFirst` accepts a list of variables and returns a function.

When invoked by an operation, the function left-folds the list using the operation with the first variable as the initiator.

<pre><code>   Init, V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>, ..., V<sub>n</sub>
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
      &vellip;
   &gt;::value, V<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
KindredFoldLeftFirst
 :: auto...
 -> template<auto...> class...
 -> auto
```

## Structure

```C++
template<auto...>
struct KindredFoldLeftFirst
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<template<auto...> class>
    static constexpr auto Rail_v 
    {RESULT};
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
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction */
template<template<auto...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

/**** Test ****/
static_assert(Metafunction<Subtract>::value == -9);
```

## Implementation

We will implement `KindredFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct KindredFoldLeftFirst<Initiator, Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            KindredFoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/kindred_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/kindred_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/kindred_fold_left_first.test.hpp)
