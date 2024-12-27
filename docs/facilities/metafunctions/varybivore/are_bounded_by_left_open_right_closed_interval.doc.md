<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftOpenRightClosedInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-left-open-right-closed-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByLeftOpenRightClosedInterval` accepts two variables, indicating a left-open-right-closed interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the left-open-right-closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &lt; V<sub>0</sub> &le; Max) && (Min &lt; V<sub>1</sub> &le; Max) && ... && (Min &lt; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftOpenRightClosedInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
// Create a left-open-right-closed interval (1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByLeftOpenRightClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<-1, 1, 2, 3, 4>::value);
```

## Implementation

We will implement `AreBoundedByLeftOpenRightClosedInterval` using only `<`, meaning <code>Variable &in; (Lower, Upper]</code> is expressed as:

```C++
(Lower < Variable) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr bool value
        { (...&&(Lower < Variables && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Lower < Variables && not (Upper < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAzADspAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgSbiYXiIN2CqAA7nFSDcYXC5KlUnFIdggeNiF4HDcLsRMBY1gwsOgLABPYKYKgEADy2IYACU8MAEG1aBlMOg7oI4gA3MRAkxJKyXG6ym4gsFvTCQ6Gw1AAOk1ADUWngmNF6ApcUC5TcCUSCDdlMRUERlExgMqZXLJRYbibTXLZo5kDc0AxxphVKliDdoqhPDcxd4nRdPS6pTcIJr1eYAGzpiAI5GhlU3HXEPUGzAKd1mDPlm4MW1JzHY3NQ/O6/WGpZt91JAAikOlcYT3YSvY9soVTyVKvRGs1F2AZNBjAIRoSeOdsq8mSMVodmHdCU7Vptdu3Kpnc5ei5TxsHEtX8tBY4hUMnKYLRcNxtv3rwvv9geDofDSN7UdAB9EVhw7N1k01dNM2zOJdzcJtCxbEsywrNMqxrCA6wQvNX1QhQ2yWDsByHLsexvK4/l%2BAEfl2G5sFUVgnh3T4gXomjTio%2BibgAWUwZoqC8BgHGyD5uO%2BbYbjcMklTRG56CZABaVA2WUwtuQIZTkD5JR0BuMIQWIaMky4VFJBMfxO1TS5R3BZUnzVFNSWAJcVwudcwmAfjBKYYTRIaCU9xJMkKRE6k6QZJlWUYTktLcPSBSFYzoxVcybks5cgRAEBgMctxXIUS9suvS4OMOG4ABUS0XCT9gBL9kBApgFCUVoIAEoSRLEgQVTMVEEgs3FcujLxMCWSjLialq2riAgIDAMBfO6wLsnS1EBpuIbMpGkAxomqaLhm1r2oWpaVv8nqgqhZSMoyradqy7BRrEcbJsHDgVloTh/F4PwOC0UhUE4NxrGsM01g2HdzASHhSAITQvpWABrAp1Q0AAOMwzAATlxrh/CxzGuCSJJpB%2BjhJF4FgJA0DRSABoGQY4XgFBABnEcBr7SDgWAYEQEA1gIVJYXISg0EeOg4giVgtlUTG02UtNJBuYBkF9KR1TMXgBUIEg8HQPR%2BEEEQxHYKQZEERQVHUbnSF0czEWIJhUk4Hhvt%2B/6keBzhmVhUXLVQKgbgVpWVbVjWbi1swkw8KX6FzMw4aWXgua0FYICQSXUmlsgKAgHO85AYApAGmhaGM9mIGiH3ojCFpaXd3h6%2BYYhaWZaJtEwBxm9ISXz2ZBhaCb%2B2sGiLxgGhWhaHZ7heCwFhDGAcQx7wMkxJFEsfaDHvYS2eGjLqH3aDwaIXfbjwsB9ghC1p%2BfSC34hwyUTtQWX0%2BjCRlYqAMNytTwJgREsUAbwxNsIUQ4hLbgJtmoH2jt9DLxQODSw%2Bgz7s0gCsNSDQ57KXGOgSEnZTCWGsGYZmT9CxYAwRAFYdge4NBcFSKYfhzIhDCEMSoIxzJFCyAIZhegeENHmMMeI5k6G9UaBMNongOh6HEQ0PorRhGcNEbYKR/CxFSOUYsLgtCoabAkJ7Dgf1GY%2BxZqHRWytVbq01pIbWSZcD6yTinNO38VgIEwEwLA8QaGkDRpIBI6pcbJEkBoSQZhJBpnpv4NMuN9CcGpqQWmcN1Rpi4GmTGuMSZpkCITYJaZTH2xZmzDmCNv68wFlnIWAcxYFyLonWWbBOAtBYCKJIykmB%2BgMJuLguN1RcAxrrfARBKHG1kGbKB0gYFKDgfbXQA1nau2bkYkxTNeAs39iLWENxg4WPDqrXSy9o59IGRoOOqAE54WTmYVOZTuaZ2zhc3OidxaFyecXQ5RhelcAZhXKulBa721bo3PuwL26d27r3B%2BA8FxDxHj7cek9p6zz7ovD%2BWwgb4A3o4Lec8ga72QPvPuR9KZA1PufRuV8MVpzvn3J%2BL9MBvyXkYT%2BoB7l8D/goABQCQF93ARMi2UzZCwLtkDeZiCv7EKsKg8l1CsGpBwZwPBBACF7ilaQ8hcRKHb0wd0eh2RGHuBkfkVhVJtFcLSBkXhORjUsMtcUbI5rVHyN6Oo21ci6j6oEIogY7CFgWtmJMd1mi5h%2BpEYY1Y6wDG6PicY72RTOB7KsV0o5vT%2BkYwccMkgZYXF3Izu4zx3jKBGMSckvpYSkj%2BFxmTBI4TImSHMms32rNbClPTjzPmgthaB1efUmWctmnEBYBHFgCgRS%2BhFGmhy4whlOMNmM02kDBVW3kDM0VOhEikEWW7eeKz43Mz9jUoOIdVAjrHROqdSpxjnMuc4hItz20PJQO8l5dSX0jHHViMCvSQLToICBU9Uy6D/JrnXBu7dQXgY7l3ehfcYWCDhaPTFmAJ5TzECih%2BaKWXUtIFi/VuKd6qD3iCYlwpSW8HJRfWkVKb60ofvS/kTKP7eXKb/B0XLAHALZHy8ZS6JBCutmu%2BBm7unGBQTYWV8B5WKp2Pg5BJDLBkPWRQw2OrfEuucBAVwGjSBsPKOG7hVqGg6cEY6sNKiPU9G9W6vIdqNOSNDfpizIag22bkVo8zOi9FRotnuwpB6OChzPeOqMl6QTXogI4kZObdGuPuQWrxIxfGU1LSAPG6oEgJH8ETBt9NMtJAyf59ZnASmczcX4kAkh/BBNJkkemmNJAEy4NjcssaEj7uKy2x9RidZFebXF/Nj84iZGcJIIAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/are_bounded_by_left_open_right_closed_interval.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_open_right_closed_interval.test.hpp)
