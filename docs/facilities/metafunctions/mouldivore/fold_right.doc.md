<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-right">To Index</a></p>

## Description

`Mouldivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.

When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::type
   &gt;::type
        &vellip;
   &gt;::type</code></pre>

## Type Signature

```Haskell
FoldRight
 :: template<typename...> class...
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct FoldRight
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

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

/**** Test ****/
static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRight
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements >
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Element, Initiator>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    Initiator
                >
                >;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    typename Detail<Others...>
                    ::type
                >
                >;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };
        
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/fold_right/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/fold_right.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right.test.hpp)
