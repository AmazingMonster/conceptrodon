<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Conditional`

## Description

Different inputs can lead to different metafunctions returned by `Typelivore::Conditional`.
Overall, `Typelivore::Conditional` yields a result according to the boolean evaluation of a condition. Check out **Example** for more details.
<pre><code>IfTrue, IfFalse&nbsp;->&nbsp;true&nbsp;->&nbsp;IfTrue</code></pre>
<pre><code>IfTrue, IfFalse&nbsp;->&nbsp;false&nbsp;->&nbsp;IfFalse</code></pre>
<pre><code>   IfTrue, IfFalse
->&nbsp;Predicate
->&nbsp;Arguments...
->&nbsp;Predicate&lt;Arguments...&gt;::value ?
   IfTrue : IfFalse</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Conditional :: typename... -> template<auto...>
```

```Haskell
Conditional :: typename... -> template<typename...>
```

```Haskell
Conditional ::   typename... 
              -> template<typename...> class...
              -> template<typename...>
```

```Haskell
Conditional ::   typename... 
              -> template<auto...> class...
              -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Conditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Example

We will see four examples that present different use cases of `Typelivore::Conditional`:

```C++
struct IfTrue;

struct IfFalse;

using Select = Conditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if the arguments can all be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfFalse
>);
```

- We can pass predicates to `Select::Road`. It returns a function such that when invoked, the function becomes `IfTrue` if the arguments satisfy all predicates;
otherwise, the function becomes `IfFalse`.

```C++
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(std::same_as<Metafunction<int>, IfFalse>);
static_assert(std::same_as<Metafunction<void>, IfFalse>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfTrue>);
```

- We can pass predicates to `Select::Rail`. It returns a function such that when invoked, the function becomes `IfTrue` if the arguments satisfy all predicates;
otherwise, the function becomes `IfFalse`.

```C++
template<auto...>
struct PositiveTester: public std::false_type {};

template<auto I>
requires (0 < I)
struct PositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<PositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(std::same_as<Metafunction_1<0>, IfFalse>);
static_assert(std::same_as<Metafunction_1<-1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfTrue>);
```

## Implementation

The implementation is straightforward. [Check out this test to see how it works.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSAKxBAA6oCoRODB7evnppGY4CYRHRLHEJXGYAnLaY9kUMQgRMxAQ5Pn6BdQ1Zza0EJVGx8UlBCi1tHXnjk4Phw%2BWjVdUAlLaoXsTI7BwEmCwpBvsmAMxuBACeKYysmADUAJJUACrEXpik91c3zGxPVAAYmIlGdsCYNABBCbvBz3DwMfCNMQQyEmADsVih9xx3wORyYJ3OTC8RDBqNx9xhXjhABFMC06PcMVZ0bSzli0djcftDsdMGc3CSiE9ydyccRMABHLx4SUKUXiqkEWEEe70xm0QWPMWQyks%2B5eDJGb7XB5nWkAt4fDnMtkc1EUnn4/mC4WoUWncFKyUyuWYBUQMBgR6rJ046l0hlMOja3X6zGG43AU03ZmnS3PYG0UGnCx29l5x1Q4tcvXOvmEgXE0moAB0DchwElB0YBAU8dxRvCKeUTGA5oz6ujsfOEAbdfM/inE0JeGQAH1RBNBTFUJ4wRAmy22IIFKsw16QCAftXOaXS5TeQSiRczX9MBPsPRd%2B3OzjuyaALKedDpy0ajGWpjhOU4zi0jiLsuBCruuwHYBAz6tnux4AG5iB8B5gsep4OiW%2BFluGeKVre16uucp4PqBXr3MgBgKAoE7KJK%2BCiPsHZekRkZqsxqBEAASqgTDoERLJEVeLpVoKlF3E%2BL5thx3rlpSH7JvcP60H%2BFrDpqgrjg2YFmP4s6QUuTAruca4bl6EDMZgrFVhxbhIa%2BjEGUeIDod4mBYR5uFFkqGKFueSpkVJFGSaR96ye52C0fRbl1nZDnse%2BSY9vcgnCf%2B9y8QJQkiecyXzo51HggFynMgRl4Vje1YXJF9XumV8XmYlxVsQGaXcblxB8ag/FAaJmLibV5FCrWE4AGqtHgTAxPQimjapGV9gOOWAaObj6ZORngXOUHmTBllwZuHWOYKM3EHNC0BmVaEYT5h7YDhZp4ZVQXvfqoWNdJv01kQLV0W1TEsSVqWcUqn4poNTLaXlA1DUVYOdYl5IVZ9GNQgA9AAVPjBOE9jqJ4/jLzYEILwE8TOOE3TuM04RZinOEdFeFg6ZuGgDA7Ckb6Q2WPXPNaZ6lkLQIgqLBHQ/cQj1JgcLaQiSJZCi5zC%2B8nwAtmublSFkLY9j9wvAGaoaGLEHzgubXxAQEATOgx4KHc1tOXLDTHmt9VBPcZhgl8Gs2l6h6ciZVs2209sEI7IDO2wruCu7CsEJ7/b1RoXx%2B16AcSzm1bYCHpaG8bpv3FwFsHa7SiRw7Tsu%2BZjrnERScOMeGkiYFTdKpStcgOE%2BzNmIS4CLOgiCv3Xzl9nVWVT30fHv3mCD7Qw8MKPx1uBPvtpf7M%2BUoHAolsH72omHi4R3bvdx5gCdH24zfy63IDt6JXez7iveL8vq/r%2BPghfObaey1lQxy/sQIe3Nf7nC3lnJS%2BogFKizJLRuBcT44yNibCY28CI9SmqgPA6BHhjyxpCMKUVfgxUnALXB%2BD0CYP2Ake4KQvALXnCA48VBJYLlPHaVkwVSxkPqrqGhBD6HxEFKhWh2EmEsNoGw3uKoPjcLNLwzG%2BtBGCmEYouEeDRGm3EecXRhDiEvRkaw5A7CTya2UWmMS9oSEaIotFNgZVT7aLVEQggYjGHMPMZYzhecbHmhGvY9R/177UPcU8QQ3i/7HVMb4uRFiFHWJ4XY/hBFHERKUkLGJ%2BjiCXVoZ46RiT5HzysUotJISMlliyTJFxjZiDACWlCGWX5oxUC8DzRoOUW4wShMeLKhU3BGO8QHPJEwDFKTbr%2BQUkImlo04iQs%2BVdbZRxjtfBO5x2ktE6d0rIcTd5ILzmCQuUIVkX3WXXeODdtkdK6Q4A55xJEEKObnXWZzoSW3PgxNZV965OR2UwPZjyBCFIIcU6eB9TnvQub8mu5TNm3LcH0wZBVNEeRfk3KFrxNYwpIcXeh9xJACPCc1WKbjVS5XSJkVCmBvEgDMUk/xXCql8LQaQsltZPRKV9LKeU9wIAaE5k8MM5yonKBpY4OlsT1YlNkWUmOiib5srUaSkiTVJoUvFVSyIAgIjADnDK/JjLSnJPKQEpQQTVGhPVXVN03KdQCz5f6QMwqMWZjFV83V%2Bql5GvpfkuMR4mWKpwqklR6SOVZPJXWeZzTdRtPufsgQC4uC9Mfv0yEgykZuElYUPAxrJlkHuHqhgBr/WyumSAL2cyFmuOWd81ZCKNkAsFECkFjRU2CkAdgHOOt86fLhdXS%2BiLW13N2Q8ztU83AAFop69u1sg4%2BFUh1/NHTcwFSbQUMC7ecedOcRb4tDo2y5/yN2Jwzdmra2Fq1pwxQu6Fy6LAcHWLQTgiReB%2BG4LwVAnB76WGsFSTY2xzTMx4KQFOHAtAHlIAAaxAIkSQdYNCSC4OiU4GhEgaCMv4MwAAOPD%2BhOCSF4CwCQGgM5fq0KQX9HBeAKBABnSD0HSBwFgDARAIBNgEGYQQcglA0CHDoPESIdxOCqDw/4Gd/hJD3GAMgCxUg6xmF4PZQgJACF6H4IIEQYh2BSBkIIRQKh1BQZ0HoAA7uAlInAeCvvfZ%2BzQP7OAAHlSS8fuKgKg9wJNSZk3JhTZckNmEFR4IT9BiDMjA6sXgzGX2saQIJlIwmyAUAgEllLIBgBSDMHwOgDCGMQBiE50gMRwitEuLZ3gZXmDEEuC5mI2hk5VdIIJ18LmGC0Eq2Z0gWAYheGAEKWgOYWtYBYIYYA4gev4ElI8ulDGeuYFUArUkuxwOLzfT1uRMRwF1Y8FgErKo8Bke/aQOlxA1xKHpONowcijBOfWFQAwzSpp4EwBZlzvwWvaeEKIcQBmfvGbUCV3QQQDD3dMAByw%2Bg8AxAY5AdYqA%2BZZAWzOh2FpIdWEsGYajqBzvXSwPDiA6w7DJyyC4RE0w/BBFCAsMoFR8hSqyFTxn%2Bbih05GJUHoZOBD9CmJ4ToehSfbr5/MUonOhdzBZ7MAYQx6fLBJ8BnYEh7McA/aQKjzmOA%2Bck9J2T8nFPBcFbgdTkXzCnC4DFiDD31gIEwMJUYxO4MgEkKcOs1RTjokkChswkh/AUcSP4Wom2SOkDIxbusgR/B4eqHhrg/hENcESB7/wGuSu0fo4x63Zn1hsc49x3j/H0uoHCyJsTHBWgsFQuiGdTBWomi4NUOsXBkOqaRBpx2QQfu6f%2B9IQHShgc9d0LlqzTAbPftV%2BrzXNHXPudJJ57zlfq%2B1/rymRvzfkOhZL8liLUXThmCt3F3PiXt8paLxliLIAl81%2BBkYRvXAM40FoAVygxWes1Yqy1j/dWGtNdbqdtrNsDrLrErPrAbIbEbU7MbCbKbajGbMnebErJbFbfYFrDbErbbXbS4fbXYajI7E7cDc7S7TAa7GAnsB7PgZ7BQV7d7T7Rgb7WQHvfTPvWQIHUzajYffQCbFAawawGHOHeARHZHEeTgNHaODHXg7HXHfHAhAMQQ7nbdCndwAXGYYIREOXCXVIJnAQaXUgAoTIdncXJYLnYXRoUXXQ0wvoOYDQ4wyXAYCw6wjnWwy3DYLYZXFwzbKfdPTge4a/FfW/NfJvFvYVRCdvM3aLWLG3UgO3B3BIJ3EPUjEAU4JvFDdEZPdEdDSQX3GTIIafDPWwLPI/VjDjCAJAAvUkc/U/CLUTNgTgSvfzFgBQVCCxVCdffkCYNvU3TTLvRgv7ZgwzeQAfdg8zU4UgUfcfOzIjNXRzHrWjNzHjefLzXw4gFgBopolotoxyNUCAMLHfeIPfU4Q/Cg0olAKo%2BISo0vBIZolIFIBcVo6oBcdogga2FYmTPLZ/eIQrN/ajb/brcDX43/ZrAAkvdrTrbrOAzAfrQbMQSA8DaA27XA3geAubOQxbZbZAVbNAwQeoDA2HLAnAw7a6Ag3gIg9IEgg4Mg%2B7HPSg/sagt7D7L7U7bvPoiQFgozIYkHJIrgiHSQmwbbInIQxoBbbGWuTHawHHH9GQwneQyw5wCAVwXQ2nIwhnLQtnbIFQ6nPQ7QhgGwlUhQswqXDUoXDNKw2XJwvU2cfnXITUy0sXRYFUxXNw/TSfGY3HHw%2Bo2TRo5o%2B4e4usJ443MIvfS3SInPW3e3LAOI1XUPMjGoOsU4U4RILDVDCjeM9EaPNPWYzgTPJjKI%2BDSQRId3RIPDIyaoSQaodDT3LgUYzbU4V0rXEM6DVXFTDMt0ujbPRss7T48nSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/conditional.hpp)
- [unit test](../../../../tests/unit/typelivore/conditional.test.hpp)
