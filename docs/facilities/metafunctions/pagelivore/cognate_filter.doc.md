<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFilter`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-filter">To Index</a></p>

## Description

`Pagelivore::CognateFilter` accepts an operation. Its first layer accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateFilter
 :: template<auto...> class...
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateFilter
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will remove every variable divisible by two and three from the list `1, 12, 2, 6, 15` and instiate `Operation` with the variables left.

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

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateFilter<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, 2, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateFilter` is implemented based on `Pagelivore::Sieve`.
It transfers the result of `Pagelivore::Sieve` to the given operation.
We will use the following function to send the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateFilter
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Sieve<Predicates...>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEv4AHKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxuxzuQkwAEcvAw8AA3EjsEAAFQAnmk8KJaMomJNMN8jsDmGwFGkmNsIdDYQikXcTAB2KzXUEETAsNIGNkmQJuAgYxisTAAOlFPOwoMmxC8Dju6Mx2Nx%2BPpTMZDx5zJBf12dwseIJbn1IFZ7M5TG5vP5LxJBNxyAA1ph0JCYW9MOLJQRpbL5VixEqLW47Y7ndS3R6WarrncY3cvFkjHcrQSeQ87sGnS6vOHApq1RrQaDdjqAEqYZCbLLwg1Gk0crnulm80GxpOmhs8w1eIii4Xiu7IAwKL5Zt1XUgt2Ns%2Bvm928pjd1C9/uDvEjsMMbY2Scxhc90UANTaeCYsXoVwUpHp0dje6Xh%2BPp/oFkvO6TAptvYA8gQEAkFIWgQStcUoygQcoYn6OJ4oGo6bpgIK8kexAnmeCEKMuQFXnBW6dshqHPhhYpYXcP5/sQRF9kBhZRlcrbxhEwDvi89KBGmvqKjBjZ0bGnZvq2OEIXhj5oRevZXvhT6YC%2BmHYBON6tjGZH/suCmsdgIAgMmBaRuquaFtc05mtyTZuG%2BRkdpaH5Cled6yQOQ7rq68HjuZ7azp2yY2rZi72auw5Us5W7yTxMZeUKcquWp4VsHK25qXZD4oVJF5Xm%2BiXCpJaEviFrYxSKorKRRgHAReXpgRBCr%2BlxnaCYhbgouOdxZeelHithG64byKI2M1ImEbJV5FW11GRpq9EJkxyasexkGcfib58WpAmdUJ3VNfMjjIAA%2BqIkydo14oQC16ErOJdybViu0wQdiHYMd/XSQoZ3EXJ/GxsNqmhepmnafpuk6VqIIMuqLJ/OCQgIN2BD0IShzAhZHnzr5r2et64GQ9D9CA0WEMfNWcPnHWxlzny7mBhlK6Ob2yjEE6fpsgBo1lejEL49xjLjVO5Ok3efXJWhEbfaBspPK0dDXt9nNxpNzEpmxEJQwQMOkx6uYqnpebRTznZ8ydQutnTMJ4HTXwQAwqDgRAy5mAAbOYtu0/ToiM8JAvY0BmnwmI2YrCsb4i%2BBYtMHQbsEXOpWttLDGJtNqaK1jpP69R6v5v9QN5TryP7plj1M5HsYx0xuLAPLaZZnCiJ05pHHVQtamedZsXB6HSF5%2BKv0CrJncvDjIM4%2BD9yQgw6CEwjWd8k3BVUaVgdUiPKpWP36fE5ZZMzhTKMzw5a6Bdm8E%2BTnJ352jFXD%2BgtWrWHUkjRKzOc25G%2Bk4jm851Tu9fi8xDmjkBuxnPLdaCLVoopQuss44K0/gkH%2BAhr5oVvoDKOy8tbfRfs/CelMgI72HL2K4wA6bskYAQE%2Baki53BLCHWgM1HiYHFkA3keCCFsEELfHuc48zIIMmCQEPCfi43uAASXrIQwQMCGBj34bw3hwJV5I3XiTXWW934BSgd/JoQs54eGAMwNkAAxOgbJiA0S5mFCeaDFFvywf5SiTt8Au0%2BH/GMc9aaW1QBQ0ODcQGgLbE/Cx95c7uwcczbxMtGLpiYKXah593oxiWt9EJ%2BU2aYGrJ2WxDNPiyRiYpX6PNwmlzgfQBBy1eLBO8Tkp%2B5DKGdlUWItWJiNYD1QWYjBSirHU1FIwzAIjiGONCYmdxVD44uKIAMzsnTukIJXpwsG3CpFEkkfsO42BVCsE5ASPhg85nwy4eYQIERBxeCwKxNwaB4JpB6ffTZiyHgIjwFkbKaIUQAHdUASMMi0ogdwBEaPKqLW59znyPJecYgOrQtoDgEPiVQaRiB3FiKgTwdxvbeG4kgiwAj6RmH8HcMwM144aDThwzWXD/jXP%2BXgB5KIEAELeVccx2dXnfOZgA8llLqVdJBWpS6yAIUMChTCuFCKqHIuzMA9FmLsWBDxQrAl0zgbEpmaS0iX8xG0vpV2Sxs9fngRqeoleVy7gAFlaFMCoLCBwOQ1UfP8VcYgwASFXDIca1oZrNxNGoVonRmB9G0EMdUlVerSqaVGbyG58I7kUsBc81AV4w0RrZQQoWmkS6k1tfazJ%2BrZmLKEF4NIxQnRlgUF4X1tKyE5rzZkAtnxi3gXjrq3%2BvIuBXjMFeWodSSXgkLTW0tssu0lvjs6015q9VuCbXcLgLacVXltq2/w7bFXghRJ8cCGyyo/x2muBIBAICTHQJpBQQptp4k7H2gg2Fc35vQKe8U/tcwcDWLQTg/heB%2BA4FoUgqBOBmUsNYC6GwtgpjMIEHgpACCaHvWse0ARJDCg0MkMwZgACciHahweSFwBkDJpCPo4JIXgLAJAaA0KQV977P0cF4AoEAxGwNvvvaQOAsAYCIBABsAgaRuzkEoGgDkdAEhRCFJwVQyRbYAFpbaSDuMAZAPKpDCjMLwemRAUJ7qbfwQQIgxDsCkDIQQigVDqDo6QXQTannfzSJwHgD6n0vvAx%2BzgX5uwcfAqgKgdxhNiYk1JmT46YO4ogB4Xj9BYW7K4CsXgtGtBrAgEgHjmJgtcYgHFvjiRgBSBbTQX1/5KCxDs7ECIbQ0SWd4Pl5gxA0RfliNocstGQM8eYQQL8DBaBFaM1gWIXhgCGloLQKj3BeBYBYIYYA4g2smxqwiT4dnMCqHLN2HYIGIhshw%2B%2B2gFLv7lY8FgOzXo8AEf66QasxB4VKCeENowa2jDgbWFQAw9qDwfCeVA19IH1PCGxNp6Qb39NqDsyZ/Qw2UDWGsPoClVHIBrFQOcnIfXRO7tTKYH9lgzBkaOypqbEPegTecBAVwMw/BNrCBEEYVQxhNuKNkAQ%2BO9AU6aIsUYNQscWoEAMaYnguh6DsNj5oUwhjE6WGT2wvPqdNvmO0enpOahrAUP%2B7YEhrMcGfSRuz5H3MifE5J6Tsm/N3AgLgQgJBMXAfC6B67aw/xMCwIkCAkGQCSECMKRDgQsMaEkGYSQtsiP%2BFtoh/QnA8OkAI8B4UtsuC22SIh9Dtt/CSFqE7mdpHeDkco9R03dHovMZi6xpznGKBJdQEF/jgmOBtBYPCBkommA70TFwRDwouCwcU/gZTeBVO6fe1piQX3ZA/cM%2B%2B3QLazNMAs/1hXSvE/2Y4I59j3Y7iubV55yTq4a914bxoXXgX4sJCN2YE3kX6NZ%2BSwlvPR%2BxjL7Syh4jmXDFUYgLlozpXCvFdII/8rlXqsOGf/VohTWWt2fa51t1r1s/oNsNqNu%2BvgHTBatWH1u%2BjNnNmyM/ktg0HZmtrEBtmiFtjsO%2BrtvtiBkdidpgGdmAYxNdnwHdgoA9pgE9taM/m9ppuIDpt9koL9kZgPgDldojlYJYKDrEODjbh%2BtDpCpwHDgQBfGxFwdYCjknmjq3hjgIVzszn4LjiPCLiECPBLssOTpkJTrkOzgUNoSUDkJoYLooU0Kzh0PoQTkzuYbziYYzmLpYfkNYY4fYfLusJsHLmFn7orrZkZqrh5hrtXkxLXvXrBrrvrspkbmFhFmbqQBblbpQArgHkHnXq7gyP4IhphoEG7h7rHsrv4ZwCnjRmQYxixmxs5olqfsQAJmwJwKXl5iwAoPCDyvCKEQ2JME3gbipnoPQR9l3u3r3n9iAMEEPiPlZj4ePirg5jni5m5qoI0c0a0e0bOJMBvgXlviFkBoEHvqUbFhsSllUQccFiAC0XmttG0YhttB0QQNtAsV9gYtlnfnlgVuVs/q/hVlVjVl/gXg1r/q1hAZgB1l1mIMAQdqARdtgQNuNtAVNkZvARWIgQdsgStrwGgRgVgTtihHgbwAQZWsQRdqQenuQREpQY9s9nQbIAwZ9oMSwX3joCMRwcYMDjwWgfwZDkIXypwLsLukDkjhYNIR%2BrIVgOyTYTkC4KoVYXoEThUAzjTjoU0GobTsYfznKaLg0NzhYWoWYf0HYaqZLpzsLlKaLnqbKQad4TLp4dpmPn4WRpwO5osS0UiisYzFbJEYbqFrsenubpgJbmMAIThikSAEhsKIEIEP4P4K7lwERmGQyOHgUXaRRrYKnvvn7KQFBpIP4I7hhgyERskJIChlwPBnbD4YELaUnkUWnlFgrgpgmRWUmamWsEdlkM4JIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_filter/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_filter.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_filter.test.hpp)
