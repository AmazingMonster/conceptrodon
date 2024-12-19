<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsHailful`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

## Description

`Omennivore::IsHailful` accepts a type.
It returns true if the type is a packed `Hail` and returns false if otherwise.

<pre><code>   Type
-> Type == Hail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsHailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsHailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsHailful_v {RESULT};
```

## Examples

```C++
template<template<template<template<auto...> class...> class...> class...>
struct HailLike;

template<template<template<auto...> class...> class...>
struct SailLike_0;

template<template<template<auto...> class...> class...>
struct SailLike_1;

static_assert(IsHailful<HailLike<SailLike_0, SailLike_1>>::value);
static_assert(! IsHailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsHailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct IsHailful<Tranquil<Melancholy...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKABJMdFRetDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXiCLFQxEoQQARI5gklkoFA7a7fbXB5HNxA14s140vZMA7Hdl0xk8znXbk7DlctxMLxEAB00pu0IMCgU0slsuQ8sVMsO2DlTAVSpVateABViIYAI5eOikZms/mi22Ck7C3nHcVSjVa1U69XKzXa3Xuv3egCytUMyAQnlOVM1QKeLwIH2%2Bv1o/0Bx2NZotabcIYMDHDkb1MZjDNB4KakOhAjhCKRKLRmO8OLxBGe10SpMO5I7lIZDwA9AAqYcj0dj/tAocjo2YMYKV6jicDscrxdUh72vlOgVb2k7oV70Wu1BFj1q0%2BBi%2Be/0%2B24PONvH50UIAa0FVj7903B5FDu/YolE8A2vb19S9U9Y1beNXgAMVoVAAHdX0wAB9DRe2BDdtztbC/1wxljyvc9gOI29IOeN44MQ5CUK4DDIM5PBkBQr04gICBPifFMAUZLjkMZKikLwN80NIWD4KEkS6OLbAQBARtsUWDCISYliFTYiAwDARMuNTRkwgIG45IUzAlK7DhlloTgAFZeD8DgtFIVBOCZSxrHBVZ1mbMxDh4UgCE0CzlhfEBrLMSVEjMSQAA5ousjQAE4wo0AA2aLDn0ThJF4FgJA0QJ7Mc5yOF4BQQECAKHIs0g4FgGBEBAVYCBSCVyEoNBdjoOIIiuThVGilKAFoUskV5gGQKEpElMxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1Cq0hdC4UgEJNFJOB4SybLswKnM4AB5CUWoTVAqFefqhpGsaJteKazFeCAPE6%2BgkXMXzFl4SqtGWCAkA6lIurICgIHhxGQGAKQzD4OhtmIMqIGiW7ojCZpTgu3hieYYhTnu6JtEwBxydIDq2EEe6GFoMmDqwaIvGAMVaFoMruF4LAWEMYBxG5vBiAZxx0VnW74QZiVNj8gzalu2g8GiE1qY8LBbtbPBcpF0gFeIFElGJHYJe1oxAuWKgDGABQADU8EwBD7ouey/NW4RRHELaA92tRbqO/QJZQaxrH0HWysgZZUBSephcGsZ0COYlTDcywzCKi3FqwROIGWOw5ayFwGHcTx2j0EIwkGCphmOwpMgESY/Db9IO4YOYhniY6K4cHpxlaOu8mH2pK4EXoWgHluh9sceu70GYF6b%2BZW/LzyNgkK6OFs0hCt4Yr3oG4bRvGybJGmgHcEIEhcR8rgIf8x3lgQTAmCweIy9ICFSQhxJQJUOIkAIkgoopXytZFKCVMocGyqQXKvlJQpS4GlBK0VMHWUkFwayYCUon1usVUq5UP5VRhvVWGjUnqtWRqjEGPU2CcGaCwdEiRBpMG1EYX6CVJRcElI5OaT9i4rVkOtYO0hQ5KHDgdXQWNTpMHOiLQ%2Bx9T53Q4I9ZqEpXivVeOwzh3DeHAH4YI4RAMgYIxBi/Q4Zh35Q2qrQphcQ2oo1QMDYYRiuGeiMFwBKXBAg0FoLjfGhMDqU1JkzKJ1Nab00ZmbFmjACDs05rdHmfMBZCyZmLO2mxHL4FlqPBWwsRGqBVtsJmGsrIHW1rrUmBsCmQ0WqbPyFsraYBtuLIw9tQBUL4C7d2ntva%2ByZgHKRm0ZGyDDvtRyiio4O1zlYSw8doil2TqnLI6dM7Z2WdYAuZ8i5LUVknLos8/AQFcGvY6jcyiDz0O3eoNzUi93qIvBY09uhz1XpPbu5zR4/NmFvB5w9fm5H%2BRvfoIKl4HxWGsfeb9EEaNIZwQxxAOFcJ4X4sxASLEaAfvNZ%2BYM36Q0/qQb%2Bv9hgANqcg1BAiNCSESIQxIiRDhQMkCNY6miyG2AoU46h8BaFNWeu41xxAWGbHYV9FgCh0RQnRHiukYxZpEvEcdCZQcpnbXkHIuZOgQAZWUaoy6yKboHWKjo56%2Bi3rStGrK%2BVGIlUCjGFYzxNi4h2MOI4x2NU4busRmKgNIN5LIBSCkFCiqEooWVQQFiGKRrY1CXEcJRMSbUxiemmmdM5ZM2SWzDmXNCmYF5vzMQOSzZ5N6c00gRTK6lKVhU5AqtqmCE1nUnWetThNKNq0pmHT0hdNtr0sI/ToaDKYK7D2XsfaMHGZIrVEhpk7T1RHQ1izjCx1WfUjZTktnVk4P2TOMc84WEOU5Y5Jd4DlxnoCy51y/kNxrh81uryihZBeU8rIL7l4j3qPPCeEL163v/ePH969wX1zBcC%2B5sKkUKD3ptdR5qiporta8B1CrnXbFdRAR%2BC07GksodDL%2BP8/6UEPnShIAjDiHGsvFfB%2BVaOJDSiQi1nByEVXJUAxI01mVcCkAlRliQwFcGSLUw4KGz4ceI0FRBM02OoZKrJxYywLYZGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_hailful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_hailful.test.hpp)
