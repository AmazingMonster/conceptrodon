<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-left-first">To Index</a></p>

## Description

`Mouldivore::FoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;, Arg<sub>1</sub>
   &gt;, Arg<sub>2</sub>
      &vellip;
   &gt;, Arg<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
FoldLeftFirst
 :: template<auto...> class...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeftFirst
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct SubtractHelper
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Mold<Args...>;

using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

static_assert(Result::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldLeftFirst
{
    template<typename...Elements>
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Initiator, typename Element>
    struct Detail<Initiator, Element>
    {
        using type = Operation<Initiator, Element>;
    };

    // Fold twice.
    template<typename Initiator, typename First, typename Second>
    struct Detail<Initiator, First, Second>
    {
        using type
        =   Operation<
            Operation<
                Initiator, First
            >, Second
            >;
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<typename Initiator, typename First, typename Second, typename...Others>
    struct Detail<Initiator, First, Second, Others...>
    {
        using type
        = Detail<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::type;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIADsSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uu/uHmMenAJ5pjKyYAHTPx9gA1MgGCgpvAPJ3xCYjVeJg0AEEJsQvA43gAxTzoUKYKgEWF4YgTUFgkxJKzgt4Et5nA5Ay4nAi3e5sZ6PbD0NiCBQg/GEyHQghvAAimBadDeOKsSU5xzx2JZBIA9BK3hYmEo3m45ewsVjCW8pXCEW8BFtHqrCcSLlcKXdmGw3gBJBjZIEkUhEylmzBvOl7RgEZlgtVsmHc3m0K5Wm1EMgu%2Bnuz1qgX6tUErxZIwOu78/ycv4AoE5QPWxy20Ouhke/zYEUx/lC0vgssa%2BG0dBEgDueF1ZcNpONjoelpzeDz9pNVOdaIxBH7nfNQkwaAY6EjrIIUN9PKYdGzwbtcPRE3tk%2Bns%2BLZej4tj8YiwCTl2PUdThP%2BCUzAiuZdjt4zwJOz5fsaDuZD9uHmJXl%2Brw7lOAizkBL4gv4opRhWMEqseGoAEpThsWQAG7OoqSggIhXqEjWWoEE2Wz2gghjoPQRIIM6NAjjRxCYM6aStA8uwYqQ1bSpRbxMcg6HOqeiYELRfGYBMerHm2RzkuOzo/r2f4Xk6m4jmOppdru4EaYONK/KJCRMgex4%2BhyforgGJyKX2anbm82kzvaBm0RiNJzgSR4ES%2BwnngOn6eTeFmrh%2BkGxnegLvm4AXhW%2BWahd5X4vjZykAR6YXXtgoF7jFmXOYZbkvGFrwgCA/kIceOLChVYqJTJZI3Jp1LPGCwBMW6jIeW8vlvAAslqxxpsFVluK17WFgo7nFqV5WilVla1RKABUK2rWt60Sliy2rW8AAqEkED8a2beC23redK0nbV5j%2BBEnxeFgKZuF4ji0IQ1yeli9Udk1zpgrpqlWCZEILuyDleLEC5MA4AAS9QAiquJlj1A4pmmEzoKVES7G1YgAPrTnMgiHic2P2mCpUYWIXjOgAtDKlPU2SJY1fNrPgt9cm/TSYLEMAxkluCPVCBDUMwoN4OQ4CsPwwkVy8/zU3YDNlILV9ewkrJjV6S1fMC1iPW9cuVBeAwDg5PyVY3rWiLIqiW5Fm4ItS9DRbKyA/V1vLetK2rQsJueqEKF4tAchLRstCbZvAlb0WmQQmMgNjmC47QBMCETjtk28XAgWWGNY4IKeAmnhMtMTpOCPa/h5/HifJ6n6cMJnVzZ5IteJQXSdF43ZeGFnVdvDXwPQXN4JzI4yB43KShtBAQchwQjPeM6g0S7TACcywihwqy0JwACsvB%2BBwWikKgnDRZY1hvAo6ybKvZj%2BDwpBL6fu%2BrAA1iAB%2BSI8GiSC4EkfwGgD4aDMIEQIZgAAc0D9CcEkLwFgEgNAaFICfM%2BF8OC8AUCANBb8tCrDgLAGAiAQDrAIGkF65BKBoH2HQBIUQHicFUNAwItNAiSDeMAZAyAc5/zMLwTA%2BAQx4ExlwGQggRBiHYFISR8glBqE0DoPQDZARpE4DwPeh9j7KPPpwX4L0qEclQFQN4rD2GcO4bw/hjwzBvAgB4eh9BiD8iflwZYvACG71IBAJAdC0gMLIBQCAASgkgGAFIMwfA6AcVwRAWIejYgRFaNcTRvBknMGINcX4sRtBTjfi/OhhZfgMFoGk9%2BpAsCxC8MARUtBaC4O4LwLALBDDAHEJU/A/FHBYSaWfTAqg0K7HSeQIu%2B9KlvViICbJHgsB6IXHgZBzTSBYWILETImBuRtKMG9IwyjVhUAMPzAAangTADY7wnxfvwKRohxByNuQolQ6hKm6AkQYfZphr6WH0HgWIuDICrFQGkRoTTaYY0Gt8qwlgzCYLWcQMREl4CrDsAUnILgZzTD8BIsIERhhVFGBI4o2QBDYr0CSxoCwRiJAkWi82Ah%2BhTE8J0PQ9LGhMsGPixYRLbCTHaCygodL%2BXUsJbS1F98tgSG0RwI%2B6C9FYPMWwjhXCeF8KkHYhxuBCAkDcc/Txr8DmrFokwLAiQIBfxAJIfwjwN7%2BCSJIABZhJCBFQQfQIG94EcEQaQZBz9HiBC4IEaBG9oFBt/lwA%2BdrggYN4FgnBeDDXvyIaQvx5CjHUJCWElxTC2CcFaCwDCSRaZMA%2BJ888XAN6PC4P/IRIiSBiL0E86RDzpBPMUC8vRuholqKYBo5pMq5Wxv0RwQxlCXrajMQWotJay3tJzlWmtGgHFOMCS4vVZgDXeKIf41AziEg0NCXutdoxp3Fs%2BO0ytXA0E0FDkZSgiTKmZNSaM592Tcn5IcKM4p7pSnlL0dU2p9TGmjNae0zpZ9unor6XowZwztgv2ThMs%2BUyZnXDmdsM%2BizlkvzWRspQ2zwNngOXwY5CgzkXKuaM5t9zZFttkB2pRbyQDRPLSgaw1g/kApRefUFORwWQtTNC6wcK40IqRYCi1PR0XOAgK4cluKZyiqWMSzIpLciCpxekNTVLuU0rZfUGTTR%2BUKekwy4z8w9NirZSZzTNnLMVH0x4tYGwpXOYmUOhVnA3hntnRexMlbq3/y1fW1xN0PFeKNaQE1ZrKAyp9X6qtACkhRpSP4SQzrOESOHfG2wibt2%2BNTUgChxjD3ZsYcwjgBarEsAUBhPhGFAsXAmHWnViLxHyJbXR%2BRjHXln10P4Ugvb%2B1aK9Z5ypWCx3GMnT54gLAat1Ya010kEwV3HqCXq/wW6SNpvK8E2h62XEgHq2kNIeNGsbzxs1gg085ucJiXejED6kkpOya%2B17OS8kFO/XukpZSKmQcwDUupYgQMrLA7szDLT0TQeRZUuDAkRkrKQ3o1DqSMMLMRTh3geHNmEd2cR5NpGmCnPOZc001HZBdYkPRwQvWu0BH0O09jPybBTMk8CvjGdOASgLsJ2F8KEjteRUCszjRMXuDs4pxEVmVPaZKDkUzlKcjKd5eyvotn8hafV4ykVsu1ea9ZcKhzBKVMStc7IwduiJveeq1w2r9W3gXceNdkLbW9URaTYQ41mBTWjCkxMhLLGq3%2BH8AfMBgDUGh6SMG%2BVNvsF5fwVF7%2BkgD62oPtAiBG9JAb2Afargg2Jn%2BGt5gzgkXk0ysEXH0vCft2rDWVkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/fold_left_first.test.hpp)
