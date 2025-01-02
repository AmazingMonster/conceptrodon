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
RemoveTypes
 :: typename...
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
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = RemoveTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

We will perform recursion over the total number of the `std::index_sequence`s.

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

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the items at the intended positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...>
struct RemoveTypes {};

/**** Base Case ****/
template<auto...I>
struct RemoveTypes<std::index_sequence<I...>>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Capsule
    <
        typename decltype(front_args)::type...,
        typename BackArgs::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
};

template<auto...I, auto...J>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> Capsule
    <
        typename decltype(front_args)::type...,
        typename decltype(middle_args)::type...,
        typename BackArgs::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename...BackArgs>
    static consteval auto idyl
    (
        // Expand `Prefix<I>...` to reach the first unwanted item.
        Prefix<I> auto...front_args,
        // Remove the next argument.
        auto,
        // Expand `Prefix<I>...` to reach the second unwanted item.
        Prefix<J> auto...middle_args,
        // Remove the next argument.
        auto,
        // Collect the rest arguments.
        BackArgs...
    )
    -> ExtendFront
    <
        decltype
        (
            RemoveTypes<OtherSequences...>
            ::idyl(BackArgs{}...)
        )
    >
    ::template Mold
    <
        typename decltype(front_args)::type...,
        typename decltype(middle_args)::type...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEkGkAA6oCoRODB7evgHBaRmOAuGRMSzxiVzJdpgOWUIETMQEOT5%2BNZj2xQyNzQSl0XEJScEKTS1teTUTAxFDFSPVgQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQaD/vs7spiJgaKpvkdgQRMCwUgYyXC3AQUS9mGxSHcmIjUOjQWgGNsUgRcfjCbDAg87gRiF5MHCrNcscc7m4mCkFF56MTDqTyZSmNT4XSGaxMAA6Y0c67jcUOeWK5X0KWYv5y7CqMkMdAAMWIsjV51BZIpVMluvpjANxsNpqu5q8lqdLvdnsEsIA7FYkw87TLrn6tTraZqAzS9SG2GH0XcoUwFF8PIImPMyKLg4yjcbsPQ2IIFBGozHna4PbIaTWmvWaW3yYwCApS4EMbPMSnQXdl6L89rA7Sm6HjVFMAB3ccdqcRld3LwZIx3ACynnQQpFw7rkWINN3B/bk%2BnxuZh8/M7n0ogmmGYgg6gLgT8sr3AAkv6E61j03rAtiEGAsCvprrmRbNv%2BoI9nyABK5KoAAbpgAAqwZfCYi7AYEgFQYcdwWJWmBWkoSEYf6640qyRBhtB3ZitGhHEWRlEvF28LjOgIAgBEWCqAA%2BkoACOErchu0G4fOMqLtcp7ZgWQb6iWxoscgADWVzEMAUkYgZK7jNqeDIOWAjjJgJFiCybJ3Hg6AorQS4rhAIWnsuuy7HcTopIYd4mAAbBoeIEngqg0oJs6lsloqoHc%2BJMMgCCiggbFeAwe6GGSd6EOS4aORF/JpRl8JZdgvn8caVAJgQSnNHZpDhRFUV3ERLCkWxBBlXckTOiytk%2BJODVXE1y58agQ2NSN0U5N0pVsfi4wLcAS2dita3MUV1m2V%2BF0risw0ALRlgqSoqpK200sNhlbmwdxYFCRbUL1/W3SsclFmGW2rWt2EGldVk2XZkPBqWX3zvR9qw8uRk8SZxYtoaVzAPi8HHrpONnhewDXre94A3UtDAwFQUQDJqMvEpAWTqiNIk2TR72TRqYPGGKyPVjenplLoFXHjuYbQJzJK8aABSQkWqJE3iVRNIc/JrqYMpakadsmX/syBsKcbKmYOpbwbmrOkOUBgGGZhG7w2ZhoWTddknk5TSOG5XKed5tCdflrPBdtYXbaeo2xfFsLJalhKZeiOUaHlBWYEVJXTWxNDEMdFVVYImC1X691Nen6WZ7OUdhj1shg4NP0rqN42TQds3G3yA1nQQtcRRtMOXUnqhxa6qcpQKDdtVnJq5UQecF33Shcne5fVVX/k153y7161bga03quGiwAXoPQ7cKBPa3d2JU0zXNg%2BLUeo%2BnuPR93KNe06h8iLnnY6Q8hbfxXH7ZGd1hqPW2i9Jub0bSfSpt9BOK5vZsUBszYMIM24DQUBDEAUNvx/ywYzIGeDr7oFvpge%2BxDSGGkfk1Ch0DbqcyJsNDksthoKy9n9ImAtMDk2Fttc8ERaY3loAlYUlDcEvAgDHdmBBZIkODNzLAgg%2BbwmEaIjktExbGgliBGiMsGJgSYkRZAmwMhkXYmxSCWZPa8TZMrZu6tmRYLDAAeSLsQIQ9szafE1iJMaL8JIhOkqouSNsTZBMdhbE0s4rYxMNopO2DtNI0mdsk7AzI/FlQCQkzSsDKYiz4S4gmOFzLXRgYHZczkQ7uQYOHHyG1/KBVjlTeOVNE7RWTrPJK88WqN2wNnXOhVip9xLmXSqe9q71T/ifMZHjDSt0EPfFhO1wk61fmxd%2BJ1h6QPWmybZ/SYrTxTsMlZS9sorxzmvKZhcZpbwEDveZldFksBOc1DO8Jz4dUvjQuhWy/7Pz2X3Q54Dlp/1/hgyKu1PD7RAUdD%2Bp0IF/3YXZdGVN4FU0QR1WM/ZercPhH/HBRY/69MuqeHuutJI0kKQkQJWTthlNdrSlcsSukQGxV2Qx4s/74tPA0u4kNPZ0xkWStw5DBHyOBhsvqhDGFozIQixsplsFM2BiCu%2BKrOG4tFZjCxVN%2BGFkEWGPRQsxUSMvNI2RIpKV4OUQbIsmjeZ0n5qTERNr5yCuMZLBidFTUoVQshR0qhWCUkcSSRiqF1TY3MBCbk0I2I0i5DyCmrt413AAGpMBRJxZx3FFZ%2BXanhYSloC1oj0hYO4TTXItM8tPYgUc7gRwlMmCwgkQ3JnMdjbEVp3qqicfLKpm4tW4TNFWvkyCPqmMsTiK8mAmhUAqvUAQxbx2loEVO409TKZ2qkaupg67uSIThCKelFE9YynJdtA2LAmCWXoXEzJwSaRcHRNsp9L631G3iWyjcgQnpcDAz%2B4af7X3c0Ax%2BxJ8J/BPVA9%2B8plM5IOv5rdHSoa5RCC8CkQoVciI2j5GO49dx8OEfSMRz4Ko%2BRXuHSgmkNaaQaB/fmwtNIzAcdY/CSQPCAKDrlCR%2Bj26KOieZgzFda6N09BY1x%2BE7GUmcbRPCCDKm%2BNuB45pxTbhkO8b0wJ3Tan9P%2BEE4um4cpyKfDI3GmdLlkD9SrAkAgKi1EKANM5mkVGiPoEkwQZkAX0RBo4GsWgnB/C8D8BwLQpBUCcFlZYawDaNhbHTeCHgpACCaDC2sSyARJCGg0AADjMGYAAnBV6opWStcCTEmaQEWOCSF4CwCQGgNCkBi3FhLHBeAKBAF1nLsWwukDgLAGAiAQAbAICkRE5BKBoApHQBIUQDScFUCVxKT1EqSDuMAZAbkpCGjMLwKuhASABT0PwQQIgxDsCkDIQQigVDqFG6QXQXBSB7mIIqTgPBwuRei7l%2BLnAfGInm3yVAVA7hbZ23tg7R27gnbMHcCAHgVv0DbcmrgKxeAja0GsCASBlspFW2QCgEAycU5AMAKQZg%2BB0DJKXSgsRQexAiM0FEAPeCc%2BYMQFEPjYjaCAbz0gy2jw%2BIYLQHnH2sCxC8MABUtBaCDe4LwLAz6jDiHl3gfE9QyLq7i8bOoiIdhZYiGSZrcXkSxD%2B4LjwWBQdijwO1jXpAyLEFiDRp42vgDIiMLltYVADB2TzR8PcPiGTi9u8IUQ4gntx9e2oUHX39CGGMNYaw%2Bg8CxEG5ANYqBeRZHV09GSV7TDJcsGYXrXviA8wLxANYtRN1%2BAgK4KYfhvthHmOUSoehCiZAEF3wf6Rh8MEGP3pYtguhAIaLMUf33W89D6C0Kfwwqi2EX54doehnLr775viQLe0vbBP/oYH3XQd9bh9t3b%2B3DvHaK2jiAuBLs48y/j7Lwe1hlSYFgIkM3qQAVpIIEIaBVoEI1hoJIGYJIMlBoP4IlBVpfi1m1iAIEFwIaIlFwIlCVhVnVolP4JINUJAYlNfh9n1gNkNj/qNsTlNiTjNpDgtlTjTtjutmwJwM0CwCREmE9EwOWAYJeFwBVoaFgSbvgEQA3rJN9nHvdontIMnkoKnh9roIzr9v9hrkDhwFFhQb1uDswdDrDvDg/oIZnijqIeIejpjuTtjrCOCGYN/oTmNowWwQkIttTqgFjiMBWEYCIVwF1jQMzAkINhAOzh9vztzuLpEYLsLqLg4OLpLpONLrLqDgrkrirmruLlrpnrrnFvgAbo4EbqDqbjYmSOLlbl0KDnbg7iiE7jsHFq7u7lll7j7koH7rkZIsHnwGHgoBHvuNHowLHrIPIY9oobICnu9nFmoRnkHlXlYJYLnvnvAEXiXh5JwOXqopXtnjXnXgkNIZ8CsbPt0FkC4K6EviEK6BvosFvkPj0BcXcVkNcQPsvnPm3mvq0LvnkK8ScQIB8c8TPgfp8bkN3tvv0ACVUKfpsOfnjqgboT1rwLfiYYjr4bTCIWIcVuju/lIfYZgU4b/qQP/oAZQNoa1qQO1oEKITAUmP4BVg1oELAfASQXoYiZwNQcNt0RNtNrNlDh4W4cQBwTsNwYjiwAoCRG5CROiQGOMOdpIVdjIc9vHg9hIOMS9soVMToBgT9n9ikLztofCTfgYXNoiHcDDnDiKWKRKVKeuMdBjl4bYQkLiasATpyaTvaRTnye6djiAOKYRkpJKRVkpNKX1KoHtkzsEazmERzlzoLtETGULiLmLh7kkYICkXLvkZgIrsrmIFkR7jkTrg0ZrvrvPsUR9qUebhUZXDbrwDUdzvUS7g3s0bwK0b7uSJ0UHnQT0UwOHpHoMTFllnIQnmMYqZMWnlqUIVntXjYHbk3qsT0OrrsBzPMdYLXoifXo3kcSvqcR3ucV8aCb3mUMft9o8SPnuWPkUE8Ufjcfvm8avjviCTeb8b0LMBCfvveXvsvi%2BVeS8VCelhfs1gaZQZwOaftqKeKR2taWSLadiSQLiXji6XQX/vnMScAc1mSe1pVoaIEIEP4P4DAQERoNhUmHgSyWDv1rYDQc4RLCASAJIP4BAfVkmJ1iVpINVlwGVmYOQc1oECDkBeRVRdoWdqRVQbQUTmsF7hkM4JIEAA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/remove_types/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/remove_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/remove_types.test.hpp)
