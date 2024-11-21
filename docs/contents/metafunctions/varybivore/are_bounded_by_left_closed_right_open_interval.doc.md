<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftClosedRightOpenInterval`

## Description

`Varybivore::AreBoundedByLeftClosedRightOpenInterval` accepts two variables, indicating a left-closed-right-open interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the left-closed-right-open interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &lt; Max) && (Min &le; V<sub>1</sub> &lt; Max) && ... && (Min &le; V<sub>n</sub> &lt; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftClosedRightOpenInterval ::
   auto...
-> auto...
-> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftClosedRightOpenInterval
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
// Create a left-closed-right-open interval [1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByLeftClosedRightOpenInterval<1, 4>
::Page<Args...>;

static_assert(Metafunction<1, 2, 3, 3.5>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByLeftClosedRightOpenInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper)</code> is expressed as:

```C++
(not (Variable < Lower)) && (Variable < Upper)
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftClosedRightOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(not (Variables < Lower) && Variables < Upper)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFcpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmgW5MXkQA1KGoAO4JFmsM6KTnpxdyqal3D%2BhH2CYaAEFxsQvA5zgDiJh7l5Hph0BYAJ6hTBUNq0DJwgBKeGACAIAHlPgwAJKCBIANzE/wBJgA7FZAecmecdnsDpgjiczqgAHR8gBqLTwTFi9AUv2pzPOwNBBHOymIqCIyiYwA5jOZdIZAKlUtmjmQ5zQDHGmFUqWI51iqE850p3nVOt1TK15wgfJ55gAbN6IAwlW7BcRhaLMApzpzLjcvjD0EsI2YfYnzkGQ2KI8dzu9PsRoY8lvG6QARI7aqXF0vUyXM1n7JiHY6vXl8gHASG7RgEcWBP4apleTJGeWqzAZovyxXKkec1vttiCBQeiWBbXVpm19mcpse1MisUSvvS5oGo0CU3my3W20qtUAfXJa4j9LdS8Tvv9cogu9D4cjV1uubfIWb7Jt%2B6aRtmMb5oWtIliuVawZWgLUgA9AAVBhmFYShqGYQAKtgQh4ZhOGAuhWEUaRNJkSh5xuJC9ajkw5z0KiAC0yDoko6BscGuIEGxqBEucEQ7MQ9oRv4FgaM8khLJ6gIboxW7ch6ELAN2vYAgOETAOcACymDNFQMIONkVaBOOEJQt8cKIsiqJuFxWI4nihKMKSYn2pyMnnJIB4AiAIA3hyxzqYufLLqugL6ngyC3kwChKK0ECGcZpkNJyKTnGYzzBOcgQ8v4vxBfaXiYEsSFAsecUJUlCQEBAYBgAZRlMCZDBmQIWXPLlBWySVIBlRVVWxfFiXJY1zWtelnWZcc2V9fl0jnMVPalWI5WVSuHArLQnD%2BLwfgcFopCoJwbjWNY0prBso7mMkvAEJou0rAA1gEZg8rSZiSAAHH9/gaAAnP4ZgaF6f3BPtHCSLwLASBoMnHad50cLwCggDJz0nbtpBwLAMCICAawEKkZzkJQaB7HQCRRKwWyqH9XpsV6kjnMAyCGlIPJmLwcKECQeDoHo/CCCIYjsFIMiCIoKjqLjpC6Ck1zEEwqScDwe0HUdL1nZw%2BJnOTcqoFQ5xMyzbMc1z5w82YboeDT9CWg9XBLE9L0rBASDU6ktNkBQEC%2B/7IDAFIuU0LQYmYxAsR67EEQtAimu8AnzDEAi%2BKxNomAOCnpDU/OBIMLQyeK1gsReMAJy0LQmPcLwWAsIYwDiOXeCQmZ5JhnrZq52cWw8OQZIw6dtB4LEasZx4WB6wQwYIw3pDd8Q1pKEWuwt%2BPRie3wBgafyeCYNc7nHUPYvCKI4jSxfctqHryv6C3KBXZY%2BgT5jkArEJDT12x4w/EsqYSw1hwa8FQCvYMWBP4QBWHYXODQXCPCmH4FIYQIhDEqCMFIRQsgCBQXoXBDR5jDESGMOoCDegTDaJ4Doeh4FdUaNQkhWCyG2GoQQsYzCMELGwXA26mwJDaw4IdUgKNwGcHNszVm7NObc0kLzN0uBBYuzMMkd2pAcZaALKQBAmAmBYESLA0gH1JCFWBoEWkkgNCSF%2Bl6JG/gvTA30JwOGpAEbJB5F6LgkNgZ/R8f4SQXB/AWK9GIvWaMMZY00bvAmxNSbG0pkHVATs6YM04C0Fg5JaRsWYpxFuttgY8i4DyU6AsiBQNFrICW19pC3yUPfRWuhcqq3VinYRojxH6w4IbMmZxzimxeMQLJOS8kGCHFwIpJSNAOxSX7Z2CZAhmA0VovG3sUBzP9kk4OzsQCZOyRxcZYdgZcBkpHaOlA46KzTknfONyM5ZxznnJehdOz4hLmXU6Fcq41zrvnJuW8thfI7pQ7u9cymqH7jsfOok6h63HpPJOM8gVPQXvnFea9MAb2bkYbeoBcYrCoPvBQh9j6n3zhfGpUs6myDvgrU6zSn472AVYN%2BCKYHf1SL/Tg/8CCAKLCy0BqNIHCx7l/bolDnAQFcJwkIjwWGLBwRkPBORaH5CVcUbICrsESsYX0SYarUG6oaPqgYPDSH0I4Yay1cxzWsKEasdYgi3YuJEbrRWaMhkjNyUaI5hTimlKUfgCpiy3YewJSsPRBiRjGJhm4jxRSbG0hCbSWkgRbGSDZikLpkTbDRNWV7Im6yEkU0DjstJbAMnDKtiwBQ5JDTkkmTydk4x%2BbBqFiLFIlKr7UplvIBp9KdBJFIK0jWDcOnutRgbI2/TBmZJrXWhtTaW2fkdvMhIizAgrNiT7TZzttl7pGPWj495Jm3hXQlatdS6AXNjvHROGc7kPsztnBB%2BdXmCHeaXPW3zq5iD%2BUvAFuKUWkHwJ3RwYLe6QuQAPGFI94UTyngiZFc80VLwxRibFW9dK7yJaqElR8T5EgpdUntEgaWywHQ/YdRyX4gLZR/eAnLuUcBQgAujrKLBgLOiK6BTHjXZCQe4a1aD5V2sVWkZVDRZVEK1eJnVDCTVWryEaxTVDbXlAtVw/osrZitG1WQ/hTqpYTvCR6yR872a1vrXaZdjFxhBpUaG7dEbdH6MMZQYR8aQBmCKYEQI/ggZBKRv52kkMzNTvRnm7Gnt3ogEkLSXmyauBSGBkmixXBaSusCJOiRUWC3CL5hFvL4btErBXpkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_bounded_by_left_closed_right_open_interval.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval.test.hpp)
