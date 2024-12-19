<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateTransform`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-3">To Index</a></p>

## Description

`Pagelivore::CognateTransform` accepts an operation.
Its first layer accepts a list of predicates.
Its second layer accepts a transformation and returns a function.
When invoked, the function transforms its arguments that satisfy all the predicates with the transformation and instantiates the first operation with the result.

<pre><code>   FirstOperation
-> Predicates...
-> Transformation
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>i</sub>, ..., V<sub>n</sub>
-> FirstOperation
   <
       (...&&Predicates&lt;V<sub>0</sub>&gt;::value) ? Transformation&lt;V<sub>0</sub>&gt;::value : V<sub>0</sub>,
       (...&&Predicates&lt;V<sub>1</sub>&gt;::value) ? Transformation&lt;V<sub>1</sub>&gt;::value : V<sub>1</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>i</sub>&gt;::value) ? Transformation&lt;V<sub>i</sub>&gt;::value : V<sub>i</sub>,
                                    &vellip;
       (...&&Predicates&lt;V<sub>n</sub>&gt;::value) ? Transformation&lt;V<sub>n</sub>&gt;::value : V<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateTransform ::   template<auto...> class...
                   -> template<auto...> class...
                   -> template<auto...> class...
                   -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateTransform
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail
        {
            template<auto...>
            alias Page = RESULT;
        };
    };
};
```

## Example

We will apply `UnaryMinus` to variables divisible by two and three in the list `1, 12, 2, 6, 15`.

```C++
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

template<auto...>
struct Operation;

template<auto...Args>
using Metafunction = CognateTransform<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Rail<UnaryMinus>
::Page<Args...>;

using SupposedResult = Operation<1, -12, 2, -6, 15>;

using Result = Metafunction<1, 12, 2, 6, 15>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

For every variable in the list, we transform it with the second operation if it satisfies all the predicates.
We will do this using the following helper template.
It decides whether a variable shall be transformed.
The selection is done by a partial specialization, which is specialized by a constraint.

```C++
template<auto Variable>
struct Hidden 
{
    static constexpr auto value
    {Variable};
};

// `Puberty...` are the predicates.
// This partial specialization will be selected
// if `(...&&Puberty<Variable>::value) == true`.
template<auto Variable>
requires (...&&Puberty<Variable>::value)
struct Hidden<Variable>
{
    // `Hormone` is the transformation.
    static constexpr auto value
    {Hormone<Variable>::value};
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateTransform
{
    template<template<auto...> class...Puberty>
    struct ProtoRail
    {
        struct Slash
        {
            template<template<auto...> class Hormone>
            struct ProtoRail
            {
                template<auto Variable>
                struct Hidden 
                {
                    static constexpr auto value
                    {Variable};
                };

                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                using Page = Operation<Hidden<Variables>::value...>;
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Slash::template ProtoRail<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMxqkrgAyeAyYAHI%2BAEaYxCAA7IEADqgKhE4MHt6%2B/ilpGQKh4VEssfFJtpj2jgJCBEzEBNk%2BfgFVNZn1jQTFkTFxiYEKDU0tue0jPX2l5UMAlLaoXsTI7BwEmCzJBpsmAMxum9u7mAduTF5EAHS3B9gA1MgGCgoPAPLJcUy1DPcmGgAgiNiF4HA8PMBmJsACrEQwKfjEFgAwEmBJWIEPbEPY47H5nQ5407nS43O77R7PJivW7XZRecoEACe/yxOJBYIID2UxFQRAASkw6KicQ90ZjAWKxZzwUIXghRdLsRKlcqxcSCedNXtDmTUHT7k8Xm8ABIkFgCQnYNXq7Gy7m8/moIUi9l2lUY20enE6wkXK6oB4ANUaeCY0XobKlPulDoeprw6CwDHF7tjnslGbtU0cyCeAhGmFUyWID31DwAbmIvGd09mcRLQ8Rw5GzgkACIHLMN8Wd7uo72xv2kwMhsMRqOUoc%2B4iYACOXjwc7eEENZgAbOYNwymazDs3W1PsCAQNXvJh5jOPfHE8nGOdD5Prde7ar673c3h82gGEWS2WFbnrWr6xhK5rIlaj4Tm29ynsB7ZdvsPYNuiSGSqByojnqgZ0k%2BbYKNGvYPF46RGDyTDAJg4r7B2HxfPCvznHeKbQS2z6EZS8E1pghrTshmF9uh15oQOQLXthRxbPiuoBuS1xGtStK3ICwBzlsjAEJxNoftipFhMADyurQNF0fKNJICAfo8nygrCrQ5yqepbCCAofE2gJ6aiZ5aLppJkn6u5xo0m5KlqZgGmuUROL6eRxmmTZzrGY54WRVp7liWi/Y%2BaiAD0ABUhVFcVJW5XlxUPDCmAjG8xVlUCBUlU1RX1b5aJmPsYTPF4WA0W4Vx0IQ%2B46W1jWFQ8HZ4JWeDpG2FjMjCADuQZ1aiAVjgAktG8aTdNs30PNS2oIOXrpl%2BP6FpsAEPNEqCeFWPG2hKG3imYACsDxmKZBx0Ro3kYdlGENRVu0zXgc0LQg6kPKtQLrUQDxbdOQI7VNYMQzCUMRSdKEPOdBZ/ldpY3XdJkIU9GIveYH37N9tEPH9gMncJ4nA0VDxyMwxDMgAsmEpEwy1a3SSSOEI0jI3xpzjS8/zhHiadMb2g0eYE/%2BxNAY9XkYgAtFtTMKyzo0VdgqisDs1Gw4C8MGhSksEKC4KfN8TE5XDItamLtvXICxDANpqKxYZPOYA0VBeAwDiZAlkLQpgcIIkiKKHM7jGZNGp7JYcoP7Zgh3LaQE1o7nh1Yy%2BQKZ/Z5zS9zfMMKRGcgMolH%2Br7/sZW7gJBw8QheMkqRKOgArVV4tDcj99Eu%2BnhxcIXOtcGYheLw8OsboXXBvf8nfd8PCij%2BP9Mh2HEdRwI5yzw8C9L4Xa%2BX5v/FA8CKvfgA%2BiFcQEBAIzoKeCisJgb9OJuF3vvQuvd%2B5pEwEPEeY97hXmQhwRYtBOBvV4H4DgWhSCoE4G4aw1g8bLFWNRcw%2BweCkAIJoRBiwADWIA3pmGuAkMwkgAAcLC3oaAAJz0I0BuFh%2Bx9CcEkLwFgEgNCBHQZg7BHBeAKBAIEChGDEGkDgLAGAiAQDLAIMkK45BKBoG2HQOIER/6cFUCwjcq9JAPGAMgfMUhrhmF4FAwgJAkx6H4IIEQYh2BSBkIIRQKh1BKNILoWei14TJE4DwJBKC0GUKwZwd4VwdHclQFQB45jLEbmsbY%2BxkhHEPAgB4Qx9AywkK4PMXgiitCLAgEgAxyQjFkAoBARpzSQDACkIvGgY84hyIgNEBJ0Qwgy2ibwEZXNmTvGiNoTADhxmkAMS5Ag7wGC0GZAkrA0QvDAAuLQWgcjuC8CwCwQwwBxAhPwHOKOlZqoJOLPMq46wyFhE2MgkJtBwbwm5h4LACSHZ4FEcc0gdziC3SUB2LY5yvlGEoYsKgBh/bBjwJgRazt0FkM8cIUQ4g/HYsCWoBJYT9DnJQHgyw%2BhwZyMgIsVAyRfhHJ1t/H6phLDWACLwVAYKWxYBpRARYdh5m/BcAwdwnhWh6BCGEfoZRBizwHoULIErcgKoKL8GYAx4izyFafBg3Qxgqr8Dq6owquijF6DK2Y8rbAWvGMa210wrVaokIKwhaxXWCI4Kg0gkiuWcEyRYqxNi7GXwKV9CAuBXHlI6pU6p8LFgIEwEwLA8QBWkFoZIfY1xOH7ASJIDQkhmEbnEW9DcnCvXCNIKI0h1wNxcD4ZwlhDa3qSA3rmtefrEkyNsPI8h8KVHqPqZolJujWntLKSYtgnBGgsErAkHWTBgrkS4Jw64XBriYJcUQXlHjZDeLxdIAlSgiUhN0IvCJTAonHNid6%2BJITpHJO0VcB46TyzInnYu5dhlV3rs3UUkpTSymvX2GYKp/alF1IaagUpcQ9FtJg0BwYs7P3UiMKurggRembGIAMoZITJljJBYR7mMy5kLJBcszSayNlbMwDsvZYhDmLNOTC9YmDrlmruUcrdqgnmbEWW86oCSvnRB%2BcyP57HqktmBWQsFELMBQrOUYWFoBIN8CRQoFFaKMWLOxQe3xR7ZCEuCZg89pK4VsqsJS0T/K6UMsyEylltErMcqkTypM9zaUdDNc4CArh7VSrFZquV2rSCKt%2BIFtV6QNXOtC3oXVvwDXNCNQl01erkshbmDqu1qWctOpKC6ypSwVgeuKx8n1XbpHvrnQupdaGf1ro3RoIpUad0gbjRB2pibk2psoLeqtNa12FoSG9ThCQEj7CLZIHJs8qucFkX2mpyjVEaK0ak%2BDE7jGmI4LOnJDwWAKErPmSsv7TgjGcfgHd7jZ76dxYZ/x8gT2mZ0CAARl7r0xK9ZVhJj7R1pIyXt6xh3jtVjOwSEYAHEPNJA/scDy2oMoGh2UzbyPBjHf7i/U7nCX7nYIG/ZEOS%2BB0Bw3h4ZozuaLJI9M2ZwrFlUcEDRzZVz6O7P2cxkFrGVNSdIJx259yQmPOQM8wTghhOfO%2BTLSTAKZOLPk5ApTMKDIDsRZRLTqL0VfExbwO7PiJBGYCc94lb2LPGApTYWz8B7OMs4Llb%2B5L2WWE5VgjzfKrc%2Bb1aK8VOQHXSsK/F6LSqovhfVZkLLNrEvmp6MHyPdQLXh7C1MQ1PuEvx7i9lt1pXfG3p%2Bw%2BgNQODtHZO%2BDzYkPI1XZIB1%2BHCbSBJpTYMdNHzBv%2BDXfsfYb0OFtvEW3hIfDfW/YW72hRNfM0JEcaNrgUhOEjdzVwBIXr9j3qkYPhHt6nH97zz21foL%2BmZBAJIIAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_transform.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_transform.test.hpp)
