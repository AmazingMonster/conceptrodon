<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsDawnful`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

## Description

`Omennivore::IsDawnful` accepts a type.
It returns true if the type is a packed `Dawn` and returns false if otherwise.

<pre><code>   Type
-> Type == Dawn&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsDawnful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsDawnful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsDawnful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct DawnLike;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_1;

static_assert(IsDawnful<DawnLike<WillLike_0, WillLike_1>>::value);
static_assert(! IsDawnful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsDawnful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsDawnful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKACJMAO4MVC8tDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXmCLFQxEowV8jhDSeSQSDtrt9tcHkc3CDXqzXrS9kwDscOfSmbyudceTtOdyTiK%2BcK6YL%2BRKZccmF4iAA6VU3WEGBQKVXK9XITXatWHbAaphanV6g0W42m81Gk36s2G3U2x1a15CLwMWh4YAIAikFlsgVikNC8XS0NyqOR8NhpmKlX223Oy1O60Oq3Jt2p11Zl2Z9Oqz3whBhTAKanGkFPF4ED7fP4AoFMks%2Bv0EVtehRl8K527VxngyFNaGwgQIpEotEY7HePEEgjPa6JMmHCmrqmMh4AegAVAfD0fjzuQfvD68ACoVggKV5H0%2B74/Ph/Uh7xqWiuPR7%2Bx2V/z9JQjL8EyVVAMxTCCcyg/M0ztAtIOzWDB0eJc61eH5/lCABrIUrG3e4P2AoCiNIn9/xAhUwJgosEOgpDaLg/tEILGs0LeAB1OhaBwzAAH0NC3UF33IwD5WI8SyIAiSxUTcCGPgpiaMUvNGNUlTbgeWtOO43i%2BK4IS2K5PBkD4p04gICBPkw5tgWOGzeKZLjaB4vBcIE0hXmc1z3IM6tjRAEA51xRYhKhEyzK1CyIDAMAGxswE7LcMJOwCoKcUwUL1w4ZZaE4ABWXg/A4LRSFQThmUsaxIVWdYFzMQ4eFIAhNBy5ZsJAfKzGVRIzEkAAOfr8o0ABOLqNAANn6w59E4SReBYCQNECYrSvKjheAUEBAhakqctIOBYBgRAQFWAgUiVchKDQXY6DiCIrk4VR%2BomgBaCbJFeYBkBhKRlTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdQ9tIXQuFIX5iCYFJOB4XKCqK1qys4AB5JULvrVAqFeZ63o%2Br6fteP6zFeCAPFu%2BgUXMRrFl4XatGWCAkBulI7rICgIBFsWQGAKQzD4OhtmILaIGiInojCZpTlx3gNeYYhThJ6JtEwBwddIG62EEEnvW1lGsGiLxgDcMRaC27heCwFhDGAcR7bwYhTccTEKyJxFTaVTYmpS2oiZ9aIsYNjwsCJpc8EWj3SBD4g0SUL4dh9n0jFa5YqAMYAFAANTwTBfhJi5iqayHhFEcQ4ebxG1CJtH9B9lBrGsfQ8GiLbIGWVAUnqd3XrGdAji%2BUwqssMw1uz0GsFHiBljsIOshcBh3E8do9BCct5mGdHCkyARJj8S/0mvhg5iGeJ0Z3hwenGVoj7yN/al3gQvQWjPwqBfWwX9b56BmMAs%2BL8JDb1qhseBs0OCFVIKtXg60aYvXep9b6v1JD/VZrgQgJB8QNS4LzZqJdlgIEwEwLA8Qt6kA6pIQ4yoRqHESAESQfUJrLXyhNEaKD5qkEWo1ZUE0uBTRGv1aR%2BVJBcHypwia6CibrU2ttahe1BbHSFqdcml0JZS05g9NgnBmgsExIkV6TBTRGCZiNZUXBlSlSBqQ9eENZDQzbtIDuSgu4o10PLTG2Mdb41QYTFG60ybnSVK8KmrxLHWNsfY4AjjnGuNZuzUWnNyGHDMFQ/m%2B19EmLiFdSWqAObDGSTYx0RguAjS4IEGgtAlYqzVijPWWtzbdINkbE2ZtM6W0YAQG2tA7alQdk7F2Ll3ZNS9oXTYUyA67xDu7NxqgI7bHNjHPKKN46J1OMnZZfNQYZyatnXOmB87eyMEXUAOi%2BDlyrjXOuDdzbNx8bDPxshO7I1KsE3uxdF5WEsEPEe8Bx6TyyNPWe89QXWBXpgteYNQ5jy6AAvwEBXCQPRqfMocD75FCyHi1ID96ggIWH/bogCIE/zvpij%2BdLZiwNAa/cBfQyXQP6Gy6lCC1hIMoSgtBGDiYcCScQKxNi7H1PSY0zJGhiHAzIdzShfMaGkDoQw4YzD9miPEU4jQkhEjKMSIkQ4vDJAfXRmKjRtgtHFN0fAfRZ0KYVLKcQMxmxLH0xYAoTEMJMQKvpGMQGKrPHoy%2Ba3H58N5ABIBToEAM1Qk4w9hE0V6jSaGMptTX1n1/WBqxCGwUYxslVNyXEfJhwiklwOsLCtYsPWNs5kFZAKQUh8WDSNPioaCBmSlR9BWbS4gdPVprA2vSJ2G2NkHc2Izra2yJtM52rt5mewLvc05pB8CBw/ussOWzkCR12YIWOBzh5HJOanc55srnpBuZu32YRHkC2eUwCu1da710YJ87xMaJC/IRgm7uybgXGAHuC%2BOm9oVT04DuWe/cl4WGRWVVFG8oVMvqPvQ%2BuRGUEsGOyvQV96hkpI1kKlYD371CAd/PDUD/7MoaF/SjHKeXcpY3yi%2BAq6rIP2Zm6JnBJUsD9QGoNJbthlogCQkG%2BT1XaIFrQ%2BhjDKARINQkJxhxDj5WGoo5aWnEhTTUYJjaDqdqatYYkf6pquBSBGsaxInCuDJH2YcKJa1OAap0REgGxmPOmadcsbOGRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_dawnful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_dawnful.test.hpp)
