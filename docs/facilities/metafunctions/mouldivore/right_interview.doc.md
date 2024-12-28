<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::RightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-right-interview">To Index</a></p>

## Description

`Mouldivore::RightInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Es...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Es...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Es...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
RightInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct RightInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = RightInterview<std::is_same>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

`Mouldivore::RightInterview` is implemented based on `Typelivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<typename...> class...Predicates>
struct RightInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typelivore::SensibleRightInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template Mold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQSktIADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJUtJ2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxidWNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGZwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIPMEIYUK8MLhbmQM3QWCoOLxvyOtwAKsiungAG4kdggISMdIxegAJTwwAQBAAkoJ4qz3gB3L6HIHMNgKZJMLaM5m0Nkc2EAdisVxBBEwLGSBiNpKRz0VmAAdHaaVcZsQvA5btyGLyBUKReKjcQpZhpXi9SDbmHbkaTWbMBbjaamOb4ZbGKxbfawdhblCmAoFHabcpiJh8KIjdiM6Hw06XQRboXUER%2BagmOhK2GTCGruHuxG49GLczrfmHZce1X0TW68QG6gALKeVtdse6iy3GYJvDILMCGaYVTJYi3JheIi3VliLyYFcAWi4HfucNX98ftNHy8j8cTCMHqfzl2ARbGowBDlriS5jl46RGLc860OgsJgvcU4zrBrbwv%2BgFsIIebpriYL6m%2B7Y6g%2B%2BGvt2H79kmfYJjGSY/mww4ZlmBi5vmhbFpuNGgW2tyQeEwC3E2LYIUh9aNs2aFuOxJZcYxeEEc%2BpEGlcFE0QOVqprcABieDEDMI7Vq67qepggrCmKEr%2BjKpI6XpBAjh2BHkdRX6qa59FpjaOLMTmOEFkWMlliO3aGbWYmoEJi6ESuPHOVGal0RpDF2mZIpCHgWDceBPahchRCobF4aOUV2XLmujSOFuaAeka%2B6Hsep7nt4V6FWOjmtWVsIAKxWF19wQMstzXt5FIgCALBMAA1pgKLpMAEToGipLpAAXjN9kVqVnVEU522dXgVDbjVe4HrCW17eGUDDmY/jmP40mcUF8K2TMpCCd6wgZR8cljU1l7LMsHUXcVRYEBsDC3Boj66g%2BynRRd3ZdEoQN7SDmBg8QEO3tDz7nZ194DSjREkbtbXES%2BcNlW5tHfklnkYZgQHYcFy58dBqEiXlc4LqSDNMyBckU9FikKdl1OxvF7l03JPmsXafNYSBLNhmzAmRZz4WRbzAGM4rfk0kpwLk4bhouTTybWtpumvRGHlurUAjoG9Fu/naADyBAIPEWWXLlxl4Hypkfb6krWc91sEG93LVU7twe17emCwanbReLVGS%2BbHky9mcv%2BRxpYfMr5XOq6msSTx7V42ntMpslNqpZ9mVFyFE6l9O%2BU83jxXtnjLcblVO61adDWoGeF4tb3RUpwjRU9SYfUDUNI0EOgY0TdNs1CgtS3wqt63N6j08zz2B1HbudVnfDx9XfaN13Q9Bflm4L2R%2B95npZlP0gH9mAA0T%2BN6luKDcGkMcbk0psfRGtAlC3FPtVc%2Bp1/5lRvl5O%2BN0H5cVJNHR2b0G4f2%2BrhX648/6T22mjDGEM7z4RhmRSB4YkZXjgYPE6xAkHLggGw7a/tA4NxDlZQMpJ47eyTlfOhtwxrU0EuXeEGCywiLEWOCRZsYI83hHgr6%2BtNqiLoUQ5qtwwBgDhEhbGpDOqA1MWVYqnDOrAMxrcMwsJLD2w9AHL05k%2BEBiDPCIRidcLWLKkojOUiWyklkQQryWiFE9kCZ%2BK8BU1EfXwZosC2jIG6MvDjCxy5cbAiyWOBh/ip6rlsVjKhT5wGpOycRQmpiRYdTqRAsc1cXZ1wVsBH2ZVVYqLghrdu3M4La0wu0wWhtuwNNyanM2EtYnqVrp5byOc/JtOZpE8MXT1ZGK5lrdCOt%2BbJKFuM4MsMJl/ABGcg4QJTm3FFFGfmG4BByguSCU55yARAlNhnaZlEa5DlwrLPyYSfa5V4ZZTxwZSa9k%2BYlOZ%2BYPEym9kXXK4UCrZUrto5pWc7TYHoHrA%2BKsoICQ5pspkzxNTsiLGNbhbifSgrDm4bFez5HLhidGLZ0ipIBUeuEvF4iQCSPiW4OFgZhF%2BNGVPEmtCwwYullinF7Si5dKJYhLmAqGV6xGQpY2otrivMBM8%2Bk2BVCsFNFeb4%2BrdXylfFc2c6MmBUC8ISHojyzgfJmdC35NpLjEGAD7RVtr7WOsyJzEFfowW7xXmNPAChZqphHGNAVXqfUaqtfSBkHwQLOqBOuSqKJfLxHslcCANrGgBrqAIUk4QCAHBxPG1RbhK1vUrXsRtggDgtqrXsGt39x4iU2WYQGhts2blzbmfNIIi3%2BodWWhgpJ2QZS7QKhtsDW3trbcujtXaf69uVbeAdFgOCrFoJwLqvA/AcC0KQVAnA3DWGsGudYmwWrgh4KQAgmgD2rEmiALqkgbQaAABxmDMAATmA1wLqAH/1cB1DqaQR6OCSF4CwCQGgNCkDPReq9HBeAKBAGht956D2kDgLAGAiAQDrAIMkE85BKBoBNHQeIkRUycFUP%2B/w15/CSFuMAZAW4pA2jMLwDiRBiAZT0PwQQIgxDsCkDIQQigVDqEI6QXQXBSDSgxMkTgPBD3HtPe%2By9nA3Ynmo7WVAh02Mca4zxvjtwBMOIgB4Bj9BDz4i4MsXgBGtCrAgEgejyRGNkAoBAALQWQDACkGYPgdA/S4YgDEQzMRwhNERDp3gyXmDEERG7GI2hagEZffRxWbsGC0DSyprAMQvDADcGIaB6XSBYAmkYcQlXdIFbZB8Qze5agnm2C%2BytXRDOahiBibLHgsCGfRHgZD3BeCsniDENImBHgteAJqIw77VhUAMD6gAajKN2VpGuSeEKIcQcmzuKbUIZtT%2BhDDGFvZYfQAdcOQFWKgZIPRcMcGvBSIxphLDWDMJhxbxAxOZXgKsGo06XAMHcJ4NoehQjzDKBUPQBQMgCEmH4dTWOeiDHR0sTo3R6izFx3oWHPQ%2BjNCJ8MSotgKdI9yOp9cdO0cM4kDDh9Wxuf6H0%2BhwzWHbhWc49x3j/Hf2OdwIQEgjiwQea89t1YXsWwjAGqQL9kgwQ2mA2CWDGhJBmEkP4VDXV/DAYFwhpDIBFc2n8Fwfw/7gNQf8D%2B8D%2BuggYd4FhnDeHX3beI2RvzFHTM0ZC2F1zzG2CcCaCwVkOprxMB8tBLgwGbRcD/cJ/AonxPqbO9Jy70hrtKFuyp3Q0XNNMG0/NvTHAT1C5U1hkzVGTy3As6L9j4vU8CXT5nv9twnOoBc/EBX/bleEd8/5kfgXXO0dC7P8L2YjDp64GhmgtA4uUESypzLqXGv7%2By7l/LDhGvFeAqV8rhmqs1bq7QBr82mvGke21i9%2BAix1EW79i9vXkD9cayG3gwvVG3G0REm22AvRmzmxfXB2WyUDW1f34iD12yYAOyOxOyf0Lwu1kxL1kBu2UwvUrwey2yBysBe1G3e01y%2Bx%2B04H%2BxXkB2ewsFB193B0h26w%2B1J062cAgFcEp3U1R1KC53xzSGxyyBZzx1IAJ0yHp0WEZ2p3J36H4K4OnVpzmCELkKp2ZxyEkPZ3UIWAxw8zWA2D5yMPg0bx9yMw4C72s24xXz7wzyzw0CH1l1EwVyV0Dyn1V0wHVwSE13g0Q1IGQzBAzyNx1C6mAxgzBGN1N0kHU0sL91sAD28yIxI3I0ozMwXyjyYxYw4HjxsxYAUFZC3FZH72jBmBzzl0hwk1kCL1wPk3kDL0IJ0Dtw0y03S3rwsOF2M3D3M0swKKKJKLKK4lrGH1Hzc3BDBE808J82Ixn3GKyKX1c2/mQGSGSBRFKOAxRHKIIBRFUC4xiy329h3ySxS2y0PzOJyzywK3PxHxKzKwq3f0wGq1q3q1%2BxfWa1f0gN4A/062/x61UD6yNEAIlGAN4FANSwgOmzExgIWyWxW0QNa2QKnz4D2wUEO0DGO0YFO1qJwMSAaIILu1aIMFIKYNexiCoM%2B2%2B0yF%2Bx2FGjIJBzB3iHYMpJUJ6Hh0Rx0JRwR1kMMKkNEJ6GUOkOKE500LZy6G4N6G0OR3FLJwEDUN5JJz0OUL0MVMqB5xMNk06IM2b04FFwGOKLPGGLLFGNcPl3c2mJSIBlIDVywD8Pr0COQxAxtDBDBC6ggziNQ1dJ1Gdyb0w04H93wxVy1xAEkC6j12gx1FQ3/UkDAy4EAxumtzBB1P9OwxmI/WtyEz9N9wDPTOtPB3SGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/right_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/right_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/right_interview.test.hpp)
