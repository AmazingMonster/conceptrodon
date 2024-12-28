<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Sieve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-sieve">To Index</a></p>

## Description

`Pagelivore::Sieve` accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list. The result will be kept inside a `Shuttle`.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Shuttle
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
Sieve
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Sieve
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15`.

```C++
/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Sieve<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, 2, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by:

1. placing each variable in a shuttle separately;
2. taking the variable out of its shuttle if it satisfies all the predicates;
3. concatenating all shuttles.

We can merge 1. and 2. by:

```C++
template<auto Variable>
struct Detail 
{ using type = Shuttle<>; };

template<auto Variable>
requires (not (...&&Predicates<Variable>::value))
struct Detail<Variable>
{ using type = Shuttle<Variable>; };
```

We will use `Sequnivore::TypicalPaste` to concatenate the shuttles. Here is the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Sieve
{
    template<auto Variable>
    struct Detail 
    { using type = Shuttle<>; };

    template<auto Variable>
    requires (not (...&&Predicates<Variable>::value))
    struct Detail<Variable>
    { using type = Shuttle<Variable>; };

    template<auto...Variables>
    using Page = Sequnivore::TypicalPaste
    <typename Detail<Variables>::type...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmZmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOtyEmAAjl4GHgAG4kdggAAqAE9UnhRLRlEwJpgvocgcw2ApUkwtuCoTD4YjbiYAOxWK4ggiYFipAyskyBNwEdGMViYAB0Iu52BBE2IXgctzRGKxOLxdMZDPu3KZwN%2BO1uFlx%2BLcepAIJZbI5TC5PL5z2J%2BJxyAA1ph0BDoa9MGKJQQpTK5ZixIqLW47Y7nVS3R7mSqrrcY7cvJkjLcrfjufdbsGnS6vOHAhrVerjVrbgAlTDIDaZOH6w2Fy6s9mc93Mnkg2NJ02N7kGrxEEVCsW3ZAGBSfLNuy6kVux%2BtmwNMHuoPsDoe40dhhhbGxTmPz3sigBqrTwTFi9EuClIdOjsd3i4PR5P9AsF%2B3Sf5Nr7AHkCAgEgpjYE4pXJK0oELK6J%2BtiuKBmOG6YMCPKHsQx6nvBChLoBl6wZuXZIShT7oaKmG3N%2Bv7EIR/aAcaUaXG28YRMAb7PHSgRpr6CrQU2tGxl2r5tth8G4Q%2BqHnn2l54Y%2BmDPhh2CTtebYxqRf5LvJLHYCAIDJgWkZqrmtYzp2zZuK%2BBnmu6lrvoKl63jJg7DmurpwROJkdmZXbJja1kLrZK4jpSjmbnJ3Exh5gqys5qmhWwspbqpNn3shknnper7xUKEmoc%2BQVtlFwoikp5EAUB55eqB4Hyv6nFdgJCFuMiE63BlZ4UWKWHrjhPLIjYjXCQRMmXgVLVUZGGp0QmjHJixbEQRxeKvrxqn8e1gmdQ1cyOMgAD6ogTF29VihATVocsYm3OtmLbdBe0Idgh29VJCgnURsl8bGg0qcFakaVpek6dpmrAvSarMr8YJCAgPYEPQBIHECplzt5z2et6YHg5D9D/SCfwAjjsNY2CACSDZsowLSNDDZz47j1NAiaDZuZarkI3ulHYHZq59soxBOn6rL/sNJUo%2BC7xVtRo3Tkz5ndkQPWJahEafSBMqPC0dBXp9DIWHG41MSmrHghDBBQ1LHq5squl5pFktdresv4eZxVttz0J4NznwQAwqBgRAS5mAAbOYftczzoh80JcsY4BGlwmI2bLMsr5K2BKtMHQ4f2wrbaa9rDG61NBvo1LR2m1r%2Ba/QDOXWzyaVHfzjuxvRiY4sAetplmsIItzGnsZVc2qe5lnRSnaeIfddfffyMkT88mNA5joPU98VMHLc2CqKwHL4kvC%2BL3jIPAmYgQREOXhYCxbhoHBqQEHXtbYw88J4JkmWosiADuqAU3DVfS5/BMK0nB%2BcIn54Bfu/VAYtE5k0xIOAQeJVCpGILcWIqBPC3Bjt4LiWdGQEzpGYfwtwzBTVTLcDQZc8xz3LsvPYQCQFgIQNzLehI6azilrbf%2BAtAH3Efs/J8r8GGYC4prKB5oYGX3gYg5BqDaDoNjlgniOC8EEMCMQ/WZDKEUItnfMGhtjZfxYZ2auiNWbIzKmjI2kdLagjuAAWUwC0KgMIHDZH0VceGbDjGXGIMAW%2BVxG6MTsQ4px5MSFCBFlLbhwDeFSVfh/S8kS6F8ORAIh2IINLNyll4nxMl57WJXkILwqQihOlLAoLwtAwLb0uP48EhTinoFKeUsCoTdGRzcFwS8KRbhcH8CXbRdxGkVNcdUnWgzmn60CUwRxG5Ghdg6d0rpXS/aXh6X0/e99kQfEqcw4C0CtqrgSAQCAEx0AaQUIKTauIuxjKwnUjIJSPhNLFAnXMHBVi0E4P4XgfgOBaFIKgTgxlLDWDOusTYKZD48FIAQTQbzVj2gCJIIUGgAAcyQACc6KemopRVwek9JpAfI4JIXgLAJAaA0KQH5fyAUcF4AoEAlKYW/LeaQOAsAYCIBAOsAgqQezkEoGgdkdAEhREFJwVQKK/YAFo/aSFuMAZAyBulIrMLwHmRBkKnI6fwQQIgxDsCkDIQQigVDqBZaQXQHS37ECYKkTgPB3mfO%2BbC/5nBPw9j5WBVAVBbiSplXKhVSqVVCiIRADwwr6BIPMIELgyxeDMq0KsCASAhUYijQKiAaaRWJGAFIFINAKl/koLEV1sQIitFRA63g5bmDEFRJ%2BWI2gyzMqhUKtgghPwMFoFWi1WBYheGAAaWgtAGXcF4FgFghhgDiD7a7Ft8IPiuswKoMsPZthQoiKyIlfzaCgNtfWjwWBXVejwGS8dpAqzEBQUoR4U6jB7qMLC1YVADA%2BP3O8N%2Bn5rTVuNcILEhrpC6vkEoNQrqrX6GnSgaw1h9CgIZZAVYqBr7ZDHdKk5qZTDAssGYGlV6tVLsQz0BdzgICuGmH4DpYQIjDEqKMDpRQsgCAo3oRjjQFgjGqMR5xAh%2BhTE8J0PQdgSNNEmIMGjix6O2DEyxjpcw2gcbo9UVYCgwVbAkE6jgXyqWutpX6qVsr5WKuVVIUNtwIC4EICQPBsb43QufasX8TAsCJAgPCkAkhAhCnRYEAlGhJBmEkH7Cl/g/bov0JwElpAyWxqFH7LgfsUXotxX7fwkgek%2BeWdS3gtL6WMvsyy5NnKU3cs9fyigWbUCRtFeKjgrQWBwnpNKpg7NExcHRUKLgyL1X4E1XgbVf79XiCNcB01YGLW6BSDau11bNPaey26jgHreU9luD6/TAb5Urjax1rrGhzMRvTQkGzZg7OJtZSV7NGaKtXdGNtvNWLKWFtZOREtZaK31t/bWytjbm0OF/e20mXae2uv7YO4do7f2TunbOv5%2BBubOKrGOv5K612sl/Vu%2Borq92xAPaiI92w/mnvPVCq9N7MB3phwxZ9fA30KA/ZgL9P6L3AaG4Bv9Y3zV/Mm5Bp9WGrCWDg7EBDbn/kobgZwdDBB0CYZgzhvDCQCMi5U/UETLgGDuAE/kKjGvFNLAYxkJjOQteUbSIb9jEnONCdVzx0TAxZPccaHx8T5QrdyZkyboTYm9f0ZU2pw1c2XUWr0/6wzrXGLtc68i8zlnNU2bjQmhzpAnMucoJpqLMWOv%2BfpP4dF%2BLAgBaC%2BlnTwfOB5aZTT9lXKeVeszbd4gYq2CcHq4GlgCg4TKrhJHxsEwetWa1XoVnAGJBAdkJz8DIBgjTfteOwPJeaXurK9631qhW/t8793syEwDtVaO9Gw%2BgQzuV9TbvnNdfT9RpAB3opm0u/os2j3ggm1V9AboC9hlEBS0Wu%2B59i9P%2BG1NotoA5VYdoEDA69pw6YADpDpiCQ4XrQ4PqE4TrzqI5LoWqo7ljo4XqY47q8A4544E4nrIQk68Bk73KU4PrU6Fa05MDvqfrfqMC/pD4Goj4c6gZc46CT687GBy42A47K5i6NBjo7AnLQbYYWC4Y5b4b9aEai7Ca27q6a55Cm7Uau5Kasbm7ZAO5sbZA%2B5cbyFO4e7KHW69C8be6W7qHu726e5WEKYWH65%2B4bDqZxoRZaZB4L4cB%2Bpr4d7oKb58zeyx7WYxoJ4FZJqOaYDOajCi5EoZ4gBmAdaBCBD%2BD%2BD%2BZcAUqJH0iJbz45Zl62D5bnbxykAIqSD%2BDeZ4r0gUooqSBYpcBor%2ByuGBDuE5F0qhFwquFqrZGLaJ6FarBXqZDOCSBAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/sieve/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/sieve.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/sieve.test.hpp)
