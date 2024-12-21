<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-bind-front">To Index</a></p>

## Description

`Pagelivore::BindFront` accepts an operation.
Its first layer accepts a list of variables and returns a function.
When invoked, the function adds the variables to the front of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Vs...
-> Args...
-> Oper&lt;Vs..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront ::   template<auto...> class... 
            -> auto...
            -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct BindFront
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `-1, -2` to the front of `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<-1, -2, 0, 1>;

template<auto...Args>
using Metafunction = BindFront<Operation>
::Page<-1, -2>
::Page<Args...>;

using Result = Metafunction<0, 1>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<auto...> class Operation>
struct BindFront
{
    template<auto...Beginnings>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Operation<Beginnings..., Variables...>;
    };

    template<auto...Beginnings>
    using Page = ProtoPage<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG7bu/uYR25MXkQAdPdH2ADUyAYKCk8A8ilxTPWPJg0AEExsQvA4nhYwugAGLEWSAoEmRJWYFPdFPU57P4XY7XO73CyYYBhBhhYAKAFojGg8EEJ7KeFEZRMYAXano5GooEY3mYnbYg54m6oe63ABqzTwTGi9Eph2wiL5GK8GSMDNZmCeRwAIl8fsQ/llLkSSQwyUYFGLSE9JcRpbLMFaHgqjtzecidW7EUqMVjzpd8aLCcTSeT5YqOU9VeSNWztYc9YzUMzNSbQ%2Bbw2KAYduZ7vcDEQB6ABUZfLFaLxfLABVsEIa%2BWq8DSxW282kYWzIcwq8vFgE240AwNikCBGfcD/TjAyLs67gbSId9fv9c5OgTH1UIvClCph0AAlJ1eWj03X61fG44AWi4NpvgSeGhtXBzeanAoDwoJtyBxApKlNzVYAngAWUwJoqC8Ed6gTPUoQYWF4UES4V0NNdIyBEAQBZNlLjvB8zCAnC8NxNx/wpedFXXQtgS3UDjwUU9z0TcDIKYaDYOvNwXyeN9XVozsQSaRxkAAfSYd44gICAxnQHCFFYTBJPlNwmJYm0dz3dIDw0s9HkWN0OGWWhOAAVl4PwOC0UhUE4NxrGsJ4FFWdYtXMQ4eFIAhNBM5YAGsQHMyRbg0SQuESQ4NHMjQzAANniswAA5kv0ThJF4FgJA0F9rNs%2ByOF4BQQBfXybJM0g4FgGBEBAVYCBSG5yEoNBdjoOIImUzhVGS%2BKb3iyQnmAZBkH40KzF4A9CBIPAFPvfhBBEMR2CkGRBEUFR1Aq0hdHvAB3Q0Uk4HhTIsqy/LszhPhuJr6VQKgnl6/rBuG0bxtuMwnggDx2voYhtW7LhFl4cqtGWCAkDalIOrICgIGh2GQGAKRAhoM84hKiBoku6IwmaABPE7eDx5hiAJz5om0TAHGJ0g2rYQRPgYWgiZ2rBoi8YArloWgSu4XgsBYQxgHEdm8GIGnHAANydS7MFUGmbk2bywm2MydtoPBokNcmPCwS6CHtbKBdIWXiGiXSdR2EWtaMPzlioAwKXFPBMH2ldrO8xbhFEcQ1p9za1Euvb9BFlAnMsfRtZKyBllQMcsn5m95N1UxLGsMwCvN%2B0sFjiBljsKWshcJDJj8e8QjCQYKmGe9CkyARy70Bv6jmIZ4nvIuHB6cZWk8do9G7%2Bpehadva872w%2B%2Bbru%2B/HhZgZWNYNgkM6OEs0h8t4Qqnr6gahpGsapE%2B77cBmgHPOB0GHeWBBMCYLB4gL0ggskQ5bgATkORJJHCsxJHirlcy8UP7pQ4JlUg2UvK3HilweKyUP7JTgSFLg5kv7xU3pdQqxVSo%2BQdlVWqkN6q3WavDRG/0upsE4M0Fg0tEg3iYC8Aw6ouAf1uFwMKU18BEFznoH2y1/bSEDkoYOO1dCBEOkwY6As14by3ldDgN1Go3CeA9J4NC6EMKYSLfibCOEaG%2Br9GG/1AaHDMCDPBFUIZQ1QH9OILUEa2OMcMDR9DXgi1YVwF86NtjECxjjHapNCZ0yCeTSm1NaamwZowAgzNWaXQ5lzHmfM6ZC1tpsWy%2BBJY91lvzWyCslbbDpmrWol0tY60JvrDJoNjZ03NpbJQ1thZGDtqAKxfBnYKFdu7T2dN%2BF%2B1WkI2QQdtq2XEWHe26crBR3KfneOicBDJ1TomKZmds5xFznLOOXRi7OAgK4GeQQkLzzrqkdIjdsgDzyPXc5bdq7zFOcPXufRDlPIEKPfo9yO5D2nlciuU9ZhfInqvJe7kQUazkVgzg6jiC0PoYw9xLC9FhVPtwkgpir6WPBrfe%2Bj9KBrwgVAth4VEhoMSFFAIACIqYJ2tg2wuCwaVWqnVBqd0HHkM6t1DgNDXosAUNLMa0tWG3HOGMLh585p8NkAIwZ615AiNGToEAhxSCSOkadMBkLaXXRIfdR6PKhp8oFU8IVbDRX0h%2Bk42GpjDgWMZdYlAVr/rsqdcMAVe5xKmvEuaySsLBp8DoL4/xuN8bkxCaGimVMpZ02iUzFmbNMmYE5tzMQKTTZpJadU0gWTi65PlorZAytimCFKZrbWusCZVMNrU029SrY2xaeSfBTtWRdLdh7H4XteD9JWhIIZG0FUh2VRM4wkcbCzPgPM%2Bo/MizyQjhnSwWdt45zmls5%2Bby/D7LLn8vQVcyjfJuUULIhzW5ZBOZPDdHzXm1F2Q0OeQKF4AomDu2egL93AsXq5Zeq1ZEXW1RwGFLBeX8sFcK81qLz4YrtTfUgd8H7DGfhrQlCQ2GHEOOZWKEVcpocSPAmlBVOA4LKjB1%2B5lP7mWSglD%2BkgP5RW/lwFVGtDh/oI0VLF/kwGTXw9vQj7HFjLHNhkZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/bind_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/bind_front.test.hpp)
