<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-harvest">To Index</a></p>

## Description

`Mouldivore::CognateHarvest` accepts an operation and returns a function.
When invoked, the function collects the type result from its arguments and instantiates the operation with the collection.

<pre><code>   Oper
-> Es...
-> Oper&lt;Es::type...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest ::   template<typename...> class...
                 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the type results from `AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>`.

```C++
template<auto I>
struct AddOne
{
    using type = std::integral_constant<int, I + 1>;
};

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

using SupposedResult = Operation
<
    std::integral_constant<int, 0 + 1>,
    std::integral_constant<int, 1 + 1>, 
    std::integral_constant<int, 2 + 1>, 
    std::integral_constant<int, 2 + 1>
>;

using Result = Metafunction<
    AddOne<0>, AddOne<1>, AddOne<2>, AddOne<2>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<typename...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<typename Crops::type...>; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BeqnpjgKh4VEssfFctpj2hQxCBEzEBNk%2BfoF2mA6Z9Y0ExZExcYm2DU0tuZUKo31hA2VDXACUtqhexMjsHASYLMkG2yb%2Bbtu7%2B5iHxwCeyYysmAB0j4fYANTIBgoKLwDyN8RMtWeJg0AEEpsQvA4Xh5gMxtgAJRoAN0wU2BIJMAHYLC90S98S8TnsAecjgRrrc2I97m5iKhkgogaCCS8vOkjC8ALKedC4/wAER%2BfwBmQu5JuzDY0LpDJAIHFDye/mwhxx6Kx/NV6tBAHoAFQGw1G4069H6w0vAAqqIIXyNpt1xqd9u1GLM/jC7y8WD5bi8jlohEuTLdHoYXp9FzQ4cwyVtIfRRLOFyY/tQLwAkiHwZCCC8Qeh0N9wursXiCWywsBCRS%2BYKpug5WFtsB/rQAPrRqaGAgXZukTO4ywvLhA/xWUEarWT0FJkliimSxX3bMECFQ35xEUCacY2c7YkHMmLu7UkHEYCM5XoysczmYBpULzh2p16GoWEkxHEFFoo6b/5AWvUE5W5Wh0Auc9L2pMcJz3EFb2rIQvGSfJMHQAAlVEvFoPNDkFADtwYdUjnLfEGybQRMFbMROwEbtBD7QQBw0IccVHZVSDIl4KJAZtqLbOiGAY3sjn7Ec2JHZ4B243j%2BJojsuwaRixOYl4zEkjjsBk5kCTkqiFKEkSmIIAcNOsKTgIxa9x1dRCXiwhQcLwgUuQfJgnxfUVSN0/ECyLEsjg0aT80LYtSTcLSB388KLjMEKYsCtx4qs2DXW7RxkHbJhPjiAgIF4hQ7myq83Ec5yB2Q1C0nQ8rcOeRZVQ4ZZaE4ABWXg/A4LRSFQTg3GsCyFFWdZMCHfweFIAhNGa5YAGsQDahJ7gADgSKQ2sxBJJAATn8Lb3X0ThJF4FgJA0DRSC6nq%2Bo4XgFBAS7pu65rSDgWAYEQEBVgIZJ/XISg0F2Og4giO5OFUNaAFptpeYBkGQEdJHuMxeHQwgSDwRtKn4QQRDEdgpBkQRFBUdQXtIXRKgAd3%2BZJOB4Fr2s6mbes4b5/T%2BvNUCoF5IYSGHJDhhGkZRl4IA8YH6GIcall4Z6tGWCAkCB5IQbICgIFV9WQGAKQzD4OhtmIB6IGiVnojCRpLgZ3hLeYYhLm%2BaJtE6Z7JqBthBGLWgbYprBoi8YA3DEWgHu4XgsBYQxgHEf28GIN28F/VnMFUTp/U2Sb%2BNainA2if5HY8LBWbXPAzoj0gUWIaIav5HYY8DIwZuWKgDEvAA1PBMGpzcusm3HhFEcQicH0m1FZqn9BjlBBssfQ8GiB7IGWelanDqGG3w0xLGsMwbur4gsdReBlg6LpnAgVxxj8SoQlmUpyjyNIMgEG/n4KTJ%2BkfhYqhqbppjv0mNUJOAgehNG/oMCoIxehAJgRAh%2BUCJBnxGhsZBR0OAdSuqzW6fNoaw3hojKQYsIC4AxjLcwE1FjyxbssBAmAmBYHiBAeaIBJD%2BHuHtTEkgNCSDMJIBIF0lo7QwSdUgZ0Jr3HWgkFaO0VpcASG1SQXA2p7SSNdXgt17qPSmi3N6n1lbfU5v9TW2tpZgzYJwRoLAkSYihkwN4BgORcB2vcLg9weroyIEfbGxMh4EwkNIMeSgJ4U10AbWmTB6YRyZpglmFNboc1%2Bv6F4PMXjWNsfYxxMcRyuPcaxCWqApZxHGmYahuiXpKxVkUtW0sAZaxqTrDJdj3gxxcVwS6NBcJxFNubCm9tra21IAMx2ztXYOCGZ7RgBAfZ%2Bx6gHIOIdaBhyGVHRumx5kJyTinCmacM7bCGTnVm%2BdC6XGLhs%2BWR8K6TWrrXJQ9do5GCbqASpfB24KC7j3PuQzB74xHkE2Q49yY9XCdPZuO8rDz3zsvFhvU4yZA3lvAUEK94HziD4k%2BK8/6gL8FfBg7hPCtD0PfEoSDKj5FflkQlEwUgv1qJA%2BY0Dz61HAc0alt9sUXzqNMBlT9JiAPZXobsCDSWMvQcNNYaClgYKwRotmHB0nEBsXYhxrTnF5I8eLMh3jZblIVrNUg9DGFDFhbnMREjXG8MxKozEmJ/B8IEco7BCTODaKeno96X0fpc3qWY0G4MODWNhiwBQSJEZIhcfcM4Uw0b4G8VjPQvzh6EwBSTEJwKdABFIJE6JjMZXxJuuzYx3NeZBqFiGsNLwI2uOjXmQpxSKHun8Hqj11SG2%2BsadLEAYbULtmre2Wt2UlXbUNt0k2lA%2Bk9RGX7Sa06xlu0mUUr2MyGC%2B1Zgs4Oodw6TTWU8i5pB8CJy6Dszx6dkCZ0OVRXOPUTnW3OaXK5Qzbl1wbk8qsei25ME7t3XuEofmyD%2BSmvxQLJ5ZqccYOeNhoWnzhevTgOoKIossPvTRh9j4wrPiArlLh8VwJJXMPltLP5v0FeSulX9EFiuAf/MBAqcgcuZQA3ovLf7CrZfRoVPLKN8pQZKwmsTZU4M4IqlgwbQ3hsjbWrVcaSC6poZUuhDCmGUFieakAZhXH%2BH8G1NqvCOkaC01tFazrC13VsDo/VixWHsLcf4FaSj3S6YSO6LaGD/AFs0a6ipitYmoxM55szlnljV3SM4SQQA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_harvest.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_harvest.test.hpp)
