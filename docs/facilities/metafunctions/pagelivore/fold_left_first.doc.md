<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-left-first">To Index</a></p>

## Description

`Pagelivore::FoldLeftFirst` accepts an operation and returns a function.

When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::value, Arg<sub>1</sub>
   &gt;::value, Arg<sub>2</sub>
      &vellip;
   &gt;::value, Arg<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeftFirst
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldLeftFirst
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

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldLeftFirst
{
    template<auto...Variables>
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Initiator, auto Variable>
    struct ProtoPage<Initiator, Variable>
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    // Fold twice.
    template<auto Initiator, auto First, auto Second>
    struct ProtoPage<Initiator, First, Second>
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<auto Initiator, auto First, auto Second, auto...Others>
    struct ProtoPage<Initiator, First, Second, Others...>
    {
        static constexpr auto value {
            ProtoPage<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/fold_left_first.test.hpp)
