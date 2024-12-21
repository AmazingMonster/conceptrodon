<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Observe`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-observe">To Index</a></p>

## Description

`Varybivore::Observe` accepts a list of variables and returns a function.
When invoked by an operation, the function collects the indices of the variables that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Preds...
-> Oper
-> Oper
   <
       V<sub>0</sub> ? (nothing) : 0,
       V<sub>1</sub> ? (nothing) : 1,
                  &vellip;
       V<sub>n</sub> ? (nothing) : n
   ></code></pre>

## Type Signature

```Haskell
Observe
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Observe
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will observe `0, 1, nullptr, 3.0` and use the result to instantiate `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation
<
    static_cast<size_t>(1),
    static_cast<size_t>(3)
>;

using Result = Observe<0, 1, nullptr, 3.0>::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Observe` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `stare`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `std::type_identity` to avoid constructing
            // an object of type `Operation<*>`.
            return std::type_identity<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (stare<Agreements..., static_cast<bool>(Phenomena)...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCD%2BZqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BflyBdpgOmfWNBMWRMXEJSQoNTS257bbj/WGDZcOJAJS2qF7EyOwc5gDMYcjeWADUJrtuXo60hACeZ9gmGgCCewdHmKfnjcRMd7sPz1eDEOXhOZzcYmAJEICBY90eLzM%2B2B70%2BbmQY3QWCo8MBzwImBYyQMBPBBKJJMw4KYl1QADoGfdjocmAoFMcAPLJOJMWoMUjHaKoTwMunKBCMVBsZi4p5jXl4ZDMgRjTAANzExxpRGO8uImAgywRJn8VmexwtxwA9FbTgA2DSYkAgMJYVQAfSUAEcvIwtuCAJKi%2BEO454dnIfW8zDoBGW622/jEY4ECXHehGVPHVBUe0acWS6VMYMOulxy36ggbBinACsVlrABFwekAF6Yd0EUUB%2B4QJ0uhhuz2YH1%2BqnnIOM/5G82Wk1mp7x%2BPlpcJvP912YD3e33A8duSdl/4mUPh5lRgmx2erm3HJMptNoLyCbO5k8aAjEX3vsM198FhgpUYYtGVLFcl0ras6wbZtzjbDsuwZAApXsN0HLdh1HPdwSQ4Np3A5dTQI1dlQYVVVGSZNtVQY59QULxaAIT5G2gkwm0NYjV3nTiSItW8AHUPhYJgAGsPnfftvl%2BY5kglQCix/BQaNTXkeN428AHcPlEGsmGQLY2WONhFmIdkczzACgOYEsNGOLx0iMaDN1UNjGzLa9eKXSTiB%2BG4ZLkqymFOU1LKLYN/Fghc1JIgSPg0uhaF1EgmIkgh0GdKS/NdRVMAUd93MXTzV283zf3wAzgosQ8TUi6KuI8oq%2BNtQTjni2hEvsj5UzPNAiUacMBDvZ9ukGnUlKaArGqXajlSJZjWLMO1ZMLYDXL7PB207MMBXgrbtBnQqpotbiGqOi1IOIBg6s828AzfB1lvk1b6zwVyfzPd9P2/UNDCvQ6zstW930ewK2IsbQ3tPdkqDEJQBVTRg81eqH01y9kVL/B0IbA06ztvAAVCV9STTABUMMqt1fPMvqpFGxA0352XoNlrvU20Ma1GtnKp98YdoJR8tZmLbTlLVaNyhiCAFbKKvMz6v1p2y2toIWb1tVklDKehfwfD4qGIWQqYRrUfN%2BSaAd4iAQYUl7XNORbzDtY4wDAfyVplesIabA6LfjW77o0a3nosV6mx/X68yDj3wch2zGg%2BIUs3l76NFIVWl1vBGay08Wq0upG0WObHbJ1SjcriNUPn1Ek8ErmSCj5BRzd94K3BNNwLStgKbZDu3Hcdt2nujr2WP7xaw0L/azgXC2aun9P06Bh0Zdyn9lcFKvME69A7xIXXxfoxjm6O/sfiMXLnXGggIBXhQBV65IjV2GeAcX20LprY26Ml4%2Bpo/sqcp5WftdGqHFgF4n%2BmzPM39GLvXZEFVK6UQCZUFrjDOzVtKeBqGGAg0MDYvmSH0NOaC/a2g0ggRUCBSINDCPA9q%2B9b48wdDTVBkDhbHEJowAUOdaENEEHgaMeYuQ8j5KwqasVc5QUQc6AgNxuTujwFgfhsifw6iYGqVAijSJjC/N0Iw11bzk1QNEbQXQmLmVkdyIR3IfiiPOHhB4OM2Grn/v2SxHZFGMEcCo84wjbGZHBDArsvIIBIWWA4pk3EIrzzQaA/swkxIKPQtuEcu5/TnAgMGSwoVgJPweERCKT8X7HQin2NKzoEkeOSZhNJ%2B54I5lFBAHJzA8lRMbEU400TwEvHxISYk0ZqS0lFM0pgsodFeAcJyaIShiCV06cUlMfTKRkiWQMr4QypzYGZAYNkoonjAH1ISLxQCAT/XsmEYAxwABKTA6DzSwIcdx4Eynx3BPsw50pcGih2g0RwyB3SiDGOCIUnhewjPCZsw0PtLQyLkeOKKXSorPCtAAKjReijFmKrQIlReijhuVcHHAxdi5FmKyXEuNL0ikayIQbKPKc8Zky/EKgEDEnpTxzmOSEF4ZIqQlDoCuRLRi81mWiMBOccC8o/kAtZAQFsG0EK9i4KsSVvzFQyqBXBBVnZey7AOvCbpCJOWXMFYfFKuwWIcmmRXfcqdjhcAFAwBitBkifgFLsOkGh7jOhuXQcEoqAnHkNc8KV6qNZxGvv2BQrAOysnBKayWApuW8rSDGBNsD8LPw4KsWgnBay8D8BwLQpBUCcDbpYawSUNhbHtrsHgpACCaGzasESIBaz%2BDpHaSQABOXY/g7RIi4FwMwZh/CBFzRwSQvAWASA0KnQtxbS0cF4AoEAqdG1FuzaQOAsAYCIBAOsAgyRLjkEoA/OgcQIgxs4KoAAHHaAAtF244wB9L2skHSMwvAYyEGhOlB1/BBAiDEOwKQMhBCKBUOoTdpBdAOo0j8ZInAeA5rzQWptJbOAckuMe8xuY72Pufa%2BpUUhP3HAgB4IkF7kx7GVbwDdWhVgQCQOe%2BgZAKAQFY8MYAUgkg0EYnEVdEBogYeiGERoNxkO8DE8wYgNwrWmIcFJ0gvVPkcgYLQSTMGsDRC8MACE7VV3cF4FgYSRhxDabwPqbolcjPFq3F0S42x61hAJBO4t1xog/Dkx4LAGHPx4BncZ0gldiBCiUI2QkhhgDXCME21YVADDAAUAANTwJgDSwjC31sA8IUQ4gwO5cg2oDDcH9DRZQNYaw%2Bg8DTPgKsVArrMhGYfZiM4jZTAVssGYRdoXiCeNXZAVYnQRp%2BAgK4SYbQgiDgGKUcoeg%2BWFCyJ4VoC2G6ZFm0MeIDqRt8l6BMFbUwqg1B6LMTbJk9B6maIdqbV3zvzeVWsatoHUMcHzaQBdvAl3HAI0%2ByQL632kbMOR3Av6aODuWPR%2BLqwJRMCwPEQ0pBW2SA9b2/wkgNCSDMJIB0Ghax2m7foTgU7SAzrrZ2rgdpb3dtvZT2skguC1l7XaD7GGl0rrXQ2%2BL2693MYPThk9HGuPECvWwTgjQWBqn8A%2BoKLJHJcG7XSLgnrv34CIP1/94G8sgYkNIIrSgSswd0EkBDTAkPGde%2B9z7mGODYaPZcKmEupcy%2B2dF%2B1ivle2Qo1KZI1Ha1mEh1zzdTGWM%2B%2Bo6ezjYe2PIOIJL6XcuePdq4KnfjBJTKUBEzBmTEnlPZ7kwpsxynVNePU5pjDOm9MGf5sp0z0WLPFvwNZxwtmMMOeQE55TrnqgYc895m4vntjFoC0F%2BtoXwuYEi2ZmLFzueJaYMltLGWsvKdy8BgrevZDFeg8W435W4udasJYGrdWhslqayqTgrW0rtYP9YHrX2%2BsDfq8dsxmQXCDkm3oEI8w5vDAdYtvkT/f/dbIoH/LbS7aoV/OoWYIAl/UbfbOYEocAnbGAm7S7M7MAi7R7JSZ7CQS3dDGDb7J3aXWXAweXD3T1EHNXPeWjQPBjZtUgWHeHSgV7EnMnRXTHfwJnMdXYLHHHBnVnQgzgDnddbnHdfdQ9XDCPYXUXbYCXZ9FgBQNUJUNUBXOkSkMYVXMHRRPQVffLUDDfCDA3bfHQEAXYUgU3c3FDInN7AgxdLDAXPDE2FgBQpQlQtQjQpib3KjNjWtPVKHYPbdUPHwuIaQqPYYZQ3ld0VQ7td0Tw90eQvXOgNPITTPYtPPLTetDIgvJTYLYvQQUvLTBvTAXTfTMQavYLWvczQfEzKzV/FvGDNvDvYLLvdzXgXvCTAffzfrEfXgMfVNSfOvGfQIufBfdLTLbkbLXgPQnXQrTfYw0rMwvfYwKrI/TzQbRHRrRuTgK0J0W/brXrOIDXC%2BU/XbN/cbD/NAh1b/JArA/IdIQAq4%2B4pbe7P/OAvbVAnIW7SA%2BAjA24h7GYPoWAu7TAh7YbdYTYF7Gwq3NnTgZw1w5Q44GI9Q6MMYKgsHWtOjIPRjGHTAOHYYRHCdNgkAMwRXXYXYWsWsTHZPDQck/tW9QQ%2Bw5dWwTneg5YFtEALHOkCkjQAdPtKnW9MdMwB1CdXYOwr7YQ7EhgidL9RkiU5ktk1YULdIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/observe.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/observe.test.hpp)
