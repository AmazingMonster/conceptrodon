<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Travail`

## Description

`Travail` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Travail ::   template<template<template<auto...> class...> class...> class...
          -> template<template<template<template<template<auto...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<auto...> class...> class...> class...>
struct Travail
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RESULT;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    using UniCalm = RESULT;
};
```

## Examples

- We will create a `Travail` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
template<template<template<auto...> class...> class...>
struct Item_0;

template<template<template<auto...> class...> class...>
struct Item_1;

template<template<template<auto...> class...> class...>
struct Item_2;

template<template<template<auto...> class...> class...>
struct Item_3;

template<template<template<template<auto...> class...> class...> class...>
struct Operation;

using PackedTravail = Travail
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using Result = PackedTravail::Calm<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Travail`.

```C++
static_assert(PackedTravail::size() == 4);
```

## Implementation

```C++
template<template<template<template<auto...> class...> class...> class...Items>
struct Travail
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<auto...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0Bfy%2BTC8RAAdLCbod9kwFApYdD4Yjkaj0QZMbCAJI/BQ3J7jYheByHAAqxCYADcmHQniYAOxWB6HDmHWaOZAIgTjTCqVLELl4ABemAA%2BgRRRKIEsnpzjqzDsRMAR1gxZZhUFRURACa8FAqAhZlQARJnszlg4H/UGvIEg76O8EO352gGuz2nSEwuEBbAInEogNBjGhtGB4NIyPY2NUmkMACOXkZgcVnNJ5Jl5vVDNoyrNXkyRkOBAAnqlMMcAubE4ZU%2Bm3IaWHGM6aLSc2Y9rRzbc6B/aXR7B96x6Ph37UFjoxHZ%2BGQwuY7io4vY6jqY207RiX3DiXwsBDm4xCxa/W881m1uUzuFyAQJXq92mczLaarfcAPQAKn/AGAUB35PH%2BAFUtgQiUkIhyASBDxgUBSH/vBvaPGYuwMPsXhHF8aBYZgqQEESGYPE8Q5epOlFOlOUIzmGK7tuuq57vc2YUq2koaK%2BZEPBR7o0dRbqnnRy7zgx4lriSBBkhxPySlwPFofxI6CQJwnTmJS4SdpUkPOxMqcWYSnkeOw4qSpmk6Ru1ksaRbEyTmhycQEJl8WZQk%2BqpwmWaJtlMYxWk2XpDmyTKADy1Y0g0bk/oBhwAGJ4MQ4yHNgqisO8NZwV%2Bh5lsoTDIAA1pg6BbvSdAXg2FW7mRpyZhynEaKQxz7pxKStfcSpGS1DXOfJrl1bcn68fceXHkIXipEUpUAEqYAoXi0DKJz1pF8TAtkTL1W18nNZ13XyR1fU9QdnIudtw09k842HPNi3LVVBXFaV5UFo%2Bp60CwXzrdFW0dtd%2BnNDykqxvEBAQBcj4KKwUpIl891LQQLWTdNGRzQtSM3CagNxeBQiYPh6BpRlvzZQBqHSZtyCg8i4MQM9JVlTSNXQ%2BKmDyheq2HJIONPBwKy0JwACsvB%2BBwWikKgnBuNY1hcmsGw1jsPCkAQmgCysRUgMLGjQmYZgAJwABwaIbwvG4kASSGYzKSIk%2BicJIvAsBIGjNeLkvSxwvAKCAzXqxLAukHAsAwIgIBrAQqRQuQlBoG8dDxJEsOcKolsALSJJIhzAMgvJSPrvClYQJB4Ogej8IIIhiOwUgyIIigqOoQekLoKQAO40qknA8ILItixrUucOFUIxzKuqHOniRZznecF5I%2BuHBAHiJ/QIoq0svCB1oKwQEgCepEnZAUBAh/HyAwBSGYfB0C8KWUDEQ8xOELQVr3vAv8wxAVuFMTaITQOqsE5sEEOFBgtB36tywDELwwBPq0D9twXgWAWCGGAOIaByVAF4FpAtIegpCZQi2KrcILwhat1oHgGINIf4eCwEPGSeBXbINIHg4gMR0Z5jQUYKhRgNYrCoAYYACgABqeBMAd3WuLVWVdhCiHEPXORTc1BD3bvodBKA5aWH0NQv2kAVioCItkJBGcLirVMJYawZgvbsOIOXfBBjug4OcBAVwUw/ApFCOEIYlQRgpCKFkAQHi9CBIaPMYYCQxh1BcY0CYbRPAdD0HYWJfRWgRL8VE2w8SQljHiRkxYXAVgKEVpsCQ/cOCi1IJ7Xg3sp6Z2zrnfOhxC5mGXrgUuG8MJFO3gIlYCBMBMCwAkeUpBtaBGhIbAIdsNA23tu7YWiRDaOw4M7UgrsAhcGhMkRIxsTZcESMLSQXBhZTIdjU4ePtbD%2BzVgIkO4d96RzHrHU%2B5914pzYJwFoLBaTMgzkwGMZYuCG2hFsyWJciD2IrikORNdFHSGUUoVRrddA3y7kwHuyCKlVIud7Ue0coSHEnt835/zAXHmBaC6EGhl6ryPuvY4GEzBb1uUHPeB9UBr3iHHM%2BnL6UjBJX8xERhgVcGajQZa8Q/YQCfq3L%2Bb8P6kHlT/P%2BACHCKpAYwAg4DIFDxgXAhBSDVaoPQZgyW%2BA1QOFwfg1uhDkDEMVWQuoQ8qE0LfvQrYksmEsNVuwzhShuGmqPHcoRTARHiMkdIxVsKFF1wRbIFRLdJaoo0fwyxVgdGuv0aMoxDRTHmLrOm6xtj4hQscaMlJVrXHuMSfkLxDB0AFP8WkDIQSci1s8S24o2Qm1ZMrQ0NJCS8idv7b0fJPiFjNtmJMDtyTx3lEieU1Y6wylFJWTioedTBVkuFRSkFYL2n4EhYyzZLKd6a1IAMoZIxRkULWRskFszmSnOZMya2Zh7bHOqZuzgvsbnnr3g8pAUdx48recnVOHBvmNLbLSXktJKV/HGMXI9ZdoUN3kbXCQ8bG5IqTToEAQR0WYr7uuwerc8XPInlQQ40Gc6wfg4hu0qUV58uPiegIZ67mPPAyfeObH14gDg9NSUCHDaSiQwQUGxAWDZ1vpKh%2BMrn6vx/oq5Vv9/6AI1Zy0B2qIFQPNZgWB8CxCIMVSa3hnqUHYKtXgpB4LVBEJeI6wQzrKHUNoRWD1jD7E%2Bt4H6rhrwg38LZXwYRYiJFSOrDI3gMasNKITXhtRhHU3GG0TYLN8BDHGP5Jwb8UMi2WBsbUuxDjs3FJiVWvwbiG25OCA23toTW0NDq2EntE7F3RJ6AIQddXR09fnb4wp2T%2Bh9cG5OqJxTSl12xeRr2nBaMyZgwoODhwxPQkk4ezpJ6emst3v0wZwzKAVPvSAI20IAgBGFrrY57tLvMl2d%2Bijv7rkBz6WM/wILX0aGBbMrgARDnMjMEclZAQ5u1JewBipZhweXN6WylY7DMjOEkEAA)

## Links

- [source code](../../../conceptrodon/travail.hpp)
