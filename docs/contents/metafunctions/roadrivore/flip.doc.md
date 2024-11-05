<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Flip`

## Description

`Roadrivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.
<pre><code>ZerothLayer{FirstLayer} -> FirstLayer{ZerothLayer}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> typename...
       -> template<template<typename...> class...>
```

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> auto...
       -> template<template<typename...> class...>
```

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> template<typename...> class...
       -> template<template<typename...> class...>
```

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> template<auto...> class...
       -> template<template<typename...> class...>
```

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> template<template<typename...> class...> class...
       -> template<template<typename...> class...>
```

```Haskell
Flip ::   template<template<typename...> class...> class... 
       -> template<template<auto...> class...> class...
       -> template<template<typename...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Example

We will flip `Operation` and its member `Mold`.

```C++
template<template<typename...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

using SupposedResult = Operation<std::tuple>
::Mold<int, int*>;

template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*>::Road<std::tuple>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, each case is pretty straightforward. We will implement the case where the function flips the operation and its member `Mold`.

```C++
template<template<template<typename...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBLSAA6oCoRODB7evnrJqY4CoeFRLLHxXLaY9vkMQgRMxASZPn6BdpgO6bX1BIWRMXEJtnUNTdnlCsM9YX0lA1wAlLaoXsTI7BwEmCyJBpsm/m6b27uY%2B4dbO0x7BwQAnomMrJgAdK/72ADUyAYKCq/P7y%2BPwUHwA8g9iFd0u8TBoAIITYheBwfABitDwiVhcJMAHYrPCPkSPkdLtdDvdHmx/th6GxBAoYYTiYjkQQPspiKgiABZTzoD7Y4mC/FC4XE0knM6Sq6nG6U5jUt7%2BT7fJi/f5w4DETBbRgERkqsXij5eVJGD4AJVQTAF%2BwAImCIVCBGctTq9Qz/ky4SaiSAQDLNh8%2BbR0GdaZ6Dd6jf4Cb7iXj7ft48aSRcpfKHoqXq9I/SDT7hWawsAQ/zBf5HZzuahQ%2BGDvn9X9ldgU9ik%2B34diAPQAKgHg6HPd7g4AKtghGPByP4f2hwvZzju2Z/GFvl4sJW3F5HBi7j7sUG5edjrLpQqnjHVcDr9jWSjwXEXQwO6LmUTjxfs1fW2mH%2ByNa8hWeJWLiyZxh2H7pme5J3D%2BSrPHCxDAIabbQSWFr1pW1ZcsBYZuihLYArGqbgV2y5wphZZCF4iS5Jg6CWpgCheLQ7IOk6z7VGcEzoAGBB0fQPoBvWZxhAQpAfBJfYwpB3bwl%2BWZUrmSFET61EhpgdRUF4DAdAIOFohiWIHE%2BkI8Ua8KifyhGoXe8mUZpzGsexRk8tpTC6fplluBJUkye8AbWravEEPxgZCXKbaOfedSOMgAD66pKA0EB8QGChPMlhpuC5bGSR8tH0SkjH5ex7zzCmHCLLQnAAKy8H43C8KgnBuNY1gfAoyyrJggqrjwpAEJoNWLAA1iA9WSM8GiSFwuL%2BBo9UaGYABsa1mAAHFt%2BicJIvAsBIGgaKQzVaKQbUcLwCggKdI0cFoixwLAMCICAywEIku7kJQaDbHQcQRE8nCqFta0ALRrZIHzAMgyAfFIzxmLwjGECQeD8eU/CCCIYjsFIMiCIoKjqI9Oh6AA7pCiScDwtUNU1o2XZwoK7t97KoFQHxg5D0Ow/DiMzWYHwQB4AP0MQA3%2BAsvAPU9pAQEg/2JIDZAUBAKtqyAwBSGYfB0JsxC3RA0TM9EYT1LcdO8BbzDELcoLRNo7QPUN/0FqCDC0Nb5OkFg0ReMAbhiLQt0tf7WyGMA4h%2B/gOodAAbixzOYKo7S7usQ0SZUzMYtEkIOx4WDMwQxB4EdEfJ8Q0SlfaUdGBiRijYsVAGKhABqeCYJTT7NUNOPCKI4iE4PJNqMzujlAYzemJY1j6Hg0S3ZAiyoIk1ThxDfEOnPViWGYF2oNX5dYCvECLG0Bl%2BBArijH45QhNMxSlDkKRpAI99v3k6S9C/cwVCqJ0SYX9xiVFdsA7of9%2BhlCGN0UBcCGjQNmGUS%2BvU1gSAZhwRqZ1mZXR5uDKGMM4YIyRiLCAuB0ZS3MDLeYcsW6LAQJgW0AwL6kEmpIfwzwACc/hcSSDmmYSQa0Tr1TWtwvaHADqkCOjLZ4a0uBrS2twraijppcHqrwtauC/ZXRundYaLdFZvSVh9dmP0NZa0lsDNgnB6gsETriCGTAgTR0Rtw54XBZqo3wEQU%2BehB54xHtIMeSgJ5%2B10PramTBaYtSwTg86rVWbmM5tzexjjnGuItFwDxXiNCi3FqrSW0szB0MMeTZ6ytUASziL9TW1SikDHSU4tURgclcFOjQdicQTZmz9nbK2NtSADIdk7F2Dghke31F7H2zMA5BxDrQMOQysAsGjrHC68cIHJ3DhdNOGdNhDJznVP2%2BdC63GLusC6ZcK5DOrrXJQ9c1mN1LEYtuTBO7d17tmIZgTh4ExCbIceZMLqRP0NHFAnVLCL2XvANeG90hbx3lWPe1hD6tRPpjFOq9AEQOcLfBg7hPDND0E/IoMDv4fwyMSsYpBchUuQa/MBQCBBdBGDSh%2BuLr5sqmOSlBegJjwI5QKyYjK5hoJWBghYkiEl4M4B8ZpmTWllhyZ42aotKF%2BOlrLcpT1GHMKwPENhJzpGyI8XNXEmjcSLUkEI6G5REks2urYAx8sarGPgKYz6HM6lWKBiDDg9j%2BYsAUInBGidVUnAmD4qhmMAmyCCQCom8gwkgopoEaJsT6YyqZro5JX1dwfC5gq4gLBg2hvDZG2UEwCkNLVtLfwZS3WVJQHWyWvq20DDDfRRKEbuGJSjQQZKpboYG26cbSgfSLojN9kNGdYzXaTOqZ7b2vtNmYEDsHUO4chqrPWVc3gWyk4pz9vs5AmcjmCFzqcpe5zLml3LpXIa9y64Nxjq8ipfB24KC7j3PuvyE3/MGKE0mk8AjgtnlCmw%2Bdz7ws3pwHsGVUUHyPpis%2BcKuXVBcIShBZKZhMrpe/aoCD6XVDFbAq%2B1QeUIMo5ApBz8KXjBAcKpjUCGP8ulT1SVBN4m5qPvKoNMMQ1ho%2BH254g6NW%2BJINqptDDSBMJYUarBpqQBmA8f4fw9UVrzROhp3ESidH8edbde6cmOH1R4fVLa61uGSG4YtPhXBAgnP8HxpJzrm1YJRoZ9z9CKmLGrqkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/flip.hpp)
- [unit test](../../../../tests/unit/roadrivore/flip.test.hpp)
