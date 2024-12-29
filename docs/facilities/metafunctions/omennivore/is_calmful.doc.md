<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCalmful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-calmful">To Index</a></p>

## Description

`Omennivore::IsCalmful` accepts a type.
It returns true if the type is a packed `Calm` and returns false if otherwise.

<pre><code>   Type
-> Type == Calm&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCalmful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCalmful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCalmful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike;

/**** Items ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike_0;

template<template<template<template<auto...> class...> class...> class...>
struct HailLike_1;

/**** Tests ****/
static_assert(IsCalmful<CalmLike<HailLike_0, HailLike_1>>::value);
static_assert(! IsCalmful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCalmful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct IsCalmful<Perseverance<Tranquil...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJhQdg/sNiF4HNcFG4xCwqF5aH8TAB2CwXSaOZAXNAMYaYVRJYgXCKoTwXABuYi8mAuBIsVDESgJABFQUSBUK8acAUCnnDTqC3H8LgqLhK7lLZcrgXCwerVVrASqQbrJQaMV4iAA6C3w8kGBQKC1mq3IG12y2xbDWpi2%2B2O53et0e20XZTRJTM6KGVakeWK7XG2Oa8F6jVqpM6k3m13up2el0O/3Zr2ZgO5n05%2B0AFWIhgAjl46Hi3YiCMjUVd0ZjsbiwcHiKHwwxVrLKzW67Q/QjGzLCcT6qTyQIqTS6QymazvByuc32SLYsL8YLd2Kzl9Pj8PpsLthVKw7hzXn9zyfDkfzxcAGqYW1VF7P8WpuP/gm8YpkaQGAbKTCmqg47FjBBYlvmvpFvB45Ni2BAXBitAsEEADWmpWDK7y7NcEoKD%2B2w/MBhr6mBoEgbREFQXBSF5lmrGloWbFoSiGEABJMHQeGYAA%2BhoopEf84E0cmMlptR6bQchHGIWWylqdxpxIrxFwCUJeD4SJXASb8xGXOWn4EOR95abOeDICJObRAQEBtlhWI4rK7nCbKem0MJYmkLpgn%2BQZonGY2bogCAa7snMJkkvZjlfo0EBgGAaLuZ2srBAQ8LRbFmDxYepwcAstCcPEvB%2BBwWikKgnBypY1jEksKwbmYsQ8KQBCaGVCy4SA8SSGaGgABxmGYACcU1cPE41jVw%2BL4tIFUcJIvAsBIGgaKQNV1Q1HC8AoIC7b1tVlaQcCwDAiAgEsBBJKa5CUGgtx0NEoSwpwqhjQAbAAtH9kgXMAyBklIZpmLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOoF2kLobQAO5VkknA8OVlXVX19WcAA8qaT0YagVAXL9gPA6D4MXJDZgXBAHjvfQdLmF1cy8OdWgLBASBvUkH1kBQEBywrIDAFIZh8HQAK9pQEQ0xEwQNBC5O8IbzDEBCdMRNomAOKbpBvQ8BB0wwtAm/jWARF4wBYbQJ3cLwWAsIYwDiJ7eDEHbjhhgHdXUnbpprN1uVVDTtB4BEVaWx4WA082eBbYHpBhsQDJKPygKhxnRh9QsVAGMAChvngmBE3T0I1d1KPCKI4iYz3ONqDThP6KHKDWNY%2BiZydkALKgSQ1AHAPDOgoL8qYzWWGYB2lwjWCzxACx2NHGQuAw7ieC0/gX9M/QxG0eTpAIYytMkqTPwwd%2BlAMExVKfAguijCvuMdoADagjB6MEPoP8H62Ega/PQkxGjf1mFwY%2BbVVgSEphwKqe0aaHTZv9IGIMwYQxGnzCAuBCAkE5J1dBEs64LAQJgJgWAYhH1IINSQsQzRTViCtDQkgzCSD%2BjteIf0pr6E4BtUgW0upmj%2BlwP6Y0pqLT%2BsNOa/C/r4PxodY6p0ep1yurdGW91GbPSVirYWX02CcAaCwZk%2BIAZMA9EYHmU0zRcFGjDOGJBEbI1kGjfu0hB5KGHvjXQmsSZMDJoHHBeD9q8EOgzR6poLgsyIRzEG2Z3FcE8d4jQ/NBby2FnQ2IZhxZGIutLWWqAhbRBesreppSBi5PVrNXaNBaA6xOhAfW%2BNzbGwdkMy21tbb22Lk7RgLs3Yezql7H2fsA7dWDtXNYCzI6n1jjTBOyAk4O1TmtOqGcs7G1zhsiWCMi7dVLuXTAlcQ5GBrqAGpfBG7N1bu3TuDse7BIxqE2QQ88Z1SiWPWum8rCWGnhEQ%2B89F4ZGXqvdekLrA72SXvRGn54DH3/g4M%2BEBXCILaIEaBMxf7v3yBkYllLP6oIpSffFgCEEgLfoymoQCoHFHvkgll2Q2WQPpQ/DBywsHoOkbg6mejOBZJIW44AHivGjX5tQ%2BG5SGHVKlsw1h7DKA4NkfIzxQj8TxCmstWIwjRGSDaEk2mR1bCGMlpda6d0HpMyadYz630OAOM5iwBQzIyTMnyWaDUwxfE0P3oE1GfcAVY3kOEkFOg4ikBiXEimErEkEPphY5mrNVB%2BoDUGkNYaMICxaQrcpsQqlOtqSgCtwsPUNoGIGpISQRLBqmiJUtIkC2hO1iGPWBsjaWxGSOq2Nto4O2mYIV27saaLN9mIf2Ds1nPMuaQfAUd8U7Pxnsg5xcjnp0ztnCEFz87XIdnc1IDyq7POCK8qW7ymBNxbm3DujBflBNjRIQF2NE0jxTQYCFk9oWnLhfVBFC5ODrFXhPLeFh0X1UxQfHFYCmV%2BEJRfGlpLuWwNyB/GoNKn41CFUgvFHK%2BXXz/h0ZlUwyU8omFR0ByCuUwLQSK9q2DM1SoOjKvtFx/WBpZCWqUwwVV%2BJFvQmtTDSAsLYQMTha0DUgGmmaWICR5rWp2hp/EKjdF8ftSdM6snuHxD4UtfEO0xqSFmlwCaZgdFrViLx5JnBGE1JwdDAzbn7W1oWKXNIzhJBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_calmful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_calmful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_calmful.test.hpp)
