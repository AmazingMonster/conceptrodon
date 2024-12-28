<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-left">To Index</a></p>

## Description

`Pagelivore::FoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;::value, Arg<sub>1</sub>
   &gt;::value, Arg<sub>2</sub>
      &vellip;
   &gt;::value, Arg<sub>n</sub>
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeft
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldLeft
{
    template<auto>
    alias Page
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
/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldLeft<Subtract>::Page<1>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3, 4, 3>::value == -9);
```

## Implementation

We will implement `FoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldLeft
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables>
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Initiator, Variable>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
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

            // Recursive Case:

            // Fold twice, handle the first two parameters,
            // and recurse using the rest.
            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {
                static constexpr auto value
                {
                    FoldLeft
                    ::ProtoPage<
                        Operation<
                        Operation<
                            Initiator, First
                        >::value, Second
                        >::value
                    >::template Page<Others...>
                    ::value
                };
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAByJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoW4mF4iAA6dFQ7A3ZAGBQKG4AeVS8Te2UxQPGxC8DhuADFPOgQpgqAQgSYAOxWS43Hk3WFPeGI5FEe4MLJvEjk7m8ynUgg3ZTEVBEZRMYAI6U8jlci68vU3WU0oS4hBA/W87Vm836/nghHQ4WodGogBqLTwTBi9AUUt11r1hvliuVqFV6pulvZABEoTqrf6edttjcLEwlDckUoQGzNQmk3SGTcBJtUfGE7bBQ6Uagbm7iB6vfbsGX/YGFUqVWr7W46w36L6ExbOS3Bwbmo5kNiBONMKpUsQbo6bgA3MReDV%2B0dDiyE4nEUkCRF3MWOCVkWvuz39yHYEAgVfeTAR6OxkfmjkxyFx3P%2B/P02joHyADueAlm%2BNqggKEJViKtJ4MQ4ykIu1Y3EImBoAw6ADqObbBp26qInBCEEEhaEYVhN7gXqlo/jh46gVODAznOC5Lg%2B64RrRg7apxm5bvqRIkg0iJUaOgn7sJ0KifxorikQ55EeM0kJpid7sZgpHoQIWFcfxqn3muG4yVqL5fspH6vpcyn5gASuh6yZMuT6ZuwOZ8b%2Byb/oBBAgZsSEIIY6D0HyCBPjQxHATWqQtKwmAgghpDWcmgU3MQ9kIU%2BXiZEYIVPml4ylrpeoVtBSIoYpJHISKZHaUhjrOgSBChQh2GDrhHahl2hHwYhqFaZhSGNc1CjOq1KnDkV1qzBOjHMfOVU1upynURN7nGV5TIsst1p3nhnUEVJk0yeJB4MCJR38SdkluNtMnHnJJBIRVt0qTeamGZp5Evf6%2BlLRdP1vSAJVPmG3ZDfEI0YpR/07QZj4vRZZkXYjOo/aZ35rTywNCtWzoXMAaWgowBA%2BtDmM3Fl4TAAqXYRpCUaoSad7A%2B2Iag4i%2BOEy8JOjZRSN8SjbnFZBdo42i6Kc5gROCKTza5pTOWg3TDN7ez0KS9LPNQ82/OC1Z3x/L8AI/LsNzYKorBPE%2BnxAibhunG5JuoV4MQEPuNI25c2MwTWFx1ShVhk22Qgu27TAOGyq0BvRk4YXNrEoX9AucjcFwALQ7nrgLo47hw3AAsnFTBUF4DAONkHwO17IuVmV4uohcxDALLQIK9ThfNCXZfvGy9MFgBm2stCIeu%2B7Q%2B3iAatuFw%2BlT43ze8zrGNOwAKpg4yV/sALTaBAD6aZKK0EAd8Xpfl4e0KQkh0g3JCv2GcrUIM2nACcSyxhwKy0Jw/i8H4HBaFIKgTgN1LDWANGsDYT5zCQh4KQAgmhP4rAANYBEkKiDQiQzBmBfi/Lg/hMGJC4Oydk0hv4cEkLwFgEgNAaFIP/QBwCOC8AUCAOhCCAGf1IHAWAMBEAgDWAQVIKJyCUDQI8Og8RIixU4KoRIAA2NO8jJA3GAMgScUhURmF4JgfA8k8DoD0PwQQIgxDsCkDIQQigVDqE4aQXQQQgL7lSJwHgX8f5/0QUAzgBIUTCPlKgKgNw5GKOUao9RNxNFmBuBADwEj6ALhgVwJYvAOFaBWBAJA4jUiSLIBQCA2TckgGAFIMwfA6DxVYRAGIXiYjhBaAAT1cbwOpzBiANIJDEbQ6EOFwPEdzAkDBaBNLsVgGIXhgBIloLQVh3BeBYBYIYYA4hRnwR6XgJyszAGznsiCZp5BBB1C8bQPAMR9ztI8FgLxbs8DULmaQJyxAYgZEwFGUESyTlGEQSsKgBhm4ujwJgICgl/5wOMcIUQ4gLHgusWoLxDj9BLJQNYaw%2BhTmsMgCsVAqQGizLTuMCiUZTBgMsGYRhjz6xYAxRAFYdh1nOAgK4KYfggihHCEMSoIxCgZCyAIZlegii8oYPMYYCQgh0vPo0CYbRPAdD0BKhofRWgis5WK2w0r%2BXiulSqxYyTVjrE2BIdxHBf70K8Uw4JCilEqLURo9B0SIC4EICQCMZhYEpPgd8lYoUmBYASDS0gqDJCQlRC/SEpCNCSDMJIeRtD/DyJfvoTglDSDUNgaieRXB5GJBfkQ%2BR/hJD4LDfIs1dimEsLYZ6zhGS%2BGZIEX4kR%2BTCkJOkWwTgLQWDLnZGnJg2IDA5S4C/VEXAME6L0SQAxRjZCmKhdIGFSg4V2N0GUpxTAXFzONaahhvAmG%2BKESiIsQSQnWr7UsyJQ6R0aBiXEnJCTXWQjMB6tJXC63NviKIgpqB4kjBxEswdXA6E0FoJUygNS7GtMafsiD7TOndIcPs/pxNBnDK8WMiZUyZn7IWR8rYgD8BpXLpsrxOzkAoi2HA8IIJyGAJOWcxplzcOpPrHcuBjznlKDeYsownzQDVr4H8hQAKgUgv2eCmd5i52yFhbYwBy7EVfOJVYSwaKYjUqxTi7IeKCVP0U9YMlO6KUGPXvAWldR6V%2BEZZhTVwRMI6q5WkHlDRrOCoaHZtVCregatlfkcVZnJVKoGOyhY9nZiTG8yy9VcwguiqNfqqBsXyFbvNZwS1oSVG/oHRejBMSnXyXvck1JXrSA%2Br9ZQY1Ka01DsjeyfwL8SGQijTGwtpbGGcArew753Da1IEEf4j9b7iCtq2B2sJLAFDLknMuQdqI7TjDHc6ylU6TGQok5Y%2BQC6ZM6BAFfVd663FJpNZ4stPiG0BKPaN8bk3puzflLEr9t74j3shE%2Bzrr77u5P6%2B9hJ95kCpFSLvKbL9d43d3qoZR5TgMQ1A7U%2Bp7SoOw46V0npCGv0DKGSMvDmBxmTLEJh%2B52HuOMdIPh9ZRG7EkbI/syjRy7G0fOQ0hj1zmP7LYy8zjHyqadd%2BWqQTgLgXElBbwMTK2JCSasRt%2BF235PGBRcp2jamgEaenJwbYBLkUkosPpoBhmqUme6OZlwVnwt6DZeUGL3LijZGc457Ibn5V%2BcVV5vIEWPMCAC3brV/RrOhcC2b1VsWFCQMNXqxLR3WscGCRdibK5rvwg3o68diS3UFarek71mBfUjADeQirIAcGokhJCfwBDC20ML%2BybNLWd1tdsJW59SwUEgEkP4UNxD2S0MSJIPBXAsFmBLeQyEYfq/MNT0gg72iq/eJH/XlYjzMjOEkEAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/fold_left/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/fold_left.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/fold_left.test.hpp)
