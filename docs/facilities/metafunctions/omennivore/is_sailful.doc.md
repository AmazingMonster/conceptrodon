<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSailful`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

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
template<template<template<auto...> class...> class...>
struct SailLike;

template<template<auto...> class...>
struct RailLike_0;

template<template<auto...> class...>
struct RailLike_1;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKQkx0VF60d3uJkSFleM0cyFeaAYY0wqhSxFe0VQnleADcxF5MK9gRYqGIlMCACJHUHE0mAwHbXb7a4PI5uQGvZmval7JgHY5s2kM7kc67HJheIgAOjFNyhBgUCjFIolyClMvFh2wkqY0teAFlaoZkAhPKdSEyWXzOScduyzULRcrVQr1Uq5Sq1dLZY1UMgANbEFEsBSUlWAp4vAgfL4/Wh/AHHbUGBh6g0M91en2oP2ym6Z%2BkgsFNCFQgSw%2BGI5GojHebG4gjPa6JEmHMl1in0h4AegAVJ2u92e63AR2u68ACqYMYKV7dvttnszyeUh6mgXmmn83kWnmC4WoDPO%2B2u20ux1Zx7VkOvb50UKegVWFv3RdrldWrc7u2K19B09vABKEavmAAfQ0ZsgQXddVy5cDnxtJ03wdD8HmDH8/zwa8AK4EDPw5PBkAAh04gICBPgvSN/iTFDrwZX9L1QwDAleajaH/dDMxVEAQHLLFFhA8EcLw6UCIgMAwDDEiowZMICBudjOMwbiGw4ZZaE4ABWXg/A4LRSFQThGUsawwVWdZKzMQ4eFIAhNEU5ZPRAFSzBFRIzEkAAOFyVI0ABOeyNAANhcw59E4SReBYCQNECDStJ0jheAUEBAkszTFNIOBYBgRAQFWAgUmFchKDQXY6DiCIrk4VQXN8gBaXzJFeYBkEhKQRTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdRktIXQuFIAB3YgmBSTgeCU1T1Ks7TOAAeWFXLQ1QKhXgq6ravqxrXmasxXggDwivoRFzDMxZeCSrRlggJBCpSYqyAoCAvp%2BkBgCkMw%2BDobZiHiiBog26IwmaU5lt4OHmGIU4tuibRMAcJHSEKthBC2hhaERyasGiLxgDcMRaHi7heCwFhDGAcQybwYhsccNFRw2uFseFTZzMk2oNtoPBogWtGPCwDbqzwML6dIbniGRJQiR2ZmxaMKzlioAxgAUAA1PBMFmraLg08y%2BuEURxGG62xrUDbpv0ZmUGsax9HF%2BLIGWVAUnqOmqrGdAjiJUx9MsMxouVrqsB9iBljsTmshcBh3E8do9BCMJBgqYYZsKTIBEmPxC/SYuGDmIZ4hm5OHB6cZWkzvI69qFOBF6Fpq/z2vbCb0u9Bmbvc/mAuk6MjYJFWjg1NIKLeBio7KpquqGqayQWuu3BCBIHFTK4Z6LJ15YEEwJgsHiRPSFsyRDhFTzDkSAJJGc3yIpU3zPKCjgQtIMKzIil8lwfynkXIgJUpILgKlH6%2BXnhtGKcUErH2Su9DKH0sq7Tyn9AG91SpsE4M0FgaJEhVSYGqIwF1PIii4CKLS7Vd5x16rIAadtpAOyUE7SauhQbzUWkjGec8F6bQ4DtHKwpXgHVeEQkhZCKHACoTQuh11brfXuvvQ4Zgj6vRShg3BcR8r/TTGo4YMjSH2iMFwTyXBAg0FoBDKGMNJoowRrjFxaMMZYxxorfGjACBExJhtcmlNqa0FprjRmmtNhaXwBzBu3M6b0NUPzbYuNhbKUmmLCWCNpbRJel1BW5llaq0wOrJmRgtagFQXwfWRsTZmwtrja2rChrsNkI7CaWkeGu21hHKwlgvbRATn7AOWQg4hzDn06w0dF6x26jzX2XQO5%2BAgK4QeM0c5lBrnoIu9R1mpArvUHuCw27dE7gPFuZclkN3ObMUe2y64XNyFc4e/R7m92nisNYU9D4/yEQgzg0jiDENIeQixCirFKI0NvDqe9HqHxeifUgZ8L7DGvhkv%2BADqEaEkIkGBiREiHFfpIWqM1hGINsMgnRaD4AYOyntQx%2BjiD4M2EQ06fo0SQjRJC2kYw2qwqYTNZpttWkjXkJwzpOgQCBT4Utemgj1qTRimIvakjDpsrqhyrlPL%2BRjBUcYn6GjDjaJ1qlT6Br7qMotcMTlKQUgAW5Z5ACvKCB4WBbVMG9i4iONhvDNGbi/Xo0xpzXGvjCbE1JjEzAFMqY0zpuZSJFS8mkFiSnBJvNknIAFmkwQItMni0lqcXJssCm42KekUpGsKlhCqW9GpTADbG1NubRgTSWEiokG00aErnbSp6cYD2AysnDO0qMwsnBWwh3dpHCwMztJzPjvAJO7cbkrLWZc7O6djkFwOUULI%2BzdlZG3X3eu9Qu7N2eUPFdZ6m7HqHk8rOjy7lbI%2Bb8hQk8hoKvgUqwFGrXhavRDq7YeqIA706hohFKC3qn3PpfSgM9MUJGoYcQ4KkPJQIiihxI/lv3RU4EgxKSLb6JBanirgUhPI4sSI/LgyQMmHEVXh2KUHrI/1arhxe%2BGWOLGWMrDIzhJBAA)

## Links

- [source code](../../../../conceptrodon/omennivore/is_sailful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_sailful.test.hpp)
