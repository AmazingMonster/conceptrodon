<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conditional">To Index</a></p>

## Description

`Typelivore::Conditional` accepts two elements and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two elements according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...&&Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Conditional
 :: typename...
 -> template<auto...>
```

```Haskell
Conditional
 :: typename...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<typename...> class...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename, typename>
struct Conditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see four examples that present different use cases of `Typelivore::Conditional`:

```C++
struct IfTrue;

struct IfFalse;

using Select = Conditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if all arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfFalse
>);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
otherwise, the function returns `IfFalse`.

```C++
/**** VoidInt ****/
struct VoidInt;

/**** Void Tester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction<int>, IfFalse>);
static_assert(std::same_as<Metafunction<void>, IfFalse>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfTrue>);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
otherwise, the function returns `IfFalse`.

```C++
/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction_1<-1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfTrue>);
```

## Implementation

The implementation is straightforward.

```C++
template<typename IfTrue, typename IfFalse>
struct Conditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail<I>
    { using type = IfTrue; };

    template<auto I>
    requires (!I)
    struct Detail<I>
    { using type = IfFalse; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...&&static_cast<bool>(Agreements))>::type;

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...&&static_cast<bool>(Elements::value))>::type;

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;

    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSgaQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn7VmPZFDA1NBCVRsfGJQQqNza251eP94YPlw1VcAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLMn0bIJM3bdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3AQAJ7JRisTAPKgAFWIXkwpFu8MRzDYqIAYmIlNDsMCxpiHLcPAx8N0xMCTAB2KxXW6c3Fg57vTDQtxMLxEcnArm3KleGkAEUwjTot1ZVhZ0uh7KBHK5oPBfIFQqID1Fms5xEwAEcvHhTQpDcaJQRqQRbrL5bQBfcjZdxUrbl50kZcQiUdDpaiMVi1YqVWrmXbtbzITD9ahDVCKXbTRarZgbRAwGB7ssxVzJTK5Uw6O7Pd62b7/cBA4jFVDQ/cqCTaGSoRYo6ru7GvVzfntbsomMAUV9i5z4xD%2BUnhagAHQry7AU1gxgEBTVrl%2B8INscT5uhl0Vt0wiArpfmfy3sbvPDIAD6ojGApiqE85Iga43r23ZYizTEAQDxed1WnW5h1uABZTx0E%2BM4oNnXUYXAglMGvbAXi3Hc0yg/cA3g2hEJDZ1y0rS9r1ve9GkcF83wID8vwvbAIBwzdBAUUCADcxCxIDyVA8CYyuFCeTnAVUMTWEg0wmi01uZADAUBRr2UU18FEUF8PTQdOVLJ1NNQIgACVUCYdAoKVKDxRk%2Bc5PxZFsNw7jd3FTkiIbEiyJbCjXQFK8V1osx/AfBjXyYd8YU/b80wgTTMG0vl8LcTiAPUkKQJAfjvEwISctE/s7VZPtILtGCLKspCDkBezJLQ2FGtkjCXOy7BlNUrKlySlLdI8usD1uaq/NDEzzMs6yYT6p9UsUikSo1AzuR1VqWsc5MFq66KetmnSc0GozR2IUzUDM88bLZOytQ2vVF2vAA1Jo8CYGJ6D0m6vPrUdx2DfyzyotxgpvMK6MfRjouY2LWJ/fbUoFZ7iFe96cwWviBIK4DsBEoMxJWsr8e9SqjhG89ar2erbrWxyHPuohtpU3aNK0uaBoIu1vLJhVyIm87Lpm1mDp60UlsJsWfn%2BKWp0lu4iStMZbmwVRWGeSdkNl6WpcBZkzChcIVK8LBmzcNAGC2ZJt09YEYLcBBUCfHMKcBY623DCDKQdKUnTbDsuwq65SaETpaidGXLi54OuhPWkBAZTImRhN3MWxYlSXnRaA5gtEc23Z3PYh59dviAgIDGdBQIUZEi7SqPQ9Ao9HKCW4zHJHFk4jNNgPVCKnxrpRmjLggK5AKu2BrgU64cBu/oFDQcVbtN2/bdPyW7gdhy1v5ARg4OzcQ5XVfofPNa37eB17l9i8H8vK%2Br6LmRhKCp4IUDfJsp%2B7XFW%2BQHCUF1zEK%2BAQD5BACj/jiLgbdFRfxLMPUCf9MAANoEAhgIDoZuHAS3QaUCoId35OJLu%2BMC6RWvqXH%2BY9MATwIW4Z%2BIdp4gHfqVT%2BK1v5wN/oIRBxBAFmzQWAwQOINA4JgYZNhCCkEoN4TCTBi99LeiXtAlavtV4EOwOvcSp8z7HB3qTNECArQHxVuCdWdUbaaPPuowOdxHoO3QPcQQJ9LjHWsXgWxoCJaWIOLcZxiEc5jHiA4um6F5LtRvBzRxXsaTeN8aCBItxkheHek%2Be0I8qDp2fOBKMypyoDkCTQsJTibHRPiAKXiNjhJxISbQJJP8vaUIybZaM7jcmegKS4opxBEY2LsdDHGFTEnIGSSJFO6SgyZPFlnUm3T2kBLukE5ybAFqe0dA8QQ7SQB9KqQMn%2BqTOx1NGQ07JFjmn5IiT7VZudilSLcb0%2BJ/TBlgWGfU66jSA7HP0q7c5fiOkwm8d08ptzNn3NqSMpsByiGnzguWKgXhzYfHDrktqCzVzEGAJ9K4XNYJQphXUAQMcX7AlAqNTpbSLlkBWQQdpno34IQFJcFFIsCLuOzrnG04dL79xLkPEeFCJ4wkxY0aFsLMh8J6cvP2Gc1HhMLqQrld9x4Pz5VioVAgSllPkUo3Za98bspleQ%2B%2BaV%2BVMEFTihgxLXGirDCnLVS0dVqU5Xq%2BVtc6GvxAESp%2BOV37uuwMvd21qJlmIBKYuW6xmgICVoYtWDjN4BpMRYmCkQBAFAyLxTA0z4WzMFA9DqSzva3ATQwJNjgU1rI2dUthOylAguDM8w5y1cnJlTPpTMlprS3AgPcE25ENC3CLFcY6%2BbC14GLaSqsIFS1bLYcCp5WTwUggzVtbNfbTl5oEBEYAj5h1fPWQCstKS0nTvGTk%2Bdi5G3AmbdmXM3aBTkULDmmk%2Ba10btTSOpO/zKm7qGViKtYyXkb1Joa41cKNZzppvTZcyLUWegxUqk1z4uB4udQS11As3ADrSMm59XycQPsQU%2BylYSZ4TlpfSxZTKdEsocbageZC2E8oVW4AD2LuhwYFAAWkgeqlemrCE2von3XVtH9UCkY8qhgLGYQce9WnbjqjtV8avnam%2BgnHXCZg8xjjbhBGcd9Txnu8mOVKe5UJmEL9CUoeEiARu17tNWt0xwVYtBOAAFZeB%2BA4FoUgqBOA0MsNYCUIatiKj1jwUgr93P2dWAAaxAE5yQS4NAAA4zBmAAJwpa4E5xLCWuAshZNIRzHBJC8BYBIDQ883Mea8xwXgPF55ha0KsOAsAYCIBAOsAg8SCDkEoGgJ4dB4iRGRJwVQCX/Csf8JIW4wBkADKkEuMwvBkqEBIC4vQ/BBAiDEOwKQMhBCKBUOocLpBdBBAAO5cOSJwHgDnnOuc0LwKrAB5YUnXbioCoLcEbY2JtTZm7cObZg20eD6/QYgQWoQrF4PV%2BzpAIBIF68kfrZAKAQAR0jkAwApBmD4HQGJPEIAxHu6QGI4Qmhwiu7wEnzBiBwkezEbQ9duC8F6wBR7DBaDk6O1gGIXhgCCloJ2CnpAsAsEMMAcQXPsx1BTTxI7mBVC1GFNsELCCCseaqTELhNOPBYCJw6PAJWmekBTcQT8ShZSi6MFUow93VhUAMKix6eBMCnce/iIX63hCiHEDtz3%2B21BE5O/oMXKBrDWH0HgGIPFICrFQJbTIsvWPlxDKYXzlgzCVZN8jLA0eICrBqCalw9JJh%2BCCKEOYZQKh6EHQIEv1f0PdAGJXxYthnX1BmHX0YbeBC9GaE3oYlRbAd88G0PQD4%2B8V4HxIfPAXts3Y4C50gFWHucE%2B6N8bk3puzbi4DjiDISDg8h6F23qwECYCssMPPpBouSChEuFLUI8saEkGYSQ/gytOf8Cl/QnAiukBKxDkuIEP4Aliltlv4LFhlg/v4EvkTlVjViAHVrbrDi1nDm1i9sKN1qjqgCDgNkNhwE0CwLxCyKxkwDtAGFwClkuFwPFotvvtnmtrIJtj7tIH7koAHkdroNjudkwJdkzvPovsvp5pwM9h1sKG9h9l9hvuQQ2JQdQfFkDjgYjqDuDmYMsFDsgWgWjqDlgdocMEzEYJQVwPPDQLQHjpQITkdlTmTkLtYTTnTgztPEbizluGzhzkTtzrzvzoLkbiLmLhLh5vgKaNLjmETvLorqCELqrkThrlrnCDrtsB5vrobiFibmbpgBbv4QeMgfbuOAoE7i7m7owB7kwd7ttqwbIP7odh5lwcHjbqnlYJYBHlHvALHvHsApwEnsPCnmHunpnvENnqETHq3l0JkEXu4CPrkGXvSP3gsIPjXlkJMaXikA3pkLMVXl3qMT3sPjkMsQXt0L3rMKUFPqMDsaPqcX0OsYsDPhsFsNPj/gvndkdlVmvt9pNgYbIVQTQd2nvstmDuYBDuocfuFkBKQGfhfgkFfgVn/gAVQc/iyE5ilrllCC/m/pIEEEIfAbYIgcCQ1igfAGge1p1roUoUjoNmwJwIQT9iwAoLxAMrxHIXOGMHQX8atkEJ7sweUbtvIOwdUToCAFCKQDwXwddg8YIXASIRgU6O9p9tSbSfSYyalE6BAMDsof4gCVCECdDo1vDqSToSjnoQkHSckMkM%2BAySls%2BEyQQM%2BKoBNjjmYfEPjpYR5nYZziFq6Q4YziFi4YIG4ZzoEZgDznzmID4SFn4VbokbwEEaHEOqEXLgrsgErlERwmrrwLEWTgkXrsjCkbwGkWkBkWCFkTbiCXwA7vkc7q7u7kbhyWURIBUXtryYHgKXUcYL0TYBrrnm0d0LLjsLfA0dYBng9lni4kMVfvsWMRAK4J3sEDMZPnMfXoUJkNOQsVcYPuOdsX0NOeuT0DMKuWPmcVMUPpcXORsTcZsHPmKU8ZVqvraZNjSXSbcOaUuFaW2rgH8YflqSfmCeflgJCfPjCSAKlkuFCFCE5pluiWViBSyCAbAc8ZwAgUgSCVFiAJIE5vfjliyGVglpIOllwElmFA8VCFeSvtVriRFg8QtrBdeaRdqasCbukM4JIEAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/conditional/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/conditional.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/conditional.test.hpp)
