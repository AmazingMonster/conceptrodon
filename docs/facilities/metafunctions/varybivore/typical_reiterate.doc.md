<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-reiterate">To Index</a></p>

## Description

`Varybivore::TypicalReiterate` accepts a list of variables and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Shuttle`.

<pre><code>   Vs...
-> N
-> Shuttle&lt;Vs...<sub>1</sub>, Vs...<sub>2</sub>, ..., Vs...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate
 :: auto...
 -> auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalReiterate
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };

    template<auto>
    using Page_t = RESULT;
};
```

## Examples

We will repeat `0, 1` four times:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = TypicalReiterate<0, 1>
::Page<4>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalReiterate` using recursion over the times of iterations.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

Here is a simplified version of the implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxuxzuQgQXgIBHo3yOwIImBY6QMSJMgTcTGhqAAdPiMdhQZNiF4HBCoTD6BirNdQf99ndsKokQx0BYmMgANbww7A3a7O4AdUwdwA7nRaHcvEo7gQEHgvlQvAwHLk5ah6YK0KqmKy9aL5aL0sRPgkAG6YdB3QzW03ITZKa3pQYKXGgpEotGYDFuAgATxezDY%2BPdgSJ1xJZIITJZrg53LuJhSVhSDxpoI9yNRBt9oLuBbl2e9vuxRFDhLuyAMCi%2BQkwAEcvG9MKR84Wy3j8QA1Np4JixegKTPh4kEUnk5ms9mcrm%2B%2BtNlu%2B3vEfuDz4V0ejukp9sFz059GYzuhq7AU3IxgEYfbq6F6XZIx3ZRMYCijEPCGN5uqn2YldrkOoakHcZ4XmwghugSW60iCaYZnSfyAshQL0uCACSXqXoIerqj8aEoYRwJZl6ubHjioYAQOQ6EmOE4xgAKoGeCiLQABKmCEAkuY7rB94HiW5HltBEZ3oWUbksoxCoEQL5vkmu7wYEsFancHKyliSggHuRakUeWI4nc6G0dc96mk2eCml8EDoUmgTpvZdwaCsOkSTGUkyagcl/m4xm3veyZ8fehYyhEwByoG76OZC0Kwj5tHKTpyYOSppmFgJZEGUQRkmWJBbmV4lmfHcNl2Q5n5cC5aUFm5z7SbJr4%2BX5okBbu1XBaFT4Bi8ZUUrF1L/n21EbiJCF5QpKWZn8gocQ6xDZJadyaewOkZfpnY5f5hYFUV1lmHZbgfkZVXjbVHkNW%2BvrNUlbXjfenXhd1UWflO8azr6T3BqK51eY1V13AAtHcZiEiAIBPblwWFmDa3fX9g2rsNUG4iBVHrsjCVBQWyVjatxaZSe%2BJgZg2HXpDIWPuF3m9T93m%2BsTpMYzBmZKalYKEfhSH3MyrCoqKnPsxzfJTSCZiBBE1ZeFgB06ts6Rk7eBGHH1VL8wiJGHj5hNhqJtUxaruNc8rQheOkJRWhxCheLQMYCw9EKm%2Bb6CW9bMZHfrcV5u1GggVwbbe77/vjT7dx%2BzpIdcCORKJYhguMi7Nu8ucoL2wnbuOUx6QsWIHFccQmUR7lYN05ikhF%2BDkWG3HdwMZ8tvq5GrSOMgAD6TC1gkBAQJM6BgworCYG3N5uGnIEm2bWQW58ruEi5ykcGstCcP4vB%2BBwWikKgnCHZY1h3AoGxbO%2BYs8KQBCaAvaxcgEki4hoSRmGYACcT9cP499JFwKQpNIS8cJIvAWASA0D7NeG8t4cF4AoEAPtz7rwXqQOAsAYCIBABsAg6RoTkEoGgFEdAEhRAHpwVQSQABsANSGSDuMAZAyBQ63zMLwK0hASB4F7n7fgggRBiHYFIGQghFAqHUPA0gug/ZinzukTgPBF7L1XhfTenAADy0JMExlQFQO4JDyGUOobQ%2BhuJ9oQA8Hg%2BgxAkwnxWLwOBWg1gQCQLgrOZjsEQEcfgxIwApBmD4HQJE81KCxAUbECIbR/TSN4ME5gxB/RKNiNoTADhwmkFwRBAgSiGC0DCSIrAsQvDACxLQWg0DuC8CwCwQwwBxDZKKmqS0xSN6YFUAk6EOxT4RCRH/DetA8CxHztEjwWAFHjjwEAkppBLTEFiJPJ45SjDdKMBfNYVADDAAUN2D4YolFBiSZw4QrFeHSF2YItQCixH6AqSgaw1h9A9OgZANYqB5a5GKQDHuH5TC70sGYcBEzVxYDuRANYdgElNBcGyGYfg/ZhAiCMaoYw/YlByAICFehEVNEWKMRIftgVqgEAMaYnguh6BxU0fFQwYVLHhbYKYHRCWFGxTSjFcKsVAsPtsCQsiOAr1IGA3gECtFkIoVQmhdCpCGJKrgFh5jzCBEqtYxZawECYCYFgRIgLSDX0kIEXET9Ag/w0JIMwkhSEgP8KQp%2B%2BhOAANIEA2VuJSFcFIUkJ%2Bn9SH%2BEkG/XVpCeUKIgVAmBZ9FmIJQfYtBqisEUFcagUxBCiEcDaCwc0KQAZMCrAYJ8XAn64i4HfJh%2BAiB/L0Ls7h4g%2BFHKUCckRuhvESKYFIkpnLuW8sURwFRGDoR3A0QKnRVDqwVNDlmnNGgSomKcQkCxgQzBWMDfAuxDjo1jrIJGtxZiUDps8a/H2NAbYJGgRAQJIjImhKSUe6JsT4mJLGSkq86TMkKJyXkgpRSkllIqVUje%2BB7SODqQoxpzSkRJPaQ0BR3TemhIGTsDewzRmnwmVMpQMy31hSDcs18ayNlbMYDs2QJaDn8PkBW4RG9q3nIWR8qwlgbmxABQ8p5AgXlvPsuR6w3y%2BW/LYZ8eAQKGggtyGC9wdLIUhDZEy5YCKshIryIJ1FEn0UUsxcSnjuLmg0pRdipTpLGXyeZcS1T0mGULG02J1lmx2WVUtVy%2BRIj%2BXaKFWm/tmbs13wlfmkgE65UztsYq5VqrKCcutbarNBqUj%2BCft/QIhrjUep9dZzg/rYFBqQag9BaiXErtjWwTgCbdEsAUOaOh5pHPekmHmqVbCi04f2RIQ5shjlEZ0CAYItb60yIs0231yjw3qM0aoHLeWCtFYNJMEdC73ETsCNOmxCDQ3paXTg0bq78tmxboVp%2BLdisEBbr1w5vjd0BKCSE6JJ7DsxLiSCpJ17BC3qyR%2BzAuT8liGfWM19czIOlJqd%2BzjIi/0OgA2MoDnTeCgb6f6CDQzVwwd4HB6ZyIkMLNnXwFZ6HMCbO2WM4tVWy21cI6cxrpHjBXMo6Bmjm86MMGKbsHulzPkWFY5vdj/yuO9F484CArg1PCfQKJqlaLcgc95%2BUIzVKSX9D0wUITIu8VacqApgzBLxe6cMzLnT5mD6md4Y2qz4DOBaL6/lu4q3cQbZc1K9zk2FWkCVSqsY6q/4BZAM/XEgRAj%2BHfh6kBzuUhOpi9ryBtgA1TZWFfEAkh/A6q/ikEBSRJCvy4A/Mw3q/6BC13yuLnnL4WcYT71PfvA9rAmdkZwkggA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_reiterate/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/reiterate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_reiterate.test.hpp)
