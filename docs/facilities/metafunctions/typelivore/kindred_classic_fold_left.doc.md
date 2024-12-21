<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeft`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeft` accepts a list of elements.
Its first layer accepts an initiator and returns a function.
When invoked by an operation, the function left-folds the list using the operation and the initiator.
The type result of the operation is used for continuation.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Init
-> Oper
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
      &vellip;
   &gt;::type, E<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
KindredClassicFoldLeft ::   typename...
                  -> typename...
                  -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
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
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Metafunction 
= KindredClassicFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeft` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct KindredClassicFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct KindredClassicFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              typename Operation<
                Initiator, First
              >::type, Second
              >::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct KindredClassicFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = KindredClassicFoldLeft<Others...>
            ::template Mold<
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCAAHAmkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn5cgXaYDlkNTQQlkTFxickKjc2teR22EwNhQ%2BUjSQCUtqhexMjsHASYLCkGeyYAzG4EAJ4pjKyYAHQP2PRsggqn2CYaAILjxF4OAGoANJhdDETDuAwKDLIABinnQwUwVAIAJM/is/gAIqcrN9Pl8APSEgEWJhKAFucnsAkE4kA%2BG0dAAgTbO4EvYHI6YU7nK43NgAp77RgEd4E37/VEghhgiFuKEwxmI5Fis7Cl5qj74jEEgH6gGcw5MY5nS7XZiCgCSDEyJpI4u%2BBoBksBymIqCIAFkEXqDei8V9nc6jdzeaGTTyzfzLfcHu8AchFQCAPLXYgmrKOoPB/Wu1FYzCNOh%2B3MB0u5g1eDJGQ38tFOyvO05Y1PpzMCXk2u1EMhC56i94gEDmqOBpvonEnQMVkP7Y2m87zsPRi23B7sk7YROKjdfYDgkWvbNN6thYAAgBKqCYzJbAMLxdovP3h81Cg3Q5H/NxFcnv/xRt9QjRdR1jPcD0wI8CDeLcKzPWsfSZNETlbd1PVQJD0BfSDoI/eM4OnWlsQAr46RJZVDQAdzwNkOWXSNwxjW4GTwYhxlIOs10FIRugEbC4O%2BfNgVBcFIXJJUESRFFeVhNiOIBXi0FlbNyyAw0GNA5jrVtRx7WIE8DWE9DvV9dS1JzXMQKjJcuUY1cBTjTdtyTCS2ziDsGEM3NhMfJgS3U5tdUCysEIvUcG0spsUNbNMPLqLyzlnaKwJYuKMwS3lkuigFuz03tOLk9ixRCict2HUdOKU/jssrL9R1IicSKIwCornOzQM0mzUrYT8tx3CSILfUVYO1NqqxrC9r1vGKHyLfznzOV8oPfPrsAqn8Wqi/8toraymO4pzlrw7yATCgEsNmkzMN9JbcNWgiPl25qZ2%2BelL26TYMgAN0wSlqRAWk3oohFqNozBOIQQx0HoQ0ED%2Bmhiuo1AARSJpbj2djSHIgFoYBcFkC%2Bv7zoIeH8cwcZ2W%2BfaHNjVjis4nq/uq2VGe0pyU1JuJRolAg/kBGU5XE6FaOVaS1TcIqFJZ9BOM5%2BH2LW4jxwNGm%2BUO3LdLwfTTuMj1TKZP9gvG4CuvDM3afXR6BuhdyMqzQSTZdPmpTmp9aosnL9RJ%2BtaubVCRNlMSFQk0WpNVXl5e5pXSuDCquou263D9ysmbtzystjps0/SjOkqzr28u1gr6fGFOy3K79riqviVILiv1qrnl65QxvrKvG8BLcXPMsIlWyxeoGnbVkf2bWm38LuY731O51zumu8A78ks7uG141o265Gv9QfWvahdurHh5p5G07zsu%2B9rqwnC15gpXnqnV6iQAKlft/34/wk6XfgEABUKZggCd%2BX83ofzAcAoe5gThhCTF4LAKE3DKW2CkGCqlqYW3Vo5AEXw2YaysI7YSQgvDRD5kwBwyt4KTS4s3baAdxjoGHGEPYB4xAAH1lLjEMBLJhnEvjDm%2BmILwmAAC0Fh%2BGCKjE9Gcu8yLoI6ofQ6e5iDAB5t8c%2B80qBeAYD0AQkV7yC2DoqMOTJxaZyivQxhghMAsNoOwgQnDBC8h4QCE47xsbqQsSAJh1iMy2I4Y0RxZxnGSDcRWTx3ibF2IYA47hghOKuMdvqL818lrKMnuKXaaiqFEJSGkJQ6APoKC8LQEqZE6EEAYV4qxkT/FcKcXEgEwiACcGSn7zwpsU1E94vQaK0ToxKbhwnVN8VEmJ9SCCcS4Bksaw4F68iISQjM5C%2B5D04Y4ZArCJJxAIBATxChbibNgm4QpnSqpeFyekCEJySnvBWLiDgaxaCcAAKy8D8BwLQpBUCcGTpYawLoNhbD%2BlAngpACCaAeWsAA1iAZ5kg7gaEkB0E4GhnkaDMAANgxWYKoTyOCSF4CwCQGgNCkHeZ875HBeAKBAKS8FHyHmkDgLAGAiAQAbAICkLwEyKAQDQAcOgcQIi3E4KoBIGLhEYskACYAyBkAAikHcMwvAISEBIHgBhXAZCCBEGIdgUhtXyCUGoCFpBdBaqohmFInAeCPJeW801lKUzcq5aiVAVAARiolVKmVcqFXwrMACCAHgBX0GIGiMwJwuArF4PSrQawIBIH5SkQVZBeXJtTSAYAUgzB8DoJjGlEBoimuiGEJoFwbW8FLcwYgFwUzRG0N0eloL%2BWahTAwWgFaGWkCwNELwwAqS0FoDS7gvAsAsEMMAcQ3b8AE0cL9EdnzMCqE%2BnsSt5ArF4s%2BbQPA0QMy1o8FgU1fM8BEtHaQX6xBoiXMLBOowO6jAQrWFQAwKiABqeBMBUTiu80F/AdWiHEAa/9RqVDqG7ea/Qk6UDWGsPoXdNLIBrFQCgrII7hH0JbKYP5lgzAUsvcQDVFN4BrC6P0lwsopjtCCLKQYZQKh6DyUUbIng2iMcKAlOjwx4harIwlPokxWPTGqLUXocwuNLB47MfoVG9CcOaBJhj0b1ibG2BIO1HBXlksdZwT14rJXStlfKxVgaIC4DVeGkFMawVPrWPDW8IwIDQpAJIE4dwmknH8JIRFZhJAYpJc8jFTT9CcAJaQIlUa7gYq4BihITSEgxbhVwZ5HmMXae7ZS6ltKbMMoTayxN7KXXcvIJQDNYbhVsE4E0Fg31/DCKYANWsXAml3C4AilV%2BBewar0CB3VQHpAgcUGB01uhc2WqYNa0dGmtPkt4E6orbqPXVdq/VxrF5mutYRUGkNKaw0RpOGYazcbGUFbK3EErfLUChpGMturrkjDNa4KSmgJTuaUGLd26t5b11fdrfWxtDh12ttFO2ztpre39sHcO9d47J3Ts%2BbOpteAF2muXaunYoLvFbt4Duvd5bD07E%2BSes9oLL3XqULeuH54n18FfQoD9X6f3rt64B/VA3ZBDZNRBkAuaDCPuw1YSw8HoiIac181D9jOAYYqVh2DuH8NxEI1gUXpGahI%2BcBAVwsmtUhAWPRkYWqmMJW1wUDInG9fcbk2r/pAmWhCeo3xsT/RFMG%2Bk4J3IDvxMW8k%2BplTQLfd4pmzpjguNiA1bqw1%2B762WttY0EG8zvZ9vRtjbZ0g9msDxDF3isLEWWuIv8Cl/w/gTiSF81KrVs2vmcCy3SmnzK2UctdRds7xAKs7Gqz6lgChvryu%2Bht7k4wOsWe61qlneqJDs8EJz8DnzdAnFIONybtqQuaYdRlzgzrOXcpZEtsPnfu%2B9/75GcY22ru7biPtk4R269JrP6m5vd%2Bw0gB77k1hfemmsIHwQTZe%2BBv5re0WiWmWrWj9sAXWg2k2kDldm2h2l2gjpgH2gOmINDuerDveoTmOmxEjijt2mjoTGuueljqarjvuhcATseoRiTrwGTjevsFTo%2BrlrTkwO%2Bp%2Bt%2BhaMzrIH1mzoatPiNiAPPnzsYHLjYLjiruLglCOoSBYgLtYHhnNgRkRmIY7hrlrvbnoLrqUJbobhxlkCbkblkC7lJsoQwLbibsYbboYXJnMGYV7poT7spgoICmpspoHmvhSrph3tKl3j3gCO/ncF/vHp1iQEntfrlnZpgA5pnhpjnjzi1icCcM8mikiiSvEf4LFulu4VSrYNlsdisM5pIM8u5s8gkJik0pIE0sXp5lwAIZwCcG4XNtXjlvGhpsqhkQ0VkbkWsJehkM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left.test.hpp)
