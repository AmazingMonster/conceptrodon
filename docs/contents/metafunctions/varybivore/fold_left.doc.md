<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldLeft`

## Description

`Varybivore::FoldLeft` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list using the operation and the initiator.

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

We will implement `FoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
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
        struct ProtoRail
        {
            static constexpr auto value
            { Operation<Initiator, Variable>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
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
        struct ProtoRail
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
        using Rail = ProtoRail<Agreements...>;
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
        struct ProtoRail
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
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxCAAnADMpAAOqAqETgwe3r4BaRlZAqHhUSyx8cm2mPaOAkIETMQEuT5%2BXIF2mA7Zjc0EpZExcYkpCk0tbfmdtpODYcMVo8kAlLaoXsTI7BwEmCypBvsmSW5MXkQAdDcAas14TNH0CqfYJhoAghPEXg4A1AAxTzoYKYKgEf4mADsVmhABFTlYvh9PgB6NH/CxMJT/c5KECo1EYoEg/4CHZXVH7Q7HTCnc6XVD/e7ER7PelJd5fH5/SHA2ig8EEBms9n0N5E2Go/6y/40o5ME5nC5Ef4ASQYWSVJElXzl/15AOUxFQRGUTGA9P1cphyM%2BBoNCrpDOdSs5jOuNze/2QBgUCn%2BAHlUnEldk9Q7HbKjZCTWbUAAlJh0GXRqHSm3puUTcPIX0CCaYVSpYj/VXMgBuYi81qj2dlduDoeI4YEDM12qIZBZDyeEq5IBA1e8mAziKS9uzMIn9rT0bdyrci49FZuVK5vv9CnXn2AxEwB0YBFeXPnjq8mSM/2TdChSXh/3jRFvtAZe4PR8EO%2B9Z8n55nJEiSzeUDkVJc1xuD9DzYb9IwNS8wmAJ9LTHU5H2fVALStd99xg48fw3d5/xRBEgJRL4SQFdB5QAdzwSlqTAl0VSZIE8GICZSHLNihB6AR0EjWNSUFMEIQZQEOK4/4%2BLQBhBLPUipzlFcGQrDUtUcHViHgnMCF%2BY1TXNVCAMzetHVUs5LM9VB1x9P0cUDEMw3qBhdOjYTMNfc8DTtHz01zRx8zkosSzLdSR1rKEQOnWFovMhs5Wc1tXIZfzEuSts3LOdLErlTstO7bjJM4kUYryt4h0izBuNkgTcunQdhxrOs8vHciEttMiSM%2BXLrOsyCiK3Rzdzwr8T3ci8r2Q197wwoykxTN8zmg8bCMlHrfO6ucQIGplRs/WCJsU8zEOvbC0IfJ8Fou3DDoIuy/znbbgPRTFEx6LZMkrMd8XYV6qLJAh6J2biEEMdB6HlBAxxoUq6OZVJmlYTB9k40hiUxCH/gPZAvrHM7kIIGGccwCYqS%2BPa1RK6T1Lq%2BTuMGoNibiU9uW%2BfS%2BREoVxLOGmCFq/iGeDFnOMe9m/N25j3TUtiCsebtJs8m6TJAyXOtlfrpYg/bf2wYaA2bFyIxO7NlYTbzysbMy2sChiCwYULSx4tVqoarrlLa2VqLEkUzmZmGxb193oyHFcUJwnKra9zLUqjjWY5bLK0ujr38s0hWSGKqSyoTtrKua0dBbkwTU4qpq3bL6MC/D7z/aTuP2bT2UqpakP2s29NAJ6vrtY9KnbL1g3CNWo62dywmbyWubrotpa7vw79xY6rbZ1ep0%2B9lr0rlHgjJsni6Z8w26VrGsfl57l6KPRAAqO/74fx%2B0WJB//gAFTJk9/gf5/KMf/%2Bf6vXMEkMIfovBYHvG4OSOxUjHQlpTTerE1SfEZmxKwJ1hJCC8NEfSTAHBSk9oaJoQUHZO3CmxSu5kmyfAALQWA7s9Ne18B67mIMAceXxJ4AFlUZMCoF4BgvQBDxXQtzX2DIUj/GkP8JIBcT5uE%2BGw9aT1Xp22QAAfUcnEAgEAeFNH4YIuObguAFzrm4LBODWz4Iri1OaoiaEJFWEiDg6xaCcAAKy8D8BwLQpBUCcDcNYawhpNjbDQmYJIPBSAEE0C49YABrEA7jJBXA0JILg0IkgaHcRoMw/h/BmAAByFP0JwSQvAWASA0BoUg3jfH%2BI4LwBQIAakxJ8S40gcBYAwEQCATYBBUiXHIJQNAhw6BxAiCjTgqhCn%2BBof4SQ/xgDIHzFIK4ZheCYHwN2PA6A9D8EECIMQ7ApAyEEIoFQ6h2mkF0FwUgtFWypE4DwVxHivGxL8ZwIMlxBmQlQFQf4My5kLKWSs/4ayzD/AgB4MZ9AyzAK4KsXgbStDrAgEgUZqRxlkAoBATF2KQDACkGYPgdA0bNIgNED50QwjNAAJ7PN4DS5gxA6VBmiNoHobSomjKOkGBgtAGXXKwNELwwBzi0FoM07gvAsAsEMMAcQwqOJcrwD9aVvjiyfX2Iy8gghagfNoHgaIrZWUeCwB8/SeBKkytID9Yg0QMiYHhAcBVRqjCxPWFQAw7Dbh4EwLRZy3iokHOEKIcQpzQ0XLUB825%2BgFUoCCZYfQxrmmQHWKgWB2RpU0ImApeEphLDWDMPU%2B1bIsBpogOsboQi/AQFcNMDoQR5JDHKJUPQ6RMiuUbR2oorlW0jHiHcmtrl%2BhTE8O0PQI6%2BjzAHcsIdcwBg9uHbOxYbbRiIo2FsHYEhXkcE8bUj5DTAWzPmYs5ZqyUmQogLgQgJAoQRMRciz16wYZMCwPEKtpBEmSCSFcZI0JJBpLMJIfw1T3H%2BASKUjg5TSCVMiVcfwnRCkJEKZ0ZJXB3HJECHU3gDSmktOiZ6zpPT0V9J%2BUM3F%2BK4WTLYJwZoLBKzQhoUwYa14uAJCuFwVJmztkkF2fs2QRyI3SCjUoGN1zdAkoeUwJ5Mq90Htw58jg3yBmXHJAChjTGWNseQhxrjqSoUwqxXCh9SQzBIqI%2B0tFGLUCwriMMvFdmTOjC08xhyRgONcBqTQWg5LKBUuucy%2BlurgusvZZyhwureXHn5YKj5IqxUSqlbquVbrdi%2BPwLjRw6qPlarxjq21YR9huOuUak19LzUZeRWyG1UT7WOqUC6%2BVRh3WgGs3wH1Cg/UBqDbq0NwmTmidkNGq5vipPxo9YWqwybyuVozVmwsnBc0EHzdN4tpa4jlrJvAattRVXOHrfJZdzbQRrsHb2rt2QTuduKAwOd7bh37drWO1oE6Zg1DqDOgYD2N2LvHXkJtuYWi/aHdW0JO7N2lcU0ezg5ZiCMeY6xjzenOPcY0FC293YzNPqs6i19mB32jC/aV2D8HONpOhFh6EmTJAgYWXcpT%2BHbCEZRR0rpvT%2Bm/Mc9RiZUyOAMZBSwBQlZ8yVn03SCYvG73lsE4c8NQ2znyHE2NnQIAUgybky86DMPrkNNU78jT8OWBC5F2LiX7oJhGec9iszSRLNs5sygG3cKecu9GKL1IqR1Hi4SOoyXBBNEI4WaSvzrMAvUtpay0LUe2Ucq5dFuzfKBVCsy5gUV4qxApdtWl1r1XSBZdVbl65%2BXLi7CicVg1ZXjWmrpVVy1tXdUNadc1t1SFiPestN1/1gbQzBt4ANhXEhhvnJV7G9Xk3jBJpsHN3bfjFuO04GiPNiai2WBLXhstuydvps%2BwdutDb3tNpCOd%2Bdl27s3b7dkUHU7nujvmCd6dDRV1lAuyupdR%2Bp0v6WI98H26TkKbvJ65w6C6LLC6i7/C%2B5XAB6Y58bwqPoO4vqkBvofqUB7pk4gBmCcZJBJDuI5LpLVI4HQj%2BAlJM6cAEatJIE/ruL/ruKFJ5IJCSAJCZJJDQhcApClZJBAH1LkF45xLQYbKHrAGNJ8GrDrD2qZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/fold_left.test.hpp)
