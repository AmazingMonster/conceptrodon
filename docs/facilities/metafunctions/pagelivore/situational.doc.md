<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Situational`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-situational">To Index</a></p>

## Description

`Pagelivore::Situational` accepts a list of predicates and returns a function.
When invoked, the function returns its first argument if the argument list satisfies all the predicates and returns its second argument if otherwise.

<pre><code>   Preds...
-> IfTrue, IfFalse, Others...
-> (...&&Preds&lt;IfTrue, IfFalse, Others...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Situational
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Situational
{
    template<auto, auto, auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto, auto, auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will create a function that returns its first argument if the sum of all its arguments is less than ten and returns its second argument if otherwise.

```C++
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<auto Initiator, auto...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator+...+Args) < 10};
};

template<auto...Args>
using Metafunction = Situational<SumLessThanTen>
::Page<Args...>;

static_assert(Metafunction<1, 2>::value == 1);
static_assert(Metafunction<10, 2>::value == 2);
```

## Implementation

We will implement `Situational` using partial template specialization, where we separate cases via constraints.

```C++
template<template<auto...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxHoADqgKhE4MHt6%2BcQlJAkEh4SxRMVy2mPaOAkIETMQEqT5%2BRXaYDskVVQQ5YZHRegqV1bXpDX3twZ353VwAlLaoXsTI7BwEmCyxBssmAMxuy6vrmFtuTF5EAHTnW9gA1MgGCgrnp8rEmPiiywqXJhoAgr3EXgcVyEhC8TDKzFo3x%2BJgA7FZflckVcAPQoq7PPAsKoATyuuzW4MwVwA7nRaFcBLQ8VEro0HK9ocjUeiSQhGFcGKg6bEmngxHgAF7g5JXPAKK5MABuTDoTAi9FOTORaKuAEkGJS5jcmEpSGKCGKJWzGMqkaqII9zAA2G3PV54d6YT7bNVUAAqAMw%2BrdADExHqrgB5Ajs4gPC6bbAgEAy7yYSZXTBxsEffHcqgBzBKxHIgn7Q7HIjqj1e/VF7l%2BrPlk6oR4hsMu7BmukEAFA56oIjKJjAA65pFwiytkXIG4CXqYVSxYiS2tXFPErYAERL/toSi2w7hy630JbqvdCHFV1ibX5FIUvOQF6FIoEpPJV1p9OW6AP6LwVCulouZlt/72m8RIum4bqel43prtWwahtEEZKlGMaLomJ5tpBOY/My%2BZEoW87gWWc7FlWG5QRW9ZweGXwDlcLwAI5eHgLwSr%2BSr/naLzAR8hwEZBPpUOugYNvBVpIbGYiQZMLb/IChqdt2vYHK6pZ8dBpH6sJ4aidcLZDiOjhjmgDCTtOs4VguElLpsq68Up26wrumwIjCNE4Rs2zkecPzAC8KyMAQTYtl4iRGBiilXCuGLEF2qA9n2hzeb5bCCAhXxOfurkrIS7lHLWjw/MQwCBTRvSjuOxnLKZRHcnFmAAPpSrp8JRTFtUJYVqViYuEUOXuvw7n1Lk/CiABUY3jRNk0otCo3jVc7rOgFVwTdNvyzZNG1jatQ2qiY1oaEIPgBM6ChHoYC0MHtGhGvi7Knpxjq4Wt6KhuCpLEmStAUme9zphF%2B0ggQqbJGIV2YW5Sm5cRDBJOCJA1mcXkddRfzoUCh0sMd9xnQwF37vC0mVAZ5UmTOz6oJ4Fnxk1FgQBqsNEMQ1hWpYBVFYmhxXFwGgDel/W9XzQ0Q3hiOnGzxU/MFwTAFcACymCVFQXgMM0D6RYDwMCKD2wY1jp0IOdppRtCMZtds4vaYN0KlQZdW6ko1QQPLivK6rl3bEUVxmJcyGWRF1mRVMg0246dv3NEBBOwrTBKyrEKHNz%2Bre11fsrpFZhSU5HDTLQnAAKy8H4HBaKQqCcG41jWHSszzEuZibDwpAEJo2fTAA1iAsIaKcmxmFwsKbJskhmBoAAcsIAJyj9IuccJIvAsBIGgaKQRcl2XHC8AoIAr83xfZ6QcCwDAiAgLMBCxCc5CUGgqx0NEoSsIsqij9aAC01qSFcwDIGOUinGYXgDpGZ4HQHofgggRBiHYFIGQghFAqHUPvUgugigkmIEwWInAeA53zoXFupdOBBhOJfQ0qBvwv3fp/b%2Bv8uaSAAT%2BDwd96CznMA3SYvA95aGmBAJAt9Yj3zIBQCA/DBEgGAFIMwfA6DLHDJQCIBCIjBFxNg3gSjmDEBxEGCI2gmh70brfZKBAgwMGpAQrAEQvDACOF9be3BeBYGxEYcQyD8AvGaFKZ0BCpxNBOIsRuwRlizxLrQPAEQMGaI8FgAhbYsSqNIJ44gEQEiYGXCsQwwBQlGBbtMKgBgioADU8CYBJEGXkRdG4QOEKIcQsCqkILUAQ1B%2BgMkoErpYfQYTt6QGmKgWIEI7Fv16O%2BayphLDWBHrwVAiTiCgK8T04opRkguAYO4TwdR/CrI6HkAoGREgQgGPUUg8R9nJG2V0Qoiy9EtGGIcnoJRrnlGGOc8YlzSr9HWYMWwzzRg7ImNMBQNcFgSFwRwAuq8CEbyuJQj%2BX8f5/3oWYH8uBCAkAivXKYnCcnTHZEwLAMQIDtxAJITYpwJ6bFhJIDQw9JD7Q0Hna0E99CcHnqQReDdTjWi4NaUeU9uV50kFwPO5LrQQuQRvLeO8m45MPifXhZ8SFX2EaIlhj82CcCqCwKUsI35MBuAYUKXAJ6nC4KcEuwCSCgPAbIKBtTpD1KUI05BugpHoMwao0F4K15TKIYqsh35NXat1fqjJXNjWmuuhAJhAiWHot7hw6V%2B8eF8NQMw6I18RGppjd0QNOrbgZKNYnGgtBZHbwgAo5B6iVH2NIFWzR2jdEOHiYY/yJizGuMwJY6xYgNzxMcRklxJc3HXM8XY81qhfHLHiYEkoBDQnhNxFExYJdYmLxrYk5JSg0lOMydLGVeTewKCKSUspjB4lVNtTA%2B1sgGlIJLi6lp2SxlWA6fO7phLS79OSIM4ZK5n0TPXjMuZ76AUPLdistZaQjmBF%2BRcvZWQUifKOSchDLzdkNDAxCVoHyoP3KWU8toaGJjfLaHcoYhHYOvJBTMOYwKpjMrBfg8VnBJTEC1TqvV%2BbDXhrNci/AjM42YsTdwnFmA8XdA/bPVl7LjXUthMK2EA8aWfyKN6whm9bBSq4QfI%2Bp9z6kIzSqh%2BT8NVseoSwBQUoxxSiNacfYvQgH8ctWAooF6alXrgfIR1d6dAgE2KQN1WD7GeqY%2BvX1F8TiUgDWZr%2BFmrMLls/Zw0Uas2CLjZsBN2nk0oFSywwzuXuhWdiLEBqRq6pJbtjF6RJb4LyMUcozR8S61aJ0Xo5tqajFtpxOYztVibG9prf25xy6HFMRHV45BPjkB%2BOnYIWdyD50RJxEumJsy12Nw3Sk7dA691Jr4Pko9xTSnlPPTa9zEhr3wO800vzj7jDtJsG%2B%2BAvSv0Tk4CiYZbTxmWEmaXIDWAQNXPAxAVwZHSAwdyHBooKGDlIfgxCIjbzMM3NI3DjD%2BGGDYZGJDqj5GcMbLx9jsY6GAVApgSFsVYWOCsZYOZyz1nEsgWSyigTbChNZdE%2BJgloLpMgDMMaweec87Uu5hoQesIeWU59Rp7eu9sWkA7vzzlsJR7/mtHnSeXAR7cqkbPTYoXpdYqTaCwBUv1NG5Ewk%2BCyzJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/situational.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/situational.test.hpp)
