<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-left">To Index</a></p>

## Description

`Mouldivore::ClassicFoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.

When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
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
ClassicFoldLeft
 :: template<typename...> class...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
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
= ClassicFoldLeft<Subtract>
::Mold<std::integral_constant<int, 1>>
::Mold<Args...>::type;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `ClassicFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldLeft
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements>
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Initiator, Element>::type;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type;
        };

        // Recursive Case:

        // Fold twice, handle the first two parameters,
        // and recurse using the rest.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            = ProtoMold
            <
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Detail<Others...>::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/classic_fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_left.test.hpp)
