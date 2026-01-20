<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Follow`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-follow">To Index</a></p>

## Description

`Typelivore::Follow` accepts a list of elements and returns an identity function.

<pre><code>   Es...
-> (Arg -> Arg)</code></pre>

## Type Signature

```Haskell
Follow
 :: typename...
 -> template<typename...>
```

```Haskell
Follow
 :: typename...
 -> auto...
 -> auto
```

## Structure

```C++
template<typename...>
struct Follow
{
    template<typename>
    alias Mold = RESULT;
}；
```

```C++
template<typename...>
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

- We will duplicate `int` while expanding `Vay<0>, Vay<1>, Vay<2>, Vay<3>`.

```C++
/**** Vay ****/
template<auto>
struct Vay {};

/**** Operation ****/
template<typename...Args>
struct Operation {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Operation<typename Follow<Args>::template Mold<int>...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- We will duplicate `0` while expanding `Vay<0>, Vay<1>, Vay<2>, Vay<3>`.

```C++
/**** Operation ****/
template<auto...Args>
struct Operation_1 {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction_1 = Operation_1<Follow<Args>::template Page<0>::value...>;

/**** SupposedResult ****/
using SupposedResult_1 = Operation_1<0, 0, 0, 0>;

/**** Result ****/
using Result_1 = Metafunction_1<Vay<0>, Vay<1>, Vay<2>, Vay<3>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

```C++
template<typename Leader>
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

- [Example](../../../code/facilities/metafunctions/typelivore/follow/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/follow.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/follow.test.hpp)
