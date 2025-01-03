<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRemove`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-remove">To Index</a></p>

## Description

`Pagelivore::CognateRemove` accepts an operation.
Its first layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function removes its arguments at positions indicated by the index list and instantiates the operation with the arguments left.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
             &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
             &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
             &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRemove
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove variables of indices `1, 3, 5` from `0, -1, 2, -3, 4, -5` and invoke `Operation` with the result.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRemove<Operation>
::Page<1, 3, 5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 4>;

/**** Result ****/
using Result = Metafunction<0, -1, 2, -3, 4, -5>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `CognateRemove` by combining `Pagelivore::CognateSegment` and `Omennivore::RemoveValues`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

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
struct CognateRemove
{
    template<size_t I, size_t...J>
    using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

    template<size_t...I>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Send
            <
                typename CognateSegment<Detail_t>
                ::template Page<I...>
            >::template Road<Omennivore::RemoveValues>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGYA7NIADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKdJ2mA45QgRMxAR5Pn5Btpj2pQzNrQTl0XEJSam2LW0dBd0K08MRo1XjtQCUtqhexMjsHAD0AFQnp2fnF0cHJhoAgsenANQAIphprozIeJgKj2fXdwel2B5wBtxu4LMgQiyG8WEeJkCbi8jlohAAnojsBDzNCGLCvPDEW5kAt0FgqFicYCzo9sKoCK4AGLEWR/U5gxksNIGRnEgjo97MNgAOjFVLuC2IXgcdIZzNZggRySsyWeiKsdwhXJ5TD5SJ1vMwxKYKNQYpFWMesKYCl%2BQkwAEcvJ9MKRHqaiBaAGqtPBMWL0BQS25SmUEOWMhjoFmyYkO52u4m%2B4j%2BwM/C1UwLYrUqiGPAuPQ1641Iz3msVRTAAdxTaaDIcLjy8WSMj2UTGAmARgWejwTLvxpbcVdrfoDQYt7rrE4z4uzGpxasXWppT196PZJ05mG5RpNZseM/TIbDso3S4sjwWerwyGtAgWmFUaWIHsPADcxC7lRZj/QTGXQIr0A9VgOpe5aWUYhMBoVQtyubVd11fU3AFIVWDda88AAL0wAB9AgQzQIc0gjaDYLweDET7AhpVLTVwTXE5%2BwQFECHoBCdz3EsDy9ecc1DOjw1Y9iAPA1dIKeAB5NgGAYPAPxIdgQAAJV3VAP0wX1vB%2BLiIWFH40iYPZHlkxgFKUmDfwg4tUPQxhMMzBdJWE2V1JYTTtO/PTANVMDGIhIEjkeCxbW7Nxwv0u47OHcsLQASVPNyIw8rydJdYMkTJEAQAiLBVHwpREyHYkEuc7EXPBPM7ibWL%2BUFRzRTFMLkAAa1uYhgCywSmxvRx7xIp8v1od8iEePB0HRWh80LCBZqbAsDgOOVjOjBEADYNAouCyqxTMtqLVBHhgkyECLBBuy8Bhq0MRl0AmrlLVqxaCx2qi9uzMaKxFKhFQIfDWm60gFsW5bHjSrSLu7SIGQ9LqfEYAhntuV6C3LEGXte8G8j6aGTp%2BCMgcRwQFBRtHQpMjqurJ8UscedZQYAWitIQ2IIDjjXp4lQabLBYQc6h/sBmn1lykaXSnXnC1a6nuvFnzM25hcJKY1HC3qsszQtW5gBg3ckZ60GWwiYB207bsaMefnaEFybpogC8kV1/W5III28zVC11kZ1XQJXNXNci7WxQS914rFAApZLpXcjStIyn5iRyvLo2fIqnUHPYyoq90U/y9Piqz4dI4qkM/NBoOHMMi1Zc67rG0Lfq7wfBhhrEb6Jqmmb6fm%2Bmm3B%2Bk1oekwtve1RPuwA6NCOgmzvxmhiAWZsbruzAHsIXdybR8fJ%2B%2Bi0/tkEXgelpaVsh7sCEux5YaJhG3e316MdPx5B5fQwR7HmDdqRJLs2n2ep1kDnSvt2JQJEHrXVuoIdej0t4v13kiaOX0I4ihYJNdA9Bj4KExurbG5946X2vrfeGwASbIxfs/fuhYcaeDxqAgmy9iZuzJi/OuNMlZ4IZszVm7NOagx5tQgsNtBaH0ENgsWIAJaYClkI62DRbaNQgOg8kWCgYKEkdI2RXCmzsPllIxWdMuFZkCvTIOqCXaYANqTRuBYTZtg7F2HsfYRFKPtrQR2TBMTOz1lYlhVJPbPG9r7QKQFTFSRYupZAOwshQ0ikoaKtxzEhxFGHfeUd3TVycmKaSoDiADldEbVysdUqEMTllNw%2Bc06FSLkmX%2BudrwEHQLlAuNTM51LcKXAS7pcmXXye0octNLRVQrmY5C%2B4DSNRri1Km9cilcOboNR8jIRqd3caDPuOiaErSHh/Ta21v4fV/vtcUh1xpAJAdfRey8oFrw3k9BBhyJ7HJQSksRAN1G4IpuDC%2B%2BMSHMKRo/RaVCtln1Wns0eBzKLPLcH/KepyZ7nMwPPBh4CBCQNXjA%2B58C5GIM6VaVBKjMEEU%2BS/H5hC/nPjvmQh%2BlCzRfLRrQ2g9Dr4wSYffQ2QLdGzI4UYpsjN6Ysy%2BvSKMMZ/oCKRC/Vx7wX6bIpk2C%2B5TiS9ISAUwZZc5FNhad3CAejgyBO9i/AVxiqpapALFc2XYJVuClQo0Rwt1GaMMSKBlr1pWYGURgtRosFa6U4U2ExEE6rjN4lrfiIpLHWPdrY5srYzaOMtr2eRAs3Hdx5tmTx3i3CRv8QuA1YofYB39n7XM6pJLBUeJFNICgvCcX%2BEhHi9kpnZOGYJM8EYq01vEuEitDp1r1piiGptGFmqtohO2/srgbJhNskO4cyTw1WhtHaSdJU9jhxSf%2BJOVUJ19vQPGAZ2ckRbqGVmQSoyuFVznXxH6S6DAruku8Ygt4BAxona8FodABE1VBbG02RZGrOLMk%2Bl9DBkzjnTKelWjEA0zsksGxt87r1htvV9ZdQyc2GxjfYs2qkmB0CAx%2B/DM0fGu05QJXKDki1wcDshtCdGsmjrvbaX4HhBD4ciGQADI6ZFimwPQXNbaUqTujMSNjn7OPEn41GqDlVz0/oQyhJDiGGo8Yqtae9vxH0JFA2%2B4TRGv3cwU2jHD3HE19m08%2B/oUmBPkbHarWDAUg0awYwx5tTG0OaZ1r4mT2G40Q1QEwEeSaDMkezT5lhFVKONWo058ttIAAqgo7xiGUKgNIiSF2oaEyUx4SW0gpdoGljLFcaMNqUzex4TI8BLyIju4T%2BXCvFeJNV2r5djN2P8w5IDbMxLDkDaWotg6VMoaqzVhYG7xoOggTHESjXRBFfSy18bBB3TTfRe1mDhZTPdatr1jm4k3CtYWAN6qcXaMjeDuNY7q3O7rejJNn6Kql6zdlPN1LS2kQ3bWw0dFPS8mycvMbLrMXlZ9hFQqOMkyeN5eSwt5rSJnuyeizK01hZKNzstcOb7k6ZvQaXOdoKtIPDAGYIyB0wA3aZdc5d1BzGH0ges/V3LJOyeYAp27IHYzLtZDwoRR4aTecEWRlHPTuXQvfq269IOQvCIWgANIxqbDBZ0NW9IQEzGYDa5gNoQHlz2NwjxI6FrkaZgAEhgxg/OraWd07/d0kcmby7Lg5wsxbwmKYmVdn6mGbFo86/%2BhNPXXCqaat2d7i20jEl9%2B7KL5qYv%2B8eBjxDENiPEgl6RvxdmsTJ6U48C35Ird1cqj2laCVox3j0qIBgHpaAKGOvER4xk7SwNM5CqpBUM5ruNFtIFVd3Oll6k3YTBesA19K4T7nFXsq4WFwLvOs%2B5ei8TxO0fjBk5NJadUrvxcyoO5d0PgsF6KYy8XyLkUivE/K8zmr34GvxRa513rg3RuTe/tM6F63SbbdM9hQ7p3LuHuJmIO7wweom0OYesOBW8On2f%2BRuceVGV%2B6O5qmOeGX6SIn%2BxeAcjmQ2l6bmamYoMe8yTYpmAAsp4MFn2GvmBpnjJggQnqEpPhEiCCwduETk8AlHuFGqBoksFKwSCGCOVl7llupuhsBjpkzjliJKziWBfFzngTzmfvPthHzufsgofn%2Bm2JgUBp2rWsOCnCwEwG1ARK0jvh0nCnnJviAIYcYfhKYbUqVEgkzFwCcvZkAQWKfqoYlGLiJNBKgEQAmpLi/CIWKCekrttv5kHntiHnIoIr%2BnVAPiJvupqm7pKikdLokTIeTpgJTkjOnpgJ%2BrQIROEfKknigSnoEfUgJC/AGtmLnkaAFkFsqnJJZMpLlIqj5MQaUWURapUW4Cehqr%2BiUT0agWnojozjkKdjgSWgodPt7t5mRn7hoaZlEUmn4QERbNHhFtnvjoNjMXwfwWCBWvSKwDyN2AOswfwYhJJLiDCHCImiSAIHsGRPMuwSxD/jkNTrTikq9hGB8a%2BvsbSKQQUUwFQNdI0AIF8XMRYjTCGGQSCWCfiP0DoagKTrIYQsqhMQCYJLlH0VwO6MEI8P4CGLiZsc7Lym4RBL2l4GkMUOvOpF2hGBcaZkIDSXSegAybWhGDbliTQW4BoO6GYO6JIKdm8SFJybbIkqZhKdyUmsCS0IiRCXyQKY8M4YKe6EzISdIKqcSbsWrBWgloTIkosoDC3m0BACnAoJhKafGGyZkPST8Fye6DKViCEhwJsLQJwP4LwH4BwFoKQKgJwDapYNYNeNsLsJbFCDwKQAQJoO6ZsG1AEJICKBoAABxmBmAACcmZXA/gaZqZXAyQkwnpHAkgvALAEgGgApvp/pgZHAvACgIAApsZfp7ppAcAsAMAiAIA2wBAaQKI5AlAaA3IdACQUQmEnAqgqZG0TMG0kgjwwAyA94UgIoZgvA68hAJAk0eg/AggIgYg7AUgMgggigKg6grZpAug%2BJ1Yz6aQnAPAHpXpPpcZAZnA0kKI/ZEYqAVAjwU5M5c5C5S5jwK5ZgjwEAHgI59Ab4uIXA6wvALZWgmwEASAw5BWUFg5EAqFo5iQwAUgQpNAtsCQjZEAsQL5sQEQrQ6I95vA5FzAxA6I0ksQ2gDQLZ0Zw5bs0kDAtAVFF5WAsQXgwAkUzKjZ3AvAWAhhRg4gvFaujQWkIl/pz4DQKI%2Bw0ZEQjIJZ/paIsQz69FHgWAL5dEeAFZolpAWkxAsQ9prwElwAaIRgcZmwVABg3U3o3w1Y2mvp0Zu5wgC2h50gXlp5agL5V5%2Bghgxg1g1g%2BgeAsQjZkAmw6W/QIlTMZINEpgIZlgZgtZZlqYWAMVEAmw9QSpLg0Yswfg%2BJYQywlQ1QegxQ2QAgJV1VmQtVDAIwlV4w%2BJBV/QgwMwngnQegHVTQiwLVYwiQ7Viw9Vo1QwQ1qwI1%2BV4ZewEgj5HA3ppANZvAdZv505s585i5y5yZoFEAuAm50FUZcFMZ9lmwl0QW4weVpAiZkggQIomZgQqQGgkgZgkgW0Gg/gG0mZ%2BgnAZZpAFZgQXAIoG0XAG0qZmZBZG0/gkguZT1G0K1L5dZDZTZZ1rZSFXZyFPZH5A5FAmFqAkFY5E5HArQLAH4yQTMTAGmoVwFmZIoINCl%2BARA2VO5sg%2B54gR5/lSggVF5ugQpN5TAd5oli1y1q1r5HA75fZKIjw35G1/585NobYXA9NjNYFEFaFCQCIUIZgp1CFbZ2NWF6F%2BNRt4wStuFOZApBFjIS8lApFF5tFlF1FpAjt9FjFzFDgzt7FSMnF3FL5fFAlQldezt4loVUl/p%2BAMEslPwL5il0SjIztalvQL5WlOl6Iel%2Bw/phlxl0ZZlFlSgVlYdps9lfATlCgLlNY7lztXlHNvlx58gPN55/p/NIVdlqVVglgkV0V8AcVZEOQiVyVvY7d1gGVa1WVk0MdsVPQfQOQRV7gPVBQZV0YU1VV%2BJNV/Q41pA69OQK9bV09LFA1Qwm9/VAgXVSwFQw1fVY1C9pVUwk1FVl9sFWwOw81T9JZYtyNnA8tW1NNytqtKZYFh1LN2twNet51pAl1WAiQN1JZANQN9Nr1yQ/gmZRZgQb1H1cNSNF5KNtgaN%2BtmN8A2NvZn5GFptxA45bAnAZNAFLACgH494H4KtIoRoCw65zNW5zS%2BJNdPlEgflsgAVTdOgIAwQgtwtD5f1S1z52Db5uNX5P5qgNDdDDDTDLDEY4FhNmtx1gQgQYDGN7ZKFGj2FpDhjUFUiyAtJ%2BEjDmZ%2BEqj%2BECjfldANtxF9t/prtPF0Zbj7tLFXthNHFXFPFEdmA/FglYgwdJlodklmdYlMljgclsdqgSlCdJlSdGlvAqdlFGdBlqYOdvAedllu4RddlejjlnY5drlVdJl3DB5vD9dAjQVwjrdYVaVNgWluVvdCVnABwOUw96VmVCQ2Vk9N1J9fgEArgm95VF901DVJQOQm929ZQD9Uz7VvQB9p919%2BQt9wzZ9u9I1d93VGzV999kzq9s1L9h5otUjtZX99jjwtD9DjwVjzDJYy8B17DWjsF8F4DkD11i1cDSQ9N2j/geZcNVZ2jyQENWDVz9ZuDzZ4Dd1/gj1hZyQVZqZkgOZXA6ZWuEjgQlza1nAnzGNi1a5kLeL0L%2BDmwZlWQzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_remove/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/pagelivore/cognate_remove.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_remove.test.hpp)
