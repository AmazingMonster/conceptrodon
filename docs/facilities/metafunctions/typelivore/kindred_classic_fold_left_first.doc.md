<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeftFirst` accepts a list of elements and produces a function.
When invoked by an operation, the function left-folds the list with the first element as the initiator.
The type result of the operation is used for continuation.

<pre><code>   Init, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
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
KindredClassicFoldLeftFirst
 ::  typename...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
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
/**** Subtract ****/
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction 
= KindredClassicFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult
= std::integral_constant<int, -9>;

/**** Result ****/
using Result = Metafunction<Subtract>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredClassicFoldLeftFirst<Initiator, Element>
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

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredClassicFoldLeftFirst<Initiator, First, Second>
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredClassicFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredClassicFoldLeftFirst<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIaZqQADqgKhE4MHt6%2BekkpjgJBIeEsUTFccbaY9nkMQgRMxAQZPn5cFVVptfUEBWGR0bHxCnUNTVmtQ109RSUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLAn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMAGY3AQAJ4JRisTAAOgR2DujAIClB2F%2BQ2IXgc5wA0sF0MRMO4DAoUsgAGKedABTBUAiUvDEIbnEwAdis7IAIqCrCdfms1ucLEwlOc3GL2L9BcLqbR0OcBCs4b9/oDHphQeCoTC2FcGKlHiRSOdIdDmPqkQCUejMQRsbiCQwiSS3GSKfLafTGcyhtrLobHMayOdrfcCHaBZzfuc42aAbdNdr1UngWDzXr4Qj0edkB7zgB5aHER5pKPHePnLE4gjnbmYOp0WPxjn8ytV%2BNeFJGM26tknTutkHcoslssCANBvAh03h20g7AgECZvktuMc3kg9vrhMa9PgxNArUZ3WW7Oqxd5j0IuHHYDEm2CNGL3fd4LAc4AJVQTEVoNHBsm1obV70fCMFFvdFl1XbcZR5NcBTeOUaTNAB3PAVTVI9k1PC1YQNI0iFDTNz3OJkWQIU1SIIoRMDQF0KxrJ1CWJUkxU9Gk6QZCj/TBQMiJNci/So846IY9AKzbXdU2PFMcIPGi2Cgq98w4sdognBgKyrZi6yAphm0HVsY2Mod317TMBw7IcAI00tqm1XchyUzB7K0pyzKHeMBODYjTV4yMvNsxcYN1U1xIESTgs7aCV11RCbLZBC4KQpLZNww99xPHV8OUnNVJvBEwMwJ9UR0rse0/H8/zZEd60bQyQLBEqysggql3i6FEs3HrkO/eilhSAA3NzJSUEAZX6r10MwzBTQQQx0HoM0EDcmhKNWx9zgSepYX%2BFlSFlc4lvOYlkCGtyLM/Ag1rOzAhlVE4MsUs8CN8md/L7PK3MC6i3v1SKXX%2Bn7b0LW7ohfDETj0/FWLdD1MK9bjfUoqdBNDP6xPoqLTXBtaWRU6GflM9KFJyl6KYBi9czU8l3Mc18vNhgyjKS6SYrja7vrc5zh1HZ1XXY8kka4n1As8pLvJ5sji00xm3D5lzqYZ8swSV6XCL8oSJc52LQq6%2BbsYkjWqzizM8Yhwmcz183ye/X9JLBOWHLVjFUvZlKdy8yn5OylNqaJ68ONvVqIIqrmqod2q7NZ5q3DDlF2svTrYJ3L2ptOT4Pm%2Bd4NjDVRWFuNyXkFbOvkz8wQWCfMvCwOrcswAB9B1DPKpmfjMauGFr%2BvtQYlYEnb4my4uIQvAiVvcVL57yYDn7zmOEGsxFJiHVrMSJ6noKSfbKtudXLy7KGdBl2Cf4HzEJuGImQRtXP01jmXYaxC8TAAFoLGf1%2BT3d9Ot29lnC4ABZRqVAvA9yeDPP4c8MywMbueIOdNk7HGIMAKGvxuagLqOAyBaRrJ2UFmxd0HFRYKhRhLdWzMCCnxAOfTAl9aDXwELfSMYIH7nC4OiI61DaH0MYcwhgrD76CFNCCbhu4T5n0EAw0sTCb51Dvuw0R5xJASN4dIi%2BcjBHCOUaJcRHcNwGxqk7BOaDk52g9qPLYm8Eg5BJF%2BB6XhaB1mgdzcedjkgOKcS4mU9UpF0JkQIhRhg2FuA4e/AAnJYwBecBoKGca4g4mCo6OISS4uqo5sFMFwQ4NWbhx6T1LA4GJmc4kABUHpJK2N8CYjhkBNw4tEAgEAAkKFhI0l8bg0mJIil4TxSh0A9N8YuWYiUODzFoJwAArLwPwHAtCkFQJwRWlhrDVkWMsXmXceCkAIJoCZ8wADWIBpmSDhBoAAHGYMwkTIlcGmVcy5XB2TsmkFMjgkheAsFiBoUg8zFnLI4LwBQIA/n7IWRM0gcBYAwEQCARYBAEheCohQCAaAbh0GiKEWEnBVCXIAGzvwJZIc4wBkDIE4ecswvASSEBIHgU%2BrR%2BCCBEGIdgUgZCCEUCodQkLSC6FaGhUsCROA8EmTMuZBylmcELCi5FdZUBUHOPiolJKyUUqpXCMw5wIAeExfQYgbIdmzF4BCrQ8wIBIAxQkLFZA0U2rtSAYAUh4g0BcZDSgERpURGCPUCEYreC%2BuYMQCEhYIjaHohC3ZGKIyFgYLQAN/KsARC8MASUtBaCgu4LwLALBDDAHEMm5kUa8CjWzYszAqhBr/EDeQGRHzFm0DwBEUsoaPBYGlQ6PAPyc2kFGsQCIXiGz5qMM2owBz5hUAMOggAangTAaE5bzN2Sy4QohxCcrXTytQ0rBX6ALSgaw1h9AttBZAeYqAh5pGze/E%2BAFTBrMsGYQFA7iCMoevAeYdhS3OAgK4UYLRSCBGCL0Yo/RWg5FSAIQD2RkjQYYFMPopQ2i/pqMMRonhmh6B/XkgQnQGhIfAyhiYIwsNjFsBhojMwuDfs2SsCQEqOCzP%2BdKoFKrCXEtJeSylUhtW6twPSo1VdaNmsnfMNaf5%2BgQGOSASQII4SRJBG8jQkgzCSAJRoDQ0yCWRP0JwL5pAfkgi4HCAlXACWXMic8glZyHlKYJax/lQKQVgr2ZO6FcKrUIvlSi8glBHWGpxWwTg9QWDDXZO/JgwdexcEiXCUzlb8DEUZXoNdbLN3SG3UoXd/LdDxGFUwUVOamMsYBbwIFcqkUoqVMq1VXGYufjiwli5ur9W2sNcakEZhTXuchZa61qADXRH8%2BiobHX%2BhqSMHFsofA6AHVBRAb1/Lg3%2Brrat0N4bI0ODrbGlE8bE3SpTWmjNWa615oLUWxZ%2BBzqOHLdKqtNbVi7PoY23gzbW3%2Bo7asRZ3be27IHUOpQI7Lsfg89Opgc6F1LotHW9LG6OVZdkDuvliz8sHonY%2BqwlhT0RHPTJpZ16WGcDvTQh9x7n2vuiO%2BrA%2BPv2VDQy4F0sHWggcKMhuDuQ0gs8SPB6o1GIOobw%2BhroPPcPVAI90UD0xBekcw5kIDcuBelDo0sBjtH9PMalc5zgHG1Wkqm01%2BLiWBPJZIF10TfWLUScwFJmIBOPmGeM/F1T7JpmRNeSCNTGnJCtHKzK4Ftg3PmqhTC%2BFiKFWjcC9i3FHAwvqpYAoYalLhrNePEMWlZuadpdkBlxHXL5A5dRzoEAIJSCFeK%2BKzXZW2Oyt84qurCek8p7T5qVkerxt2q6yCXrIeBsoE74aqPg/%2BjJ7sU3VPkSm7p4IE3VQJK5sepZF6n1frQ3rbX2GiNUbdtDbjQmpN13MCpvTWIM7faLtjp%2B7mkteT7v8sexdWtfbXvSo%2B22iE32u3vv%2B7wQHw6ARQcJ1%2Bs%2BAZ0FB51F1l04dc8EcJAkduUi891S8MdjAKcbAPs6dCdqhs01gpEsdrAX0Ks30P1MDxc0gmd3ByMgM2cwMaNecucYMqDOcENlccMGdhdJcxd2CJcqNpcOdxgMMxdeD2diNGMFg1cOVSttdAVdd59SVE9k9zhJ84QZ9TchMLde9xNSBJMsB7cmMncQBbk4QQQQRplHlfctMTD2RLMnMZDA9QVwUtCTlJBplFMXl2QtNLlJB7kuBrkzBHMPkQRpCKtOAxN%2BsmMaVbCQjA8%2B95gB0UhnBJAgA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/kindred_classic_fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left_first.test.hpp)
