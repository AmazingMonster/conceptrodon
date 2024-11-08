<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SetContains`

## Description

`Typelivore::SetContains` accepts a variable number of nonrepetitive elements and returns a predicate that checks if the argument is in the previously provided elements.
<pre><code>   Arguments...
-> Element
-> Element &in; Arguments... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains ::   typename...
              -> typename...
              -> auto
```

## Structure

```C++
template<typename...>
struct SetContains
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Example

We will check whether `int*` or `void`  is inside `int, int*, int**`.

```C++
template<typename...Args>
using Metafunction = SetContains<int, int*, int**>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

The idea is that we create a class that inherits every element we would like to check against.
Then, when the user provides an argument, we use `std::is_base_of` to inspect whether the argument is a base of our class, subsequently determining whether the argument is one of the elements our class inherited early on.

This idea is also presented in `mp_set_contains<S, V>`.

Since inheriting the same type multiple times is illegal in C++, the requirement that elements must be nonrepetitive is necessary.

Since fundamental types are not inheritable, we pack every argument into a wrapper--in this case, `std::type_identity`--before the inheritance.

```C++
template<typename...Elements>
struct SetContains
: public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {std::is_base_of<std::type_identity<Inspecting>, SetContains>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename Inspecting>
    static constexpr bool Mold_v 
    {std::is_base_of<std::type_identity<Inspecting>, SetContains>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHOaxwcjeWADUJrFuXo60hACeB9gmGgCC1zcEmCwJBo8HbgRnCYysmAB0AOw9DYggUl3u42IXgcuyEmHqsiYwTBtxAuwSXgip2Qu3G6BAIE%2B3wA%2BngsIJzu8gU9GAQwbFsAC/vcTAB2Ky3XZc3aPZ6vTDvIk/Ni7ACSDAU30qRnBnO5kOhBF2ymIqCIAFlPOh7tz9uzuTrdfKao4cWgJY9VAliLsIqhPLsAG5iLyYfZyo16ix4gl4BTEiJMJTE1BUd4%2BwlfTCk8mOT7vcWSiqOGUM0iw%2BEeQRIiWXAnO7wC1kAEQOHJuurZpdi5cNXN5LyYb0OQuYbCZN2AxEwNNBsor3K8KSMu01tHQ%2B1ixeVqo1Wvene7vbpTPBNZZHp5T0bzY%2BUbbbsTUpTwH7uvGTbwZoE40wVptdodY/QxMd7oHXLZ3oI%2BJAfoDQbRqG4Y/gSQoxrSlKHEeybBKeaYZgi2bInmIAFq6VZliyJZYbc9wAPQAFTESRpH4QRJEACrYEIlEkeRtxEaRzEMXceFmJsDDbF4ezvMcdBQVceG3A2/KCvuvwdsQwD0kJNxDnBo7wkwVBeFx7STtOcJITUKGHMEBDpgZhFGYIxH9gSz4LtJCirgyuFsTcF6msSQZKHUEDqspqnqWk7zGah6GYHMDnOVerkKO5BAQGAYBKTUPmVAI7yOqgZKBS6wVlhwCy0JwACsvB%2BNwvCoJwbjWNYuJLCsbobDwpAEJoOULAA1iA%2BWsn8sQABwAGysrEA0aL1g0AJzxHlHCSLwLASBoGikMVWikGVHC8AoICLU1HBaAscCwDAiAgEsBAYoZFAQGgzx0NEoS/Jwqj9QAtH1ki7MAyA4lIfxmLwmD4EQxBkno/CCCIYjsFIMiCIoKjqLtOh6AA7sQTAJJwPC5QVRXNatnAAPLHOduyhrsT19a972fd9ki/bsEAeDd9A2vVcy8Dte2kBASDXQkt1kJdfMCyAwBSGYfB0I8xCbRAER4xEwS1GcmO8IrzDEGcBMRNoyaq6Q10ggQBMMLQKuI6QWARF4wBuGItCbSVltPIYwDiBb%2BDdpUjqYI7K13hUxxrA1BmtHjpwRGjmseFgeMEMDc1Oz7xB2koxYu0YpxGM1CxUAYMkAGp4JgyME98xUNWDwiiOI0NV3Dah47ozQGNnpiWNY%2Bh4BEm2QAsqAJO0jvPXiBzFu3ViWGYK2oMnwNYL3EALOUSV%2BBArgjE0pCBFMRQlNkySpAIm8H7kaQ9Hv/RjK0sECJ0wyeI0egr%2B09%2BTIUfQxGMEwn9/XQX5/CQy8aqrCAfoHGS08ZrXJi9N6H0vq7B%2BmYBmuBCAkH2BxLg7NGo5wWAgTATAsAxCXqQdqkhYh/AmqySQGhJBmEkH1Ba%2BU%2BpjXAdNWacQuB/D6lwPqPUxo9V4flSQXB8oTT6pAi2a0NpbRwYjfaR0eYnWJsccglBhYs3umwTgtQWCOlZM9Jguxtiu0QWNP4XD/aAxICDZoVcIa12kPXJQjcLa6AlqjdGqtsYcEKpImehMVFKjJro/RhjjGt2AGYixfwNAMyZvzFmGDYhmGwZzHK3NeaoGZtENRV1smJP6KEgxJijBcDGlwRaNBaDS1lvLC26tlb60aZrbWusHD60NrSE2Zs8ZWxtnbWgDt9ZYBYK7d2K1PawR9n7f6qhA6PH1qHKaK0I5RzODHNYK1454ETg1ZOqdMDpzGZnOCOc%2BD5wUEXEuZdGD63sTXKGTjZANwRitdx%2BhXYoEqpYLuPd4D90HmkYeo8pwT2sNPUqc8yS%2BwBS0NoaQXAMHcI/UY29kUAJmF/RIh92i/xxWffIu9AHXwRXfH%2BqKt4vyqBMTF%2B8/4P0yFS2lxKsVgIUCAqGPi/HLVKpwXYxTwmlKieUmJcSICoKBskrBHNcGkHwYQ/oJCpozVIHNWI5jaGsjEayQadCGEiP8Xy9athZHpIUfAJRp1zp5I0XdB6HBdFwJYAoR0OJHSiv5OMf61j56g1kA4p5MN5AuLeUjeIniMYlW5bjKRgSzrHFJlQAVxAWDOtde6z1TZfZKkZgUgWyT5iyvkZklA%2BaWa2vLf0N1CQEivnKcSL1BBXKprepLGp0Q6kKyVprZpPatY6z1k7Lpggenm0mZga2tt7aOwaqM8ZWzeBTO9rCi2AdkBByWYIMOFs1nK02XHBO%2BsDnJCORnN2ZyS15yYIXYupdy73IDY8iQzzYahqbgMSJ3yO6/IjovQFQ9OD4R9OCqeM9oULzhdS5w69kX4p3h/NlzQchH3SJS0%2BqG6VX3hbfDoFKmXPxvqvN%2BWHsUXkZU/Bl79pj0uAcsUBWC2E8qgfyp170XVuqdFmx44wUG%2BulWkuVCqiGUB8aquaZhzGxFiPlfKtDKkjViKyPhRr8Yms2ttOVZCzDcK4CkvqKSxo8LMIw1kbDYixoCSa81Pi/qqekXIvaCxk4pGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/set_contains.hpp)
- [unit test](../../../../tests/unit/typelivore/set_contains.test.hpp)
