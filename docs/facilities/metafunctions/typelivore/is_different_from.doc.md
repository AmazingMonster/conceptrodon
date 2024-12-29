<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different-from">To Index</a></p>

## Description

`Typelivore::IsDifferentFrom` accepts a element and returns a function.
When invoked by an argument, the function returns true if the argument differs from the element and returns false if otherwise.

<pre><code>   E
-> Arg
-> Arg `different from` E ?
   true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsDifferentFrom
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = IsDifferentFrom<int>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(!Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsDifferentFrom
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAAzADspAAOqAqETgwe3r7%2BgemZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfgG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgSbgIAE9UoxWJgbgAVFrATAESHYIHjYheBz3BQAETwVCocUYBAAYsRUCwgSYklZLjdWTcQWC3phIdC4Qi2DdsM9KVigWybrj8QQbspaUQALKedBitmMiwS5qOZA3NAMcaYVSpYg3aKoTw3ABuYi8SLVBDx3KSRMh6sZzoSzMBLLZ222KIQeAUN1S/TwYgl8OQYdoeAAXm9sjcAO50WgmpHIBAZRgq1m%2Bm6km4mABsGiFoJFpYLQaw6HxmHQNyYQZLGlRxHRmNLADpc%2BzQU8uTzRd7WZKCbLUAqlTz252RxdxWqNQntbr9YbjabzVbvLamVQxEo3S6i06XQzR/3ORCobD4cw2N3nxdgMRMBXBAoF%2BKvJkjDciq0I2kJEjKcqoEBypQq%2B76fgQCjPr2CTYh6l6LmyHKDrevIPoiSEXB234oX2sxajqAgbkaTZeEQgFKgA%2BhaRZXmqk7TsBPKEcAiHPliIAgLuNonmhlwiZ6QI/H8RwAlJgqqKwTxIp8knSf86FyfKGJMFQXgMA4iYqZcWHgtyd58o%2BmAEURC5/mEwCAdpun6e8oGEiSZIUoINJ0jyYSYiRlwCVBXFEUhoqiV6VyHCimDjEGRkXGReDIAxzZKK0EBac0zkGQIfmCLs/GCdamBLBelzJal6VxAQEBgGA2U6XpeUMAVAXYAJQllS6HArLQnAAKy8H4HBaKQqCcG41jWBKawbLaZgJDwpAEJofUrAA1iAg2SN2GgABxmGYACcJ1cINh0HVwSRJNIA0cJIvAsBIGgaKQo3jZNHC8AoIDvWtY19aQcCwDAiAgGsBCpLR5CUGgjx0HEESIpwqgHcWAC0xaSDcwDINqUjdmYvANoQJB4Ogej8IIIhiOwUgyIIigqOoQOkLoXCkEmxBMKknA8P1Q0jetE2cAA8rRMPSqgVA3OjWM43jBM3ETZg3BAHiI/QxrmMtSy8IDWgrBASAI6kSNkBQEDm5bIDAFIgQ0LQILEH9EDRKL0RhC0MIC7w3vMMQMLi9E2iYA4/ukAjLwEOLDC0H77NYNEXjAG4Yi0H93C8FgLCGMA4jJ3g74GRacWiwaEe0VsK3%2BXUosxtEvPBx4WCi/aeAvTnpDl8QppKESoIFzGRjrSsVAGDxABqeCYEm4sPlHNPCKI4iMyvLNqKLnP6AXKAzZY%2Bh4NEf2QCsqCpA02eY%2BM0FEqYljWGYX198QlMV%2Bf3QRw0LgMO4ngOh6BCGEIYlQRhcyKFkAQUw/CQIyNAhg8xhjxC5nYH%2BvQJhtEAfkNBdQMECD6K0ZB4DUG2CwbAvQsxiGgIWBAlYCh5qbAkELDgw0Pqi2%2BvLDG2Ncb40JntdWEBcDk11ktLgBtVrjxWAgTATAsDxAgFtfwCRuwnWSJIDQARJClg0INYsJ19CcCeqQF6y1uzFi4MWA6J1rrFl2hddRxYOHs2%2Br9f6UigYm3BqbSGUtYbW1tjrFGbBOAtBYBaJImMmA6gMABLgJ1uxcH2qTfARB35Uy5ivOm69pCbyUNvdmuhAg8z5v7Vh7DPq8G%2BpLaGtEbiy24YrXGyA4kOQSUk/aGstYWx1kWJaZhJFG2Br4oJcQ4Y2zpL0kYrSC4JK4O9Z2rt3ae3ZoHX2Ud1nB1DuHSOPcY6UnjonUWKc04Z1oFnKOecR5bHGvgUujhy7Z3GlXZANco71weuNJuLcYRt1uYbd%2B3cVp9wHpgIe%2BcjCj1AF4vgU8FCz3novRgy9ZA5IZnk2QW82bjWKXvMej8rBHybmfJRE0r7ZBvnfUChLn6vziBkz%2BZL0GtT/gAvIcCgj/xIYseBxRsiUL5YgnlEDv6tSIdgjlVD8HiqwSKsh1DJVALQXK2hKCWGrHWMwiRRi2Ei1cZwJpvDYkF1Vok5JGgNYiPSf0/WhtpGkFkfIkYZKHomLMYkrRSRBonVugkbROMuZVLFj9WwHjhnePgL4qG0sJljOICErY4SlYsAUBabUFoOmmXGKk0RlNqZorXhipm8gCk4p0IkbmvN%2BY5wqfqr6Et/EyzlqoFNaaM1Zq5OMbpUzLa2oSEM8eIMza9p1nG0dIx02pFSExBJDFs0EAYq2vJdBlmUFWeNLZScVpbp2T/KOBzBBHKTnczAqd06Z2zita5UKAWkHuRgp5ldVDVxBB8wQDd2Y/N9v8juQKo6guzBCke9kh2TyYDPOeC8l492yUWiQmLmZlp3pWtpB8n7EpPqSi%2BFLKKcG2HfdDRKLAv2qW/D%2B2GxW/wgK4QVXL0Dyr0FAhodHmPZEY3gnohCKE4M5SyhoEqOPkP6HRxVHGGFMIZnWlxDaODyzbemy0naQTduEWkkgtqJH2q8TIuRCjKCsPdSAU63YEgJEGpdSQCyNBmaSNYmT1TODuIBg67akhBpqJukkN6B1JDnS4EdMwziHoJHrY50NEbWEkwcyG7TxsVh90yM4SQQA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_different_from/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/is_different_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_different_from.test.hpp)
