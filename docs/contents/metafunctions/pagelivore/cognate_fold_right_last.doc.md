<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFoldRightLast`

## Description

`Pagelivore::CognateFoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Operation
-> V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>, Initiator
-> Operation&lt;V<sub>0</sub>, ...
   Operation&lt;V<sub>n-1</sub>,
   Operation&lt;V<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
   ...&gt;::value</code></pre>

## Type Signature

```Haskell
CognateFoldRightLast ::   template<auto...> class...
                       -> auto...
                       -> auto
```

## Structure

```C++
template<template<auto...> class>
struct CognateFoldRightLast
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
    
    template<auto...>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

template<auto...Args>
using Metafunction 
= CognateFoldRightLast<Subtract>
::Page<Args...>;

static_assert(Metafunction<1, 3, 4, 3>::value == -1);
```

## Implementation

We will implement `CognateFoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct CognateFoldRightLast
{
    template<auto...Variables >
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Variable, auto Initiator>
    struct ProtoPage<Variable, Initiator>
    {
        static constexpr auto value
        { Operation<Variable, Initiator>::value };
    };

    // Fold twice.
    template<auto First, auto Second, auto Initiator>
    struct ProtoPage<First, Second, Initiator>
    {
        static constexpr auto value 
        { 
            Operation<First,
            Operation<Second,
                Initiator
            >::value
            >::value
        };
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {
        static constexpr auto value
        {
            Operation<First,
            Operation<Second,
                CognateFoldRightLast<Operation>
                ::template ProtoPage<Others...>
                ::value
            >::value
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxCAAnKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BXIFVNQJ1DQTFkTFxibb1jc25bcM9faXliQCUtqhexMjsHASYLMkGGyYAzG4bWzuY%2B25MXkQAdDf72ADUyAYKCvcA8slxTI4CdyYaAEEFARiF4HPcPMBmBsAGKedAAJTwwAQvSYwP%2BAJMAHYrID7gT7kdtt9TgcLtcbgA1Bp4JjReivP74wnA0Hg5TEVBEZRMYCYe44qzYgAi%2BzxWJZBIA9NL7hZ0QLzkoQJjMYT7rL7nDaOh7gJVld1YTiSczhTUPcacQ6QzMKR7hb7gBJBgZb4kZkAjVssEEe6c7moXn8s7W230B2u91EYhejVC40agnA754ZCPATAzCqZLER2XS0ANzEXlOUuTQven2Iad%2BB3D9MjLrdjg9cb22BAIBL3gFOLFewlCdF4rVFa1Or1BAA7unMEaK6bSebC9q8MRgQ6nUJqgJ0Nu19G27H46yQX6A1yeXyyW4YRut/dd2gGAeWzHPZ2k4LcT%2BffUjgZq%2B2a5vmTq9mWgoViOFjQd6yaIR8Xw/AwZwPpuBCkP%2BiHVihmRnC%2B%2B7YTBuEasedKnqRiF3N2kHlghZEErRPalgxZEDmOFacUO46MZqcoItUyzpEWSqKqqgI/lqADqNobPqlxEggArPP6s6WvwuoKA6CCGOg9DKQKNCYUSM6WskDSsJgGybiR/Favp9zEMJm4Cl46RGEZzmYMCRKWqg0T1GE3lhJ%2BxCLvxy67OSa4YU%2BO57m%2Bh6UlcbwECpm5nimF4ctewa3uhj5Yc%2BSXvulmUKDcRrftxf7UfcqZAZmDCgXmBZEPc9E4cx9X8WRyG1qhRWYfZTGEoNdZoQcRHJT1TGQtCmBTkiKJohiByTcNtX9eN9zdtFAqBjeoabRlcRVbcO17cmdFsfNCadndfYPYSLHdQ1PHDm9o68VJS6bCSMXnIW1UAsALmbIwBAKNl9weWEwABregp7CKV5BiGd7g5DbCCJdNXYFxWK/RKmLSgAVFT1M07T0rkzT9wACq%2BTD9w0/TgKU7TPPU5zkoAodq6dQCKWWlYO2%2BuCQheEFtYOGqfUAWmwFZhsYEdcW911XB3oALTyr%2Bg5k6TfFC7FqUAsQwCwztCNeQAsjZTBUF4DCdAw8H7Oji2kityKosE6IEIRssgkwCs7d2WNnFbNvVX8f0C016YAProkojQQE79Su%2B721uFwDp7A60j3Hs71sajg7o3rXBzOKHALLQnAAKy8H4HBaKQqCcG41jWI1SwrP2Zh7DwpAEJoTcLAA1iAreSFcGiSFw2J7BorcaGYABsO9mP4gQtxwki8CwEgaBopCd93vccLwCggFfU9d03pBwLAMCICASwEMklzkEoGgLYdA4gRGspwVQ/gd56x3pIe4wBkAZikFcMwvBMD4FjHgdAeh%2BCCBEGIdgUgZCCEUCodQr9SC6CLjOWsyROA8Gbm3Du08e6cDeJcf%2B/pUBUHuFAmBcCEFIPuCgsw9wIAeBAfQfM5hx5zF4C/LQCwIBIGAckUBZAKAQDURokAwApBmD4HQWyj8IDRFYdEMIDQACeDDeCWOYMQaxbxojaGqC/CewC8YEDeAwWgtjKFYGiF4YA5xaC0EftwXgWAWCGGAOIQJG53F4DEpE7uOZhIbDseQQQmBj7d1oHgaItYnEeCwKwkEeBz5RNIGJYg0Q0iYBFJsOJhSjDTwWFQAwNsqR4EwDOZCncJ54OEKIcQxCRlkLUKw6h%2Bg4koAHpYfQRTH6QAWKgZIqFIl62BOgb2phLDWDMLfOpNosCrIgAsDoqEXBvjGK0IIb5pgDHiEXVI6RUL3L0O8woDBnllEGEXa5tQRhNE8C0PQwKuigv%2BbMIFoKvnwqmGEfoALXlXOHqsCQTCODt2vqwu%2BfDoGwPgYg5BS8xEQFwIQEggox71wUR0hYKkmBYHiJc0g89JB7CuAkPY2JJArzMJIHel9W47ySMfU%2BpBz7jyuDvLgO9/AJH8IqxeXBW58p3viyhd8H5P0nh09%2BX8VE/04QArROjpHgLYJwBoLAizYj1kwR4BgvJcASFcLgy90GYJINg3BsgCHjOkJMpQ0zKG6EMbQpg9Cok4rxTfXgd8OF/yUjwx0xAHVOpdU8OJIjPXeo0OIyR6jpF0r2GYeRhrX7KNUagKRcRAHaIbWWwY9rHV6zzUYD1XAr40FoCYyg5jKEOJsdksdTiXFuIcNkrx0NfH%2BNYUEkJYSInZJia0tY3d8AuRqKk1hGTkCXDWBPMIGx8m8EKcUmxZTt0KJtNUiedSGlKGabEowbTQC1r4N0hQvT%2BmDOySM4NRDQ2yCmRQ7uUa5ntIOVYJZ16LnrM2ZkbZuz9mLIsMc5NpzsG%2BXgFcvJyTnAQFcIix56BYWAvyB8zIFGfmoWo682wxGPbdFGOC8YrH7CoQ470FFMwaOpk4zkB5ImBMlBedixYywsX130MwnVt9OCZuzc611%2BaPVeuXuI6lsYK0MprUo5lmBWWDA5VKs%2BIA9iepXtiTV2J16SGFXAouSa2H31sAaxRb8P7f1/lw5tVqwEQI4PawRLAFBFgzEWbTJxgS%2BppWcwN%2BCxlgZIfIcNUGdA2dIDGuNjDFO4pYbq9h5ruG8Ii/AqLMWurxdJH5CRraNEVr2NW3zdaUAtekcFnrgwYvJGSKnOLCRU4JYIOnLNcCjGDousOixVinETqW841x7i50Nu8YugJO7MDBNCWIddNTN2fvvaQXdySD2UKPSe7J568msOvSU6xd6KmPuyS%2Bxp77WmIyNV0vk/6%2BkDM%2BEM3gIH0sSHA6Q7LMy8tuuMFh5Z0RkM91Q1mTg0pdkLMOZYHDPc8PnMIzxkjfgyN3K4w8kIgnpNvIKJ8yn3z6eZGY5CtjfGEWM6BezkFyKpNoshZzsTgu%2BeorhRiuTRCE2lZUxwNTkXouxYaxsJr%2BnaWyKM510z5n2U4ulefMwnq9h7FblvVel9jfYiVcp5NnB9XPyZZykAkhW68tbv4XeCRJAJHXvyrgJdj57Bl7brzWvitoJt55xltaFh1PSM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_fold_right_last.test.hpp)
