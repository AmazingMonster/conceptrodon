<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldLeft`

## Description

`Varybivore::FoldLeft` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list with the operation and the initiator.
<pre><code>   V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeft ::   auto...
           -> auto...
           -> template<auto...> class...
           -> auto
```

## Structure

```C++
template<auto...>
struct FoldLeft
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<template<auto...> class...>
        static constexpr auto Rail_v
        {RESULT};
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<auto...Args>
using Metafunction 
= FoldLeft<3, 4, 3>::Page<Args...>;

static_assert(Metafunction<1>::Rail<Subtract>::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldLeft {};

// Base Case:

// Fold once.
template<auto Variable>
struct FoldLeft<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            { Operation<Initiator, Variable>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct FoldLeft<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value 
            { 
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<auto First, auto Second, auto...Others>
struct FoldLeft<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            {
                FoldLeft<Others...>
                ::template Page<
                    Operation<
                    Operation<
                        Initiator, First
                    >::value, Second
                    >::value
                >::template Rail<Operation>
                ::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEElz%2BpAAOqAqETgwe3r566ZmOAuGRMSzxiQCcwXaYDtlCBEzEBLk%2BfkG2mPbFDE0tBKXRcQlJKQrNre35XLZTQxEjFWM1AJS2qF7EyOwcBJgsqQYHJgDMbkxeRAB0dwBqLXhMsfQK59gmGgCCk8ReDgA1AAxTzoUKYKgEQEmQJWQIAEXOVh%2BX2%2BAHp0YCLEwlIDLkoQGi0ZiQWDAQJdjc0QcjidMOdLtdUIDHsRnq8GWdPj8/gDoaDaODIQRGWyOfQPsS4WjAXLAbTjkxThcrkRAQBJBhZZUkKU/eWAvlA5TEVBEZRMYAMg3y2Eo76Gw2K%2BmMl3KrlM253D6A5AGBQKQEAeVSCWV2X1jqdcuN0IRmGadFlMZhMttqflkwjyD9AkmmFUqWIgLVLIAbmIvDbo5m5faQ2HiBGBIytTqiGRWU8XpLuSAQJXvJg00izg7M7Cxw6UzH3Sq3PPPWW7tTuX6AwpV99gMRMIdGAR3tzZ06vJkjICAEpMOgws4IwEJpO0Rk7vcHwRbn0n8enqfIsSGYKocSoLiudzvvubBflGhrnhEwCApa1r3o%2BprmqgKGelBn5HquUp/qiiKAaiPykoK6AKgA7ngVI0qBrqqsyIJ4MQkykKWLFCPUAjoFGcZkkKEJQoywJsRxgI8WgDD8SexETvKS6MmWmrao4urEHBWYEP8JpmhaVo1oa9qns6jEem6FngcyBHrv6uJBqG4Z9NpMaCc%2Bt6vsBJnprWdbZo4uYyQWRYlqpQ7VjCPmpg2Zl1nKznNq5FzxQlSUtgwjJpQl8rthpnaceJ7GijFCUfAOkWYJx0l8Tlk79oOVbGblAFEf5vnTkBHVKdZnrKcx3prtgG6Oduu7QYex48j1coIZeN53ucj6ecmFy4TB%2BE/p87WdaR3yngNXqoONH6bdNp7zUh2FochBlYUZb4TXh37DftbUzuRWJXvU2yZOWI4Euw3UUeSBC0bsnEIIY6D0AqCAjjQJU0SyqQtKwiYJAopAkliMOAnuyB/SOV3wyOe6TNSPxHapxWSaptWyZxEE3MGBAI%2BxAm6fyQnCqJFx0wQNW8UzIbs1jdkzaZwE0yx%2BXPJ2blGtz%2BmYdh/5%2BZmR2y0NvoOYGjYuZG8mzcrenxomXk5dLpuGoFdF5gwoXFlx6pVfVdqa7lhqUSJooXGzHOvUr3sDkuyGPalZXe4byXG24HvpU2mXZdHMd5epCskEVEmlbbrWNVVwsyfxacF9glXNYnToVSA4eLa%2BAfJylM3p3KlfDtXH3WyR7U5drfUqbZ22jYGp2TbBJuZqTDe3atjduBtU2S/te19zLg%2BDSdkHPedSukzdy13WrkeL7vy/be9vefRiABU98P4/6Ikg/AAq2BCK/D/P%2BRj9/7fP8DqojMGcCI/ovBYHvG4GSuxUhHijGiEKBwhyAloAIJCaDLzpGogkCAmCMHoNLJxfBqDCGxDWNKRScoSEkNzPaJg3dgL8GIBAZEsQwBgGWlwNhABaHhFDgINmQLfZaDDxyjlPHuAg2wGB%2BivkiMi3wdYsm%2BMzFiVgTaCWUKgHBWkFKnntsFfMBwwquwrFXQRcJATYNwao7EawJF92vt1ZR25iDAAuj8UmABZS2VAvAMAaAIaKB0Hy8z9oyM4nFpCAjOLXdW613HB1/DfQxAB9RyCQCAQF8c0fxgSUpuDMLXBujJtG6NrlVNCR9/AAA5AhcCqJIQIQQzj%2BAoeODgGxaCcAAKy8D8BwLQpBUCcATpYawRotg7BHOYM4PBSAEE0F0jYABrEAvTJA3A0JILggQzgaF6RoMw/h/BmFqbU/QnBJC8BYBIDQGhSCDOGaMjgvAFAgEeUsoZXTSBwFgDARAIAtgEFSNccglA0BHDoAkKIGNOCqFqf4Hh/hJCAmAMgXMUgbhmF4JgfAnY8DoD0PwQQIgxDsCkDIQQigVDqB%2BaQXQcxqLNlSJwHg3S%2BkDOWSMzgwZrhguhKgKggJEXItReizFgJsVmEBBADw0L6AljmVwNYvBvlaA2BAJAULUgwrIBQCAur9UgGAFIMwfA6AHHYpQWIPLYgRBaAAT3ZbwB1zBiBOuDLEbQ9RvkLKhZtYMDBaAuoZVgWIXhgCXFoLQD53BeBYBYIYYA4hw1sT9XgAG8bhmFl%2BgcV15BBA9B5bQPAsRmyeo8FgHluk8B3ITaQAGxBYgZEwAmZNRgy1GGWRsKgBgPH3DwJgaizlBkLNJcIUQ4gqWTtpWoHlTL9AppQNYaw%2Bhy0fMgBsVAcDsjxp4ZMOSCJTATMsGYF5zb2RYC3RADYdQgl%2BAgK4GYfg5hhCWOUSoBQMhZAEK%2Bn9RRsjDC/WMOYD6%2BgDGmJ4DoegIONAWCB0YiRwMLAA6hwYSGVgofvdM3YEhOUcH6U8nlrzRVIpRWijFWKtmyogLgQgJAYQgNVeq3tGwEZMCwIkO9pB1mSDODcKoZxAiSB2WYSQ/gHm9P8FUK5HAbmkDufMm4/hki1KqLU5ImyuC9OEykZ5vBXnvM%2BYs3tfzAXauBQK8FhrjVKrhWwTgLQWDlkCDwpgo1LyNJuFwbZeKCUkCJSS2Q5KZ3SDnUoBdDLdAWpZUwNlCbCPEcM7yjg/LQXXApCKlzbmPNeaQj5vzGg5UKr1Uq5jZwzBqrMz8rVOrUCKoSBCo1jXytjFy%2B5hyRhGlcEeTQWg1qPkQDtQy91zrC3jc9d631DhC2BsPMG0NPKI1RpjXGwtSaU1puGfgQmjhs08rzUTAtjaIgHB6QystFbnXVr2MMutDaFnNtbUoDt23ELmf7VaBQQ6R1jsLZOsLlKIuyHnfS4ZsXl09tPVYSwG7Yi3p3Xu/MnBD0EGPbD6wF6jNXqJZgJH3RejZBcLJdDIRZJYe/XMQof6cgwdmGkX9fQqdgaJ5mgQUG2gM7fezx9XPWcofmIMcn2ZWiC4I5sbY%2BHVXyZS6RzgpZiCufc557rhWqi%2Be2XKhjnZKusdq5qjjmAuNjF45dxTynNc7MCHpwI%2BzJASdRXMVLxnbCmY1b8/5QKQWCpa/Z2F8KOAuYlSwBQ5Zczlh8/SSYAXGPXpC2S6dIPqXyCixDnQIAonxcSxyuX3KGWvIy4K7LSuWCh/D5H6PHpJilba/qyrZwaue/qygevSr/ft7GBH1IqQ0lR6qGkmPBAMnK9RZawbWNbX2sdZ6ybs%2BvU%2Br9fNxrQaQ1ht25gSN0axAbcbVtrt93E0ZoaIdhlx3rh7AWedktV3y2VqdXd2t7Inu8Be2297XbPt1b4AO37w7R0wxx1eAgdk8JBQcaV09F0s9odjA114drtCdd0%2Bh410Qj1V0z0LAccRk8cb14B70egOcn0X0ec9AP0yhkNAM6dydacWdP1KDwNCD%2Bc0NSDGDidOdEN6DsM4MWC8hecxdFgKDuDZcFA8NKVksC8XlFcQ80Uw8I9AQB8bhh8ddAtlUWNm92NSBONuNKBCNLcQAzBNczgzhekjldkHljCWlLlXdOATMvlND%2BNekhNelakTkmkahLCuAolLszhJCjNbDDcVl5NcUSNC8AiW8Nhm1MhnBJAgA)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_left.hpp)
- [unit test](../../../../tests/unit/varybivore/fold_left.test.hpp)
