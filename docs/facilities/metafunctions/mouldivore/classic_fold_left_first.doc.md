<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-left-first">To Index</a></p>

## Description

`Mouldivore::ClassicFoldLeftFirst` accepts an operation and returns a function.

When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::type, Arg<sub>1</sub>
   &gt;::type, Arg<sub>2</sub>
      &vellip;
   &gt;::type, Arg<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeftFirst
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldLeftFirst
{
    template<typename...>
    alias Mold = RESULT;
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
    using type = std::integral_constant
    <int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= ClassicFoldLeftFirst<Subtract>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `ClassicFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldLeftFirst
{
    template<typename...Elements>
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Initiator, typename Element>
    struct Detail<Initiator, Element>
    {
        using type = Operation<Initiator, Element>::type;
    };

    // Fold twice.
    template<typename Initiator, typename First, typename Second>
    struct Detail<Initiator, First, Second>
    {
        using type
        =   Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type;
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<typename Initiator, typename First, typename Second, typename...Others>
    struct Detail<Initiator, First, Second, Others...>
    {
        using type
        = Detail<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::type;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_left_first.test.hpp)
