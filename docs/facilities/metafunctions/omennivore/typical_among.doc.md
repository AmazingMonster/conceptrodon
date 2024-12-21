<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-typical-among">To Index</a></p>

## Description

`Omennivore::TypicalAmong` accepts a packed vessel.

- Suppose the vessel is a container containing elements. In that case, It returns a function. When invoked by an index, the function returns the element at the index via the member `type`.

<pre><code>   Container&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;
-> I
-> E<sub>I</sub></code></pre>

- Suppose the vessel is a sequence containing variables. In that case, It returns a function. When invoked by an index, the function returns the variable at the index via the member `value`.

<pre><code>   Seq&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;
-> I
-> V<sub>I</sub></code></pre>

- Suppose the vessel contains operations. In that case, its first layer accepts an index and returns a function. When invoked, the function instantiates the operation at the index with its arguments and returns the result.

<pre><code>   Vessel&lt;Oper<sub>0</sub>, Oper<sub>1</sub>, ..., Oper<sub>I</sub>, ..., Oper<sub>n</sub>&gt;
-> I
-> Args...
-> Oper<sub>I</sub>&lt;Args...&gt;</code></pre>

## Type Signature

```Haskell
-- Pick a `type`
TypicalAmong
 :: typename...
 -> auto...
 -> typename
 
-- Pick a `value`
TypicalAmong
 :: auto...
 -> auto...
 -> auto
 
-- Pick a `Mold`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
 
-- Pick a `Page`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<auto...>
 
-- Pick a `Road`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<typename...> class...>
 
-- Pick a `Rail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<auto...> class...>
 
-- Pick a `Flow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<typename...> class...> class...>
 
-- Pick a `Sail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<auto...> class...> class...>
 
-- Pick a `Snow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<typename...> class...> class...> class...>
 
-- Pick a `Hail`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<auto...> class...> class...> class...>
 
-- Pick a `Cool`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
 
-- Pick a `Calm`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
 
-- Pick a `Grit`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
 
-- Pick a `Will`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
 
-- Pick a `Glow`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
 
-- Pick a `Dawn`
TypicalAmong
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
// Pick a `type`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        using type = RESULT;
    };
};

// Pick a `value`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};

// Pick a `Mold`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

// Pick a `Page`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Pick a `Road`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};

// Pick a `Rail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};

// Pick a `Flow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<typename...> class...> class...>
        alias Flow = RESULT;
    };
};

// Pick a `Sail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<auto...> class...> class...>
        alias Sail = RESULT;
    };
};

// Pick a `Snow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<typename...> class...> class...> class...>
        alias Snow = RESULT;
    };
};

// Pick a `Hail`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<auto...> class...> class...> class...>
        alias Hail = RESULT;
    };
};

// Pick a `Cool`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...>
        alias Cool = RESULT;
    };
};

// Pick a `Calm`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...>
        alias Calm = RESULT;
    };
};

// Pick a `Grit`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
        alias Grit = RESULT;
    };
};

// Pick a `Will`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
        alias Will = RESULT;
    };
};

// Pick a `Glow`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
        alias Glow = RESULT;
    };
};

// Pick a `Dawn`
template<typename>
struct TypicalAmong
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
        alias Dawn = RESULT;
    };
};
```

## Examples

- We will pick out the element at index two from `std::tuple<int, int*, int**, int***>`.

```C++
template<auto...Args>
using At = TypicalAmong<std::tuple<int, int*, int**, int***>>
::Page<Args...>;

using SupposedResult = int**;

using Result = At<2>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pick out the operation at index two from `Vessel<War_0, War_1, War_2, War_3>`.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Vessel;

template<template<template<typename...> class...> class...>
struct Flow_0;

template<template<template<typename...> class...> class...>
struct Flow_1;

template<template<template<typename...> class...> class...>
struct Flow_2;

template<template<template<typename...> class...> class...>
struct Flow_3;

template<template<template<typename...> class...> class...Args>
using ResultOperation = TypicalAmong<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

template<template<typename...> class...>
struct War_0;

template<template<typename...> class...>
struct War_1;

static_assert(std::same_as<Flow_2<War_0, War_1>, ResultOperation<War_0, War_1>>);
```

Note that we must instantiate the operation before the comparison.
This is because the function returned by `TypicalAmong` is an alias template pointing to the actual operation in the packed vessel.
It is not quite the same as the actual operation.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Forlorn<ResultOperation>,
    Forlorn<Flow_2>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Forlorn<ResultOperation>,
    Forlorn<Flow_2>
>);
```

## Implementation

If `TypicalAmong` or `Among` have been implemented in other namespaces, we will redirect the items extracted from the packed vessel to these functions.

Otherwise, we will transform the items into types and employ `Typelivore::TypicalAmong` to do the job.

We will implement a simplified version that picks out types and `Flow`s.

Since `Typelivore::TypicalAmong` exists, we will use it to deal with types.

```C++
template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typelivore::TypicalAmong<Elements...>
{};
```

To pick out `Flow`s with `Typelivore::TypicalAmong`, we will wrap every `Flow` into a `Fly`.

```C++
template<template<template<template<typename...> class...> class...> class Sorrow>
struct Fly
{
    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Sorrow<Warehouses...>;
};
```

Here's the implementation to pick out a `Flow`.

```C++
template
<
    template<template<template<template<typename...> class...> class...> class...> class Vessel,
    // Extract items from a packed vessel.
    template<template<template<typename...> class...> class...> class...Flows
>
struct TypicalAmong<Vessel<Flows...>>
{
    template<auto I>
    struct ProtoPage
    {
        template<template<template<typename...> class...> class...Arguments>
        // We warp each of `Flows...` into `Fly`
        // and invoke `Typelivore::TypicalAmong`. 
        using Flow = Typelivore::TypicalAmong<Fly<Flows>...>
        ::template Page<I>
        // The `type` we obtained is an instantiated `Fly`.
        ::type
        // We call the template member `Flow` with the arguments.
        ::template Flow<Arguments...>;
    };

    template<auto...Arguments>
    using Page = ProtoPage<Arguments...>;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQSAKxmpAAOqAqETgwe3r56KWmOAsGhESzRsVwAzADstpj2BQxCBEzEBFk%2BftJ2mA4ZTS0EReFRMfGJCs2t7TlctpODIcOlo5VVAJS2qF7EyOwc5hUhyN5YANQmFW7IE%2BhYVBfYJhoAgk/PAPQAVN%2BfpwAqAE8knU8AA3EjsECApJ4US0Z4sATAU4/T7vN7MNgKJJMXb/IEg8HETDnKpWF5vAiYFhJAxUi5uAgEzGYAB07Ow9DYggUDzeE2IXgc%2BJhcIRSNJViqABELuTXi8qTS6ZgGUzgSzTgAxPDECZ8l4CoUEEWwsTiowMnV6ggG15kt6nJ2nJW0pj0y5pABemAA%2BiaAJJ252nI3C5TEVBEZRMYAkkwOmVyt6O52ulUM71%2BwPB53EgCOXl1mAUpwgQYqssrGjWqadYZNEajqBjcYZFceLxDCYspy8aSMLoJ50r2t1%2BoqvYTVfldZd1LdHrcTC8RHZrOewGJ1MYBF5FU7zxD/ZCyNb8dHTejsdVl032%2B5e/XDxAIHVt9nScnKcVC4zl3fTVrQmUghw1VgSSEHoBHQUDAIg9cAHkCAQGJ90PBtTTFRFLUuYCCFAqC0AYWDTmQ1C9WfA8UwdLs0z/d1bzcLN/VODs50wq8Wxvc46KdHs%2BwHZF3xHaUsPNHDgAZci0Ko7BX3TRjTi48921OABaU4zBfN8CTlUkZx/I96OVRjMzwH1WPYvjTgLItiVLcsLiraUaw4ghBXDSNrzbS5rOM/iyUE08wIvMT8P06dkwpGzFKXFic2omy7OLRyKxcrhaxszjvO43y3H87sgpPQcROc04iJgyKv1nWKGKXFc13Ze9MB3HlcydEqzx48qVJvBkWrap92T5b8KRqoyopij5UW1WgSDNBgUR%2BdFf1Mpc4qYza1XqrbmQQkaD1OY4mAUBQ5OOgwzouk6zoqkhIwAdztTCtXm4hFpo%2BUQ22gDdp29a9vAtgbqu87DuwS7TvB1kAHUWkwBAtiUdC5y6ubUEe0T7uIJ6GXh4kkf7Es5Oi%2B1DOmr4fnE%2BFJOW75VueX7GX2tgXo840aYtZEeyisaFSZ/6/sBtVWbZCGobujxBCYRYyFCll105IbUcNDnhWhM1aaRBlpeaOWGWVx8YdGw8QFOJIvEiWhYRFQkIVfTXsJ1y4jd3E2kvtKUKYF7aKUuOdmaDoXGRD%2BCQYl26PchqPQehuO7oANRLOxSDnd53lObBVA83ETUIalSyoSMWFOJgLdxABrTB0FOUEU7qVlA7DluRYAsWE%2BjyWu9j9k3sx3l/Yw9WTSdiSXbcZOzrqK15se6O7V5uq2%2BXVdUDYjrQxH5TctUmyl4CkN5xX4OT47yOwc79dnmIYAfHdzeQwz05YZJR6WiSU5MFxBBTlQKhzgADYND93ns%2BYBpwQhECASA96n1gFzifpnQwtcQjgmrjA6E9tiSOyBFrbmJhgGsl4ofY8QkMZY3Klgm2RJIRj21rhNw/cPqiAYLPAeDxSY2RDApXayl%2Bp%2BUfs6Z%2BfxUIwPfIQjQpxHoklQJEfWoRUGlkMJAhgExDCOEYrXSRzD4EaCbtw50Ck9KGKdM/V%2Bx0xC0BdGIzapw2DLGIDA0BkjpGEF/ihEkLQ77GwMaQoxb4%2BEuLvLfe%2BPJSb8yKj7ZuK9GqoGvqE42m90bnmxn1fKN8fHuwiZ%2BaJLwqaokKaiRmBTfh/BLHuemaI3ilKKYUxmKYzCHAYMcLwZwGSrjoIQAEi98mzXwlnVQrBaQkmKZSEOcSEnAFVs8dGTNsb0IIZ6Ag6AFJeBGQyKBoEoGfG2YIb4eyCA/FNm8V8qkQnTJyUZdGQh1l5BrgAJRLF4WgJpyo7M%2BGTN46MnkKBeW80cTMGTaQPMY4EXy1bulhL6aGMQCAQBuK%2BBQEEYX7jcL8/5hE7mpEec815Dxaz8xqbNSqJFBnDPoFUxmp9FxbVbrS0WwNxZNyOr3FlMdL4X3jhDfk28p52AhYLE%2B9L/wsyZVfLl10eVq08iaUBvoNCCppaKoO592Xdwley3lsqKG%2Bi4EqkVZlhYMvbuKyVPdOVaplZzeVILapCpNaHYVZ8zXqrZQ8DV0rnivTnr6CoBrnWOtVa6j17rWWWsyTMn5eKCCIWBMQKFAgFl4Odow/lM88K%2Bo0KBeVsxdWJF1f66inszkCLcCCs2IBgluEjVc6ayqjVisYAdN1lr2Y6oJgqgNQaw5qtDW2z2mFO36qJZCxwyBUVKFaAilZSKUWnXYY9X0IK3CduzS/FoeqHigQxa8uNMRE1sMuGu0Cw7TaEvtaU/4CBdS12zhS0ZK1xmBpVYajafbw3ctbV%2B/tP7B3by1CQd6R7L2ZwAOJuDcMdVANI6AkxqZnNwBhBwoNOAAWSEInKDVBZa0D8eo8dk64UztWSAZFbBUUMjnIB4gwGGS7tjfGw927qNAZIEephvqK0pgPBeoyz8kOGGRKhjDWHoOwfoH45%2BEHsO4fOryqFE7YXToYFGLepHyN%2BgXQHGyNG6OXAY/uhNDQWO6bY8QDjtrF68blBwDYtBOBxF4H4DgWhSCoE4G4aw1hQxbB2PGJpPBSAEE0HZjYlcQBxEkKyDQkguBVAqBoOIGgzCAMAWYAAHBl/QnBJC8BYBIDQ2aXNuY8xwXgCgQDZpC65uzpA4CwBgIgEAWwCCWwIhQCAaAJMxDCBBTgqgMuAPUoAyQpxgDIGQKcKQrIzC8BroQBaqzZj8EECIMQ7ApAyEEIoFQ6haukF0LMR6CakicB4PZxzznQvuc4IhVc7W/4AMG8N0b43JvTei2YMsHgetOIOJlXgNWtAbAgEgbrMJ6BkE6xDuDsRgBSESDQV5aFKCRBu5EEILQATnd4Jj5gxAASIUiNoHoNWgvdcfIhBgtAccHawJELwwBly0FoJV7gvAsAsCE%2BIenxZej13Z25zAqgeirj2EFqBdQbs20iAmwnHgsA3Y8ngArHPSD12IJEHF0pqQ89PKFjYVADDTMTngTAj190uaC6t4QcJNvSFt7ttQN2jv6CEygbzlh9B4EiJVyAGxUBJAaOz9SNxnKmEsNYMwpXNcfSwP7iAGxui9GcBAVw0w/CzCCIsEoZRcipHSAITPBf8gZCGHnlYtR6h9HmCX2YKeGj9FaBXkY5Q5gDHrx3lvue28SGT353Y/ecscCc6QErvAyunBeyNsbE2psze%2BxAXAi3/uBbWEDw3GxUJMCwLEJPpAIuSAqKyAAnNUSQsWzCSGAUlwBp%2BR95dIAVioXBWSAK4IAjLp%2BMuf6i1wOIc/QBcfG7MrCrKrYLQ3erJrMHFrB7VccgSgWHKHPrNgTgFoFgUEKodScuE6QcLgU/VkN/YXfAIgePPQW3dbcQLbJ3JQF3A7XQRIE7JgM7DnS7Ufa7A7Mre7NrVcJ7MuYgTA7A3A5DZEAgogmLH7GDSHGIc4JpMwDfSA2rUHcHaQuHRArrNQqHEADArA9SPAhHU/LgbNZHKkPUNHDHLHQnXHUgfHbHYnUnBwGwynXcanWnG7BnJnFnNnGwrnHnPYNzfAYkAXEsG7EXMXKkGwqXBzA7WXeXAERXAIoHD6NXILTXbXJQXXbnIwG2IwKA43WMBQM3C3K3Gwyg%2B3CQR3WQZ3fbNzRg93PIyPKwb3WXRPQPYPDIUPcPSsJo6PWPGIePUIgPavMnDIFwEiLvHPYoPvWYPIIvTITwDoUveY1vRxPQRvWvTvRYmYEY1PRoeYVY/PBvOvbYrPbvBYaYtYzKTYbYIfa4mIsfCfW7DgAQoQnAqGfAwg4gssFfMguQ1/RQ4HMLUgHfPfSgdgp/F/Qg2LKoQAqoBLSQa/UbWYJ4sA2wCAoE0HGApAVrdrDQ5A3rfrDgDAt7FgBQUEKbUEcQlUCYebUgpbCg2QKgh3bbeQOg2onQEACoUgZg1gi7EfR40Au7eAk0f%2BV40k8kyk6kxiCYKQv7f4ioQEqA2Agk6HJArQ0YCkpIJIX0Kk0/X0GkggGFQQ0bPgOgMwyrCAdHA7Ow6w9XW0onEnMnZwmDKnGnOnQIzARnZnKxdnILPwnIpI0gII0YwXMI0XZAcXKIwQaXWI33eIxI5XFImw9InXPXHIg3ZQvgE3Io83S3DUMopkiomg6o9k13Lkho4wL3GwVo%2BAdokPTgd4RFXoywGPSfOPPABPOs3YhocY9wU4vQKYpYI45IQvBoLvOYhoQ4qvDYgQZvNoAchvOoUYucg43vK484rvdRHvS4o4gfW4zbdgwUrgzgcUsbMkikuuaUqkWU5fektfAEzfZQ7fb%2BMEg/GIyEkAMwQgioCoOIZLOLIrX8qoL/EAk88rdE6rLfQ/fwOIM/OIDLVLU/SQU/BLaoSoEfCoTg0rTgJ8kHdgubMCnCiCzEjYTXNIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/typical_among.type.test.hpp)
