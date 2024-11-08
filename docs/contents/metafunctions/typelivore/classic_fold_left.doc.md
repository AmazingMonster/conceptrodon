<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicFoldLeft`

## Description

`Typelivore::ClassicFoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function left-folds the list with the operation and the initiator.
The type result of the operation is used for continuation.
<pre><code>   E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type
   ..., E<sub>n</sub>&gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeft ::   typename...
                  -> typename...
                  -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct ClassicFoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;
        
        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Example

We will left-fold 2, 3, 4 and 3 using a power operation.
The process can be described as follows:

```C++
   ((2^3)^4)^2
-> ((8)^4)^2
-> (4096)^2
-> 16777216
```

```C++
consteval int power(int a, int b)
{
    int c {a};
    for(;b!=1;b--)
    { c*=a; }
    return c;
}

template<typename A, typename B>
struct Power
{
    using type
    = std::integral_constant<int, power(A::value, B::value)>;
};

template<typename...Args>
using Metafunction 
= ClassicFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 2>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, 16777216>;

using Result = Metafunction<std::integral_constant<int, 2>>
::Road<Power>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::ClassicFoldLeft` relies on recursion to reduce the number of arguments.
Each recursive case has two functionalities:

1. left-fold several arguments;
2. use the result from 1 as an initiator and perform recursion to fold the rest.

The function always ends in base cases, which fold the last couple of elements to produce a result.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct ClassicFoldLeft {};

template<typename Element>
struct ClassicFoldLeft<Element>
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

template<typename First, typename Second>
struct ClassicFoldLeft<First, Second>
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

template<typename First, typename Second, typename...Others>
struct ClassicFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = ClassicFoldLeft<Others...>
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2BehlZjgJhEdEscQlctpj2JQxCBEzEBHk%2BfoG19TlNLQRlUbHxSakKza3tBTXj/YMVVRIAlLaoXsTI7BwEmCxpBjsmAW4EAJ5pjKyYAHS32PRsggpH2CYaAILjxF4OANRuBgUWWQADFPOgQpgqARfiZElZEgARI5WD5vd47PYHTBHE7nS5sX73XaMAgvdFfH4wgFMIF4UHgyHQ3HEx5kgKvNHw9G/Xm/TH7JiHY5nC7MQkASQY2SFJHJHz5v0pf2UxFQRAAsuCeXy4aj3orFQLsbjjUKcSL8eKbrcXr9kICFL8APIXYhCnLyg2G3nKmGIzDNOg6n16kM%2BvleLJGfn42EKiOKo6Il1uj0CXFSmVEMhEh6kl4gECii36xNw5EBfXho27QXCk51k2WsVXW7XO0O2kKdvvYDETAkp5exNR8LAX4AJVQTHQsICKYDQdouL7A6HBB7to5RZLKPDFf3aITvLNDZL1t7/cHbOeHPDY5jWtoc%2BTv1V6tQz/Qq%2BvG63Hb3lW6KHsBx4Yk25qmlaVy/CCeDEOMpCxq2hJCJgaAMD%2B94fH6/yOvSYIvky7JuPBiEEMh6GYdhnLvGGJ78pB54wZK0qOLKxAjnyeEfpq2qMQx3o%2BmeFqNliUEtgSNqAdg9qOqm8Tpgw3E%2BnhS5MMGjFJty2kRo%2BE4lvGwmJvOKaukpDS4jWpkXrBFnulZxw2aZvxZhxObIeR4wuRGhbFviVEYQIP56eWO4BRcR4mTplbVmFTESeezFiXZbDtp2jpXuut6qYaBlTjOr4Lr8GnBsca43qSAH%2BXuYEmaB8UmaJ0GoTJlX/nlBXfmZ75qvxL6/jl1UZUB1ZItF6ItVJ1pwQhSEodJvzUSFyFpTJzoEAg8R3nReE0nSDLEVCpHeZRy3BVhyGbdtiGjXRQm1klqWsZgbnsXgnF5bx/VfgJDW6TFfLTeJ9YvW193yd2imOZ6OFA76BDfH8ZUrglj2ub8BVGb5SYlQdwJERCJ24jdO33bjfK7ilvzftZCWJutMPKfTCO2a9zNOW4lOue5n2eXNFE84atWBRdNHC3j2C7viwu1TT06zqTaZOa89XlhN9W%2BSDOuvZDXZAtlVXDvDo7RhOivFYugaaSuFV/re90y1F6u6prTVPWDrXSUbnWm5G5u0%2BCvV8X9g328NTwU1r7sgR8AD0ABUycp6n8foknycACrYEIWcp%2BnCep8XieF/RaJmAE4QOl4WDzm4mGbGkm5euimHjJgABuYi/OEMIZAA7vEEB978TDIaPMRLCBgOKqPyCwvCTCNeG/DEBAKIxGAYDJlwm8ALT79PgnwvaifJsvVaL8ijEDgQ6wMPak0TeButtb87xrRzVjw7xqBD1xLkZYA7jkWgeEq4x0BFj7pgfsYgAD67dmiCFxH3ZCg9h7vCLN3bwmBkIWGwWILwmBp5jRnnFOOEFnre0vLcd4xBgC7XRN1G2VAvAMAcDkYyb4CaEUZCTZyjFIHQMELA90tBEECFmCg44aDfgBBeKQcMwiQAwLgRIpBhhSJyMkIo5RBAoGqNEeoyRDBpHaMEMhMw3F/J0wqgwmqZDwIFSEF4NIRRMDoEnJgBQXhaBkjRBAgxIidgmM0TItwciuAADZEhxLMDE8kWsPgFW8b4/xvUNSsPYZwjMxwVFqPEaY8xqDLG/GsUBOiRZLa4mUP/eISSmqzEcMgeB3Z4gEAgCohQVw2l3jcGkvx51XHuMyJ4wZ/iXikIsBwFYtBODJF4H4bgvBUCcG5pYawSo1gbDeuYAIPBSAEE0LMlYABrEAyRJDXA0JILgiQAgaGSBoMw0TolmAABwfP0JwSQvAWASA0BoUgyytCkDWRwXgCgQDAuORwLQKw4CwBgIgEAawCBpC8JRCgEA0B7DoPESIVxOCqA%2BdE/e0TJC/GAMgBeUhrhmF4J4wgJA8BQJqPwQQIgxDsCkDIQQigVDqHhToPQA93RpE4DwOZCylknPBZwZ0WLMUwlQFQX4pLyWUupbS349KzC/AgB4fF9BiCwkrlwJYvA4UItIBAJAeK0gErIDix1zqQDACkGYPgdAdiIUoDEeVMRwgtFOFK3gwbmDEFOM6GI2gMJwsOXitkzoGC0DDSK0gWAYheGAG4MQtBoUrKzbsQwwBxCZvwAOThncfHyswKoDCWKtiHJgfMzNtA8AxHdNGjwWB5VIzwAC4ttbiAxDGQGFgZbO1GBOSsKgBhGEADU8CYAHhZZZhzOXCFEOIPl27BVqHlboGoBhZ2mE2ZYfQXboWQBWKgZuOQi370gcmC9VhLBmDBagUdxA2V1rvd0BNOQXBYSmH4GooRwhDEqCMGoRRsgCHA4UTIiGGDzGGNUIDuTGgTDaJ4Doeg7DAYEH0VoGHYNYdmJMAj0xbB4Yo4sS1qx1ibGWD8jgiyQXyohRqslFKqU0rpdcg1EBcAsrNfsy11q50rG2rOEYEBzn%2BACNcAAnAERIkhblmEkNEoFyRolqY4380gAKDnXGiTEj5amPkxKuVwZIGnoncczRCqFMKjlzrtSi%2B1aLlVYvIJQN1pqiVsE4C0FgndEj7yYFDGMXA1PXC4Dcpl%2BAcxsr0Nu7le7pAHqUEezNuhvXiqYJKlZMrONyrc4qgLqr1WRei7F%2BLE5EvJZuYa41TrTXmoCGYK1XmRWIodagE18Qgu4tG91kYjWYtdiMIlrgwKaD%2BJ2gGoNIbo3htIJG0Nsb40OG28m0kqb03yuzbm/NtBC3bawFOowFawVVuA7WotYKG1Np2Nttt8rO3dtDX2rYYLB3DsOaO8dShJ3TvHN5hdTBl2rvXWKbb2Xd28ry7IQ9wqwXFf0GWlA1hrDXpiLepT4LH1SM4C%2Bgxb7Cefu/b%2B/9pOVjEZw6B9wtGIPBCwoxuD6RUMNGQ/BgXORedUbqCR3D/QhfYYaGRgY0GFh8%2Bo/h/IXOVdi/YwoHZbHmPtq46C1ZnAx7ECizFuL83WtJZSxoQ14mcy9ek4NhFcnMAKYSGT9tpnzNJduSkNTcSAiSF05SmohuFWQtsJ5m1syfPwD8%2BilVE2QuEuJRwSL2qWAKE7gvTubXsTjDSxJzLHLZA5fR/y%2BQBXseiqCKV8r0qOMG547VjFWLfhqpNywTP2fc/5/NOMTrU3nW9YCANmPw2UDD9Ncn6fIwc/uPgXntT8CC8EDaabylPrVv%2BogIGzNu2tvFsPzGuNCajujZTWmjNT3MA5rzQWothy7vTqB7wZ7Na62Zo%2B8gZt33RHtpgp/Y9qnCA4Dp/qg68Dg4TqloPYw5DZ8CLoKArproboo5l5o4SAY4CrV7HogBBBnrGB042B/bM7k4NBFrxzCLvrWBfqrKM5YBkGs4NDs4y5QblCYYobFA5Ay4IYNCa4zAS44by4y7MG9AMaK6cEzB4aiESEcGUZa4668qVbN41YcBd49456/DL7XBr527pYkCO7j6yakDyZYAe6Vbe4gBmBJYBABDJDPJ3JAp2GJDRLfLh7uZR6womEXKSDJDqbJAfKvJqaSAB4uFcAEGcABDVbfqcAyZDaVaMquaxGR4T4rCjpZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_fold_left.hpp)
- [unit test](../../../../tests/unit/typelivore/classic_fold_left.test.hpp)
