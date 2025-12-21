<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRightLast`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-right-last">To Index</a></p>

## Description

`Mouldivore::FoldRightLast` accepts an operation and returns a function.

When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::typename
   &gt;::typename
        &vellip;
   &gt;::typename</code></pre>

## Type Signature

```Haskell
FoldRightLast
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct FoldRightLast
{
    template<typename...>
    alias Mold = RESULT;
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
= FoldRightLast<Subtract>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRightLast
{
    template<typename...Elements >
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Element, typename Initiator>
    struct Detail<Element, Initiator>
    {
        using type = Operation<Element, Initiator>;
    };

    // Fold twice.
    template<typename First, typename Second, typename Initiator>
    struct Detail<First, Second, Initiator>
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
                typename FoldRightLast<Operation>
                ::template Detail<Others...>
                ::type
            >
            >;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

```

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/fold_right_last/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/mouldivore/fold_right_last.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right_last.test.hpp)
