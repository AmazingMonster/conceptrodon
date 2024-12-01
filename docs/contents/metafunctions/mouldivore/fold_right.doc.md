<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRight`

<p style='text-align: right;'><a href="../../../index.md#algorithms">To Index</a></p>

## Description

`Mouldivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Operation
-> Initiator
-> E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Operation&lt;E<sub>0</sub>,
        &vellip;
   Operation&lt;E<sub>n-1</sub>,
   Operation&lt;E<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRight ::   template<typename...> class...
            -> typename...
            -> typename...
            -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeft
{
    template<typename>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
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
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>;

using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRight
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements >
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Element, Initiator>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    Initiator
                >
                >;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    typename Detail<Others...>
                    ::type
                >
                >;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };
        
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAc0gAOqAqETgwe3r566ZmOAuGRMSzxiYFctpj2xQxCBEzEBLk%2BfkG19dlNLQSl0XEJydIKza3t%2BTXj/YPllSDVAJS2qF7EyOwcBJgsqQa7Jv5uu/uHmMenAJ6pjKyYAHTPx9gA1MgGCgpvAPJ3xCYDVeJg0AEFxsQvA43gAxTzoABKeGACAIoLBJgA7FZwW98W8zgcgZcTgRbvc2G8AJIMLJAkggvEEyHQghvZTEVBEACyCIxBLe2NxYMFgqJFyu5LuzDYz0e2HobEEPyZorF%2BNZMIAIphmnQhTjsdrjiKBRq3gB6S1vCxMJRvNz29gY80a61whFvARbR5usUSklSimyzBvRV7Rjo/zYf2CrXs3X62hXCPK6Ox5ka4Vxi1eTJGQkUoX%2BbV/AFA7KppVR0g0umOBnEEH%2BEUWw0m1uurNij3w2joQkAdzwvtz%2BMDRzJIYecLwxHGdellLDQkwaAY6DV7YTbyTTDoV1h88XbzXG63MfHhrb7YJ%2BYiwCLd2vguOZfx/wSlYER5PBFIV8LS/QFgROc8BHQQCezvC1aXpIhmxg2CS0zdUUIJFtb2zLFOzNZD8Q9RF1w2TIADcwydJQQG7dDextAB1YhCDDdZ2QIBAwy%2Bdih1QN5%2BAHBQ6wQQx0HoQlOP4/9hz41IWgeXYF2gujBQ9US3mIEiFzDB9Cw4sNNPGQk%2BNQWJ9QYCSwwiBCSD9AjCT2YkpxuGVZ2PBcAOfFcz3XSClxnOVnl%2BfSF23C1d33Q8Tnc08IM3Otgs4hd5TCnDsLvXSn2XID8XfAkQJ/Bg/w85SMMFAqwLcOKoJyu9l1DPc9QPFMTkShIFBSq97IwkAQGy7qLVSsqsOvY1TVo9tJ1JFyV3lMFgE0yMVSGwVMrePkBxLMtIpatx5sW9MOpeGNeuyrsezG86VMwnspuDVzAsefbMCWggFCGtaNsHPLOW5VAvquZ7XqOv0ryuy78LBS0ACpYbh%2BGEctDEYbht4ABVMHGH54aR8EUYRgnYdxzFwXMfwIk%2BLwsBLNwvEcWhCGuNUMTu6cHrDMF/PZ201V3IQvDMwEHAACTqAFXSNHs1v6ui8vGdBeoiXYFrEAB9DdZkEK4lbrMFerIsQvDDABaW19cN0lY3B3DxtJ8FWZm0M5uIYB3q6sE1v5wWmBhPKvYIIWCFF2hxZOMEXZB15TopW2SbBB36oeZ3XbVT6mqoLwGAcbIhVJ0tPQHZFUWjKqBYDn2MwxXqAZOeXFcETAVdodWBE1kudbefwWzQ6v%2BTDiPOqtyG1uIhQvFodk8p5dPM%2Bz3887cf065AJXG8BZuNeaLWTg7rhXlKlkCAVleG6bluGDb7XBDrLuYwPzUj/r5X1/Py%2Bd%2Bvt5JGZsHIdmRxkFVvaJQrQICj3HgQc23gwzvjysbLgyxTQcFWLQTgABWXgfgOBaFIKgTgi9LDWDeAodYmxoFmH8DwUgECsFINWAAaxAKgyQjwNCSC4FifwGhUEaDMIEQIZgkhJH0JwSQvAWASA0BoUgmDsG4I4LwBQIApHUK0KsOAsAYCIBAGxVIdNyCUDQPsOgCQogPE4KoJIgRjaBEkG8YAyBkBvCkI8MwvBMD4EQngBWNR%2BCCBEGIdgUgZCCEUCodQNDSC6BqEOQEqROA8GQWgjBmheByN%2BHTXR7JUBUDeBYqxNi7EOKccwswbwIAeCMfQYgQpyHwN4CopBpAIBIEMakYxZAKAQFae0kAwApBmD4HQRSiiICxBSaQWIEQWjXHibwSZzBiDXF%2BLEbQ65qGUMMemX4DBaAzIiVgWIXhgBOloLQRR3BeBYBYIYYA4h9nzjWXgCi5zsGYFUCRXYszyANxQREhmsRASLI8FgcZAc8DiIuaQCixBYgZEwLqa5RgGZGBSasKgBhXYADU8CYCHF%2BTBlDfHCFEOIIJRLQlqHGVE/QNyUDWGsPoPAsRFGQFWKgVIDRznG3lu%2BUwBDLBmFkdC5iWAWUQFWHYR5zgICuCmH4GoYQIhDAqCMGohQsgCDlQUDIGqGDzGGIkGYdQpWNAmG0TwHQ9CSrnqauYSqFiqtsGarVMwzX6pVYaiVJCtgSESRwdB0jxlyNyZY6xtj7GOOcaUiAuBCAkBqRQ5Y9TUWrE4kwLAiRxWkAYZIfwjwACc/gsSSFYWYSQgRJGoMCPm4RHBRGkHERQx41RAhJHzUkLggQmFcFQYW4IMjUmcAUUoqhqKmmaOadojJejOndKqaYtgnAWgsDIliY2TAPgGELFwfNjwuAsLcR4kgXi9BEv8aS6Q5KlCUoiboAZMSmBxIuX6gNA6cGcHSQQTJ3ocnLtXeuzdNynG7v3RoMpFS2lVITWYJNo6aFqJaagSpCR9FdKQ5BkYf612fBuTurgUiaAT3apQMZET5nTK%2BeRxZyzVkOC%2BZsqM2zdnjIOUck5ZyvlXJuXc7B%2BBNLZ2eeMt5HztiUNXr87B/zAXXGBdsbBYKIWUOhbCpQCLuOPjHeipgWKcV4plF8s9JLAmXtkBS8J2C700pRXyqwlhGXMvgGyjl2QuU8tLDZ6wgrUnCq8ZjRz3QTUuE3C6kIm53WLDVTqhoIX1UNHC4661DQ%2BiTAtdMALNrksDHtQaq1zrUvyqdXasoOX4FrA2D60rvzX1Bs4G8LDAGcPbpAywspsbEIJrqXB1RqbMDppGFm359bG27tYViXtWIOGSDLTYmob65HDuUWO9RWidEzoMeh9pC7tjLoKSwBQZFHFkR3Y8C44xD1xpFae2Q57jPBPkNe8zOgAikAfU%2BhJtbqsRLSdOrJv7iAsF2/tw7x3TvsnKRtqDZN/CwYaQhlAEOUOzoR4kA7qRUiqyO/m1WoPAH/ZsYMojC4SPjKo3syhpOaNrPo0hrZOy9m8cwIc45YgOOQq40iuTlyHkCb8xE4TyA6aid4OJ8ZUnpmydBcxRTvBlNwrU0ijT8G%2BAYoUNi3F%2BKDPXaMxIEzISHtUue1u4w9K7P/LFU5zlnBLR1w8wKoVCQRV%2BdZelhoQX3D5b0Iq4rHrtVFGyDFqL2R4uGpd70PLeQCuJbD0V5VEXCspYj7lmPDrPVldIb6j7ySvu1Z27YvbB23iY5OySIyMaj3VLJp12HPW%2BuZr9UNkAZhd3%2BH8Kg7hbDJEt6xK2wN2f5G2BHdX7NIBJCoILagpIvD82SHzRwotXB/C1v8Fn2RQ6uu0Nra43vq/%2B9D%2BhZkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/fold_right.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right.test.hpp)
