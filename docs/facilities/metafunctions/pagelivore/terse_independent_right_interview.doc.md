<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentRightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-terse-independent-right-interview">To Index</a></p>

## Description

`Pagelivore::TerseIndependentRightInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentRightInterview` prepares fewer base cases than `Pagelivore::IndependentRightInterview`.

<pre><code>   Preds...
-> Vs...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Vs...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Vs...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Vs...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
TerseIndependentRightInterview
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentRightInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

- We will find the indices of `2` and `-1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Equal ****/
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TerseIndependentRightInterview<Equal>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction<2>::Page<0, 0, 1, 2, 2>::value == 3);
static_assert
(Metafunction<-1>::Page<0, 0, 1, 2, 2>::value == -1);
```

- We will find the first index of the value which is less than `1` in the list `0, 0, 1, 2, 2`.

```C++
/**** Less ****/
template<auto I, auto J>
struct Less
{
    static constexpr bool value
    {I < J};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_2 = TerseIndependentRightInterview<Less>
::Page<Args...>;

/**** Tests ****/
static_assert
(Metafunction_2<1>::Page<0, 0, 1, 2, 2>::value == 0);
```

## Implementation

We will implement `TerseIndependentRightInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentRightInterview
{
    template<auto...RightSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<First, RightSides...>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<Second, RightSides...>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/terse_independent_right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/terse_independent_right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_right_interview.test.hpp)
