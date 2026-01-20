<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Follow`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-follow">To Index</a></p>

## Description

`Varybivore::Follow` accepts a list of variables and returns an identity function.

<pre><code>   Es...
-> (Arg -> Arg)</code></pre>

## Type Signature

```Haskell
Follow
 :: auto...
 -> template<typename...>
```

```Haskell
Follow
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Follow
{
    template<typename>
    alias Mold = RESULT;
}；
```

```C++
template<auto...>
struct Follow
{
    template<auto>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
}；
```

## Examples

We can duplicate types or values alongside a pack expansion using this function.

- We will duplicate `int` while expanding `0, 1, 2, 3`.

```C++
/**** Vay ****/
template<auto>
struct Vay {};

/**** Operation ****/
template<typename...Args>
struct Operation {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Operation<typename Follow<Args>::template Mold<int>...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 3>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- We will duplicate `0` while expanding `0, 1, 2, 3`.

```C++
/**** Operation ****/
template<auto...Args>
struct Operation_1 {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Operation_1<Follow<Args>::template Page<0>::value...>;

/**** SupposedResult ****/
using SupposedResult_1 = Operation_1<0, 0, 0, 0>;

/**** Result ****/
using Result_1 = Metafunction_1<0, 1, 2, 3>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

```C++
template<auto Leader>
struct Follow
{
    template<typename Follower>
    struct Detail
    {
        using type = Follower;
    };

    template<auto Follower>
    struct ProtoPage
    {
        static constexpr auto value {Follower};
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/follow/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/follow.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/follow.test.hpp)
