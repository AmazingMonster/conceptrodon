<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRightLast`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-right-last">To Index</a></p>

## Description

`Pagelivore::FoldRightLast` accepts an operation and returns a function.

When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRightLast
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRightLast
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto...>
    static constexpr auto Page_v
    {RESULT};
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
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRightLast
{
    template<auto...Variables >
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Variable, auto Initiator>
    struct ProtoPage<Variable, Initiator>
    {
        static constexpr auto value
        { Operation<Variable, Initiator>::value };
    };

    // Fold twice.
    template<auto First, auto Second, auto Initiator>
    struct ProtoPage<First, Second, Initiator>
    {
        static constexpr auto value 
        { 
            Operation<First,
            Operation<Second,
                Initiator
            >::value
            >::value
        };
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {
        static constexpr auto value
        {
            Operation<First,
            Operation<Second,
                FoldRightLast<Operation>
                ::template ProtoPage<Others...>
                ::value
            >::value
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/fold_right_last/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/fold_right_last.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right_last.test.hpp)
