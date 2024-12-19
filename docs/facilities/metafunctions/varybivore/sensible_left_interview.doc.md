<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleLeftInterview`

<p style='text-align: right;'><a href="../../../index.md#list-examinations-3">To Index</a></p>

## Description

`Varybivore::SensibleLeftInterview` accepts a list of variables.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function first binds the arguments to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Predicates...
-> LeftSides...
-> Exist (...&& Predicates&lt;LeftSides..., Arg<sub>I</sub>&gt;::value) ?
   I : -1</code></pre>

## Type Signature

```Haskell
SensibleLeftInterview ::   auto...
                        -> template<auto...> class...
                        -> auto...
                        -> auto
```

## Structure

```C++
template<auto...>
struct SensibleLeftInterview
{
    template<template<auto...> class...>
    alias Rail
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

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = SensibleLeftInterview<0, 1, 2, 2>
::Rail<Equal>::Page<Args...>;

static_assert
(Metafunction<2>::value == 2);
static_assert
(Metafunction<-1>::value == -1);
```

## Implementation

We will implement `SensibleLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct SensibleLeftInterview
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...>
        struct ProtoPage
        { static constexpr auto value {-1}; };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

template<auto First>
struct SensibleLeftInterview<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct SensibleLeftInterview<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...LeftSides>
        struct ProtoPage
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        SensibleLeftInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
                        ::value != -1
                    )
                    { 
                        return 2 + SensibleLeftInterview<Others...>
                        ::template Rail<Predicates...>
                        ::template Page<LeftSides...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMz%2BpK4AMngMmAByPgBGmMQSZmakAA6oCoRODB7evgFBaRmOAmER0SxxCVxJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxickKza3teV3j/YPllaMAlLaoXsTI7Bzm/uHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8jj6FhUt/dPjwImBYKQMQJObiY51QADo4X9HuNiF4HIchIwMjF6CFMFQCABJQTxABueEwAHd/iYAOxWR6HBmHIEgsGYCHM0FMcGnKFEOEw26HfZMBQKfnKYiYfCiIEKBEPRmHJEogiHCWoIgAJSYdH%2BippdIVisZHNZEN5sPh/ju9ONDOVqPVRGUTGAbNtdoNSuajmQQoE40wqhSxEOFsOxLEXjeBoAtFwaQARE4WY7U5P%2BQ16u1M4Gc7mQ6H8h7ASXAxgEOXW7N2rwZIxq10x/yJtXEDWoF1uiElstsQRiq13TM1tMZrMe3Msrls06mmfmotDoUGUXiyXSmdVm1Ghl18LAQ7aujvVtO1DH2gQiVSvAyzCDgXVkePJMpqmAvNmnnQw4AMTwYhxnlB1VXRBhMWxXECSJYhSQpCEAKAgh5QNUd5wLDDZ0LPll2FNc4RvTdZXlRVQLbDtL1HNDJ0VLDF1wmEcTxIQ8CwbdRzIghkUddtnSbTjGS9BlBLtWZfX9CCgWDUNw0jbwY1onMaN3HNPQAVisdTEwgJZDljQUvhAEAWCYABrTAAH0MmACJ0EslDTgyAAvKzHJ3NS1JUzyfMOPAqEkwMZOOJTfMZKB%2BXMAA2aKiLvLcIWY4Q2IfflSH/QDgOtYz5OjJYllEsK01TSUCHWBhDg0FMxw/VSisZOolEKsKvVK8r9ITTMatCzyk105qhPTd8erfF8ATqk0vwXH9GN7TBywHUic33Bsu2bM8%2BM7ATTjmhbK0i59DX1IaxvQqbMPO7CLQO7AVxFR9dv7Sslr3etD0vU8KK1HUrx20t5qex8/lOk6JweeiZtQDLkPS8N0TQBh0FhpcYQAeQIBB4g4xFuJVNEMTwLFMCSwkgTgslKVOJDxnS%2BGBCRw50cxoCbqpWkzunC7OaulHBXwx84vvbHVPI88qMnbycwhnDLSY6DWPYl7jVFza1sK4SQomsSfTvQLpJDMNf1yxSteNSX6pMTTLZ0vSDOtb10GM0yLOsvBbKlByIRctylZa9merC/y9aDA2Bp8iL4TMGKo8FhLTiShXUrhdLqfcnKo0wfKw962lDja4gKqqrq31fAPfMat4g4RoLQ7L8OIEiqPYo3eKSPj%2BWUsfWnMAR9BbnThSs7rnOSswMqC8OTrUxL8b6rtCu/IC6v9eIbO1IgNffPAyDieg0mSQpiEmax1nh7C4ysKPH7rxboXT9NufDgvy7G27duWM7%2B/H7Ugfo0OMAwAnFbPGTedoCpn2UrnUBnl84VTMMcSw%2BMIKEygnife5MEKnGPizIc0Cf4gEvlRU4sdZRf2/naZ%2B3NX7YQTp/XBECfK/1nNPBhZshqlwfuXWgTVWHHVHuPCqIDi7sM4Z6dM/Vh6jSOpA8ctU1LS2unCR6FZhZqRWoeNan1zxqz%2Bn2FRrMxrHVkRwuil12RmMhjdO6BEYTKMWtWSc6ir4niAV9C819dEA30bgkGxjxoAHoABUwSQmhP8f8IJwSAAq2AhBRJCeEx4kTQlhNqs8Bg%2BwvBHAhOcOg1xUKfm5gxKG%2BJkZEEOAAKRArjVE2AACOXgxBs2kfaHWfpl4h1DDEVAngIwZ2orSfEp5XFVNBmzPx/wFEoweMQYAwsnEAFkx5MCoF4DJDRPrbxQbvNBsF4KUzcBodKXB0rJEOGYeUxkiFuHqY0362BjI6LcDMuZBiwbiTvJZe68QUKPAgEs5oqz1lZAhBc7KIBjbDJbOcgqY0PnIC%2BaKH5/x/nLKBQ4EFpwhEPIhRnKFwCuCwosBwFYtBODqV4H4DgWhSCoE4G4aw1glRrA2DGMw/geCkAIJoElKwzIgHUtSGE/gAAcUVqT%2BHFRoUVEqACcQQyUcEkLwFgEgNBHKpTSulHBeAKBAEc7l1KSWkDgLAGAiAQBrAICkc45BKBoBBHQeIkRWBbFUGK2MUVJCHGAMgP0UgYRmF4LeIgxA2J6H4IIEQYh2BSBkIIRQKh1BGtILoE55JiBMBSJwHgpLyWUp5bSzgqNzg2tVKgAK7qoqeu9b6/1khA2HAgB4R19BQw7EJbwQ1WgVgQCQA6lITqyAUAgAOodIBgBSGSDQWgZM9UQBiIWmI4QWhXBzbwZdzBiBXFRjEbQPdDWcodU9VGDBaBrpTVgGIXhgCQloNw9dpAsCmSMOIS9gED14GJA%2BQtQYe7nC2Jy8IQJFU0suDETN26PBYELdxPAqruC8G/cQbpShEzAkMMAS4RgeUrCoAYOZAA1CmqMUiMEfZG4QohxBxso4mtQha036EwygRllh9CEz1ZAFYqAUgND1RwWMXwgGmEsNYMwWrkNhvYvAFYdhP3OAgK4KYfgTmhHCEMCoIwTmFEyAIFTehdMNHmMMKo3QFONAmG0TwHQ9DyYxQIPorQTNabM7MSYNm8gnPcwMDTCxtNyZZZsCQeaOAUtIJq3g2rDhVprT6v1k8G3wIgLgQgJAEEcqWF23DKxMZMCwAkXSpB%2BWSH8DCeV1JJAaEkGYSQUV1XqSirK/QnBlWkFVRymEUUuBRRFbKkVPX1KSC4OpeVUUIuFu1bq/VXLcMmvNX2y1pbbUjrHW2l1bBOAtBYMSaksYmB3QbFwWVMIuAwhpSGkg4aTmUejTR6QdGlAMZTboZIGas3rtC%2BFyLRaOAlutecQ4FawzEB23tg7wojsnbOxoJtLbB1toy2YLLs2jW9v7agVt8Q7WjsxwjkY23duxkh5O2VXAjkzrnZQRdKbN2rsfXT7du790OEfceisp7z2FqvTeu9D7ENPow6%2BrYNL8CSgxd%2BgTF3VD/qBI%2B4DdRC3gcg1caDIuu1hoQ5y5DqHMDoZfVhg8c38OugUMRikpHyMC9u9R2ND3ZD0eTTS17zGcOiasOx8DXGiu8f45wITBA%2B4tnd%2BJyT8RpM/u4%2BZhzfglOIwM2pxGLnFg6fSHp7InnVOpDT8Zvzpm7N1As056zuQs/2YaMX5P2nbBWYTzXuYefXMhdWOsYLhKWthYLSm6LhPweHcPMd0752m2pdDRlztqOe25cwPlkYRXFVtY6yd6r1JRvUglTVurw2Jvd84NNg1c3TUWqtWWnHa3nWuq26Dr1hwWAKGJH6Ykg/WTjGDfgUN1341UZjRIe3CantO46ABCkDvbZqIZfZd5arFrLbloBTbY3534P4RjP5biqjNp45DoZb%2BAo7drGqLbn7Dr2oYFtoQrIApApCWRP6yqWQv4EBfLX4PZ0BU4LpLorrboM5sE7p7oHps6Y4npnoXqi6YDXq3piD86crPqYZvqi4foS4/opp/rIAAby5Eiga8DK6rpq6waa6Po67pB65C6G44Zo58AEZm4kZkZUqco24/60YO4AGMbAEGBu5sY2Be6ya0p8ZZACb%2BJGQh6WASZRZSadweHl5ZAuDx6Z56DqZlD56p5FBZB15GZZBV5uaF4x7F515hGOZWapF2a15RHea5GN4p6Bat6xoQE75QEcAg4sAIH36P4oGyhoGj7pYdo4E5akB5YFaUChaL4gBmAnaBDqTqTVbk7Sr%2BDUi9ZVFRZ762Aza4H5TFYgA1ZdZcD%2BBRwbGyrdZRwaDUgd7%2BCQGzE6qT68od5BozG/bZZo4rDIYZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/sensible_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/sensible_left_interview.test.hpp)
