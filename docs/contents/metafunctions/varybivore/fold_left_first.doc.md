<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldLeftFirst`

## Description

`Varybivore::FoldLeftFirst` accepts a list of variables and returns a function.
When invoked by an operation, the function left-folds the list using the operation with the first variable as the initiator.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>..., V<sub>n</sub>
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       V<sub>0</sub>, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeftFirst ::   auto...
                -> template<template<auto...> class...>
                -> auto
```

## Structure

```C++
template<auto...>
struct FoldLeftFirst
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<template<auto...> class>
    static constexpr auto Rail_v 
    {RESULT};
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
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<template<auto...> class...Args>
using Metafunction 
= FoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

static_assert(Metafunction<Subtract>::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct FoldLeftFirst<Initiator, Variable>
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

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct FoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct FoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            FoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbLGkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcBJgsiQbrJgDMbkxeRAB0pwBq9XhMEfQKe9gmGgCCQ8ReDgDUAGKe6AGYVAIXzwxCGHxMAHYrBCACJ7KzPR5PAD0yI%2BFiYSg%2BByUICRSNR31%2BHwEK2OSPWm22mD2ByOqA%2BAEkGGkmEQyB9DkQPhdiFcbjTdg9nq93gQibQ/gCgSChrTmaz2aQeZdrvR7vioUiPjqPpStmzBW59dTaVzUKdyUKPsgDAoFB8APKJaJs9Ia566j6iz7KYioIgAJSYdG1ushCKeXq9E0cyBtAiGmFUiWInPpHwAbmIvJhwZ7ozqI06XcQ3QJ5SzHGySMrefz1UKQCBs9485C4btI16O/D8QWdSbDbShzt9ubLfcbXaFJansBiJgNowCHchWGdV5UkYPsG6ODdjCPn6A6g97RafPF8vBLPThqu5rO5GCWifpK9QB3PBkikbA1jnS3IKtWSrptywKggQyrmh8QiYGgDDoB6LwEG8nzvlKgKQXK%2BwgVcYE4dBcEIQIyHroiWoDnq/6mvso5GhO97WramIOs6rrVChMZoWKx7%2BkGIYXtREYbtGsY/gmDBJimaawa2ubglRUaFtGHFllx%2BxiapJace6WnUTpXr4TWHJEdpqn3M2CmYMq8GIchhmWU2LY5jSTlFrCfYiV5j6ItRDEjrRw7jvSk4sTOc4LkubC3txupbsEwC7kJB5HiegmhvsV4xSud5Wg8flPL2RWvruCFLKkmZ5ji7D9iib7EgQ34rMqCCGOg9B6ggeY0FB3XXh8iT1KwmDrKCpBlR1HyLsglV5olO4ED1M2YEM5LPIFoXAVWBG1uBDJETBGb2WRx0nKcjrLdEa7Cqh6Hiph/zYbKBCVoq%2B1HSRDnKldPWguFd2iQFwWAVtQEWsx2DTmxukafpd08Q9/GnueYnAyphYSfGiEyamB1Zm5SndkZOpPdK5kGZjpO6up5YMLSFmk3TmluEzNM6iZhGvezOlWa5bZ2aRSG8852DWW5v3XQD94edG/MMSlWVuCzCOizqEttuzJUk55z71V64Pg0xBUw/aUXXrFq7xZu27JeeaUo5lF7ZdFN6roD3nFb5L7PMiABUgdB8HyIEkHAAq2BCOHQeh37wcJ/7cfFYiZi7MEtpeFgB5uIhKyJNbFEp08xsZk850MlYRc%2BuKQheBEaFMA4mq696dRxlJeNyRmNno1CHxPAAtBYSn65RY/F0boOMWFUNm/lTzEMAt1IotyUALJjUwVBeAwDjpPmxWHhKWEylBtKtB8uzKtIV/82j2VL/lD6%2B6hbrIAA%2Bmx0QEBAm91DvPerM64NzLM3FyNk0p7CPIPAAnLMeEHB5i0E4AAVl4H4DgWhSCoE4GzSw1hvSLGWO2NOPBSAEE0Eg%2BYABrEAqDJDHA0JILgEJdgaFQRoMw8QzAAA5eH6E4JIXgLAJAaA0KQTB2DcEcF4AoEAEjKFYKQaQOAsAYCIBAIsAgiQjjkEoGgTYdBoihFGpwVQvDYiD1iJID4wBkDxikMcMwvBMD4HZHgdAeh%2BCCBEGIdgUgZCCEUCodQyjSC6FaJ%2BMsiROA8GQWgjBVCcGcEdEcXR4pUBUA%2BBYqxNi7EOI%2BE4swHwIAeCMfQNM5hdhcFmLwJRWh5gQCQIYxIxiyAUAgK09pIBgBSDMHwOg415EQAiMkiIwR6gAE84m8AmcwYgUzHQRG0AhJR5DDFW0dAwWgMzwlYAiF4YABxaC0HkdwXgWAWCGGAOIfZII1l4Gquc7ByYKrrFmeQQQlRkm0DwBEMsiyPBYGSWhPAoiLmkGqsQCIKRMAwg2Dcv5RgqHzCoAYZeZw8CYE/BxTB5CfHCFEOIQJhKQlqGSZE/QNyUDWGsPof58jIDzFQAXdI5zB5DHIjCUwBDLBmGkdCvkWAmUQHmHYR5zgICuFGC0UggRgi9BKP0VouQ0gCFlTkFI6qGBTD6DEcYlRJU1GGI0TwzQ9ASv3gIToDQ9XKoNbYU1mrximvtTMWpCwlgrAkAkjg6DJHJJkTkyx1jbH2McYwkpEBcCEBIOCMhdSKGovmD1JgWAYhitIHQyQuxjiwN2BCSQzCzCSFiOI1BsRYGCI4MI0goianHFiFwWIvDYG8JbQwrgqCC0JCkbwGRciFHJuUU0jRzStHpL0Z07plTTFsE4PUFgmYISDyYDDHcXBYHHC4Ew1x7iSCeO8bIPxJLpBkqUBS8JugBnRKYLEi5fqA39pSRwNJOijgkmyUulda6N3JS3TuphpTyltMqQm3YZgk0NJURO2d0R9FdNQBU/oP7V2sSMFurgEiaC0GGZQMZ4T5nTM%2BcRxZyzVkOE%2BZslc2zdnJIOUck5ZzPlXKRasbB%2BBZqOGeckt5c0PmQuCOsFB4S/kAumcCjj9S%2BQQvIdC2FSgEXXKMMi0Ao6%2BAYoUFinFeLPmEtPQE89shyVhOwTe6lKLeVWEsAyiIoqWVssTJwTlBBuXWesAKgdQrPFrXgOKo11q/DSqQi6%2BVSF3UqqSNq6oYW1XVEi46q11RbVmqyHK5LHQ3WKumFFiYIxzVjCdZMHL%2BrfVepIeV0Tz6g2cE5MQZdq710YYA9u3dGhSmxvZBB2p9SU2kDTRmygfq60Nu3cwiEPaIRsMkKWmxrQX2DtsMOmDY74ATu0RkxD8HiDztWEu/JLAFCZnjJmQD1Ihj7rjcK49vjiVGaCfIS9ZmdAgGvneh98Sa01fCTI99GSv31ZYId47p3zuGjBGU5DYHogQd2NB1FqiWnQ/adtlHlSWzIESIkD%2BZ3YEfwuwQL%2BDWbGDLwzdAj4zJmLNI9TpZKy1nUeQ1snZezOOYEOccsQLHIVsdU9J0gXHHm8fCfxo4qxyHCZ%2BWJ/5gKplSdBbJz5Cm4XKaRUlRH6KmCYuxbil0%2BLeAGfuxIYzwTnuUre5Z4wdLbPiYczgpz0lODIi5bSvlFgvM4J8yK/zbRjUuFC4VuVCqihldVTF9IcWI8FFKw6y1gWUvOqD/H9oNrsuh7j66roYX8vdFjx68VxCfWeuq0k37dWDu2KOydrM4P1iQ66/G6pvWR2NNTZgdN/Qs2idGyAMw27di7FQZwlh4jB8QlbYG8vsjluKP6zm1B%2BbUG8O4bAyQsC2GFq4NfUTuwy/SM4H10dfqXFT4PzP1b8xoWpGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/varybivore/fold_left_first.test.hpp)
