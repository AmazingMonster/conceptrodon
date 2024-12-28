<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Disjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-disjunction">To Index</a></p>

## Description

`Pagelivore::Disjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies any of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... || Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Disjunction
 :: template<auto...> class... 
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct Disjunction
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Disjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (10 < I)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<auto...>
struct Pred_2
{ static constexpr bool value {false}; };

template<auto I>
requires (I % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<-1>::value);
static_assert(Metafunction<2>::value);
static_assert(! Metafunction<5>::value);
static_assert(Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `false`.
static_assert(! Disjunction<>::Page<1, 2, 3>::value);
```

## Implementation

We will implement `Disjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `||` is `false`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... || Predicates&lt;Variables...&gt;::value
-> false || ... || Predicates&lt;Variables...&gt;::value
-> (...((
       false
    || Predicate<sub>0</sub>&lt;Variables...&gt;::value)
    || Predicate<sub>1</sub>&lt;Variables...&gt;::value)
    || ...
    || Predicate<sub>Last-1</sub>&lt;Variables...&gt;::value)
    || Predicate<sub>Last</sub>&lt;Variables...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `||` is commutative.

Here's the entire implementation:

```C++
template<template<auto...> class...Predicates>
struct Disjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {(...||Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAbACcpAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoW4mF4iAA6dFQ7A3ZAGBQKdGo5TETD4UQghSYoHjYheBw3AAieAU2i8DAc2SBJgA7FZLjd%2BTdYU94YjkWj0QA1Fp4JjRegUyHYIECm7U2kEG5E1BEZRMYAIvkC7m8i4qlWzRzIbECcaYVSpYg3aKoTw3ABuYi8BtNZv5xogBO5biDRJJeDJmAVbilxBlcsjgcVIBAHu8mCW3PpUJNKsz2eVRsN/KF4IR0LFqAJMbj8spRZuXkyRk1eswNyh9M1xG1qF1%2BsR1dl8sTSshJrzY853z%2BvwBP12N2wqlYTzbnyB85npynV0OXZJAH0NB9t99tjcAEqYAjrBgKQU0tt4KiChBtlrAHyMDVMm7AYnwo6BAIIYNxcBoqJAiWIrliilYYoqVIEDSdKhugR6cjyqrNJa1p3iC9qOs6rqpl67Y8lQYhKBOFjkVmk6XFBoLChCsFEPcdYXMSACOXh4MS94QOB7bQvcGaXGqqHEuhGiIncnHGthbzhnhtqEU6Lq0O6nptsayFejRdH5ox063GhB5cCe%2BxzueV43sQd4PmRz6vu%2BxCfi8P73vK97AaBEFMXCrFInBI5IShGrmVwmG0RaKloPhdoOhpJE6eRFiUbQ1FcvRtE0Tu0HBRWHGIZcPF8QJNwQHcIluDcGjiRckmRdJFlyQpWFxVaCVqclxFaaRuk8vpCI5dmRkMYCpn7Pu6FmFZuw2Ze163r5j43C5wFuR534bfemBuowkGXIVZYheKkGlU1%2BlSYeZgxUpuE9QRfWadpabpZl2W5RN44ncxpainBJVKmVmC8fxkZVTV5j%2BDc80dh29WNc1s0Hvd0LyVdildapL1EW9g3pSNhn5SZu63AAsteTBUKy7ICAtAKnUDF1ccACqgxcjZhMANzU80dNsu8SOMsy9MNIi5kaKQaNcLL5kY1zyZ9md7P4gho5/RTM0ACqRgQ97rhJOHhgeTB4nEBAQALtMSxy0IALTRUmKY6Rmk1deblutDbNNCwzDCIkryaDR7JpexbSi%2B2AYD8/79sCIi/iYqH7vGddynIN70fW7bAeS07Idu2m4c7ts553C%2BDCoDcDphhGe1192bp4Fg6CkBu55be9zn3mIADuTAAJ73iYCQaF9CIT8dmeWjnVsQLHDJMiywsO8Gruq4i8vw7LkKpyXXrhxwKy0Jw/i8H4HBaKQqCcMGljWKqawbLpZiQjwpAEJop8rAA1gUVEGgAAcZgzBJCSFwfwoCQFcC5FyaQ58OCSF4CwCQGgZbX1vvfDgvAFAgBlj/G%2Bp9SBwFgDARAIA1gEFSCicglA0CPDoHECIrAtiqBAQkR2CRJB/mQFaKQqIzC8DDEQWM6A9D8EECIMQ7ApAyEEIoFQ6gSGkF0PLAexAmCpE4DwM%2BF8r6/zvpwAA8iiOhGpUAvk4dw3h/DBGSGEVVDwzD6COnMJ/JYvBiFaBWBAJATDUgsLIBQCAQSQkgGAFIMwfA6AgmIAQiA0RjHRDCC0YeejeBpOYMQYepjojaEwA4LJpAmGeVMQwWgmS1FYGiF4YASJaBZVKVgFghhgDiFqZDdkh0CFqLtMUlEWwv5hBBMg2%2BtA8DRG0XkjwWBjHITwOg7gvBDrEGdEoekoIOlTKML/FYVADAcwlHgTAA9TGpEYKU6RwhRDiAUbc5RahjEaP0B0lA1hrD6GmQQyAKxUCpAaP0x24x0AdlME/SwZgcHrIkZGeAKw7DFIaC4Bg7hPAdD0CEMIQxKgjHlkULIAgph%2BEJRkYlDB5jDHiPLZFgc%2BiTExfkOldQUW9AmAMXFCwCW2E5aSvQsxWjUvxbSpFr9NgSAMRwS%2BpBsG8FwTcWxPC%2BHAAEWBJx80IC4EICQdsH8uDeO/gclYb4mBYHiBAABIBJCQlREkSEiCNCSDMJICeGh/A1GQag0g6DP6ogSFwBIICkhwISIEaBDqEhyuMbg/BhDjUkP8ZQgJ1CLH0LCRE9xbC2CcBaCwN0XJHZMGxAYZsXAkioi4MA0R%2BBxFtykbIWRDzpBPKUC8tRuhYlaJ0Vk6Vsr5UmI4OY2hKIbjWKVVwlVpaOlgUrdW48EBXHBPcfqyEZgjW%2BNIamrNcQGHhNQG4kYOIOkVvAnE2gCSkkpLUTkjJpS715IKUUkpqyymHoqVUmpt86kNKaS0t9bTdlbB/T0xwfTjGDOQMM0pYy6jGKmTMjJ8yQM%2BNjCsr%2B6zNmYG2e0owezQBJr4MchQpzzmXOuW%2B25zb5GttkM81Rt8u3vP2ZCqwlgfnRD%2BVau%2BQLsggrBRCr50LYVxHhdxpFbLA5ooxXkMlpAcXlBpXoIlDQBXkuKNkEVixWU9AEIytozL5P0oaAZ7TvKhWGbk4Kzl5mxWrHWJKw1%2BhDExrUYq5V9iT3lvncAqqOrxFrsNT4k1pAzUWsoNKn1frK3Oq5P4JICDIQurdZIeWg6422ATVu5N8BU00Msfu3dxAc1bHzfYlgCg3RWjdBW1EpZxi1t1RIxtMj7m0cUfIdtjGdAgEhKQHtujVn9qMe5sx6arE2Iq1VmrdWGsaiXYeldcQ12Qk3QcshgSlshKK9t9xKZkCpFSAeWrSQDzzYPKoXhF6r2UBvbfR9NSv6PefSi0p5TvyVOqcY39jSxAAa/kB/DqHSD4GJL0hFAzVBDJBLBwQ8G1GIdmcPFDiz0OlKwxkHDOz8O8w20cvUpGzkXKudfL%2B1H2sSDo0o7rry%2BsseMMJmwiGJO8eBZwbYYLPlQosDChVcK24Iv%2Bd0dlzgICuHUwp9FdmVMUrU0Z2XmnSjcuU7p0XjR%2BUK7Vwy2zKvRU2f6JLyzMvnMKAlfIkbbmcGcCVdN6r7o5vwnGP5uterPHBcTX401mBzUjB496tBIAIGokhJCfwMC0uYND1yYNVuFWcHjUQ0LgDJD%2BHtfArkmCQGSCgVwMBZho3IMhKN63eDPd/xcxwERceh0haTSsdZmRnCSCAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/disjunction/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/disjunction.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/disjunction.test.hpp)
