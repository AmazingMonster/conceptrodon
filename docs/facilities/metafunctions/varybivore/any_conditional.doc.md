<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyConditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-any-conditional">To Index</a></p>

## Description

`Varybivore::AnyConditional` accepts two variables and returns several functions.
Check out **Examples** for more details.
Overall, `AnyConditional` yields one of the two variables according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...||Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
AnyConditional
 :: auto...
 -> auto...
 -> auto
```

```Haskell
AnyConditional
 :: auto...
 -> typename...
 -> auto
```

```Haskell
AnyConditional
 :: auto... 
 -> template<typename...> class...
 -> typename...
 -> auto
```

```Haskell
AnyConditional
 :: auto... 
 -> template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AnyConditional
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

We will see four examples that present different use cases of `Varybivore::AnyConditional`:

```C++
using Select = AnyConditional<1, 0>;
```

- The template member `Page` of `Select` is a function that returns `1` if any argument can be evaluated as `true`.
Otherwise, it returns `0`.

```C++
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 1);
static_assert(Select::Page<0, 0>::value == 0);
```

- The template member `Mold` of `Select` is a function that returns `1` if the value result of any of its arguments can be evaluated as `true`.
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
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >::value == 0
);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies any of the predicates;
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
static_assert(Metafunction<int>::value == 1);
static_assert(Metafunction<void>::value == 1);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Metafunction<double>::value == 0);
static_assert(Select::Road<>::Mold<>::value == 0);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `1` if the argument list satisfies any of the predicates;
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
static_assert(Metafunction_1<1>::value == 1);
static_assert(Metafunction_1<-1>::value == 1);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Metafunction_1<nullptr>::value == 0);
static_assert(Select::Rail<>::Page<>::value == 0);
```

## Implementation

The implementation is straightforward.

```C++
template<auto IfTrue, auto IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail<I>
    { static constexpr auto value {IfTrue}; };

    template<auto I>
    requires (!I)
    struct Detail<I>
    { static constexpr auto value {IfFalse}; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {Detail<(...||static_cast<bool>(Args))>::value};

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { Detail<(...||static_cast<bool>(Elements::value))>::value };

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;

    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQSAOwAnKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJXCm2mPalDEIETMQEeT5%2BgfWNOS1tBOVRsfFJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iI8qAAVYheTCkO7wxEPKgAMTEShh2BBkzRDjuVwYAE8PAx8E0xCCTIkrNc7hy7mCIR9MDC4QjUMSQZy7mSvBSACKYVp0O4sqyJSUwtnA9mc7kvXn87GoR7C9Uc4iYACOXjwxoU%2BsNYoI5IId2lsto/IeBquooVto%2BeGQdzQDEmmFUaWIWMFdwAbmJ0fLWbjUeiWcroRY4ynVSKNeCtVDYbr9dCSTbjWaLZgrRAwGAHissxzxVKZUw6K73Z7Wd7HH6A0GQ2GC9HvJg4xZcQTaESlSr0yrmTa/vs7somMAR9961yc5C%2BfnBQA6Q9XYDG8GMAgKducrxZIzL1cjmGSx3N1uwiCH/cstzf%2BbdgD6oiTPyMSoJ4xIQMep5vBeKx1kWc7XJumo7jqB5HsQwCXghNp/r6/oCH2obhoiK5rv%2Bkajk6LYuu%2Bn7fr%2BrQAUBBAgWBtHYJBmEKHBxIgCAQ5JtOqbzh6nKLncACynjoF85zIdu2qwgQ1JpIwrCYJ%2B2CvOe2HFmJHI3uEwBSTJ8rQs%2B1Fvm4H6HgxiRuHhyCAUwwGwqB4FFhA2lnoICj8YJmC8QhIlITaKFKW4KlqcwbBaTpflXg2TH4b2YL9iRerSbQ6AUaOL7Ovytlfg5jE%2Bs5LFsZ5nE%2BTB/kCTGQXwdgAWNbOoVqgZW48nmUWKb10XqXFdlFv6BgKAon7KMa%2BCiGCembo2DrTagRAAEqoEw6Cbgqm6ejaooRQNqlDZph61bpSWincRl3tlslPgVNFFfRpUOU5LluW4HkcRA02YLNvLYW4F1%2BfRRatcOwUkh1e3Zj1u5RSdsVnfuoMXldopOQRgbpcRBb3XlcMcl6Vm0TZr0/u9KUVa5rHuexEH/YD838ujk0jS1DVQ81kOxsmiFdQLsMLscdwbVtcmHECh39YjR3y8jGng9gY2uRz%2B7M76QNXbdJkSw9FnLsQq2oAb/Ja3NFYq4LCkI/yCtoUQKtqxNU0zdrrM4V1S3G6ba3PTau0HfDuaI7qn4AGptHgTAxPQC0h4Zt4mWRj5G2TL12W9jk0599PfYzXmWzrsLR8Qsfx9bnN801wodddjfykn3Vh07qBRzHccJ5jnLY2lwb4xGadEy3pOvuTxX2bn5X51Vv0l17bjl5XCcq7X0O1%2B1qodhmO2i/cAdyhu4Vyw7Z97s7nOuxri8VrrKfizR5nPit63PbCd8a/XmbCZmvwAkASfG4Ys8QWkmHcbAqhWAvHXPJABQCgFAhBBJIQDRMAUmAXrO4aDGgv0pDSOkDIchMlhEEO4Ggf6iQksiCsDpgEfXVvEAgEBcEYIIPxNO/JyFmD4tzfmFlHpcHgqqRhE1mGsPQQ4ThD5%2BQaExLwiG/D04pmfMIwWYilDtEkY0GRa45GYkoUowKL9HoaBEdQxBiCgSoIwQIWSUCYH0ClvsGxVikGiXMNCcIyBvBYHMkjNS/47Qtgxt7UkecmHaM3Gw6RIB7o7VhMTW06B%2BLhDBCeMQgFCKtEEPydJmIuDEkxMkyYqSQDpMwJk2g2TcaGALgUu4ij9KemMW1J8QiQQWLClcTREiYlSI4fEmSiSfwtzKWkwQVTiBZLSvU/JghDHFObl1LGBBymVOqbU%2BYeTYSNOaYkrmJiOlGyKdcbpnU%2BnRJtLEoZCSg5JPGesyZGSZk1LmbstwjSjHYBKU8jZUytkfIaYsihV0%2BHHMEUbSh5zbYIPcYCFBYtkQIAtA46BEI4HSyRQixFPSJKR1QHgdADxBAuKBL7QlxLSX03/iA%2B4VL0C0KDGGYBjtlJK2Gl%2Bb2lKiVMroWMO4aQvDx3whMkAVBCSYGCSdUcws6Xsp/Dyu0EoHSMuZWCYg/JIx8r4kKkVtAxXPJACq6Vg05V/1Eoq90vLiUaviPyRlNK9XCtFX6cVpqZVqQtXvfFYsaX2tZfA0EF9AmnRttcX2AaBUJH1W6lJ/FJWTjNbK3alqenWuVfaR4ghA0LPpi1ONhr3XGs9eatNvrOqZv0lG3NMbHV8udRDItRrylltTayeVlj7iSWbFQLwDAHA5HJSCRVg0UafiuNxd02De2tH7YOz4j1bkgn4ubMufLA2YmjSy90/EEmwinVhG2It6WHDuBqq0DDIniO0XOpgC6h0CHzRC9pUK1EXKuSw%2B9j6mjat1W04cpjTmfpvVo79faB1PoYA26luyjlvtUXcdRHUv0QB/VBv9sJ0AbCrq%2BoDJznzmI0WBiRty12bW2kkpRB6lUIYI%2B%2BihFycW4tOG4%2B4eINjtAQJAjFsCR3wtY8AljS5IgCGKNkSMmBA0CZDfbS%2BHdOYROzWJhgEnHBScDSAFtJbylJqUF6x8nb01VtDQWN03tSzmktHcCADwAlmLuHWSNKqKSqfU3gTT9bYQWcLa64tCaTVohTd6itcK5NtwUxG3prmHSqYiMAH0XmWXaf862xNUrDM%2BvC4q8z7orPlkrBoBzRtazKdVXceLVSkvSe824XzqWDXpaC%2BiLLYXT0SQw4u4dbKzPoX3EexOVxZ2Qe6wIf8XB8EruuGuj%2Bbh3OZEk7VllmIquJY08tzVe6QBcMPdxE9dKaF0KvcGtDXXoMTe4fhgRSGUOiNI3e0bF2imwgALQvfozdoRoHZ5RIg/OzDORLuwh%2BVvQjyGfsAT%2B%2Bhp7TRgduAYF4WgtA0h2muyosxkPfT/mh%2BRkAR9yZ8N23RsHjHiOpg4GsWgnB/C8D8BwLQpBUCcB/JYawYouPbHlGYaEPBSAcIZ5TtYABrAIkh9waAABxmDMMkZIXB/BS8l7URI0hqccEkLwFgEgNDyPp4z5nHBeD%2BXkQLrQaw4CwBgIgEAGwCDCoIOQSgaBnh0HiJEDSnBVCS4AGyvZ95IO4wBkB%2BikPuMwvAAaEBIMSvQ/BBAiDEOwKQMhBCKBUOoQXpBdBBAAO4zLSJwHgVOad080LwQ3AB5BEDu7ioCoHcb3fuA9B5D8h8XZhbMeFd/QMMXjhG8DN5T0gEAkAu7SG7sgFAIDj8nyAYAUgzB8DoJq/yEAYjl9IDEcIbRqRF94Nv5gxBqSV5iNodh%2B/SAu5gpXhgtA99Z6wDELwwA4TI/8twXgWAWCGGAOIR/5YQ6UmH%2BjOwYGCCIOwfOlS6ujOhqMQMyx%2BHgWAm%2BdoeA2un%2BpAUmxAoESg0oP%2BRghqRg5eawVABgWEkceAmAueleMUl%2B8ewgog4gKe9B6eagm%2BOe%2Bgv%2BKA1g1g%2BgeAMQ/kkAawqAqOOQH%2Br2ZST4pgbOlgZgBuWBFcWAghEAawdg7COQLg9IMwfgQQoQ4QIwVQYwRQi2TQ2hegHmZQ%2BhSwRhvQ6hAgAw0wngXQegah0GDhQwVhowNQtgUwHQThBQQQ8w7QiwXhEgqhnOyeJeHAtOpA%2BuFenAjevu/ugeweoeHetmuA0efePOA%2B/OxBawCAmAW0YwKhpAoukg0I%2B4yQ0IquGgkgZgkgPuuu/gPuqQ6umupA2uvO%2B4PuXAPukuyQyuPu/gkgCu1RPusRm%2BhuxuIApuxBI%2B1uo%2BtuNeCITuM%2BqAPe7unuHAbQLAkYiQr2TAasd4XAyQ%2B4XAEukeDIMeqSQQ9BieTB0gLBSgbBWeugS%2B%2BeTAhen%2BURMRcRTOnA1e9uCIdeDeTeyRxxJkpx5xEuXeGxE%2Bve3O0IZgKwg%2B8xSxs%2BveaxmJYwviv%2BpxXA8iNAtAq%2BlAG%2BWeh%2Bu%2Bl%2BlJx%2Bp%2B5%2B0iGB1%2B54t%2B9%2Bm%2BT%2BL%2Bb%2Bk4l%2B3%2Bv%2B/%2BjO%2BAxoQBFYm%2BYByAEBl%2B0Bm%2BcBCBtIGAOwjOqB6BfOWBOBmAeBvJxk8xpBq4CgFBVBNBjAdBsgDxyeTxsgrBmejO7xnBRB0hVglgfBAh8AwhohhEnAEh6yUhPBsh8h8QihwpQhth0Gmh7g/hOhwQ9IIRhh3hFhuQYZ5hJhOQUZywgRgy/QvhZhqZfQ9hvhyZNhQRfh%2BQ4ZBZeZNQ4Rmw2wYR%2BgpekxWehuiRzegeeJJxZxFxxW3k1x2RvOqJeRgucEpAhRxRCQpR7RWuIA0IZxdRiQ/gyQiQiQ0I9RjRoxtZBunAMxcxfZCx8ASxduDu2J8Jk%2BHubAnAuxLeLACgkYfokY0JO4kwVxWRsedxxpjBppqe8gLxlpOg45pAnx3xxe1Z0RZedZgJKxDo9ejeZ5F5V5N5QMDoEA3eCJ8QSJ0IPZQ%2BFuY%2BB5WJ0%2BOJCQl5aQaQFEpx/4t5BA/4qgAey%2BJJ8Qa%2B5JjONJD%2BfO9FdJF%2BjJGxN%2Bd%2BD%2B/JmAz%2Br%2BYgXJGBPJBB8pX%2BgBG2IBkeqg4BYIEpUyMBvA0pu%2BSBwl/OFcSpvAKpmQap4IGpRBm52p5BlB1BtBGB9xL5EgZpaeH57B35Bgtp3pNgcByhLpTQH%2BuwEydp1gchFeChxKAZpRrhTQIZmZEZ6ApZCZJQOQwVsZYVWZdhzQGZ8ZsVbhuZnh0ZLhCVRZ6VCwqVKZ5ZWwkRAFfxUxCR5Fge55l5UYMF80cFmRRAXZuRaFBRRRWAw5URHR2usu%2B40I0I/giuoxuu3ViQ/RK58RRutgsxvZ5uIuIAkg/gVRKuuukukg8uXA0uZgEx6u0IQFq5Y1jVAFEeI1AJu1%2BRmB1FGhkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/any_conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/any_conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/any_conditional.test.hpp)
