<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Disjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-disjuction">To Index</a></p>

## Description

`Mouldivore::Disjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... || Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction ::   template<typename...> class... 
              -> typename...
              -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Disjunction
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Disjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (10 < I::value)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<typename...>
struct Pred_2
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Example ****/
template<typename...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

static_assert(Metafunction<std::integral_constant<int, -1>>::value);
static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert
(
    ! Disjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);
```

## Implementation

We will implement `Disjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Predicates&lt;Elements...&gt;::value
-> false || ... || Predicates&lt;Elements...&gt;::value
-> (...((
       false
    || Predicate<sub>0</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>1</sub>&lt;Elements...&gt;::value)
    || ...
    || Predicate<sub>Last-1</sub>&lt;Elements...&gt;::value)
    || Predicate<sub>Last</sub>&lt;Elements...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Disjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...||Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMxmpK4AMngMmAByPgBGmMQgAGwArKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uu/uHmMenAJ5pjKyYAHTPx9gA1MgGCgrPj8rEmHwol2CleJg0AEEJsQvA43gARPAKbReBgOHLgiEmADsVkhbwJbzOByYRxOBFu9zYv2w9DYglB/mwmMJb2hsIIb3%2BqCIAFlPOgWYScXiIazWXNHMgPgIJphVGliG8YqhPG8AG5iLyXfHigkiiC/HFuY3/QF4YGYRluWl7RgEH4vJkgECa7yYZY4%2BHHUWsr0%2BoX63UE4kXK4Uu7ManPW30h1g4NvLxZIxvfm0dBvY7wrnEHmodOCk6x%2B2Ox5g/yi/2VzGYgD0ACom82W626/WW28ACpWh1vFvtyGN1sj5uDrGQ8z%2BcKfLxYLMnNBozBpeNM2tDztm9AAfQ0/bH9brbwASpgCBsGAoiTDMG88FQiQg761gD57ffr8AAaT4k/DG8XAaOWkKhr%2B4aUlGTxOsykLsnC257rWuJsi0UoyleuwKkqKpqm62pZriVBiEo1YWIR3o1pOoF7CSZI3JGDxvAAkgmEIAgAjl4eAAteEBAQubgsS6%2BEepi8GcohGhXKx66TihkoWhhcrYcqqq0BqWp3iKBC3mRFEBtRELDk2uaAjuXAHk2451seZ4XsQV43gRD5Pi%2BxBvnGn5vPQ3z/gwbzAZiYH0RGVLQeWclQrpHJmbuXDIeRinSkuKmKmpeFaYRFjEbQpHYpR5FkRuEIhZc5KQUxsmwexmBcTxVpvBAzEiVlVyBZ6cExQhALxTJbEiqhpJKalWHpbhGmidlMWXAVPoGVRE7GVuvU7mYVkNjZdnnpe14zfej4EM%2Bbyvu%2BgjeZg6qMCBpW0WGFWMdGkU1RJcVrYlQ3oaN8rjepmnutluX5YVC1VjR5zgQ94UsWxnHcbxTUta6bVmMkbzrdm2YdeJ3WSatZj9VFg3JcpY04X9U06Xpc2VqDJUmQ2bzYKorAHHeA7BXdkMMeFvzscAjI1cm4TAGm55MFQqLogIC45oiyJS40VxSaQb1cKriEE1FLqFlc/NlhWYPRcNyA7kw3zxAQEC8uLktokrJwTOgLrhLs35iDuo2GAQVyu6rAC0CXrs6yPup6i3JWbFttNbtuKxijsEM7ICu5g7u0J7sotIIvuCKrWvMiHonh6Kkfm0oMdgGAYstHb0sMFcTsu4IafEB7Xs5ycftvMkFbYK1YeGcbUpRxXVs27X8cCI3SfN27bcZx3Ptd3nbz%2BwXrwD9qJf08ezGPgwqBvIq5qWt5iqoOqeBYOgpBHm5/0udeYgAO5MNc14mIkGhA5c383WXaOPtIQQEDG8KuCIkQontgnE0UVWQ6wFGAq4YCJSzxTi3dOmdMLe1zgQVWQdsB30TGg5OqcsFLzwfnV4xCxR6lQmQzBC9sFzE7m4bu/g2J%2BiLlpTEJcOCrFoJwZIvA/AcC0KQVAnATSWGsGydYmxtJmH8DwUgBBNACNWAAaxAMkSQjwNCSC4NifwGhkgaDMIkRIZgAAcNj9CcEkLwFgEgNAaFIGIiRUiOC8AUCAdx6jxECNIHAWAMBEAgHWAQNIXh8EUAgGgfYdB4iRAeJwVQNjEj%2B0SJIN4wBkDSikI8MwvBzREGINfPQ/BBAiDEOwKQMhBCKBUOoIJpBdDqxfm3NInAeCCOEaIjRkjOAAHlYkxM5KgR8GSsk5LyQUwC%2Bj1oQA8Ek%2BgSopxcGWLwQJWhVgQCQIktIySyDxKOSckAwApBBBoLQXYxA/EQBiEMmI4RWjXF6bwV5zBiDXBGTEbQmAHCfNIIkuMIyGC0A%2BW0rAMQvDADcGIPKIKsAsEMMAcQMKGroiun4tp8ogWxO2Ko1OQi2m0DwDENuvyPBYCGbpPALjuC8CusQFUSh4R7HRRSowGjVhUAMALAAangTAL8RmRhBdU4QohxANOlc0tQQyOn6HRSgaw1h9CUr8ZAVYqBVw5Dxf7J22ZTCyMsGYLxrKKlYB1RAVYdggWNBcAwdwnhOh6FCOEYYVRRjq2KNkAQ0w/D%2BsyIGhgCwRgJHVo6%2Bu/QpjuoKDG%2BoTq%2BiTEGN6xYfrbDpuDXoOYbRI2%2BujQ6hRWwJD9I4CIjxQzvFvBmdk3J%2BTClLKargQgJAszKK2TsvlqxnxMCwAke1pAdGSH8I8AAnP4bEkhDFmEkN/MxiRJ0OI4E40gLiVGPESFwRINjJ02L3XorgyRp2JBrW07xvj/FqL5SE8JBzInjNieQSg5z1mpLYJwVoLB1TYn9kwD4BhUxcEnY8LgBjSn4HKZU9W0ralyukAqpQSq2m6CCF0pgPTmWVurZ43g3ixnRNiW8KZJ1iB/oA0Bz46LALgcg/uFZqA1l/inGYbZd6gn7MOSx456y30JL4xc39/7/a0aMGBoCfA6D3Mec8tp3z3kgqU78/5gLgXMtBSx8FkLoUSNhfCxFtBkVadRdy7YBnsWOFxUMglyAiUgtJUMilVL3m0sszsipTLVGsvZZgTlaKjA8tANxvggqFAirFRKxgUrZCIfqch2QirWkSIw6q3lZqrCWC1TEO1eqDWyk4MapOpqNUWqtfEG1Vp4AOpTfXF1br8ghuCK6otSxQ0lByHmzr4b2vZtjY0eN7RE0tcG2m%2BYmao35tzaNmbk2KjTa2WsDY5bltkvw7WzgFGqOAeA3RsDEGDFtpg52zZnHdmaNIAOodlBK0bq3eBwx2Iz3YhMZIBdOT1YEeGT42wt7Lv7MfUgKJEzBMfpSWkjgv65ksAUOqaU6pDsXAmNBjtNqqnxdlYlxp8hUOpZ0AEUgWGcN9LXZtq9oyX2TMfDD3JcOEcamR7%2BCYTVVn8bY8o/wF371Poh6c99wn1mumQGkNIO4keTp3CjggZtKM5Jk3c%2BI8mXlvN%2BSptXfyAVOpBWC%2B0EKoVDMMwipFeLVHmeC550g%2BAAQ4pq/i1QhLdhOZbmSiRrnqXXA8/S7zIK/OZAC1y4LIt70CqYMK0V4rJVaYQ9jiQSWmn4%2BVUTkDxhys2Fc/lyRhWrycDrE3LL1hLWEetdfGruqeipucBAVwPXWvoH69G9IYbGh14DY0Rv%2Bb6tDdm81rvvQBDDc7zG3vHqR8LZ9R10tq36l4cGZTjgO3Yfw8R8zkEnIIDtvKV2lRPPuP9swIO0YI6yUPZAGYcD/h/DJHMUYtxV/sT7svV4zgN6Al9tHSASQyQp3JBsZYydSQSdExGdLgfwNdfwefF/P7QHStEpZ/QjV/LjPZVYVlLIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/disjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/disjunction.test.hpp)
