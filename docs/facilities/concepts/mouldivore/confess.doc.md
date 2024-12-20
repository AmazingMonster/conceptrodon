<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Confess`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-confess">To Index</a></p>

## Description

`Mouldivore::Confess` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the elements returns true and returns false if otherwise.

<pre><code>   Pred, Es...
-> Pred&lt;Es...&gt;::value</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a class template predicate into a concept so that it can be used for subsumption.

Since `Pred_0<***>::value` and `Pred_0<***>::value && Pred_1<***>::value` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<typename...Args>
requires Pred_0<Args...>::value
constexpr bool fun(){return false;}

template<typename...Args>
requires Pred_0<Args...>::value && Pred_1<Args...>::value
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbgQAnilGKxMAA6cE/bCPJ6zYheBync5XDTQkwBKzPY5Y46zJiOZDHNAMWaYVQpYjHGKoTzHABuYi8mGOaIsBDhmDRABEfhinlyeajngcjoiLpcuLcjg9nq93p8Ob8AUDmGxwaDIdDYfCCKKrlxUejodicU18YSBCSyRSqTT6d4mSy2Yz%2Bd9eS63UK7scqF4GJLDtKXm8PniFX9AcDVeCnsRgAoNc9zgBHLx4c4KXXXH5uGNxtWQkAgO3O55Ey3kynU2je30QFYs84ETZ%2BqhiJQCgLc57Q2Uhr6KiMqsHR2Px75QxOYFNpzAZs5ilG/XMKfPjwvFh3VcyJTP6pej1fYdcMjmli2vK2Vmk%2Bhh1huYJvEP1OhVWTuCp7Cw7HAAqs51dyBrsuzHNgxDECQmqmngyCXEwChKC01C%2Btm4QEJCdb1q6HBrLQnAAKy8H4HBaKQqCcG41jWDiGxbJu3w8KQBCaDhawANYgPhiSggAHIkUj4QEiSSAAnN8QlmN8%2BicJIvAsBIGgaKQxGkeRHC8AoIBKcxJE4aQcCwDAiAgBsBApF4BDkJQaDvHQ8SRCCnCqHxAC0wnHMAyAElIoJmLwFyECQeDoHo/CCCIYjsFIMiCIoKjqLppC6FwpAAO7EEwKScDwuEEURLFkZwADyFnmTqqBUMczmJG5kgeV5xw%2BWYxwQB4tn0BS5gMSsvA6VoawQEgNkpHZZAUBAw2jSAwBSGYfB0K8xCaRAMQFTE4TNP82W8OtzDEP8RUxNodQ6YxNlsIIRUMLQW2JVgMReMAbhiLQmncLwWAsIYwDiHdM71LSs4FaSdQWTsjFod0BW0HgMQZftHhYAVbJ4PJ72kIDxBUkonJvN9MNGCxaxUAYcYAGp4JgqVFcq20xcIojiNFYXyEoagFcl%2BjfSgVGWPosOaZAayoCkvRvS5szoD8nKmJY1hmKpmPEMFQNC10PRZC4DDuJ47R6KECzlJUeiFJkAhTH4KWm70QxG6MKW1PUAj9JMut5A73QnQ0cy2yMCQO3MFt6LiLS%2B0s/trAotHbBIuUcIRykFWpVWue5nneZIvktbggWdZJXA9UxRNrAgmBMFgCR1qQHGSN8oJiQEkgaJIZiSIkilcSJ0kcLJpDyd8Zigt8iQBDx3w8fh%2BFcOJIk8YniVqRpWlF7pA1GYNJmlRZVkTag7X2Y5HDVbVhIGEYjUiaCXCgqRAVEMrIUpSzEVM9ILNxeziW6HN6WZdtccJxUrwNSJUzIWWOBVFONV3LIDPsAC%2BV8b4tTaiNDqzJJJmELn1PSG9JodR3ng0YsDvpcBElwJSNBaCLWWqtRKu1Np03oftQ6x0HB03OowAgV0boFXuo9Z6tBXp00%2BvjHYpF8DnABkDRKINkBgzppDPCiUYZw02ojMRvVlZo0YpjbGmBcZfSMATUAq8%2BCkwUBTKmNNGB02fozKKb9ZAfwSqRb%2BXNCayysHzFRgsq4izFpwCWBApbfBlrzCwCtgFKxVr4yOnsnZ%2BAgK4IOKUDZlD9ibdIZtshu0tqkLJNtDYZI9hrZ2gdcnB3ib0F28x0nh2DuU3IeSQ61MWMbAu6xNgxw6UowBSdOBQJPsQ8%2BpDEE3AgDne%2B6Duq9WLqQUu5dRhVw4uQpSSje793wqCUS%2BERJmD2dUHi09hLz1UpwJe2kib6XXkgUyZUCF71QQfNgnBmgsHciwBQtICS0lGfKWY/l8D32CqFWQL8HH02cRzEAUlf5ZXegA/KC9ipb3KpVVQHyvk/L%2BaGWYyDHmjWmd8LBVzcEEvweNQhCRvkpBSJcX5IlLj/IIJcDFb8FrxBoWtDa%2B1GE8oOkdE67C94XS4ddW64jMAPSei9N6jERFGI0aQCRXtAZvVvqoUGrwFGCChso2G8N/jqORloumuj0j6LxkY8IJj%2BpmKYOTSm1NabozsZFCQjjYpsxcToGF7jjDhP5jEWJZFRZZDersSWPM5aWEiWRaJWAQ2O16FrHWTT9bazDu0/JRQsgpJzdkrN9t1ZezKQMfNybvYDCLf7cY5aKkB2rUU%2BpHSo5dKioi05wCBlsuOJ875dIcWvDxRMoFJBpkF1mavEuZcK6UDjhsmFg9jkYLMGYLgPENCJF2V2wq6lbDL2wSsdiIBa5X3HvhFu3x8JbskkJbu3wkVnP3UeuOfld2LxXv1NYmMMjOEkEAA%3D%3D)

By turning `Pred_0<***>::value` and `Pred_1<***>::value` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept Confess = Predicate<Elements...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ZTETD4USg0i3AgotFsLEY7AvRgEBQ44FoBhbNIEW4eBhUTCE25QgAixNJ5PhiKZYJZCgZOJAIAAbmIvAjElYrsDfv8zrqjrcACpC1mfA0/fXHQGGu4kskAfQ0FoOgNhz2l0JpqOY9OxiWwwImxC8DglTo0wJMAW1l1uCduc0cyDxAgmmFUaWItxiqE8tzV3kwItjBFDCICoqhcZj1a10at9sljq4rr27rBnsh3tpfsxAaDVxDYd5DvQrejseBiaTLRTaYYGazObzBaLGtLFnLGrrNan9drTYOtyoXgY7c7cJ7yN96IZl2IwDZgeBpIAjl48KSifzBYTEXHZ0qUfZ9FVfK5OWXbNc3zWhT3PCBlhjCxSQIDYLyoMQlH3KtGxBLsIU1W86QHDFQJfIdH0wT9vyFPkBH/F83CAjQQKfBVBxFMxknMZIGIFIVmKArh2LAwcOXTUEV1ggszwYJCULQjDqQrXDqx1Y89hNM1L2Dec8GQR0mEJeICGoc9EXCAgcSQ5CtQ4VZaE4ABWXg/A4LRSFQTg3Gsawk3WTYS3MRIeFIAhNEc1YAGsQBc5IMQADmSKQXICZJJAATkSDKzESfROEkXgWAkDQ2I8ryfI4XgFBANjIs8xzSDgWAYEQEB1gINIvAIchKDQJ46HiSJ0U4VQUoAWky25gGQVMpAxMxeDJQgSDwdA9H4QQRDEdgpBkQRFBUdQmtIXRRIAd2IJg0k4HgnNc9you8zgAHlep63lUCoW4JuSabJFm%2BbbkWsxbggDwhvoHNQq4ZZeEarRVggJBBrSYayAoCB0cxkBgCkMw%2BDoUFiDqiAYhemJwlaJF7t4anmGIJE3pibRMAcenSEG14CDehhaDps6sBiLxgDcMRaDq7heCwFhDGAcRhbohw8BVIUXszDneu2cLrPqF7aDwGIbuZjwsBe8s8FKmXSHV4g8yUUUwQVo2jCi1YqAMZ8ADU8EwS63t9LntuEURxAO0PjrUF6Lv0BWUH8yx9GNurIFWVAeRyaXJomdAxVMSxrDMKr7eIDaNfTnoOcaFwGHcTxOj0UJwmGKpRlE4psgEaY/E7zJu4YBYRgSUS7BrvpJnaRuCjH%2BoJ4Efo2mH9vR9sKfe70OZl9bxYO9WBQgq2CRHo4NzSEq3hqr%2BqaZrmhbJCWiHcDW2H8vhxGPdWBBMCYLAEiQqQOKkhEgYhygESQGhJBmEkMkcqCUsqFQ4MVUgpVEhmAxCkAISVEhJRci5LguUspJQvi9aqtV6oRQ9i1dqqNOqfV6v1HGqBoYjTGhwf6gM8QGCMKDLKGIuAYi8qtIg5dNqiVDrtCO0go5KBjmdXQRNrq3Xpqfc%2Bl9XocA%2Bt1Xqtwfo3wBjNfECs%2BECKERDKGGMYbcXQQjKhTUUZoxYVY%2BITDcYwxQDwgmWUuBsRoLQUm5NKZnUZrTLmoTmas3ZpzW2PMWT80Fi9EWYsJa0CllzOWrttheXwKSVW6tpbCNUNrUEXN9bOTOkbE2tNzbZMRuXG24V7aO0wM7eWRg3agAcXwb2Cg/YByDowEOsgpH7RkbIaOp0vKKPju7QuVhk5VLToAzOjQc55wLknCwJcr5lwrssg%2B89VbOAgK4TeokW4VBHnoLujRznpAHo0FeSw569EXhvGefdq7HKaFPZ5Hd14DHudvQYu9rnwzWBsY%2BEKKnqLIZwAxXDjG8K4PwwRLoIAv1ETYj%2B9jkbf1/v/SgsUypsQqSgtBLkMTZRcllMwdKeJJUIZlUhZ1yG2EoUjZqrUOpdS%2Bm45xmNRpsE4K0FgM0WAKBVKmFUqKMREQmCtfAoiNpbRGeHMZh15ByKmToJIpBlF3Rlmo56bL3oMO%2Br9VQEqpUyrlQq3kkNBXWNCokOxXLHEoGda47G7jRjSrSGkR0sqsqOgdY6a1MiSbxCCVTGmzNwnxpZmzGuXM4mCASULHJmBRbi0ltLcKmSOl1NILkieBTNbFOQDrMpggDaVONqbJEtTLYNK5s0zIrSXYdPCF05GPSmC%2B39oHYOttJEaokOMo6OrY76q8YnIuizU7wAzlndMnAdh5wXQs7Zpd4hiMroA8ePy64N3yF8y5bcXkPJKDke5tycj/LXsexoS9p7nq3kc19fywWry3h8j9Y8f1XL/RCw%2BUL9omtZVVBFkbbiSulYWe18IJjP2VSQHF7qv6kB/n/UYgDyUlSSBg5l%2BUzDka4ElDQyRaXQavpwChDVsPANAYQvB0DEguWo/lDKSDEimpgzVPF0UkHLTo5oz%2BDjVj2yyM4SQQA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/mouldivore/concepts/confess.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/confess.test.hpp)
- [Example](../../../code/facilities/concepts/mouldivore/confess/implementation.hpp)
