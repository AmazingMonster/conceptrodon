<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByLeftOpenRightClosedInterval`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-bounded-by-left-open-right-closed-interval">To Index</a></p>

## Description

`Varybivore::AreBoundedByLeftOpenRightClosedInterval` accepts two variables, indicating a left-open-right-closed interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the left-open-right-closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &lt; V<sub>0</sub> &le; Max) && (Min &lt; V<sub>1</sub> &le; Max) && ... && (Min &lt; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByLeftOpenRightClosedInterval
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByLeftOpenRightClosedInterval
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
// Create a left-open-right-closed interval (1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByLeftOpenRightClosedInterval<1, 4>
::Page<Args...>;

static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<-1, 1, 2, 3, 4>::value);
```

## Implementation

We will implement `AreBoundedByLeftOpenRightClosedInterval` using only `<`, meaning <code>Variable &in; (Lower, Upper]</code> is expressed as:

```C++
(Lower < Variable) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr bool value
        { (...&&(Lower < Variables && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Lower < Variables && not (Upper < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgKykrgAyeAyYAHI%2BAEaYxCAAzBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxickKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHASYLCkGeyYJbkxeRADUwagA7nGkl%2BdXcikpcSfYJhoAguPEXgclx%2BxEwFg2DCw6AsAE9gpgqAQAPLvBgAJTwwAQLVo6Uw6AAkoI4gA3MTfH4mADsVl%2Bl3plz2ByOmBOZwuqAAdNyAGpNPBMaL0BSfCkMy7/QEES7KYioIjKJjAVl0hnUiyXMXihnjJiOZCXNAMcaYVQpYiXaKoTyXMneFU/bVqmmXCDcznmABsXogN3uFrZlz5xAFQswCk1Zm9UcuDHlrte7wDpyD/MFwpWmc1VIAIidaY7nXmEgWtfSmYc9azTs8udyfsBQftGAQRQkvqr6V4MkYZUrMJqEjmZXKFf22Q2m2xBAp3aKSxSy4z9pXjjWOe7g6HhaLOxLGvrDQITWaLVabYrlQB9ElL9WuudRn1%2BuKDtypkPp8OR6Oe2PxiBE1fQMty/BRMxWbNi1LXN80XX4AHoACoUNQtCEIpZCUIAFWwIRsNQjDELQkikKIylEIQy43FBKsnkuehEQAWlQVEmJDLECCY5BcSUdBLjCPZiDtV1kkuSQTH8HMPV%2BCsWTZWt3RBYA2w7H5uzCYBLgAWUwRoqC8BgegERch2BUFwUMqFYXhREUUYDFOLcXj8SJIS7TZMSJPbCkQBAS9qzcZTZ25edS1%2BXV9SvJgFCUZoIF0/TDOMhg2TMR4EkebzsD8u0vEwFY4Iig88GQaLYriAgEr0pgDKMupUtOLhHnSy5MvEz5crEfLCoXYq9VK8q4qqsAwB0mq6pStkmOay5Zta9rsq6%2B1eosDg1loTh/F4PwOC0UhUE4NxrGsCUNi2AdzASHhSAITR1rWABrEB/DMTkqTMSQAA4vv8DQAE5Xo0T0vsyzaOEkXgWAkDRkl2/bDo4XgFBAZI7r29bSDgWAYEQEANgIFILnISg0AOOg4giVgdlUL7PSYz1JEuYBkANKROTMXh8UIEg8HQPR%2BEEEQxHYKQZEERQVHUDHSF0ZrbmIJgUk4HgNq2nb7oOzgkQuInpVQKhLlp%2BnGeZ1m5skDnXQ8cn6ADMxrpWXh0a0NYICQMmUgpsgKAgT3vZAYApHSmhaCElGIGiTXojCJoYRV3gY%2BYYgYSRaJtG6dGbrJ6dkQYWh45lrBoi8YAzloWgUe4XgsBYQxgHEIu8FBHoSXDTXTW6C4dhuwSak12g8GiRWU48LBNYIENoer0g2%2BIK0lBzfZ68Hox7rWKgDBUnk8EwW57N2m7BeEURxDF4/JbUTW5f0euUBOyx9CHlHIDWViGqrpjxnQE4c1MSxrBmARnPEMWAX4QDWF0FKLhIRTHaEESEgwygVD0GkDIDU4GoMKA1JBwx4jNSgQ1PokxPBtD0IQ3ocxcFLHwbMfomCCFUIWMgkYXBIHnW2BINWHBtqkHhrwRGRs6YMyZizNmlszCulwDze2jtnbrzWAgTATAsDxAgaQZ6kgEicn%2BgkKkkgNCSE%2Bp6WG/hPT/X0JwSGpBobXU5J6LgIN/pfUcf4SQHRdGej4ZrRGyNUa3XXljXG7t8a62Jr7f2dsqZsE4E0FgJIqRMSYIaAwvYuD/U5FwTk%2B1uZEFAQLWQwsz7SAvkoK%2BMtdDpQVkrBO3DeH8K1hwHWhMLiXANk8Yg8TEnJJ4vXOaGSskaGtqgW2wEHZmCdgEjGbsPYjK9nbEmfs5kBziQk7iqSg7/S4MkUO4dKBRxlknOOCdSBHJTmnDODgTk5xbEifOhd9rF1LuXSuJza4rx2I85umc8Btyrjk1QXc9gnL7uDfag9h5xzHp852U8TlzwXpgJedcjCr1ANMvgW8FA7z3gfE5x8imixKbIS%2B0t9qVNvmvf%2BVhH4QvAW/FIH9OBfwID/Ic1LAHALiKA9ur9qi1CyDA9wpDpgIPQNQlBzU0FFGyCK%2BB0qcHMLweQmoPz6hzAYfytVDBiHzFKMqxh9C5XkKYfqmhXD1ibE4WwyxPCNYy0Eas7pKS%2BnpMydkqR%2BA8mRjkVM12ijlGqMoNw6xtiMmGKpP4f6VIqQJCMZIRmzUGm%2BNsP4l2mNsZ4wJnrRZkTKbU1iZ002LAFAkgNCSN1LJxhcy9bzfmzUCWnyJeLeQZSyU6ESKQapytq51PtQjbWYT9aGzicW0t5bK1VnGMM0ZsiEiTPTTMlAyyFkRJXSMMtbwbzpKvFWgg0Ui0lLoHsyO0dY4pxOWc1O6dM7XJGbnO5BdNZPLLmIV5M93mophaQfALdHB/I7oC5A3cQXEjBbwCFI8YTQonnCmeCK8TIpXppQJm8lTYt3vvVE%2BLClNokMSiWbbr6do2ffABtLn7wAZUyjgCFv5kZpRYIBAiQF815eoihzgICuE1SEJV5qpXYKyJqhVWQJWsK1SlXVmrOM6tNYsSVdCSG5HgbqZo4n8HsKtaLPt3iHWcA6SwMdZbbSTr2NOiA0jvVXTYfI6ZAaVEjHUeDUNIAzAZISAkfwf13Gw081SEGemB1I1TWjBRGiQCSCpBzSNXApD/QjborgVJbUJH7QIzgdn/W2s5kFjLIXF1rDnhkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_bounded_by_left_open_right_closed_interval.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_bounded_by_left_open_right_closed_interval.test.hpp)
