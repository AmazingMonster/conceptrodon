<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Flip`

## Description

`Raillivore::Flip` accepts an operation and flips its *0*th layer and the *1*th layer.<pre><code>ZerothLayer{FirstLayer}&nbsp;->&nbsp;FirstLayer{ZerothLayer}</code></pre>

## Type Signature

This function has multiple signatures.

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> typename...
       -> template<template<auto...> class...>
```

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> auto...
       -> template<template<auto...> class...>
```

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> template<typename...> class...
       -> template<template<auto...> class...>
```

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> template<auto...> class...
       -> template<template<auto...> class...>
```

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> template<template<typename...> class...> class...
       -> template<template<auto...> class...>
```

```Haskell
Flip ::   template<template<auto...> class...> class... 
       -> template<template<auto...> class...> class...
       -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Flip
{
    template<typename...>
    alias Mold
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };

    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };

    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<typename...> class...> class...>
    alias Flow
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
    
    template<template<template<auto...> class...> class...>
    alias Sail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Example

We will flip `Operation` and its member `Mold`.

```C++
template<template<auto...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

using SupposedResult = Operation<std::index_sequence>
::Mold<int, int*>;

template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

using Result = Metafunction<int, int*>::Rail<std::index_sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Although there are many cases to consider, each case is pretty straightforward. We will implement the case where the function flips the operation and its member `Mold`.

```C++
template<template<template<auto...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEs6SuADJ4DJgAcj4ARpjEIGYapAAOqAqETgwe3r7%2ByanpAiFhkSwxcQm2mPaOAkIETMQEWT5%2BXAF2mA4ZdQ0ERRHRsfGJCvWNzTlttmN9oQOlQwkAlLaoXsTI7BwEmCxJBjsmAMxuO3sHmMenu/tMhydMXkQAdK/H2ADUyAYKCq/P7y%2BPwUHwA8klYncMu8TBoAIKjYheBwfABitDwSVhcJMAHYrPCPkSPmdbvdTgBPCHMNj/bD0NiCBQwwnExHIggfZTEVBEACynnQH2xxOF%2BJFouJpIuV2ld0uDyeqH%2BgO%2BTF%2B/zhwGImF2jAIzKO2Alko%2BXjSRg%2BACUmHRhUcACJgiHEKECK5anV6pkqo0myUgEBynYfAW0dBXeneg2%2B41HAlw0V4h3HBP%2B4MKynU1iYOkM/WG42sonm0LAUOC%2B1O7m81BhiMnKOMmNvP3x7HJ1Md%2BEAegAVAPB0Oe9j%2BwOACrYITjwcj3tDhd9uc4%2BHmI6hb5eLD2txPOiECksldwjOym4yxUvVufNUa6/Y9ko8GQmoMDvi4sk8/y2VUxg52N/UfTka35Ss8SsXEU3bVdP1PE4CD/Glc1eOFiGAQt/VLS16yrLkeTA8MPXQv57xgnEoK7WC4Ww8shC8JIUiUdArUwBQvFoTljidZ9XVfK5RnQQNQiwVQAH0lAARy8RhNiPQN6yuUICFID5lL7GFyOxeCs3/WlUJIo9aNDTB6ioLwGC6AQ8PRTErl4t03z9eEFMFYiMMArT4WM1j2M4vC%2BVMphzMs/iTmU1T1PeQMbToASCCEkARMwcSpJkyyFTjNN4VGKFkDE9UlEaCBBMDBQcwKw03F8jiVI%2BejGNSTAWLY2r3iWVMOBWWhOAAVl4PxuF4VBODcaxrA%2BBQ1g2TBhTMI4eFIAhNC6lYAGsQF6yRng0SQuFxI4NF6jQzAANlOswAA5Lv0ThJF4FgJA0RJBq0UgRo4XgFBARJlo4LQVjgWAYEQEA1gIJInnISg0D2OhYnCHNOFUS7ToAWlOyQPmAZBkA%2BKRnjMXhmsIEg8CErgZEEEQxHYKQqfkJQ1BW0hdEpgB3V0kk4Hhur6gaWY%2B0EnkhzlUCoD4UfRzHsdx/HtrMD4IA8OH6GIOaFqWXg/oB0gICQWGknhsgKAgQ3jZAYApACGhONib6ICiFmolCBoKR53gXeYYgKVBKJtE6P7Fth5tQQYWh3f%2B3gsCiLxgDcMRaG%2BobSCwFhDGAcQo9TvAdS6AA3NiWZSzoni2RblKqFmMSiV0fY8LAWYIYg8EelPC%2BIKImodXYM4xIwVpWKgDAwgA1PBMHZ59BsW/hqdEcR6bnxmVHUbO2f0DOUHGyx9DwKJvsgFZUCSV9k7RwTuNMSxrASYaO5brBD4gFYOisvwIFcCZWkCBh0H6EoZQ9BMQKJkTwLRgH5FfAAwYcRKZv1fD0cY4DJiVGqN0GYMCFhwOmL0b%2BehcqNCwUArgr9pqbAkHzDg/VSCvWGpwSWqMMZYxxnjAmisIC4FJurNcpDtaDxWAgTATAsBxBfqQDakgjjPAAJxHFxJIXaZhJCnWer1U6MjbocHuqQR6C1ninS4KdS6MjLpGK2lwXqcjTq0MFpwL6P0lqDz1iDfWYMRZQ1NubNWiM2CcAaCwfOuI0ZMCBBnfGMjnhcB2sTfARBH56GXjTRe0hl6KFXizXQAROZMG5kNKhNC6HvU4MLCGTwPjiw%2BAEoJISwmWi4JE6JGglYqyNmrDWZgtZOKjoDA2qBVaxGhmbfpbShjVOCWqIwDSuCJFtjsYgDsnbZy9m7D2pAVk%2Bz9gHBwayQ76jDhHFmMc44J1oEnNZac%2B5bDevgPOjhC7JzeiXZAZc1mVx6tnGudcKQN2udrFubdFody7koHu6cjD91AD0vgI8FDj0ntPNZSSF501SbIdJzN17xE3gPa%2BVhd412fsfU%2BGRz6X0dHi2%2Bb1UAP3JkXI%2BaDA4ZBcH/fBlNghzEAUMSmIDXxsryGkaBnLYEEKqEy2oMx%2BUIIwb0Yh3LcHIOyD/QhsxigitIasdYFCNUfMKXYjgVTiCBOCaEyZ5YGlRJ2krLh8SNZ8O6QDQRwjRGUCoTovRkTdq4isbiA6khlGY0pkUj6DjfrOKBqDcGoshneIRkjDgASZYsAUPnPG%2BcLUXFGLE7h5NEmyGSaihmGK15vV0EcUgOS8m8y0Xq7OQsPFiwlomrGybU0fHTZEzNnJlYjONhrI4XSdZdT1n0gZJsYa9rViAVNjExIdrEl2gqRrMZ8DoPMxZztXY%2BzWRs32/tA67P6aHcOkcbmYFjvHROydFqXIhX8nOdy8APOLqoUuOw3mCCrp8/e3zflNwBWs4F3de4QrLM44eTAx4TyntSJF%2BaUUSDRYIYtmSQDloMLineNhCXwGJWfTgPZSqUssHfd6tKn64cZe/Fl7gUE/w5Wq7BkDBUZH5byjIcqcHSolXgujor0E8aIcKpj8DJV8dE7K4TJCyFarpgUgWdaGHNo%2BK2tNGb5SjGtXEkgdrB0CNIEIkRQxxEfPdfESJRwji9WOntZ6lncTGNsYpz6thHFDqWOtEAkheqyN6pdM6MjJAyIOvIrg6HOBHAU9S%2BxDrVpaKJk56LLn3MrA7mkZwkggA)

## Links

- [source code](../../../../conceptrodon/raillivore/flip.hpp)
- [unit test](../../../../tests/unit/raillivore/flip.test.hpp)
