<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftReview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-left-review">To Index</a></p>

## Description

`Mouldivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Pred
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Pred&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;::value
  && Pred&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt;::value && ... && Pred&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt;::value && Pred&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;::value
              &vellip;
  && Pred&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
LeftReview
 :: template<typename...> class...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LeftReview
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-preserving pair of `Vay<0>, Vay<1>, Vay<2>, Vay<2>` satisfies `IsNoGreater`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** IsNoGreater ****/
template<typename L, typename R>
struct IsNoGreater
{
    static constexpr bool value
    { L::value <= R::value };

};

/**** Test ****/
static_assert
(
    LeftReview<IsNoGreater>
    ::Mold<Vay<0>, Vay<1>, Vay<2>, Vay<2>>
    ::value
);
```

- Note that the order matters when the predicate is not commutative.

```C++
/**** Test ****/
// Reverse Vay<0> and Vay<1>
static_assert
(
    ! LeftReview<IsNoGreater>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);
```

## Implementation

For every element in the list, we will check if it satisfies the predicate if paired with every element behind it.
We will implement this process in two steps.

First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template<template<typename...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestElements>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestElements...`.
    -> std::bool_constant<(...&&Predicate<OnDuty, RestElements>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            LeftInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate, Elements...>()
        )::value
    ));
}(std::make_index_sequence<sizeof...(Elements) - 1>{})
```

Here is the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LeftReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate, Elements...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcpAAOqAqETgwe3r56icmOAkEh4SxRMVxxdpgOqUIETMQE6T5%2BZZj2uQzVtQT5YZHRsbY1dQ2ZZYNdwT1FfaUAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKY8a6MyHiYCmfbB8enex87r0eHP2YAzMFkN4sGcTP83F5HLRCABPcHYX7mQEMYFeUHgtzIBQEdBYKgIpFvbZnZTETA0VTPLbfAiYFjxAx0zEEWE3ZhsUhnZIAL0wAH0CITjmhUdcCKTyZSwf8LmcCMQvJhwVZjr93p9NZtvhqzgBJBn0NiCJhtana9Vaq37IknEkBCkEPUMBQ3Bzmm3HOmG03KiGs9msP2I444xXuh1UJ0ut0SkwAdis8YuKtt3sZvsxvIFBAAdPm9cKjmGvBHHc7XRUhRCcegQCBglhVPylABHJVizF6/O5wn/bBgtWJ35nUfy%2BkZ5n%2BidMv1uAOMIM9hFnYFMBRPMmYfCiOlcreUrsIntchcczBnADyDAuUNhp7Zi7YPYASo8CNgjYwCAoi2PuTUjjIKuAg4pgABuYhnEwUKoGceDoLCtAQDMI5jqsqxnAA6heaBFBM8oIBe5IKF4tA/mcXjJEY0FnPwtDoGcmCqPEJHJAIZyoOB0RggAbBo5i8YJJj8b2xz/hhZwACpEWc8RMMgADWZwAO4XrUF70fgNF4E8IkaG%2BOKfvS34KMuoloaOAC0K61vWESoJ4/KijihjVm4EDLmYQneVuO6ZhC163qyXKGR%2BX6CL%2B/b1pB3iYKh/apkOKb/KqPzEuckYEG%2B4EPCpHq0jOAXzkVU7zo%2B57Lv2q4GBukrbngu7Br8JZllGOV5Uiw7iWO6aziyFVLvmxnGj%2Bf5jq1EpkqgRAALKeOgllgt1Rz/v%2BrlASBLp0ixxBnA5nhnLFSpLf%2BCZpWtl1ggArFY10pW42aCj2hb9hAdkNgwTYtpg7Z3HO3b5giqE9VdY7nadYNjuSBCLAwkNQ2cnlA95gkQAjiNjlgwILhjmNI3j%2BNjllFaxlmuL1iwTCKQKjbMT9f2dhCr2IoloNE2D9Z9b68GIbQmJ%2BY1vpciNplVdgKGE4jMwxWIJ3s/jMwJRdmMJhc70UyAVM0/ydPNm2HbLFmeB8qgVA9hAouRTMZxWWcXCEsOyYg6tV1qyqg6u6O7upba/7c2VZ5DbmVtjWzXuUdRwBnPNDEynK01zQtmKh2ZQOJb7yVJeldrWp8OokgAYngxA4mc2CqKwjIXi8lp5x83xIgCQIgheA03IKxBMIQUUhjnuoAGpMLCBW/AHc4wUQ%2BpFpNZxD/CQ4WABpqNVtYG7dBsFHXLbeJoWyYez7aV15s%2BoKKEqAAOLkr6e2116pVzkHbBnAED6Bi/L4zwqpYSnq59XxvnSYgXUVajg2qvFyO1WL7UcrQbecUlrnVfrLOKMo3DgjlC%2BVBSplopWPlnTO/cSRSXfKPUMgFGr8nXEoOovx0bsyyh1TAKkuwAOvpgW%2B41Rz1ljotCE89MQCX7FyQREIHYiLnsPTEZgESiOkRCWRGc%2B7/hwcqY4ytbQanrl8E%2B6wzhCAqAIRiFcq70HIbnHRuxG4ZVPqQsu98TiYRytEJQUj4QQmEQOQwjExFuAkX3CByBqEbmiEKY4DCI5gDAK/R0zDWHM3YUA6I3Czi8OTgIhR/i5HuKETkvxSjsDyI8W4QpqS1G/GVhwOYtBODXV4H4DgWhSCoE4Bgyw1huQLCWG3AEPBSAEE0NUuYikQDXUkLmDQAAOMwZgACccyuDXWmVMrg8Z4zSFqRwSQvAWASA0BoUgjTmmtI4LwBQIBDmDKadU0gcBYAwEQCABYBB4hQnIJQPC8Q6DRFCEGTgqgpm8SsrxSQZxgDIGAlIXMZheANSIMQBCeh%2BCCBEGIdgUgZCCEUCodQNzSC6DiCpLu8ROA8BqXUhpQyWmcEvFCN5EozZnEBcC0F4LIX2wmWYJGHgGQ/L2siLgMxeDXK0HMCASAvn8o%2BRAKV9AYjACkGYPgdBgEXIgBEalERgi1FhGS3g2rmDEFhJeCI2gqz6tIHhUa15aB6vxVgCIXhgBuDELQC53BeBYCpkYcQDqS5VjwNxD1zTmIVChCsfpwQ6RbOaTCCIXdjUeCwNShUeA9metINxYgDklBXB9cAGERghlzCoAYYACgB55UvOyS1KLhCiHEJi%2BtOK1DUsJfoQwxhrDWH0HgCIFzIBzFQPENoHqrK1kwaYDplgzAnOzYirAg6UK2BaIG5wEBXDDCaKQQIExCjFCyEkFIAht1HpyKkboB7pirtaFUMYZ7mh3oEB0OoV7eglAGJ0R9X6337o/RIOYChunLEA/oSlRzqWnOZUCkFYKIVQq5UjXAhASBgj6cKgZJa5hESYFgGIK7RmSH%2BLmOZ/wNkaEkGYSQ/ENDXV4nM8D2zdkgH%2BFwXMvEuC8SmXM1ZvFxlLLI7xSD%2BLTnnMuVhm54rHkSuefS95FBZWoD5fKv5bBOC1BYOBeMVkmA1S7fbOZuZ2OhvwAipFcR61oqbdIFtSg234t0Mq4lTBSWeopRwepImTm0vk4yqgMHWVgrXDRLgRmTM8uU98%2BV6H/hmEw6K25sm5XRBlSlmIIXFWLMOTQcirjKCavxYa3VlrivGtNeahwlrrXfltfa5pjrnWutoO6y13qu1%2BoawGyowbqVhuQBGy10aWjUvjYm2EyaVjNLTRm/p2bc2YHzR14IoApN8HLZW6ttbM1WcbRi2zshW14uaU5ztxbp1WEsH2gd8Bh2jtSOOydsoLvWDnbwLi0RF2PFu7e9dfhN1fR/XugoAG4jZBPWkTwjRz0Q/fVMT95RKgvofVDkYv2kftDGHDw9oxv2o53a5P9IP4dgeA4sUDQqmNeeOe9zggW4P6dC%2BFyZyGzNocFQl7DpBcP4coB5nZpA9n/CM5R%2BM105nrP%2BFRmjkg4g05pWc2wEnEvSfgLJl5DK0tRf5WplYmm2UsAUOBYC4Ewu5lnDiOFbPF3ItkNZ/bWL5D2eOzoVjpAXNufJVTqlonfOvKhJxALqgDdG5N2bi3EoIC8uizxZE/xOdreS9r%2BVWuVN9GN/EeI/JTdzP5BH/kwfbOqvyxqrVOrjWlfLyas1FrM01cEHV6ljWXVuo9f09rvqpteu644Xr%2BL%2BuDczcN2NvAxu6sm6mxFs3eDzaSIt%2Bky3i1rbLUwCtVaWE1sYHWu3e2JAHexc79tbuDDnZ7Vd%2BNy67tjs4KsOyL3Z3zs%2Bwhb7Q70dtBcID/H/gvrY5veDtoP6/%2Bl6/6JOT6f2r69QX%2BYBGOEBv%2BCOKOGQBOWOIBOOQGIGGKHm1OUGdOheZwhuxuR04evoZcls1usWQqIqXOPOfQK6WyAuey8yuY/w/w10yysuByzB8Y3G3mtOiuFyVyXORG10pGay8YByUykgiyXAMy3kTG/wPuPmiuKuHmsKPBCulBUmcw2a7EfgkgQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/left_review/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/left_review.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/left_review.test.hpp)
