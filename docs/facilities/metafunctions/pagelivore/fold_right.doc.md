<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-right">To Index</a></p>

## Description

`Pagelivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.

When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
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
FoldRight
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRight
{
    template<auto>
    alias Page
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
= FoldRight<Subtract>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3>::Page<1, 3, 4>::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRight
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables >
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Variable, Initiator>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
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
                        FoldRight
                        ::template ProtoPage<Initiator>
                        ::Slash
                        ::template ProtoPage<Others...>
                        ::value
                    >::value
                    >::value
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };
        
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/fold_right/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/fold_right.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right.test.hpp)
