<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-left-first">To Index</a></p>

## Description

`Pagelivore::FoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
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
FoldLeftFirst ::   template<auto...> class...
                -> auto...
                -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldLeftFirst
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

template<auto...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Page<Args...>;

static_assert(Metafunction<1, 3, 4, 3>::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldLeftFirst
{
    template<auto...Variables>
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Initiator, auto Variable>
    struct ProtoPage<Initiator, Variable>
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    // Fold twice.
    template<auto Initiator, auto First, auto Second>
    struct ProtoPage<Initiator, First, Second>
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<auto Initiator, auto First, auto Second, auto...Others>
    struct ProtoPage<Initiator, First, Second, Others...>
    {
        static constexpr auto value {
            ProtoPage<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15HeP9YYPlw0kAlLaoXsTI7BwEmCwpBjsm/m47eweYR25MXkQAdPdH2ADUyAYKCk8A8ilxTHUMjxMGgAgmNiF4HE8AGKedDBTBUAhQvDEMZA4EmADsVhBTzxT1O%2Bz%2BF2O1zu9wAak08ExovQFIDcfiwRCCE9lMRUERlExgJgnlirJiACJHHEYpl4gD0UqeFiYSieVyUIHR6PxTxl0NhTwEm1u6vxhPOlzJqCeAEkGJk/iRSE8zU8qcQaXSSdhDXiWZCOVzUDy%2BZcrTaiGQndTafRGcCNYLPRqnmM/nhkC8BGNMKoUsQHTdzQA3MRefnx2PYr4/YjJgRB62OW1h52uqP%2BbAgECF7wlkVi%2BNY0X%2BcXxrUw2joAkAdxTmANkoJuyJh1JectdZpoftjuRqIIm5XQi6AnQ0Y13rZvu5vJJbmD9Y30JRY3tB7QDGPrb72NLzMajlTr4zLMc0dTtiwFL85wTfFvl%2Bf5Lm/KCYKrODjgQqD8Vvdc7QfHc0NjVt21AzBn0PN88PxR5CKLC5IIontB0/AchznLUACUunWDJ835ZV2DVFjZVHccCCnTZ7QQQx0HoAkEH5Ggdxk4hMH5FImlYTAdlRUhh1lSSniU5BOP5LwMiMGT%2BSUsZZxjI0FxNZciFXENsK3R9d1zRyXyPPdyVuT4CFk1ETx/cEfU5S9A2OTCG3tbcnyeLy33tfzAoUe4DQ/Oc41or1fxTNMGEA7MPILajwPFdCEwvf0r3gnLKorWCsjqmyGoTJDqwBVD6ravFovvOKCHIqDKI7aiSNfY8evQ0aiOSgK4jSh5prxWbqLQ/teyy%2BjmNa%2BczmJU083S4FgCU3ZGAIBlMr2kywmAdkrwFfxhXZcKasitxTvOthBCWjKPQYkFNqBiVgSlAAqKHoZh2GpXRSHoaeAAVTAxg%2BGH4ZBRHYdxqGsbB41Doc81gR880rBus8Eq8aICCrBw1Qgvakz/AqiuAlciM/CwnmBABaXmQaHHb%2BOBImlyuY77mBYhgGuj0QTusyAFkNKYKgvAYboBAFYGXu1Md4URQbLiEWn6aYRmCJAANr1l%2BX0sBUH0VZlMAH0FSUZoIDVxpNe1lC3C4e1AieaQnn8Nau2egdXv5gBOJYxQ4FZaE4BJeD8DgtFIVBODcaxrETNYNhLMx/B4UgCE0VOVgAa0SSRbg0SQuExfwNCSMwADYe7MAAOAf9E4SReBYCQNGSbPc/zjheAUEBkhrnPU9IOBYBgRAQDWAgUhuchKDQPY6DiCJ1M4VQB57/me8kJ5gGQVMpFuMxeEwfBQzwdA9H4QQRDEOwKQMhBCKBUOoVepBdAhwnFWFInAeBpwzlnWuedOCfBuPvNkqAqBPCvjfO%2BD8n5PBfmYJ4EAPAn3oDmcwlcli8BXloFYEAkDHxSKfMgFAIBsI4SAYAUgzB8DoJpReEBoioOiGEJoABPBBvBJHMGINIz40RtBdBXlXY%2Bv0CCfAYLQWRkCsDRC8MAK4tBaCL24LwLALBDDAHEIYlE6i8DcUsbnTMHEdhyPIIIGoqDaB4GiFWJRHgsCoPpngCeVjSDcWINEdImBhS7DsQEowtcVhUAMPLCkeBMAThgtnKuf9hCiHEMA4pYC1CoOgfoOxKAi6WH0IExekAVioBSP8Sx/MxjvmFKYSw1gzCz1iS6LALSIArE6DrPwEBXCTD8CHEIcwygVD0GkDI/x5lrMKP8AYKzhghymf8XoExPBtD0EcnoMw9lDHiIcmYWz7l9BuQsO5kzS6bAkEgjgmdSAz14HPPB19b730fs/ZuZCIC4EICQAUFcuD0OruklYskmBYHiBM0gjdJD%2BFuAnfwmJJCtzMJIHuU8Eg9wTiPDgY9SAT0rrcHuXAe4DwTgPZlCQ24JHxT3P5qC54LyXki1ezCt4sJ3pgg%2BXCeHUPPmwTgTQWD5kxPzJgLwDBmS4AnW4XAW7v0/iQb%2Bv9ZAALKdICpSgqmQN0II2BTB4FWO%2Bb8/5aCOAYL3jcXUuDFXKtVequxJDtW6o0OQyh7DqFwv8GYRFjC17iplXEQ%2B3DUBUOGD6lVrw7Faq4MkGgtARGUHEZAhRMjvElqUSotRDhvFaMuro/RqCjEmLMRY7xNiUlbFzvgAyjhXGoI8YZLx0Swg7HTpAgJQSZGhM7Qwl0USq6xPiUoJJtijCpNACKvgWSFA5LyQU7xxTTVAPNbISpEDc42tqWk/pVhGkTvGW0jpWQuk9KOH0hpFghkApGd/NG8BJk1Gcc4WZb5HlBDfC81ZId1lFGyGcvI0GdlZEgwc6otQrl9DA5c%2Bo1zlm3IuQ8%2BDCzbC4dKPhhFqx1ifIo2O51/LOAOmIEqlVarM2aqDS3ch0LQyRoRQw5FpBUXosoN82l9LtWt0xNyzEHdJAkrviHF1ArbBCtjaK%2BA4rd5YKTQm4gcqtiKsISwBQ%2BZUz5i1bcc4Yx9UwtGca/%2BpTj0gPkJa89Oh8h2odYg6ldHIFz3dVgr1jGWBGZM2ZizVm2QUJTeGuIkb/AxvSevVhMWOE6dS9QjsyAUgpHduZhO7tIueyY3fIR%2BbFqFokVIpRZbqvKNUeomtKbtH1oMV2zAxjTFiFbdE9ta6Z2kG7c4vtkCB03C2FXEdfjx2BOCdI6d4S53eMXQkldKT7pJcybyHduT8k/EKbwQ9jmJAntAa56p%2BQNXGA/U06ID685PvTJwKUPT6kDMsF%2BvOP6xn/rQ0BmZcyiN6CWWR152yNlZDAzB3ZeGweHMA9Mk5LQgfw/Qzh55sOoMkcwyj7HzQUNvMo2XL5PmUF%2BYY4Z%2B%2BxnTNPHy5Z4kYwuMGpofCxLIqUWYDRcMTFY6xMgDMNq/w/gEhJDblPIXmIWV8vJ/PFTy8BPYoSHihIA9e4J0kAnDuBKuCBDHf4Mns9OD8fZ9St%2B0vDey7UysWJGRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/fold_left_first.test.hpp)
