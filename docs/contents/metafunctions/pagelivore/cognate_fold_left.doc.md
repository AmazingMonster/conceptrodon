<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFoldLeft`

## Description

`Pagelivore::CognateFoldLeft` accepts an operation.
Its first layer accepts an initiator and returns a function.
When invoked, the function left-folds its argument list using the operation and the initiator.

<pre><code>   Operation
-> Initiator
-> V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, V<sub>0</sub>
   &gt;::value, V<sub>1</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
CognateFoldLeft ::   template<auto...> class...
                  -> auto...
                  -> auto...
                  -> auto
```

## Structure

```C++
template<template<auto...> class>
struct CognateFoldLeft
{
    template<auto...>
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
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<auto...Args>
using Metafunction 
= CognateFoldLeft<Subtract>::Page<1>::Page<Args...>;

static_assert(Metafunction<3, 4, 3>::value == -9);
```

## Implementation

We will implement `CognateFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct CognateFoldLeft
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
                    CognateFoldLeft
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgABxBAA6oCoRODB7evnppGY4CYRHRLHEJAOwatpj2RQxCBEzEBDk%2BfoG19VlNLQQlUbHxSUEKza3teWMTA%2BFD5SPVAJS2qF7EyOwcBJgsKQa7JgDMbrv7h5gnbkxeRAB0jyfYANTIBgoKLwDyKfFMDWeJg0AEFxsQvA4Xh5gMxdgAxTzoEKYKgEYEgkyVKygl54l7nA4Aq6nW5EF4ASQYmQBJCBuPx4MhBBeymIqCIyiYwCuDLxWJxIPxwpeTKhQg%2BCAxIvxAulMpFhMu1zJqEe9wAai08EwYvQFPShQrhWKWWyOaguTyXnLKgARE6C%2BXGvEAeldLwsTCU0O97Axzpd7peiNo6BeAi290DxqVxJVd1QLy1xB1epJ2BjCtNrPZnO5JLcKbT9ENLtl2Kz5fGALwyDeAnGmFUKWIL1VLwAbmIvLyjeXhQKfn9iLWBNcqTSiGRk9rdaXjtgQCBu95MDb7Y6qyKsQ7jk6%2BUGPaHwwQAO51zDRw%2BxvZEo6kxMhvDEcakdtPoSYNAMdBlgc5ua%2BY8tc8Ivm%2BLxfj%2Bf6Ltug6VjeAHNI49Y/k2LZth2q69jaiHlkOcEDr8/yAqchHlsRo6kW45EDnik6OLSM5ga%2B6J4XRNqLsu2GYO%2BUECH%2B7F0c83E9n2HEVnugrCZu%2B4BkJ%2BLBgASt%2BGwZJ2643EoIDyf2R4hkiBIXls74IIY6D0ASCDrjQrFGUmKQtKwmC7K%2BpC0cG5kvMQqmvuuXgZEYVnrj54zXnpt4XPGj7kixEEdvxv7vqq6rfAQ1mvv%2B1YEBCUJAZaBageBBB8d%2BAnvmlGUKOqWUunKCkyjWKENgw6Gth%2B5I8bR8HSRJIownCmAniiaLdQqy75VahZjRRI5jgw1wzS6lHzYtDV9fR1KMdO75xWxEUbbKXErmJpXQUtxoiSda4XUdS4gHGuysoVpyVfE1VPLB63GqJN3fZJW7rbugMHfyskHqDBJ3sqMVqo8ILAD5eyMAQBpfZDAXhMAz3WicdqQZKy6Peuk0vW4CNI2wggfdGsFyYewP05ih7EwmDzw4jmDI9TtWY0FU2cfjpMgacFNc1TqM1XTTrg7proAFSK0rysq66GIK0rLwACqYOMXzK2roIayrJuK4bzMgqzsMvCCyVPlY6M5kIXgxDlTAOAGCF6U1dYtW1mFPl1DPYjbAC0FgblJntR6CGJWzcibqiCxDAGjmagnz2MALIuUwVBeAwDhZLhmLHPjA3EsNqLoqczuu6OHvHVN1xcFdzeiynNNAkzGI%2B8gAD63pKK0EA580%2BeF9RxzvtILzHFdPGC3jLyhwAnMsjocKstCcP4vB%2BBwWikKgnA0ZY1iiusmzruYxw8KQBCaFvqwANYBJI9waJIXCVMcGj%2BBoMwAA2IBZhEiJH0JwSQvAWASA0DUA%2BR8T4cF4AoEANRH6Hy3qQOAsAYCIBAOsAgKQ7jkEoGgfYdB4iRGcpwVQiQgGhyAZIF4wBkD1ikPcMwvBMD4GnHgdAeh%2BCCBEGIdgUgZCCEUCodQWDSC6CCGeUcKROA8G3rvfeT9j6cG%2BHcEhLJUBUBePQxhzDWHsJeJwswLwIAeEofQNst8uDLF4JgrQqwIBIAoSkKhZAKAQG8b4kAwApBmD4HQVyaCIAxC0TEcILQACeqjeBxOYMQBJ3wYjaG/Jg%2B%2BFCJbfAYLQJJcisAxC8MAG4tBaBoO4LwLALBDDAHEKUl8OS8AaVqUfZsqldjJPIIIOoWjaB4BiKOdJHgsBaJyngWBdTSAaWIDEdImA7R7CaSMowT9VhUAMKnDUeBMBnmIgfe%2BwjhCiHEBI850i1BaIUfoJpKBrDWH0KMtBkBVioBSA0WpodxgwTtKYc%2BlgzBIMWamLAHyICrDsO05wEBXBTD8EEUI8wygVHyOkTIAhkVYsKFkQYGKRhjDqPCxosw8Wkp6AIPorQiXDASDMfoVLbCzAZYsJlsKr5bAkOojge9SCIN4Mg4xDCmEsLYRwj%2B1iIC4EICQG0Zg74uIfts1Y1kmBYASDC0gb9JDHHuKvY4lRJBfzMJIIB8D/BANXpAjg0DSCwLvvcIBXAgGJFXskIB/hv7%2BGNUAoVWjkGoPQWqrBHj8GeMIXo0h/jAkOJoWwTgLQWCdkqKHJgbwDBBS4Kve4XBP48L4SQARQjZCiKudIG5Sg7lyN0GEpRTAVF1P5YK4V2iOC6OIXcCMRjU3pszdmpplj82Fo0DYuxPiHFKuOGYVVbjsHRoTfEMhATUD2JGAOjN7wml5q4DUGgtBImUBiXI1JiT%2BkXvSZk7JDh%2Bn5JRoU4pWiykVKqTU/pDSNnbCPvgHyRdOlaJ6cgO42x77hF2DvORIyxmJMmb%2B1xqY5n30WcspQazGlGE2aACNfA9kKAOUck5/TzmVvEdW2QtzZFHwbY8rZwKrCWDeTEaFXyflZD%2BQCvGjHrBgpFRCgRut4CwrJUXBFSLPAdD0Gi0ojL8U4uyFJ6YpACiKY5Zi6l5K6VtGUyi7o2n2Xovk8yyYem9A1npcZzlfK1gbF5c4%2B17bg2cHbMQNNGas27tzWOz%2BNj5XTlnc41x6rSCau1ZQfljrnX5q/pUf1lRf6SAtcwoIHaQ22DDYuyN8Bo1EP0WuldxAk3bFTWYlgChOz1k7Hm%2B4lxxjFoVZC8tIjLkUckfIWtNGdAgGnk2ltainOaLkcg7t%2Bi%2B1uZYOVyr1Xav1ZZLYjd074izuOAu7ZOCvFLd8YV7bDiVzIBSCkfuNXV793m4PdzzDwnHveqe2J8T0lXsexkrJOSH0boKUUkpf7MDlMqWIT98zv3YcQ6Qf97SgNyJA2B/pkGhkwdGeMhJCHpnIf6WhlZmGNlYw27s7khHDnHL%2BKc3gZG2sSEo1Irr9zev0eMC85jsG2PHw442TgroAXPJBRYfjx9BNQpEwZ8TfhEW/lZbJhYmnVPYoaKytTDQNMkuFw0HTrK4Ui500rplbKWXmdM3MOTNnHMKB5eIttw2kGubKywirVWuxzeJOMfzJbHHKuC%2BG9xGrMBapGLq6D0WQBmHzccY4/gAHf3gaHyoHqg0jc4KGjBoX9X%2BCNf4RIwDV6SFXr/E1XBp7QeOJbkVCfPfP3tdwuPVuUFl%2BWKsRZGRnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_fold_left.test.hpp)
