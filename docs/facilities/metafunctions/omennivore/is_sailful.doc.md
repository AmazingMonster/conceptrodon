<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-sailful">To Index</a></p>

## Description

`Omennivore::IsSailful` accepts a type.
It returns true if the type is a packed `Sail` and returns false if otherwise.

<pre><code>   Type
-> Type == Sail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsSailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsSailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<auto...> class...> class...>
struct SailLike;

/**** Items ****/
template<template<auto...> class...>
struct RailLike_0;

template<template<auto...> class...>
struct RailLike_1;

/**** Tests ****/
static_assert(IsSailful<SailLike<RailLike_0, RailLike_1>>::value);
static_assert(! IsSailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsSailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct IsSailful<Melancholy<Stockrooms...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFEImHQqF5aACTAB2CxXaaOZBXNAMUaYVTJYhXaKoTxXABuYi8mCuRIsVDESiJABFwSShSKCecgSCXgjzuC3ACrkqrlKHjL5arQQiIZr1RCmF4iAA6E2IykGBQKE1Gs3IC1W00JbDmpiWq4AWRqhmQCE8UNIiuVurBOuBapDbgNxsdzrtrodNqdLst1oaqGQAGtiMyWAoCU7kQRUeibpjsbRcfiIZ6DAwfX75WnM9nULnrYiO3LiaTGuTKQIaXSGUyWezvFyeUXOWKEqLCcLZxKLj9vn8vtsrthVKwHlz3gD1yvjkv11cAGqYS01N7HyVhrUa%2B96yFPiNR1DtpNxlMx5MJztnCiaIEFcWJ0KEGbalYcqfPstxSgoN67H8wbai%2B0pvoaH6/t%2B/4FucQHogASuWEGYAA%2Bho4owYCr5oah8rvp%2Bsb2sxhbFiBJHgXgkHkVw1H/LB1wACqXgQiH7gRvZ4Mg5HxnEBAQKWYEVnijakTxaFcbQZGUaQVzabp/EFk6IAgGOnILAJZIyXJV7NBAYBgBiKmVvKYQEIiZkWZgVmzhwSy0JwACsvB%2BBwWikKgnAKpY1ikisawTmYCQ8KQBCaAFSwZiAwWSEaGgABxmGYACcpVcMFRWFVwhKEtIQUcJIvAsBIGiBOFkXRRwvAKCAgQZRFAWkHAsAwIgIArAQySGuQlBoPcdBxBE8KcKohUAGwALQbZIVzAMgFJSEaZi8Jg%2BBEMQeDoHo/CCCIYjsFIMiCIoKjqENpC6FwpAAO7EEwyScDwgUhWFmVRZwADyhozSBqBUFc63bbt%2B2HVcx1mFcEAeIt9AMuYqULLwg1aEsEBIAtyRLWQFAQFTNMgMAUhmHwdBAsQfUQNEEPRGETRQsDvB88wxBQlD0TaJgDhC6QC1PAQUMMLQgufVg0ReMAka0LQfXcLwWAsIYwDiGreDENLjispeEO0tLhobGlHk1BDtB4NEANix4WAQ0WeCtfrpDW8QTJKIKwLG27RiZUsVAGMAChnngmC/VDsLhWld3CKI4jPVnb1qBD336MbKDWNY%2Bju31kBLKgyR1HrW2jOg4KCqYcWWGYXXB1dWDVxASx2JbmQuAw7ieG0eghGEAzlEMP0FBkAgTH4C9pEvDCzIM8Q/UPDjdGMLQT7ku81MPAg9M0W9zzvtiHyvejTFfM9zPPg%2BJesEigxwoWkJ1vDdSRptHae0DpHXyljCAuBCAkG5ClLgxN0oxyWAgTATAsDxAHqQHKkgEhGlKgkeqGhJBmEkBtdqwUNqlX0JwZqpBWqpSNBtLgG1CqlRqhtPKlUCEbT/hDbqvV%2BpIKGuTcaFNJqw1mnTBm%2BMVpsE4E0FgrJCRbSYC6IwGNSpGi4AVM6F0SDXVurIB6udpD5yUIXT6uhWb/UBkLb%2Bv9/6Qw4DDaahorgIyASjPacYNFcC0TojQ2NcbU3xnAhIZhEGk2GuImRcQ5r01bKEoYvjmYVUCDQWgHMuY80%2BiLAWst8liwllLGWgd5aMEVsrVWkV1aa21rrWWhtI4bFqebYe1s9aRTtsgB2stnaNUim7D2AtvatJJldAOaVg6h0wOHI2Rgo6gBEXweOidk6p3TrLLOJinpmNkAXD6kVrEl2ju3KwlhK7RH7rXeumRG7N1buc6wXcAE92ujbGunRz5%2BAgK4B%2BP1p6lG3noRedQAWkDBZka%2B8xT5dAvvfY%2Bq9vn7wRTMF%2BILd6IpyMip%2BfQMU3y/ssVYn8EE0J/uDT6gDkYgPUcATR2iCrY2gZdcJCCSbINIKg9BQwsGNToQwrRxDCTBVKnVJIpDdo/ScQI2wQjomiPgOIqacMElxOIHIjYijUa5lZBSVk/ijRalGHomBvcjH3Rznsl68gLFHJ0IkP6AMgb6wcZSrq0NJHw0RqoHVCg9VskNcakCOMkk03CQkKJMcRqUzDfjNVcahh6uSMkciBrSrkWDeRX1Zj2ZxBybzfmYtClFvFpLS2ssKmCCVirCGdStZiEaYHZpizxmkHwBbfenTbaqHtkCfpggXafWGZ7KEYzfaTNljMtIcyI6LLCMssmqymAJyTinNOjBtnGKtRIfZr07VF0dbWYw5dLnDJuVFO5A5OCbGbmXDuFhXlRXeX3eAg8z6ot%2Bf8pFU8x4wvnpC9e4Kf1r0KNCglsKUV1EvkfHFj8P3QcPv%2B2%2BeKIV4uQ0ShQH8npur4VSzgSM/UBvTUamUoxmX6IJvAqNIiUFoIwZQb%2BAqQBlSNAkBIwUqqSC4O1djhJWF4Y9T1OVA1OU4OCvg2qhJ2qFUkBVLgxUzC8Magkd1ADOActo%2BS06gn1PCYVUsYO6RnCSCAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_sailful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_sailful.test.hpp)
