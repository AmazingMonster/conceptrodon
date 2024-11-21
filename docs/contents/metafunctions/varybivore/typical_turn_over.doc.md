<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalTurnOver`

## Description

`Varybivore::TypicalTurnOver` accepts a list of variables and returns a `Shuttle` packed with the previously provided variables but in reversed order.

<pre><code>   Variable<sub>0</sub>, Variable<sub>1</sub>, ..., Variable<sub>n</sub>
-> Variable<sub>n</sub>, Variable<sub>n-1</sub>, ..., Variable<sub>0</sub></code></pre>

## Type Signature

```Haskell
TypicalTurnOver ::   auto...
                  -> typename
```

## Structure

```C++
template<auto...>
struct TypicalTurnOver
{
    using type = RESULT;
};
```

## Examples

We will turn over `0, 1, 2, 2`.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<2, 2, 1, 0>;

using Result = TypicalTurnOver<0, 1, 2, 2>::type;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will implement `TypicalTurnOver` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Turn over several variables in the front of the list;
  2. Invoke `TypicalTurnOver` by the rest to turn them over;
  3. Switch the positions of these two flipped parts and concatenate them together.

Here's a simplified version of the implementation:

```C++
// We will use this function to concatenate two flipped parts.
template<typename>
struct ExtendBack {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Endings>
    using Page = Sequence<Variables..., Endings...>;
};

template<auto...>
struct Shuttle;

template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAcEADqgKhE4MHt6%2BSaSp6Y4C4ZExLPGJQbaY9kUMQgRMxATZPn5VdpgOmQ1NBCXRcQl5Co3NrbkdY/0Rg%2BXDQQCUtqhexMjsHOaBEcjeWADUJoFuXo60hACex9gmGgCCd/cA9M8HAOqYBwDudLQHXiUBwICDwCgOVC8DG6AmBqAOaGhTAIjGRXwI33hVAuyWSmHQB2SfQUADoniiWMkDCjjm4CJc8cw2DcnqNiF4HAdsKoUQx0BYmMgANZHADsVlFABFjlYHuTMJTqZhaRSqWjaUwzqgSTqbgiDApwUJMABHLyMDakA6aog6kkANSaeCYsXoChZDzZHIIXJ5rgFwtpxrNFuVJ0dxGdrswpN1gVu8aeJnFTwOaeBCrVNJONu1OuwfIiwHdiYe6YB6SMB2UTGAX2OkoOwfN0LDbgjUbddqtBfwRljZMTgVljylMqTD1VSo1WrtHvuXs5QgQZwI9HHcsnmenOdncdunoI7M5ABUGXhRLQT2sGAB5ABuCTFEulw4n9yn6t3RAOADE8MQozzouPpnskF5iNexB3o%2BxC0v%2BgEEPOyYjuWgJFsCDL1oEjbLqu64nAhQFDiOyavqRW6Kl%2Bbi5n%2BAGjFatHGoi6DAUe3oHGBEFXjeD4JPB9EEFazECKxpajqh6boVW9J4kcOFNiuBBrm2Il8laRFISRSZjm%2Bm4ftu1G0ZpjFak2XSiaZto6reIIJCWB4Luxp7npeUEwfxhGCcJFnqQctkIPZc7iShqZSZWwCYXiYVpg2vq8vygpCiqWFMl8XFubxsG0gFQX7iAICyWGjnlgVn4otWtaqb56AaYJLJ6aO5Hvs8ABU7UdZ1zxPG17UntgQgnh13UPL1nVde%2B2y7Ps2GnOcVzIZRWZtrmwWOSBin4WGFH3NJkVCF4uJpPiABKMZeLQPpxXhykEW4ZhWg9BxcFaGgNTte0HGdCgXVdCkZZBWWeW4GhWi9BxPWYNxlVhG6PIeyIXgA%2BkwhoJAQECjOgBUKKwmAoyWbgHUdSjoN9v1WuTl03IsMocMstCcP4vB%2BBwWikKgnBuNY1gHAoqzrPWZiBDwpAEJo9PLEKARmCSopmJIAAciv%2BBoACc/hmBoABsivBIzHCSLwLASBooOs%2BznMcLwCggKD4ts/TpBwLAMCICAqwEMkZzkJQaCUnQCRRHjnCqIr2sALTa5IBzAMgyDPZIJJmLw%2BKECQeDYy9/CCCIYjsFIMiCIoKjqI7pC6C93zEEwyScDwDNMyzEsc5wt5nN7PqoFQBxh5H0ex/HifJwcEAeAH9DEEcwtcIsvAO1oywQEg/vgZPvsQKvgeJMAUgPTQl32ZQsQt7EERNJc9e8GfzDEJct6xNoXQO6L/tsIIt4MLQl/l1gsReMAGitBaC224LwLALBDDAHEL/ACz88CPlAezTAqguhnE2KLCIKIDbswuLEGud8PBYBbkePAJswGkFgrEY6koFRQIuEYCWyxsS1gUPaPAmBvi3kZFfIuwhLwF2kDneQSg1At0rvoKBKAeaWH0HgWIttIDLFQMkOooCI5YwbKYSw1gta8FQLBSMWBFEQGWJ0GEfgICuAmH4F6YRZhlAqHoAoGQBA2OcWkVxDABiOOGC9cxdRejjE8G0PQASejTB8UMRI/jpjuNiX0KJ8wYlmIFhsCQjcODM1IBbfRnBe7hyjjHOOCcpAjwgLgdOU9tiz3nkw5YgUmBYESKY0g0tJCBBJGrQIopJAaEkArbWZt/DazVvoTgRtSAmxFiSbWXBdZq0VvM/wkguD%2BG6drHJLcrY2ztmLJhzs3bLw9h3H2FBN6oAnkHEOHAmgsHvKKCOTB9RQOemrEkXASTIPwEQIxehhF53EIXYRJcxHl10A9autcr6ZOybk1uHB25ezOAcbu1piD3Mec8vYryuDvM%2BRoUe4815Pm2GYOe%2BzHZLxXpcklZBzlb0niAO5DyI44qMHirgoMD4okAsfU%2B58768JvhfB%2BT8HC8LfowAgn9v4tz/gAoBIDeEQPoZsdm%2BBiDwMQS3FBaCUS8KwTUFueCCGXCIeq%2BekZyGiyoTQuhRgGGgCpXwAwxZ2GcO4YwXhAKBESCEbIUFZd2YQskYw7RVhZF4JMco1RmR1GaJwhG3RltDGZxjPAMxNR4HOCsXyeJIQ%2BRJKcS9FxdQC1lsyMWvx1RagRL6AW8JAggkzFKNEsJcSQm5ASc0atKSVhrHSbPcZWTm7lytuizFTyXlVjxR8r5o9Km/OniLClC9JakEac0ygmTJnTPef00U6zRSikCAMyQ0cXrwp2bYPZ66l5HKQJ7TuG9GXXLYJwO5A8WAKHvAne8c6lSjFTj8jOWc%2BGAsEXwoN4iQDBChXXMBsKx2WzbqcruPcv0xx/X%2Bg4AH3lAZ9GPWl28V2BDXQc45b76V%2BxI0yv9uIkb4aRoRlGGLo58DoLy22EAT7lxFUKihAn76P2fpKy578ZVfx/hqzA/9AFiGVRQ1VjrLWkE1dqjN5c9XIHQYawQxry6movhakh1reF2qULQyBjqiwHJYe6jhXCeEUN9fnf10HRHBp0HBsNxgZE2GjZmjmcaBCgOeFjaROjLB6I5mm4xwWm2WOsV22xhb0B9o8YUTIFbPF1Ey/47NFiW2NqK4EyJDj209paKljtiTKvJIyQOwWTWDZwu2fkrDBwcP/sA2iUYi7QPVJnhRqlDTMBNOGK0g2e6QBmHeYEQI/hVarLNot0Uustnjs4Ls%2B29S2kgEkKKZOR6uBSDVoe7pXBRQjsCChvJ1tKWL0ySnLbqHHv3uWLBdIzhJBAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/turn_over.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/typical_turn_over.test.hpp)
