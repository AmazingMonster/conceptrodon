<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Agent`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications-2">To Index</a></p>

## Description

`Pagelivore::Agent` accepts an operation and returns a function.
When invoked by a packed sequence, the function extracts the list of variables from the packed sequence and instantiates the operation with the list.

<pre><code>   Operation
-> Sequence&lt;Variables...&gt;
-> Operation&lt;Variables...&gt;</code></pre>

## Type Signature

```Haskell
Agent ::   template<auto...> class...
        -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Shuttle<0, 1, 2>`.

```C++
template<auto...>
struct Shuttle;

template<auto...>
struct Operation;

template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

using SupposedResult = Operation<0, 1, 2>;

using Result = Metafunction<Shuttle<0, 1, 2>>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will invoke the returned metafunction again with `std::index_sequence<0, 1, 2>`, which is an alias for `std::integer_sequence<size_t, 0, 1, 2>`.

```C++
using SupposedResult_1 = Operation
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2)
>;

using Result_1 = Metafunction<std::index_sequence<0, 1, 2>>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

## Implementation

`Pagelivore::Agent` uses partial template specialization to extract variables from a packed sequence. Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    { using type = Operation<Variables...>; };
    
    // This specialization handles `std::integer_sequence`.
    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    { using type = Operation<Variables...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMxqkrgAyeAyYAHI%2BAEaYxP4AbKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxZkl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbrv7h5gnbkxeRAB0jyfYANTIBgoKLwDyyXFMPWeJg0AEEZsQvA4XiDgIwCMCQSYAOxWUEvdEvc4HAFXU4EACef2YbCBaIx4MhBBeABFMI06C9kVYkdSTqjEWT0VjLtduTjrrcHk9jq93kxPi8hJgAI5eRhbUgvQWoR73ABqTTwTGi9AUpJBGJeFKhtPptGuUtl8txbg1xC1OswClVQJFCMNTJeXnSRkxhMwjOO1J%2Bf2IAMy1ztDt1LrdxwsjJZbPdGJT6IA9OmXgAVBB4L4KP7ILW0PAAL3DAheCEM6F1jISGhm6BAIDCu1hxAA%2BkorQwtiZG/c05i9tijnixzy8f7iZhFcrY6KPl9LXL%2B/O/UTWAHs/6F3cVY8o9rdfrDcaqaamHQLTL1wPTnu/oqT47ncLsOfUyivT7gFuAYnMGvz/ICpxvjGn5somrLxgiI58hOZyzjuqowsQmB7HCepupyf5hABACynjoIGwbXrepwYVhbCCB%2Bw4iq2BJ/MmoLInB7IIumABUfH8QJ6bcfx2bYEI2b8UJoK8QJslSRyiJmMcYTvF4WCBm4dx0IQ%2BL6uYyn9t46nXMgzZYFQelKSpRlAacaAbskBC4V%2B7HSQJLwAGJ4MQMwvNgqisAcAaSQiSE2ou0GgpekoIHcBD0GxClhQKh5Lgi0WgWG4FcaCyUztubDocQwDOQi3qES8RF0kwVBeP2PTkdCsKCNcmWVgwzytiRtDoNcILFQxro5SC5W%2BkIXjJAUmDoAASk6Xi0FSwEhmBEanIELxcIqZhDQhoKjQBc0KAtS1BpV1W1fVa1uEIsUEPFNobVtLw7XGX7wa5YKNI4yBduKSjNBAzatgoO5/bhbhHSdirjZNaTTVDi3PMsiXCfxkq1AIZH%2BYF9AvCF%2B3/pKE1TbN82LV2XCNW1gLsacI4zOGv2iDM1zpGWmBdvCIoQBoqwM99eDM%2BK3NuOznPc9gEBcPz%2BGMz9XYs6L4tc88EBmCjdPvcNB0vIjBCU41VWNJddQCGzBAtm2DBYKoPb3ta1xPdtrra3tX1M%2BDAMEEDlsg2D4rXPrlMwyT8Nk8dFNcMjbIcKstCcAArLwfgcFopCoJwbjWNYRrrJsQFKTwpAEJocerAA1iAicJPcAAcCRSInSIJJIACcxwt0p%2BicJIvAsBIGiBKn6eZxwvAKCAgSl2ncekHAsAwIgIDrAQyR3OQlBoPsdBxBEO6cKoDcALSty8wDIMgm2SPcZi8NNhAkHgLZbfwggiGI7BSDIgiKCo6iz1ILoLaAB3MMyROA8HjknFOZcM6cG%2BHcdeVJUBUBeEfBIp9JDn0vtfW%2BLwIAeB3vQYgjIi7LF4DPLQqwIBIG3skXeZAKAQHoYwkAwApBmD4HQXYPlKDRDgdEMITR8SQN4EI5gxB8TfGiNoWoM9i7bzogQb4DBaCiMAVgaIXhgA3FoLQSe3BeBYBYIYYA4hNHeXkXgAAbk6OBmBVC1DuNsYu7YuhwNLNEMMUiPBYDgQQe0A8jGkDscQaI8NaSmKMKWIwZdVhUAMCVNUeBMAgNAqnYub9hCiHEN/bJf81BwOAfoMxKAc6WH0HgaIk9ICrFQI5TIhjj7NmAqYSw1gAi8FQGE%2B0WBakQFWDUM2fgICuEmH4LaIR5hlAqHoAoGQBATPmWkRZDBBizJGFtYZPQ%2BgTE8G0PQOz6izA2cMeI2zZjLMuf0M5iwLlDPzlsCQ0CODJ1ICPbpnB0EnzPhfK%2BUh8EQFwI/Uh%2BkZaUPiasBAmAmBYHiIM0gVdJDHHuB3JEkgNCSDMJIRsGga5tx7hwPupAB7HC4PcRuCQ65tzrlwBIidJBcETh3JInz4Hj1sFPEu8T55L1oSvJBG9mGsJIfvNgnAmgsBsUiY%2BTA3gGF9FwNu9wKXpwfkQPpehskfzydIApSgimAN0FwsBTAIFGNee89lY9EFrzuC8VBSpiDStlfKsUSqVVqoIUQhhJCyHHA1pC2eNC6GoGIXETeLDw1%2BpGFKmVx8PUcLblwQINBFpxEnhAARgCJEiLEaQPNUiZFyIcAWpRcJVHqLgVonReiDEFpMWYix6d8CYTqHYwx6qnHIBcQW9xCdAFeJ8fiPx2x06BLwME4uYSIlKCic2wivLElMGSak9JRIC06tyV/fVshCkAPTia0pcT2lWEqV4gZ9TGkCGaa0oMZ7Omj16c/exdTOjdEyC4G21ygg2zuXMraCyei/uA5kADWyP3WIEHsloBzcjbK6NB3opyZnnKOVc%2BDkyxi3LQ/cl5awNjPJlkS61cCx7OtdXKhVZjNpevuBoAhILNUBohTykN0LYXwsoK8klZKVVYqRCypESJjjYtxUyj55HOAT25VQueC9l6r2QVG0Ve8D4cClWfFgCgbFXxscq%2B4lwZj33wJq5%2B2rZC6t3T/eQhrD06BAMcUgZqLVQNI7AwBtqhUoLQVp7BOm9MvAMyq4zVJCExsYQG44FD2PUPnmGiNTCt6RZISAPTk0uwha7GFv6LrW7cIzXw7NgjhFSILUW6Rsj5HlvDcoqtGjW2YG0bosQDaQlNpieO4xViO32MAY45xux%2B2CA8UO6pI6x0BKCQW2dkS9iLriSGvgSSFApLSRkrdVmd0SD3b/ezxSnMnuMBUmwl74DXp6IY9MwNH2WC6RnF9/SLtQZGd%2B9wWG9DTNKOhoDqyQOfb%2B4UcDeHAOvd2ZhnI2HjkwdQz9/DNz9lQ4w7h%2BHgHHlEa/lazzo9vn%2BZeIF/ThmwtMbMyQVjsX5PLE43CkYiLB18f8Cq44xxE6JyxamjQLOW51yk15mTXLp5QqRSAFFqrjh10ZUpdnCQlItyJccHHXzOVU9eXfPnuOVfC7CekZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/agent.test.hpp)
