<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::TypicalPaste`

## Description

`Sequnivore::TypicalPaste` concatenates a list of packed sequences. The first sequence will be used to hold the result. The result will be returned via the type alias member `type`.
<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Variables<sub><i>i</i></sub>...&gt;...
-> Sequence<sub><i>0</i></sub>&lt;Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

`Sequnivore::TypicalPaste` can also handle `std::integer_sequence`. The function `static_cast` integers to fit into the first sequence.
<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Type<sub><i>i</i></sub>, Variables<sub><i>i</i></sub>...&gt;...
-> Sequence<sub><i>0</i></sub>&lt;Type<sub><i>0</i></sub>, Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
TypicalPaste :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Example

Here, we paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
using SupposedResult = std::integer_sequence<int, 0, 1, 2, 3>;

using Result = TypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::TypicalPaste` first reduces the number of arguments via recursion.
When the number of arguments reaches one of the base cases, the function utilizes partial template specialization to extract variables from packed sequences and place them into the first sequence.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Step:

template<typename PackedSequence>
struct TypicalPaste<PackedSequence>
{
    using type = PackedSequence;
};

// Recursive Step:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<VariableAs..., VariableBs...>,
        Others...
    >::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<TA, static_cast<TA>(VariableAs)..., static_cast<TA>(VariableBs)...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsXKQADqgKhE4MHt6%2BehlZjgLhkTEs8YmpdpgOOUIETMQEeT5%2BQbaY9iUMjc0EZdFxCck1TS1tBeMDQxVVEgCUtqhexMjsHASYLGkG2yaBbgQAnmmMrJgAdDeH2CYaAIIKBMReDgDUACpneKK0yiYL0wHxMAHYrGCACKHKxPB6PAD0iI%2BFiBIMamDSIARCO2u32mEOxzOFzYH0ByAA1ph0EJMABHLyMDZ3BEvN6fH5pP5iQHA4mUml0xnMhiswL3eEQhEfOUfLxZIwfU7nUGBKEUpjU2n0pksomBOGPcEwo24p7Ij4AJTqayyADcMdtsRbHvi9kwDvCjrL5R7CcSmF4iDcrncPsgDAoFB89WKNo9SH65QGvYa3MHQ7dJZHo7H4wabCmPlnUGGAGrNPBMWL0Z6kUFPeWlkPlm5V4g1uuYCwKZPN/2k5hsMMAeQICASClxkvZr3eBG%2Bv3%2B/IOR0L4swJqOne79YUYbujc3Gysu%2BrtfofaPksbE6nxEPOalJplg7lioiwBVpPVmu5XkASBb1HhbYkSxbU9t2JPcr23Z8rkbOCexvF8BzAlt5Qfacjw/dVsBAEBVUNY1TVhN001AiD8KojMSJHTBGzLW9sDzIEC1FA0kxLOjiQYy5mLbVj2JjOMuK3YtaOHS5vh46TzkY74pMwuUWI7S8ewbJtVNbbMrhQ69%2B14mTRxuHCn1nV8OUXZceVXECM2gnc3C%2BJMPkMhDWJPCSz2JL4bA8zSjO8j4LMQtlpWNFsv2VEj/zsoC1yJfCaN0qDfJgo43MbF4vT%2BAB9UQXn8ndsAgTznkWMNcqaRxkCKkDSruCrgt7BRqvQyDsMnXDblSyUiJIijpTNMj4TMQIIijLwsHVNwQzoQgTkik0nlin8hC8NIilpW0FC8Wgl0OTUXnQIiIm2YAEgKpR9S3YlLsbDRG1SD4zEbQI2XNeF1qVH99sO46NUShyBR9NwSzOi7BEwa7iFuzLHsEZ7jx0ltoZACIsFURH7olNw3rMY8oYIc6sYYHG8YTDMvrnH1COI0kRrW546sKjiEgICBMYUS4CqBYlAaOk9tt29BhYIO5FhZjhlloTh/F4PxuF4VBOEhyxrA%2BBRVnWEFzECHhSAITQ5eWKkAkkK4NEkLgwUCDR/A0MwkiSMwAA4Pf0ThJF4FgJA0F6Va0Uh1Y4XgFBAF7TY4LRljgWAYEQEBVgINIQ3ISg0F2OgEiiS5OFUD2kgAWiSSQPmAZBkA%2BKQrjMXhaUIEg8HO1J%2BEEEQxHYKQZEERQVHUOOdD0AB3YgmGxVX5cV5WzbDzgxxDDOl1QKgPmLsuK6rmu6%2BtswPggDxc/oYhQUmrhFl4WP49ICAkBznkz6ziAn7zxJgCkD6aCO6dKFiAvWIERmgnE4MbYBzBiAnDHLEbQdRY7GxzmwQQY4GC0DASPUgWBYheGAJmWgtAo6q2wTsQwwBxBYPwMQBBeAnTENDpgVQdptjgN4JdboC9aB4FiJPaBHgsAL1eHgAOJCnTEFiJkTAUIyFGG4UYM2ywqAGGAAoCseBMBjzHIpNh/dhD/F7tITu8glBqAXroVIBgFGmC1pYfQPCo6QGWKgNIvRiGlzOidGxVhLBmFDqgcRXYsCOIgMsWo9RnAQFcFMPwqQwgRGGJUUYqQijZAEDEwomQ0kMDmCMaoXQegNAmK0Tw7Q9DhN6P0FouSkn5LypMUp0xbDFJqQsK%2BKw1gbCWD7DgStSAhzVpwTeJdy6V2rrXeuh8IC4BbufQ2V8b6KOWFOJgWBEihNIJbSQgQrgAE5AhgkkLbMwkgkhB38EkXZPS/akADkbK4KQkge12R7LgSR/B238PspI/SF7h0jtHE2ij77JwfqnFemcKBv1QKffOhcODNBYA6MEpcmDsWVFwXZVwuA2ybvgIgQS9DGO7uIPuxjB5mKwboD6E8p5sNnr0%2BeWDw7L3TiGD469SzECRSitFUZyF1yxTijQR8T7PwSBfQIZhr5ApHgnR%2BMLxVkChe/M%2BIBEXItLvyowmKuAvV/tsJ8ACgEgOgboyBoDYHwIcLo5BjACBoIwQvHBeCCFEN0VgFg5DKGh2obQ%2BhC8mEsM2MbDhCssHcN4aAgRmxQ7CNEcbcRkilAyK9XI78wLlFMFUeozR2jGC6OJQYiQRjZAUuHqHal%2BhyEoGsNYexsQQnONcTkdxniNTeOsH4tWgS26YCbQU2hkTomNNiSESmrTknpCyb0DJKSZ05EnXU7oQ6%2BjFLnYOiJa7ZgJPmFO%2BpJT8hjoPUu7putOm9wZX0gZi8OBcp5ai9FP5MXYptkfGZBLJULNlfHZZmBVmjA2eGm5dysW2zBF8sEDtJAnIrqkG9/zbCAtvnLEF8AwVp1Xq/VVcK2CcERTvFgCgHS1wdC%2BwkLw8WzLbkS2QJLDF6PLeYkAwRaXTx4Fepl/il4QrXhvAjlciMkY%2BGRrFFGlzH0VR/SVgQZUoflSgKTL8VVKdGCRnaBVRMFXEwLblFc%2BB0ENVHCAgCsEWrNSQ8zMC4EINtTClBDr0GYN9ZgXB%2BCxDupIZ671sbeB%2BvqAGrBQbkAhhDew2G4bQ6Rr4ScGNQiuwJt4EmqRqbvUZrlXwFRaiNFaJ0SQotPcS2MdMRW0ewQrHGDrXYyNA6XFuM4IiaGnbfH%2BN7cE%2BAYSV1bpcJTDd8Tyh5MycUHIG7Um9FPTULrlT12jvKVNopO6Bu1PKTNo9K3FuJLaWEvWXT2nhuvX8oZAmPhCdI%2BR9MLx334pIF%2BuTSzSArLWZQBlIGQBmCxYEQI/hnZ2yDp9sETzfnMs4ACmO92tn%2BD2f4D2rtdmSF2Q7A5XByucECFxwZEcf3mx6Y3IH3HMfyeWOIrIzhJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/sequnivore/paste.hpp)
- [unit test](../../../../tests/unit/sequnivore/typical_paste.test.hpp)
