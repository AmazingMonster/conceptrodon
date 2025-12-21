<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateInsert`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-insert">To Index</a></p>

## Description

`Pagelivore::CognateInsert` accepts an operation.
Its first layer accepts a list of variables.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.

When invoked, the function inserts its arguments into their corresponding positions, which is indicated by the index list, of the previously provided variable list.
Then, The function instantiates the operation with the inserted list.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>m</sub>
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>k</sub>
-> Oper
   <
             V<sub>0</sub>,
             V<sub>1</sub>,
              &vellip;
       V<sub>I<sub>0</sub>-1</sub>, Arg<sub>0</sub>, V<sub>I<sub>0</sub></sub>,
       V<sub>I<sub>1</sub>-1</sub>, Arg<sub>1</sub>, V<sub>I<sub>1</sub></sub>,
              &vellip;
       V<sub>I<sub>n</sub>-1</sub>, Arg<sub>n</sub>, V<sub>I<sub>n</sub></sub>,
              &vellip;
             V<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateInsert
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateInsert
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateInsert<Operation>
::Page<0, 2, 4>
::Page<1, 2, 3>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<-1, -3, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateInsert` by combining `Pagelivore::CognateSegment` and `Omennivore::InsertValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<
    std::make_index_sequence<I>,
    std::make_index_sequence<J>...
>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateInsert
{
    template<auto...Variables>
    struct ProtoPage
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule
        <
            std::make_index_sequence<I>,
            std::make_index_sequence<J>...
        >;
        
        struct Slash
        {
            template<size_t...I>
            struct ProtoPage
            {
                template<auto...NewVariables>
                using Page = Send
                <
                    typename Send
                    <
                        typename CognateSegment<Detail_t>
                        ::template Page<I...>
                    >::template Road<Omennivore::InsertValues>
                    ::template Page<NewVariables...>
                    ::template Page<Variables...>
                >
                ::template Rail<Operation>;
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

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_insert/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/pagelivore/cognate_insert.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_insert.test.hpp)
