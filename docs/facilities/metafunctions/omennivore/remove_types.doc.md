<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::RemoveTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-remove-types">To Index</a></p>

## Description

`Omennivore::RemoveTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices and returns a function.
When invoked, the function removes arguments from its argument list according to the `std::index_sequence`s.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
RemoveTypes ::   typename...
              -> template<typename...>
```

## Structure

```C++
template<typename...>
struct RemoveTypes
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will remove elements of indices `1, 3, 5` from `Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `RemoveTypes`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = RemoveTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Mold<Args...>;

using SupposedResult = Capsule<Vay<0>, Vay<2>, Vay<4>>;

using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `RemoveTypes` is similar to that of `Omennivore::Insert`. We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct RemoveTypes {};

/**** Base Case ****/
template<auto...I>
struct RemoveTypes<std::index_sequence<I...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Capsule
    <
        FrontTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

template<auto...I, auto...J>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Capsule
    <
        FrontTargets...,
        MiddleTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> ExtendFront
    <
        typename RemoveTypes<OtherSequences...>
        ::template Mold<BackTargets...>
    >
    ::template Mold
    <
        FrontTargets...,
        MiddleTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEoEAHKQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcXKl2mA45QgRMxAR5Pn5Btpj2JQzNrQRl0XEJSXUtbR0FXLZTwxGjleM1yQCUtqhexMjsHOaBEcjeWADUJoFuXo60hACel9gmGgCCh8enmBdXyAoE6CwVCeL3eZiODBOXnOlzcBHuaUwAH0CMQmIQFCC3qCAPQAKgJeLO2FUBFcADFiLIzoS8TjQWSWGkDGTYfDEcw2AA6HlY17/YheBzE0kUqmCC4AdiskoAIpcrNi3ozmUxWVcVSzMGyEYxWJgeVynmcTkwFAozh5BOjImQzuy9dyedh6GxBJjAs83gKhQQRWSGOhKbJYVaWktiLCXZg3QQFIaQZ7QSZpaCzun7THVeq4brOQaeVFMAB3aOxj1e14Zs5eLJGM4AWU86B%2BsstshtCVhRdLrsYccNpGJffdCaTgUV7zlCuTb3xhLOymImBoqhphPpyqzWp1HP1Q6yAC9kQQ%2BWhIZg0n6lyu8GvLm3UV5tRPZ695wTLUw0govPR1wSm6vJqaovrme5OkaSbek%2BwpuN%2Bv70DOSrvrSZwAEoxqgABumAACq6hatJASBOYOvmY6Vj6wqYSwOH4YRUoyvKr4oR%2BRIWGa3zwUoAF0gy26gbCTA3KghoAJJ8tRfq0fRBGIh6bj/OgIAgBEWCqEiSgAI7PhesLiZRfIppO1akdqbzVrCabVhmOI4mcADq3y1t8JgAGwaDeq4GU8CaefaqBnIwPgJKBFyecGgh4a0wCYHGHkaEalm2em3l3r5nqGlFBAxcQcVxqQNmpfZTnfOgVJpPaCDfJEpJnLFoWCMlVapfaeb7sVtnkfqhqccgADWeUFZiKXpny1b/GqeDICaAj/Jg2FiA1olnHg6D3LQEDrF1AC0xrwT%2Bf4Wa141XF11Y5cN8XxjyRVjbZ/VDbFN0Jg9iaTl15m7o6BZcq8wDLjG/YVl1tYRMAjbNq2ZxYCcDoQOtm2wgDQPlpR207axU4sZ9W5MjuVwiUQElDsTYk8gAUlJsEyVhuHyZginKap6mYJpOl6XsBmUQeAKs4G7NaZgumMNzVyU0Z0FTqZGbfe950PdWpXOTWvGJelqiZdg/kaIFwUMKFaJkhFGhXS9CWeS1bWLsuPlXJJWU8ub%2BU3fdp22Sr5WVdVtXs36jWxtbbU9Ww7s217atuZ5muwtTTtGgFRBnMAQVMMgVLmr7sN4FN%2BlK3ZDnxAQxaYIw9rFkFUwjcHqWxxLfk8g263oPQ12FRdhdlbDPsEDVZx1QH%2BVNQQtfdR1Yed%2Bmod/U97ejR7E0ZlNjizeeC1LbQK3J0jW07Q9%2B2el%2BR1IQrbhT2cLs13dF/N4CbcW7dXLh21c%2BP29i/jnjHvfRqE9/ajMu5Yl7pnBvWJstAWwPlhg0WgCNd4o0BkAkGGN1hY0%2BtObGuI0KYWQDsLIuEvy8WIgJAmQkiaiVJtvCmXJKZDhnoaAA8n3BIQgRZcyZjTQUNF6YMQUrCFmalBYc3YWLMChleSej5ipIRGlhai30hLXmZxmE1WIGwhRewn7GVTA9eWn9z4F3TJHVypt65uEdjrXkScgohTYMbaOZtxS5UfolMe1ZzGWOys4%2BeL8SoOVVhVVAVUWED39g1YeQcL4zz8Z7AJLl1YxzthlBuCdEr61Tg1DOmQLShPwHnbmRizilWLqXcuJcq7vwvuY%2BOViuR31bvhR%2BsTlbxJ7sE7Og8InABHu4uW/8Wn9IgrPdOz1XYJQVpWSaLRV5zQYBvZa5M1obT3ntY0JIAxBmcV1ayRSZ4YV4YzRSqjWGiIvNo6WNtVLmShpA2Eb9xkXKmRmEBZxrmCRNhA9AOzFYe0uj49%2BN8ikNIfo8j%2BVkv5vjMh8sCDCeSAOBu6V5YDIZfJhnDOBupEYrMQWjFBkjsCY2QjjYl2DaTkvJUBdiZw8JMzjHxKlFKmWATfB8SEXwfjXFuA8Yy%2BNsxgSWZY0E0koYMFQEQBgjxsTSjOCvGacyFqqDSMQahZxN7PiYpJTBFgpS4zfL/cCv0jIwW4X6Q6iEXzfwNXC/6%2BVQZvBRY2eKTAqBeEhP0GGskGaEWTL86ZMiWBMAGsiNmIjNFgS4E8WJgjA3BqRKG%2BRHDYSBF2lwVNUauoxqDSG4RiaxGwn8LtFNkbpZ8lUl8lGdqpbf0dUILwaQiiYHQJhRCfpoHmuOrCJsYqJWPCuBoKNorxUCD7W4Mwg7u3DslbCSQiZnhYIdXWSGLa/xtsCG2BszrXXupyF2gQU7R0DqkUO3tsJ03Hsnaeq446L37qvW4ItE670jpnU%2BntL6ri7X8HO0lMFprICRGaJQbQICCIUPqQDik60NsyE2ldcChzwdPJ6dBHBNi0E4P4XgfgOBaFIKgTg59LDWFldsXYblwQ8FIAQTQaHNgDQCGYLkkozCSGSMkfwGgACc/gzAaHcskYIGGOCSF4CwCQGgNCkBw3hgjHBeAKBAFJmjuG0OkDgLAGAiAQDbAIGkG45BKBoCZHQBIUR9ScFUMkdyu13KSBTsgWaUguRmF4E2wgJB1p6H4IIEQYh2BSBkIIRQKh1CqdILoOYxY0RpE4DwdDmHsO0fw5wRhNx9N%2BlQFQM4VmbN2Yc05yQLmzgQA8CZ%2BgKrDhcHWLwFTWhNgQCQMZtIpmyAUAgM11rIBgBSDMHwOgZJiCKYgLEZLsQIitHuHF3g43mDEHuIw2I2gGgqao8Z2MjCGC0Cm%2BFrAsQvDAHgrQWginuC8CwIGow4hdt4GXI0XCp28PswaDcfYVGIhkmE3hu4sQ0TzY8FgZLqI8DibO6QXCxBYiwdlDGQwwA7hGFo5sKgBhgAKAAGp4BLIwjk02gvCFEOIQLPn5BKDUMlyL%2Bg4coGsNYfQeBYiKcgJsYJ/RTu7WUg%2BUwxHLB8d4PRYgxB1pM3gJseojRnAQFcDMPwcwwhLAqFUQomRsgCBl8r4oOQRiK9WD0PoTQFjq7mOL/ogw2ja7GNUeYQwjfW/Nwry3Egxdkb2E7/QiXpPJbkzl6ztn7PAEc2cZzZgSu4A85VyjNXqNI82DVJgWBEjbVIAxyQgQuRccCJKSQGhJCsc8hofw7kuPu5E2JkAgQuBcnclwATXHkg1/8JILg/gM/uU9%2BFuTCmlPR9Uw1rTjWdPpYM%2B1zrFXzNsE4K0Fg2FJS7SYCaAw9YuBca5JXp7%2BAiBC5UnMEnfmifSBJyF8n4XdB9ei9%2BabCWOBYfb7J1LQ/MvZanzPufC%2B4dB5X2vkrZWWsVYuOCMwKPOrNTAfUfBIQzDrVAcrcYZ/WfU0IwZfLgKTGgOBBIYbUbcLWbSbPHLA%2BbRbZbBwPHdbfsTbbbZLPbA7I7E7PHC7OHa7PDfAO7RwB7ZLZ7PBMkPHD7XoZLH7P7e4AHfYPDYHUHKjCHKHJQGHS7eHCGJHPgVHDHLHYsHHRgPHXfQnALA/WQI/MLPDU/KnRHbnKwSwenRnUXfDK8HIdnTnddQw6wPnfDCHLfEXZnPXFbHIFwQMW3eXcoR3OYIoVXXITwToDXAIi3FYK3E3A3G3II2YVwiXAYBYMIpXY3Q3GI2XO3RYHw8It3BQF3ALK/G/GTfnTgCJafWfefeAyGZfVfLkPWCAMPTff/CvIAmPUgOPBPSgK/UTUgcTQIFfHPSUFvSUSUQIXPSQOzOYIolLeTWwbvYAvveAAfXTDLCAsA4gcffYKffLFgBQbCWabCaorUf4NzDfTzbffHPfDQ/HbQincvUgc/WLM7AopLDve/PTG4M4LLUo7Y3Y/Yw40Cf4b/KA3/BIJowIFo3vdTJrYE1rVYmEirEAPYhtJEA4rjJEI4ggQDYgFgOzfrVAobSgDAvDXAnbKjEk/AlbIgqAjbLbHbBgzAfbQ7MQagsHWgq7QQ87W7Nwlg8LNg17TgwQbg8LXgybAQoHIXEQ3gMQ6HWHK7GQyElHJgNHTHbHXHMHNQ/zCQTQ4LMnHQnQO4xfYwWnYwn7JnJPVnSwzgHEFmWw3nWTRw4XM0sXXoNwyXaXNIvQbw5YZI9IFXfoW3fw/oJI3XSIgQM3doD043F0%2BI8M4MiI1I/IdIqae3LI5I53HYV3arEvQor3EorY%2BzHYvYtVf4skQE%2Bo04iPZo2rVo9o8YJPYTbo8TMwFfQIQIfwTjJvSTVsyUATW/YomYxTZTVolPSUFzQYmoSQLjAYjPLgSUEvQIF4u/GY%2BYq/VzPs6Y6s3vTYCHLIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/remove_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/remove_types.test.hpp)
