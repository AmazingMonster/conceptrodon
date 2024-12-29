<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-conditional">To Index</a></p>

## Description

`Varybivore::Conditional` accepts two variables and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two variables according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...&&Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Conditional
 :: auto...
 -> auto...
 -> auto
```

```Haskell
Conditional
 :: auto...
 -> typename...
 -> auto
```

```Haskell
Conditional
 :: auto... 
 -> template<typename...> class...
 -> typename...
 -> auto
```

```Haskell
Conditional
 :: auto... 
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct Conditional
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<typename...>
    alias Mold
    {
        static constexpr auto value
        {RESULT};
    };

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold
        {
            static constexpr auto value
            {RESULT};
        };
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    };
};
```

## Examples

We will see four examples that present different use cases of `Varybivore::Conditional`:

```C++
using Select = Conditional<1, 0>;
```

- The template member `Page` of `Select` is a function that returns `1` if all arguments can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 0);
```

- The template member `Mold` of `Select` is a function that returns `1` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >::value == 0
);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
/**** VoidInt ****/
struct VoidInt;

/**** VoidTester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int>::value == 0);
static_assert(Metafunction<void>::value == 0);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Select::Road<>::Mold<>::value == 1);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies all of the predicates;
otherwise, the function returns `0`.

```C++
/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction_1<-1>::value == 0);
static_assert(Metafunction_1<1>::value == 0);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Select::Rail<>::Page<>::value == 1);
```

## Implementation

The implementation is straightforward.

```C++
template<auto IfTrue, auto IfFalse>
struct Conditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail <I>
    { static constexpr auto value {IfTrue}; };

    template<auto I>
    requires (!I)
    struct Detail <I>
    { static constexpr auto value {IfFalse}; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...&&static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {Detail<(...&&static_cast<bool>(Args))>::value};

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...&&static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { Detail<(...&&static_cast<bool>(Elements::value))>::value };

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSAGwAHKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iI8qAAVYheTCkO7wxEPKgAMTEShh2BBkzRDjuHgY%2BCaYhBJgA7FZrndWXcwRCPpgYXCEahiSC2XcyV4KQARTCtOh3RlWBlimHM4Estkcl5cnnY1CPAUq1nETAARy8eANCh1euFBHJBDuEqltBlsIeuquQtlVo%2BeGQdzQDEmmFUaWIWL5dwAbmJ0TKmbjUejGQroRYY0mlYLVeD1VDYVqddCSZaDcbTZhzRAwGAHisM6yReLJUxpTyXQXazGU/NHD6/QGgyG85HvJgO7iCbQifLFanFfTLX99ndlExgCPvu21ZDubm%2BQA6fdXYAG8GMAgKV1CrxZIxLlcjmFiu2Nug8iD73fmRKfrvegD6okmHkYlQTxiQgQ9jzeM8VhrNtkznN1M05HNeSId8rmIYBzzbS0fx7AQ%2B2DUNEWXVdf3DDt7SbWhX3fT9v1abt/yYQDYWA0CC3AzCFBg4kQBAIcEyneDrnbBc7gAWU8dAvnODcsy3HkCAATzSRhWEwd9sFeU9sMLRDWSvcJgEk6SnUfKiX1hN993osxEjw5jWLcdiaM47ST0EBR%2BMEzBeLg9NLU3DVYRUtTmDYLSdK8i82Tw30CLBftiO1KTaHQciOyfB1aNs%2ByGK9ZAnIIICQLc7AIA8qDvIEqM/Ng7AfLqmcROVAz2QUkK3GClCwvUyLbILX0DAUBR32UA18FEME9PbetbQm1AiAAJVQJh0HbWV23dS0hR67dutU/rNP3KrdNioVDOvEy0pkh9suo3KP3y%2BzHIAkq2LKsCJswKauWwtwzq8uiCya4d/JJVrtqQ7MDr6iKTt3IGzwuy74t7JKiLzW7Muh1kPUsty3Bs56v1exi/3e0qOIqn6/pmnlkbGwbGtq8GGrB6NE1nS1uah%2BdjjuVb1tkw4gT2zresluGjoRkHsGGljmd3OnvX%2B1GjJvYW7uhR9FpWtaNthVXprLeWefa%2BTkLh6XNT3FnFdG8bJrVhmcPa%2Bal2IJbUGWx7eaZPGOutu20P3AA1No8CYGJ6Fm3a2U1kzSPvXWHqs4m6JehyKaKqnPppiATfV2FI%2BIaPY7NlnOfqgVWsuhuZQT1l9tD1B3zLiu49RoV0cSwMsbDFPcebrLCaeuyc8K4rqfKouXdNgHO5juP5ZriGa5apV3WE7e2TEwW/eldcgtt0Kz9Q9uHeQEbleLt39Mva6heo8yvZ9o%2BifvquPwC%2Bld4QguAEwCgTiTxKaSYdxsCqFYC8NcclfjAKQWLQBgshANEwBSE%2BVwk53HQY0N%2BVIaQ5DpLCIIdwNB10CjcQWyIyy2mwY5JW8QCAQHwZggg/EU48nIWYPibMua63ulwWCSomGjRYWwjBDguF3h5BoTEfDQYCNTkmR8GhRGoOQUg0BaDMECBktA2B9BRb7F0dokBCFzDQnCDfLwWAnSHTUr%2Ba0TYUbu1JLnX8zD2gQHbOwmRIBbqbVhEHSY6B%2BLhDBEeMQ/5EqGA%2Bm4KJmIuDEkxGEggESQBRMwDE2gcT/StEEDyZJdwlGP33so3y5lhEgk0aJa44ilC%2BP8dIzhQTpIhLcBkrJOS8kFPmMU2EpTKEFnSaPcJkTBC5OILEjGCSSmCEUajfh1SHz3UodcepbUgEWOweJZECBTSGJgRCeBKDEF7MBFow4dxw6oDwOgB4ghTFAk9vcx5zyPrUPEh89AdCAwhmwa3UKssNLm0adaUUto/kArBAkO4aQvCx29FaLJVBCSYBcUdDsfNqEgu6e7d5Dz/n0PiDycMJK%2BKIuRbQVFkyQBQqxX1XFACGmggvq6Yljy4XktLiSr51KkUop9Aypl2K1KsrTDcxcXzeVAoQRykOoLwrgpZp4m0jxBDypADSkVaL%2BIYonMynFW02VtQJVyqFFI5VkuIIsj6jU9V0tFZk/i4qWVmuleyy1RLrW2ltYCnkfzBWg2dfSt1jK0QmslV6i2IJxISUbFQLwDAHA5FeSCAl8M1W7gwlhV0uCk2tBTWmz490AklWuPxbWwaSXysxIG%2BFrp%2BLBNhPm5WVCZV3DheaRhXifGsOLUwUt6aBAOtWc1dZacNEWyaZI4do6mgUqpVUqdQiZ3bPnb4xdqax0MDrZ8oZrM1kbsfCIudA6JG%2BMrTWw2PJ%2BFtsJSe9dai7gXv5jQq51zLm3LxBsdoCAoGnLgZm3937sEJsFpEAQxRsjhkwPKsDSrYZtwhVcT2MGGBwccAhnV4bXXosxRK%2B8gdzVZovnmVs%2BliwmjNHcCADxHEbLuDWSFmqsM4bwHhu1LYhW0ojVkj1pqyPeotZR%2B2v99KYYEBEYAXoeOAt1cKl1BqQBGqUCRqV8brgEqo66WjpZywaGY2nasGroV3Cw3JhTiHePOn4/qsV0atNxs/Ym5Ne7PjAok2HPN3FC3P13WWnIv4uBv0rSCGtj1YSccyPBuzgLMTWdybZ%2BVLaQDcPbdxc27naH0L7Yq7dQ7PMhYEGFnkABaVJa7hw1M3Ze6eg6IDBf3RVshk66vTvUVuq9zSSslq86FmrbhRkvq62e99vWmvXtYbekAn8H3KKy8%2Bze3WpuKg4GsWgnB/C8D8BwLQpBUCcG6ZYawwoAPbBlGYaEPBSCcMO1ttYABrAIkhdwaGSGYMwABOX7XB/BfeSFwBkDJpA7Y4JIXgLAJAaAUQdo7J2OC8G8gox7Wg1hwFgDARAIANgECRQQcglA0DPDoPESIGlOCqGSIkSriRJB3GAMgH0UhdxmF4L9QgJBHl6H4IIEQYh2BSBkIIRQKh1BPdILoIIAB3WZaROA8G27t/bmheDI4APIIiJ3cVAVA7i0/p4z5nrP30fbMAxjw5P6AhmsSI3gGOtukAgEgMnaQKdkAoBAD3XuQDACkGYPgdB4XeQgDEDXpAYjhDaMpZXvAY/MGIMpLXMRtAcIT6QMnUEtcMFoPH6XWAYheGAHCWgE4s9YBYIYYA4gi%2BlnTQh7y0vAyYIRDse7OTIdHbpTEWZKePBYCj9aPAsPuC8AQ8QYCSgJQ16MHSowGu1hUAMFhcOeBMBy61%2BFLPAvhCiHEKL/fEu1BR9l/oWvKBrDWH0HgGI3lIBrFQGkJoLfKvhIfKYc7lgzBI6n%2BXFgI/hAGsHYBwjkC4NSDMH4EEKEOECMFUGMEUPFk0NAXoFxmUPAUsEgb0OAQIAMNMJ4F0HoGAfugQUMFgaMDULYFMB0EQQUEEPMO0IsFQRIKAVdiLqrhwHtqQIjprpwEbnTgzkzizmzpbgxrgDzvbrdo7g9svmsAgJgOtGMCAaQG9pINCLuL9tCODhoJIGYJIIkPDv4IkL9voJwNDqQLDndruIkLUMkL9iDokP4JIIDtoYkLwVHsjqjiAOjsvq7rjm7vjrrgiCTr7qgLbpTtThwG0CwOGAyJVkwIrDeFwL9ruFwJ9lzjSLzhEkEPvkLkftICfkoGftLroMHgrkwErhPlwTwXwcdpwDroTgiProbsbsIckSZKkekZ9tbhEZ7nbjdtCGYCsE7v4UEX7nbmEZMWMDfLXqkVwAojQLQGHpQJHtLknnHlnpsSnmnhnjIhPtnhEbnvnoXkdsXqXuXpXocdXrXvXucY3rhmWFHm3sgB3lnt3lHn3gPspEPjsEdqPuPvdlPjPpgHPnccZP4aviuAoBvlvjvowHvrIAUSLkUbIKflLkduUZfkvt/lYJYHfg/vAM/q/jkO/p/rrHidYH/prgAY8s8U/rgfupAe4PQTAcENSCwYgdQRgbkGyegSgTkFycsIwW0v0LQWgaKX0PgbQcKTgUwXQfkOyQqXKTUOwZsNsGweYdwertLsjoISbkznMSkWkRkSZpVNkdIXdqMXIU9jBKQIocoQkKoZDpYdYWkXoQyP4L9mDtCPoYYa4Z4XqZwD4X4XaQEfAEEQTkTtMf0V7lTmwJwLEabiwAoOGD6OGN0VuJMFkVIXznkciYfqiWLvICUZiToCANCKQJUdUSrtqXUV4Y0SEbaAbkbimWmRmVmf9LaBADbgMfEEMdCDac7lju7nGVMT7jMQkOmWkGkORKkb%2BNmQQL%2BKoIziHisfEOHusUdjsYXvdruXsZnocTnqeHngXlHhcWXmINcfdrcQvv8bwPgAaE3s8a3qoO3mCB8dMj3rwN8XHn8SPuXECZPvEKCeCQvpCeGdCevpvtvrvocfkUWRIGieLmWefpWTicYDfgSX3sASSW/pwLsJMlSb/v/vEIAQyaoaQU0CyZKRyegKqQKSUDkHRbyYxVKXgc0BKfyRxWQbKZQdySQdxUqUJQsAJSKeqVsJwfWbqUjgIauUzqmemRGF2TND2ZIUQFabISOQoUoVgM6VwW6SAH9ruNCNCP4EDq4fDmZQyHUPUd4bYL4baZjq9iAJIP4FoaDgyPDskJIADlwN9vZNqdCLJfwSjs5c9tqZzkGXJeFTpaQFPlkM4JIEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/conditional.test.hpp)
