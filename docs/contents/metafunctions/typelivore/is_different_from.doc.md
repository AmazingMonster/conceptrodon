<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferentFrom`

## Description

`Typelivore::IsDifferentFrom` accepts an element and returns a function.
When invoked by an argument, the function will check whether the argument differs from the previously provided element.

<pre><code>Right -> Left -> Left != Right ? true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom ::   typename...
                  -> typename...
                  -> auto
```

## Structure

```C++
template<typename>
struct IsDifferentFrom
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
template<typename...Args>
using Metafunction = IsDifferentFrom<int>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(!Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename RightSide>
struct IsDifferentFrom
{
    template<typename LeftSide>
    struct ProtoMold
    { static constexpr bool value {true}; };

    template<typename LeftSide>
    requires std::same_as<LeftSide, RightSide>
    struct ProtoMold<LeftSide>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAAzAmkAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOYJYcjeWADUJgluaAwbKQQKx9gmGgCCd/cEmCwpBi/HbgQAnimMrEwBwASnhgAhhHgsDcnmNiF4HAcAJIKAAieCoVDijAIADFiKgWE8TAB2KwPA6Ug4vN4fTBfX7/ZhsA7BTBUSHQhK3ClUuEIggHZQEogAWU86CeVKOZIOM0cyAOZzGmFUKWIB2iqE8BwAbmIvEDSRYCPD6STUccLDLLQlyY9eZSae8mJ8ToyASy2RyhFD6dypVTiJgAI5ePDBhRygjoEAgBSAgD6TGuJ29nMwpBBYIhvq5PPu0v5iOFqDFEq%2B6bz/oL0uN0ddeEVypeao1Wp1%2Bu8RrJVDESlJtutg6txMd1NeLrd3z%2BnswADpF/dgMHXjjU7WqV4MkYDuLaOgjglUUKRah95KTsvV2xBApF/OYXax4Wqc66QzZ8yF0viMAN4GlLyk2SoCCqbYHEwXhEHuEqJrqRzjsapblgeXz3H%2B96LjccZdoaI7Pg8BH2k8AD0ABUlFUdRpFkVRAAq2BCPRVG0Q8FHUZxbEOo8Zg7Oc%2BxGicZwXFcMJEQ876uv6M5MoCD4Yf%2B4n3NuYTAHumBNFQXjnPUR4nii6KYtigj4oSXxhAQylxhe6GYQ%2BT4kQ8wHIMmChKC0ECippTDabpWQWYI5E4SAeGYIso7OU0CpuR5BAQGAYDeVpOkOAFJyWSFYURXaHDLLQnAAKy8H43C8KgnBuNY1hyqs6xGnxPCkAQmh5csADWICFZI84aJIXAkgkGiFRoZgAGxjWYAAcU36Jwki8CwEgaBopClVopAVRwvAKCAq0tRwWjLHAsAwIgICrAQKTQeQlBoG8dBxBEgKcKoU1jQAtGNkgHMAyCKlI85mLwmD4EQxBQno/CCCIYjsFIMiCIoKjqIdOh6AA7sQTApJwPD5UVJWtZtnAAPLQddgqoFQBxvZ932/f9ByA2YBwQB4D30Bq2xcIsvAHUdpAQEg90pI9ZAUBAoviyAwBSIENC0C8xC7RA0TE9EYTND8eO8JrzDED8pPRNomAOLrpD3beBCkwwtA62jpBYNEXjAG4Yi0LtZVO68hjAOIjv4MGaW6pgXsbaqZvQZsTWWbUxO0Hg0TY4bHhYMTpp4Et3uh8QWpKKivtGInRitcsVAGP%2BABqeCYBjpNMhb0PCKI4gI83yNqMTuhcPofsoNVlj6Enu2QMsqCXFkXsfWMl6oqYljWGYG2oLnENYKPEDLHYZv1C4DDuJ47R6CEYSDBUwy94UmQCJMfhX%2BkN8MHMQzxL3O9pQIvQTEfeTv7Uu8ejjH6GfeYl9bDALvnoGYLQX4XzftvOqGwJAEw4MVNaxMtq03el9H6f0AY9VZhAXAhASBHEanzZqZdlgIEwEwLA8Qt6kE6pIBI84ACcCQSSSD6mYSQY0VqFTGuwuaHAFqkCWgkLg84xpcDGlNdhU05HdS4IVThY0MGOy2jtPaVC0bHTOsLC6FMbqS2llzZ6bBODNBYLqEkH0mBKgMLuLg7D5zSIjmDEgkNe7N1hm3aQHclBd0droQIWMca61Qeg9a5UyYmKpjTGxdiHFOL9szNxHi2YczFlzchCQzCUIFnlIWItCS5LiLdKW5SZbJPsXsP2riuCrUVsrVW6tHb621hbLphtjam3Nt7K2OJbb22Js7V27taCewtlgFgfsA4bSDoA0O4cQaqCji8C2ccCqO0TsnbWadNgbUztnJqud86YELvM4uaky58ErgoGudcG6MCbrIfx8NAmyE7qjDaYS%2B6lwXlYIe%2BzN7j0nmBTgM8YzHHnoPCwy9yprz9OCrogDnAQFcFA3up8yivz0NfeoOLUiP3qHAhY/9uhf0gb/e%2B6LP4NGARS8BMDWh0ugcy0BBLeYrDWMg3luyYmYM4JBYgtj7GOIaS4zJvU2YkPBvk3m/NqGkFofQ4YTDdniMkW4vqJI1EkkGgEfh/VNEr04Do/a9yTrnUupTKp5inovQ4DYhmLAFC6kVLqVx846RjBBl49eUMPmty%2BYjeQwS/no2SBE3GZVolEy0fEq60EDjUzFSwd1nrvW%2Bv9YKdmNS8nbASEUm1ZTOaVLMUW4YXqUgpHgq4xM%2Bbkziu%2BnwOgbTKAdI2r0h2TU%2B39N3hbYZghRkOyWZgF2bsPZeyanMhZxzeDLJDmHYmkdkDR22YIeOeyk4px%2BEcjOEMzm8AuekK5Rd/Z3P0Q8pg1da710bt7PxYaJDfKRlG7uiRAXGARcPaIaKJ71C9qRWeA9F6WCRZtFFG94DbwAYy/eh9cj0rxefSlpKihZBJUSrILK34MvqN/dlqHoGIeI1y/F8DOV9BJWygjKC%2BX1SY0KpNFqOCZuzV6vUebpJjHlUGpVZb9E0LoQwygqCdUgDMG4pIhURr9RWkkEk8jzVxO2rYXRxTFgdX8IVDhhUprjXYZIdhg0uFcGSLshI7GNMqtE6I4G6mSaaZ08sXOGRnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_different_from.hpp)
- [unit test](../../../../tests/unit/typelivore/is_different_from.test.hpp)
