<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftClosedRightOpenInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-left-closed-right-open-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByLeftClosedRightOpenInterval` accepts two variables, indicating a left-closed-right-open interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the left-closed-right-open interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &lt; Max) && (Min &le; V<sub>1</sub> &lt; Max) && ... && (Min &le; V<sub>n</sub> &lt; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftClosedRightOpenInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftClosedRightOpenInterval
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

```C++
/**** Metafunction ****/
// Create a left-closed-right-open interval [1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByLeftClosedRightOpenInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 3.5>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByLeftClosedRightOpenInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper)</code> is expressed as:

```C++
(not (Variable < Lower)) && (Variable < Upper)
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftClosedRightOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(not (Variables < Lower) && Variables < Upper)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcTC8RFuoVQAHcEqRbrD4XI0mkElDsMCJsQvA5bpdiJgLOsGFh0BYAJ6hTBUdq0TKYdAAJTwwAQBAA8jiGPdBAkAG5iYEmZJWK63OW3UHg96YKEwuGoAB0WoAaq08ExYvQFHjgfLboTiQRbspiKgiMomMAVbL5VKZZczWa5o5kLc0AwJphVGliLdYqhPLdxd5nR7PXK3bcIFqNeYAGzpiAMO1J3XEfWGzAKW6qhHIhLLEtmDPV255gtGkvQ25YnHEZaVqUAESh7rN3d7kpdcsVz2Vqoxmq1l2A5LBjAIxsC%2BOHty8WSM1sdmCbXettvt29VM7nr0XKZNgXdpvlo4hKuhk5T9YNRpNq%2B9eF9/sDwdD4cjB0nQAfVFG8E2lJML2rTNsytCAX0LYtS0RFF2yrGs0zrPVXyLJs3BbbEK07ZIeyvSVSMHK5gV%2Bf5jkBWjbmwVRWGeHcvhouiASHa4jluABZTAWioLwGAcHJPjOGidluNxyWVdFbnoZkAFpkFZJR0BU/MeQIFTUEFW4IlBYhoxLfwLC4NFJGWVMrjvcdH3VFMyWAJcV0udcImAAShKYESxMaSVAj3MkKSpGl6UZZk3A09kuV0gVGGFEzo1VKzbkkd9LhAEAgIfNxXIUC9lyooEfj4gAVItF0kg5AU/ZBgKYBQlDaCBBOE0TxIEdK0TMNFgluQINX8PFcujLxMGWMrGua1qEgICAwDAXyusCnI%2BtuAbhus8aQEm6bZpaH15rapaVrW/zuqC6EMp2obpFuMblwmsQppmq8OFWWhOH8Xg/A4LRSFQTg3GsaxzXWTYd3MQIeFIAhNG%2B1YAGsAkkDUNAADjMMwAE58a4fwcexrhkmSaRfo4SReBYCQNA0UhAeB0GOF4BQQCZpGge%2B0g4FgGBEBAdYCDSOFyEoNAnjoBIolYbZVGxtMVLTSRbmAZBfSkDUzF4dlCBIPB0D0fhBBEMR2CkGRBEUFR1F50hdCspFiCYNJOB4H6/oB5GQc4Pk4XFq1UCoW4lZVtWNa124dbMJMPBl%2BhQzhrhll4HmtFWCAkGltJZbICgIDzguQGAKQBpoWgTM5iBYj92IIlaOlPd4RvmGIOk%2BVibRMAcVvSGls8%2BQYWgW8drBYi8YAYVoWhOe4XgsBYQxgHECe8HJcTRSLP2gz7uFtgR4z6j92g8FiN3O48LA/YIfN6cX0gd%2BIcMlC7MFV/PoxkdWKgDDctqPAmAkRJUBgjM2whRDiGtpAu2ag/bO30KvFAENLD6AvpzSAqwDKNAXipCY6AoRdlMJYawZhWYv3zFgLBEBVh2D7o0Fw1Jph%2BCsmECIwwqijCssUbIAhWF6D4Y0BYIxEhWQYT1Jokx2ieE6HoSRjR%2BhtFEdw8RtgZGCIkTI1RSw05rA2FsCQ3sOD/WZn7Nm4dlaq3VprbWmN44QFwIbFOZh4bp0Rr/VYCBMBMCwIkOhpB0aSBGvjFIkgNCSDMJINMjN/BpnxvoTgtNSD03hhqNMXA0zY3xmTNM/hJDEzCWmcxjs2Ycy5p43m2chY5xFkHCWRcS7J3lmwTgrQWCimSCpJgfoDCbi4PjDUXAsb63wEQahptZAWxgdIOBSgEGO10ANV27tW4mLMSzXgbNA5izhLcUOVjI7q3UqvWOQyRkaATqgJOCQqyBDMB4zOfM6nNNRE0m5%2Bdk4oH6eXImTMq410oPXR27dm4DzBZ3buvd%2B5PyHguEeY8/aT2nrPeeA9l5f22MDfAW9HA7wXsDfeyBD4DxPtTYG59L7NxvtijOD8B4vzfpgD%2BK8jDf1ANUvgACFBAJAWAgekCZlWzmbIeBDtgbLOQT/UhVh0FUtoTgtIeDOAEIIEQkKsryGUISNQ3e2CeiMJyMw9wciCjsOpLonh6RMj8NyGathNqSg5CteoxRfRNEOoUfUI1AhlGDE4Ysa1cwpheu0fMQNYjjEGJhtG6mmyLGcCOTYvpZzBnDKxkmZxEz7lpwzl40gPi/GjECdTFJaShmROSP4fGFNAhRJiYU0prNOAVO5r/fmtSkCi2DpLYunyC6tO2B0qOLAFCil9KKdN94JhjJccbKZ5toEiptvIBZEqdBJFIKsj2i8Nm%2BzKQHBpIcw6qFHeOyd07lQTGubc1xgRAhPI7a8gdyc%2B1vMSBO7EoFBnARnQQYCZ65l0CBXXBuTdO4Qog13HujCB7wsEIi8eOLMBTxnmIdFT9MXsrpaQXFRqCV71UAfUEZKRQUt4FSq%2BdJaV3wZU/JlbJWVf28h2/%2BjpeXANAYKQV0zl0SFFbbddiCt2/NQWQ%2BVmD4BKpVbsQh4m5UWAodsqhxt9WBPdc4CArgtEhEtZGtRQjbWNF08Il1Bm9GGqkf63TmnpERoqFG8Nob8iOpDQGxzhn9EKGhkY/R8aD0to4OHc9E6oxXtBDepx4ySC5qfdU7xvj/GUBMeWkABMNQPv8CTQpjMH3JGyc27ZrbbCVOeR2IJIBJD%2BA1ETCmjNsaSCJlwXG1YkkcECIF4r7MqlZxMXrIr/sevldWC/LIzhJBAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_bounded_by_left_closed_right_open_interval.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_closed_right_open_interval.test.hpp)
