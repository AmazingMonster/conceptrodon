<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different-from">To Index</a></p>

## Description

`Varybivore::IsDifferentFrom` accepts a variable and returns a function.
When invoked by an argument, the function returns true if the argument differs from the variable and returns false if otherwise.

<pre><code>   V
-> Arg
-> Arg `different from` V ?
   true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct IsDifferentFrom
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = IsDifferentFrom<1>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1.0>::value);
static_assert(Metafunction<0>::value);
static_assert(! Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsDifferentFrom
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {false}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxCAAzAAcpAAOqAqETgwe3r7%2BgemZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfgG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgSbiYXiINwAKi1gJgCJDsEDxsQvA57goACJ4KhUOKMAgAMWIqBYQJMAHYrJcbkybiCwW9MJDobDUDcAGotPBMaL0NFA5k3THYgg3ZSUojKJjIsXMukWCXNRzIG5oBjjTCqVLEG7RVCeG4ANzEXkwN1VBCxHNpeMharpzoSDMBjOZ222CIQeAUN1S/UFtAlqUwyDDeAAXm9sjcAO50cOxbUIDKMZVM303Qm2gBsGn5xEFwo5xfzQaw6GxmHQNyYQZMxcRxGRqOLADocyzQU92ZzRd6mZKcbLUPLFRyoe3OyOLuLVeqE1qdXqDUaTWbLd4baqqGIlG6XbanS6aaP%2B2yIVCYURu0%2BLsBiJhQaSFIvxV5MkYZTOtoJHiMpyqgCpKlCL5vh%2BggKE%2BvYJOiHpXkuzKsoOd5co%2Bz4dl%2BSF9rMmragIm6Gk23IAciAD65q2teqqTtOkFuBceEIWiIAgHu1qnihlx8Z6QI/H8RwAiJNzYKorBPDanzCaJ/yoRJACyKJMFQXgMA4ibyZcGHgrO2GoAhbHAPh6KXL%2BYTADcanNJp2nvJCIF3PihLEm%2BggUlSnJcIuXEQUZZnwU%2Bor8V6VyHAimDjEGekXEReDINRzZKK0ED2RpWk6QIfndhonHcVamBLJelxJSlaVxAQmXqY5uUMJyhVIVxPGleViUaslqUKOltVgGAdn1TlDR%2BUV7VlR6HArLQnAAKy8H4HBaKQqCcG41jWBKawbAeZgJDwpAEJoM0rAA1iA82SAVSRmGYACcD1cPNGhJEkXC0rS0hzRwki8CwEgaBopDLat60cLwCggCDJ0rTNpBwLAMCICAawEKksLkJQaCPHQcQRKwWyqEkhYALSFpINzAMgWpSN2Zi8A2hAkHg6B6PwggiGI7BSDIgiKCo6jw6QuiBEmxBMKknA8LNC1Lada2cAA8rCmPSqgVA3CT5OU9TtM3PTZg3BAHh4/QRrmIdSy8HDWgrBASC46k%2BNkBQEDO67IDAFIZh8HQILENDEDRIr0RhC0ACeMu8OHzDEJHyvRNoUZw0duMvAQysMLQ0ci1g0ReMA0K0LQ0PcLwWAsIYwDiPneBvjp5qxYr%2BpRrCWxHWEIK/attB4NEksJx4WCK/aeCAxXpDN8QJpKHioI1/3RinSsVAGOZvJ4JgSbK5Gy1HZzwiiOIfNH4LaiK2L%2Bg1ygW2WPoA/Q5AKyoKkDTl2T4zoC5piWNYZhwYzzLFgZ%2BEAVh2FTtkFwDB3CeA6HoEIYQhiVBGIUDIWQBBTD8Og4o2R5jDHiIESBjU%2BiTHgfkYhdQoECDIQMZBCw0G2AmG0ChODmFzAYYQiQEDdqbB4foeWoNFYQ21qTCmVMaZ0xusbCAuAWaWwOlwG2x1V4rAQJgJgWB4jgNIJdSQCRuwPQSN9DQkgzCSGLBoeahYHqCL%2BgDRIXBuyFi4IWJID0PqFmui9YxhZhEiwhlDGGqj4YOxRo7NGassbu09hbQmbBOAtBYOaWkZMmDagMP%2BLgD1uzONWszIgICOayG5qfaQ58lCXxFroP2EspYxzlhwRaATwYq2iRrLWOsJGZJrobXJ%2BSTZmxdhbW0B0zAqLtgjSJcS4jYw9lSEZIxkBZJ9s9EGNBaCB2DqHEWcco4x1IPshOScU4OEORnUk2dc6KwLkXEuZdDlVyXlsVa%2BBG6OGbuXApqh24gkOd3Ooit%2B6DyjiPV5tsyyTyOjPOemAF7VyMMvUAYS%2BAbwUFvHee9GCHKPmU3mFTZAX2FqtWpN8V5/ysA/EFYDX7v2yJ/b%2Bv974WEAbwVAwC2Ytxft0GhfgICuGwYg2BBDUFELSBghoQrcGYIYKKxYVCei0JYdK3lpCWHyqYbMcheR2HavoeUbhyjVjrH4ca36LSwbss4GI3WVMVl9JyXkgqJt5FFLGdbW2ajSAaK0SMXRv1/qkEBgkXJZjaTzQel9BI5jLFdCtUrSGtgQlTPCfASJ6N1bzNmcQBJWxkl6xYAoc0WpzROsMuMJm%2BAilsxKVzE%2BBL%2BbyCqSSnQiRSD1OlhXJplqRHtIxrCG4mttaFuLaW8t7JxhDMWa7D1CRJmr0Rk7GdFts0rpGCW1IqRaI5OohWgg1FVCU39lsuIOyw4RwToc45idk6pwuVSTO1y85vMwIXYuYhHlT2eUiiFpB3lQK%2Ba3X5yAO4AsEECkWIKh6R3BWPKFhzYVZgRUvGyi716KgxdvXe%2B9cWlIbRIQlAsW1X3basu%2B/9qVP3gHSj%2BnBtjfwo1S1lQC4ggO5bokhDQYFwN1cK9AmrxVFFlaq4TDRBN6C470FVbDJPUPVZww1YrJMyb48QjVXDlPGoUHw3mPaFaBJtUeqmRaS0WgnSCKdcjq0kA9cor1YT1GaO0ZQJpQbAaPW7AkBI81XoBGBt52k7jWnWqTdDWG3r9HzSMZ9WkwMkiSGelwO6Zh/G/QSAZtpSbU1NMZiFxNDn7YrBnpkZwkggA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_different_from/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_different_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_different_from.test.hpp)
