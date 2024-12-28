<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-conjure-set">To Index</a></p>

## Description

`Typelivore::TypicalConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalConjureSet
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalConjureSet
{
    using type = RESULT;
};
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalConjureSet<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Assuming we have smashed every element that has already appeared, the ordered collection of the elements left is the result we want.

To translate this idea into actual code, we need to implement smashing and collecting.
We do this by

1. placing each element in a capsule separately;
2. taking the element out of its capsule if it has appeared before;
3. concatenating all capsules.

We can merge 1. and 2. by:

```C++
template<typename, auto>
concept Prefix = true;

template<Prefix<I>...FrontElements, typename Inspecting, typename...>
static consteval auto idyl() -> std::conditional_t
<
    (...||std::is_same_v<FrontElements, Inspecting>),
    Capsule<>,
    Capsule<Inspecting>
>;
```

`concept Prefix` is a technique explained in `Typelivore::Amidst`.
Namely, we use `Prefix` pack expansion to enumerate parameters.
In `std::conditional_t,` we check if `Inspecting` has appeared in `FrontElements...`.
If so, an empty `Capsule` is returned.
Otherwise, `idyl` returns a `Capsule` containing `Inspecting.`

Here is the entire implementation:

```C++
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<Prefix<I>...FrontElements, typename Inspecting, typename...>
        static consteval auto idyl() -> std::conditional_t
        <
            (...||std::is_same_v<FrontElements, Inspecting>),
            Capsule<>,
            Capsule<Inspecting>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::Paste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::template idyl<Elements...>()
            )...
        >;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEhoAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf99nc3Ew0govPRGYdmaz2UxOfDubzWJgAHQO0VXSbKhw6vUG%2Bhqik3KkeVoMPAANxI7BAABUeXhRLRlExJphjedQXzPmkmNsdagA8HQ7CAOzqkHXFlsjmqq08xi2h12p0urxuyNpaNiOMJgtWfMPb0av67O4WeOJ3VKEA%2B0vmy1ua3VtjUjMAa0w7lkTAiCXrSsbUubrdj8enceQy9XgnXkWITpMhdBd3vdy8WSMiqrcoVx9PHnPG6vgSLN49v%2BPq7AOABKmDIJsWRBiOw7jn2VyTuWmLwneD7IRaFYzlWqa1uidxQvGXzfq0v5XKQ6H3ph06znhjqBNghEGAoJFrr%2BNhUa%2BNpsLW2D0GwgjOgKXF0TWDr8ayjAEBYCiUdcD7cXO9oOgA8gQCAJAoqEYtcDZNlGMbttOpEXgkILwpJgkEM6%2BGMQKpkcQSVnSbJdnYAK6macQCjuZit4KQ%2BT4RMASnvnce5GYeqqBfeBJcYpjmXhZbguUJvkOgKaUyRldb2QlD5eVp%2BGxXK2AgCAs69iC3bVf5PaIVqgLNcmlL3AAkmWUnnk0SbAk1LUAsCoI0dhYm8RJAnSdpjGgvpu6GWI37aJsmBCJgBD%2BUWimjVyuG2k6inzY8G3rrQnaAXVpW7fCWQAF6YAA%2BgQtbtYdD7HU8ZG0ASxIVREWCqI9SgAI4qhKBLtX5s2lTe22KRhZoofCNJ0ngqiQ%2BitYAGLELI2VyUpqZ3O1DAKC8DghQK40qXlulXAjH2tI4yCEQICZBmIgrCnceDoCitAQCsdwALQEX9KACPgTRiM9BVxWhpWM/eED4fmbg3m4Et4AowO2o9QYErj%2BNTYIhOk%2BTkGOEY6JrPLCO6vqhrYei8kM8riUes7kNkxT1vAO9jPksBsO1SHxbu9RSNYXtPEVvTR3bm6AASfNYAwF1hwB13R9O91PS9DpvTDkd3Mdqckowv0EOg/0MIDwOYGDbzYVDDEYiXilw/bwUvrO4X%2BoYua0hVkVttF9vxUrytYFCVXT4zED2x7X1ndXtcgCwTDLo9AOYEDoPg9smOzZ3HvKxVo28/zP2WabBC5eiQvLw%2BKwlaXXeMZfVbVV3Wc%2BopXuoV%2B5wgVBXdO68Kpbx3nvA%2BTcj7YXzqgKgtYIAExWMHcqlUf7h0urgtqg0mSaipNgVQrB2SJh%2BMQwhRDEJYkhNCRMBJxTbDSA/a8BDtSO09JQ2hSFc5jX2hNOmc0k5Sm4d7fBvp7hCC8GkYoK4IKeilFQ64QC7iyPkZkRRnxDRSlAe6J2Xp4QRAIAKUx%2BxzGCEOMHbO0jDh3CUXovqoJ1FONoPo%2BUEVFq0GWqtdam0TGCCsQQSxvNrFhIsfsdE38XhXXsdqcMnwVF8PmCzR6xEEgEAgBLBQ%2Bt4wEncWYjRciFHoCKbbNUHA1i0E4P4XgfgOBaFIKgTgGtLDWDLhsLYTDwQ8FIAQTQ1S1iLgCJIO0GgAAcZgzDJGSFwfwUzJlcHzPmaQtSOCSF4CwJIGhSCNOaa0jgvAFAgD2YMpp1TSBwFgDARAIANgEDSIicglA0BsjoAkKItpOCqEmQANhFv8yQdxgDIFZlIO0ZheArkICQPmeh%2BCCBEGIdgUgZCCEUCodQlzSC6C4KQAA7sQPUnAeA1LqQ0oZLTOCqURM8qUyC7h/MBcC0F4K7iQrMHcCAHgPn0GILCPpKxeAXK0GsCASB3ktgFa8iA0rPmJGAFIMwfA6Ash8pQWI1LYgRDaCiMlvBdXMGICiVSsRtBW0NaQd51lVIMFoAa3FWBYheGALqWgtBTncF4FgLeRhxDOrwLSSmsFvXNP3pBREOx%2BmmIaNS5EsQSWmo8FgalSo8A7J9aQWCxBYjaKeP64AyIjBDLWFQAwwAFAADUPiEtUrya1SLhAxjRdIZtWK1DUvxfoQwxhrDWH0HgWIpzIBrFQGwnI3qRbElAaYDplgzCHNzcQPmnx4BrDsFbHILh64zD8ASsIG4lhjAJcUbIAh916HPU0RYowai9G3QIAY0xPBdD0Fuymz6phDGPfej9P6r0EvmO0O9VRT2bu6dsCQFKOD1P2dSo5zKAVApBWCiF4zuVoOliQIVgQuAioGWWtYmkmBYESELUgozJCBDtMkQIayNCSDMJIf5GgND%2BH%2BakDZWzSA7Pw3af5XB/mTOSMs/5/hJALPo/8hDuKjknLOURy5Eq7mSoefSl5FB5WoH5V8n5HA2gsCDPmEWTBmJ9s5ckO0XAJkwpw6u2uBLm0ovEOijtSgu24t0Kq4lpKfWwfgwc3gRy6VPMRHcJlLLUMWZfFwaztmNA8r5TKhIeGzCEbFVc9TCrZXady2MIiRh4u1DVR4rSWqdV6tNda41%2BrzWWocNa210l7WOupS6t1HqvXWr9X2wNzT8AhscGG6lkaoIsmtXGjZzTE3JpRKmnYzSM1Zv6bm/NShC39ZCmWvglaa11obYwJtshXNtoxfITzOLmk%2Bd7aW%2BdVhLBDpHRulpk72acBnTXOdA7F3LoSI59dY7H1fr8BAVwQGQj1zA8sM9mQL25DfQUOHJQcgw9PSDpoL6OhI4PZj/oP70cPpAzj/IeOSdE5g%2BsTY0GCP6EpXJw5nBkOspBUV0K8WbMTJ5bgOFgqsQEdFcR0gpHyOUFg7x/j1mmP5n8MkVZgRmOsak4zkLnBFPnN2zc%2B5jyGVyoK8Qb5bBOBGbZSwBQQZWZBk5%2BWSY9m%2BcIuc6d1tEh22yE7ddnQIBgh%2BbSIawLVL5O0s04yqgzKzcW6tzbrCkxku6dS/z8EgRMta6lfHxV%2Bv08CpAJb%2BRBt4uPVtwQR6qhgVlY1aciA2rcV1Zq9m2vZqLVWuzS1wQbWnWDcwK691YgevZr6wGpbvrg3btG7i8b0apuCHjbiub%2BrFvptXat3g62C2sm26WlTe2mBVtrZgetjbs0uZd%2B593V3u3e7u/2hdNhE2jsoxOpo3rdh/Qe9YJdIWV1rvv5uhoT6wcQ6456BHoVD/oo4I6Q43po5/rgbE5/6g7Y6Q6fpY6E4wGw62CAZAHAaoGgGwFU4KBQZooB6q40ocDh4grm6W53DW7WZF484OZ4aC7KbiokaYBkZjCUY8bbIgCzJ2iBCBD%2BCLJSbsb8H5giYkEKa2BKZZYrAjIgCSD%2BB0YrL5jsaTKSDzJcDTJmCyYbKBCB5M7HLMHDL04cDQoSHq5GGyE5paQ7qSBAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_conjure_set.test.hpp)
