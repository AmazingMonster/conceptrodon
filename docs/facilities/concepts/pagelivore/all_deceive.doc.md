<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AllDeceive` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `false` for the value result of every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&(not Predicate&lt;Elements::value&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllDeceive = REQUIREMENT;
```

## Examples

`AllDeceive` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&(not Pred_0<*>::value))` and `(...&&(not Pred_0<*>::value)) && (...&&(not Pred_1<*>::value))` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&(not Pred_0<Args::value>::value)) && (...&&(not Pred_1<Args::value>::value))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EAHRXx9gmGgCCE8ReDgDUysSY6AD6Gnf3JmSVger1BrzmjmQrzQDAmmFUaWIr1iqE8rwAbmIvJhXoCLFQxEpAQARY7AgHJUn%2Bcn/Xb7Q6YY6nc6oK4XG7/J4vAjvT4/Lj/PH/MHglqQ6ECOEIpEotGY7w4vEE2hEylkwVq6mCh50g5MI4nM5EV4ASQ5Dy5bwAsgJUEQGABPDXkkUQvBQmFSxGvI2oDFYxVAs2amkh7X3XUMpkEB1pRisTBs%2B7EYAKc3JzAARy8eE%2BCleEDZ5gAbCWIAw7byvr8mcnUyAQPLsTcG03MMtlv9PbtpcjUbRXlQvAwIJ2gZ8CBsGIPCYytWqHrS9nqDW4Y3HmGwkym0/5bg9Ptnc5h84XrmZSxfy5WPtW/ic6wpWwGW42Ax3cReSwWi1%2BrxWeVvflax3Z8FVfNsOy7SUe29WUByHEcxwsCcp1eAhnjnKwFwBC0xXdb4mAUJQ2moYcmRtACBCdE4BT3G5R07akOFWWhOECXg/A4LRSFQTg3GsaxwXWTZFTMfweFIAhNBY1YAGsQECYsLgADmLKRAmSYtJAATn8LTxP0ThJF4FgJA0DRSC4ni%2BI4Xgn0s6TuJY0g4FgGBEBAdYCDSc5yEoNB9joBIogTThVDUgBabTXmAZAoSkC4zF4L5CBIPB0D0fhBBEMR2CkGRBEUFR1Gc0hdC4UgAHdiCYNJOB4Vj2M4mTeM4AB5c5fJ5VAqFeCLi2iyRYvi15ErMAsPCC%2BgkXMCTll4JytFWCAkECtJgrICgIHWzaQGAKQzD4OhdmIJ8IFiVrYgiVoHQa3hruYYgHXa2JtEwBx7tIQK2EEdqGFoO6yqwWIvGAU5aBVL6sBYQxgHEYHjwcPB0RPVr4Q%2B85tkkiJdjYsraDwWJauejwsFajC8DM7heFR4gUSUYk9jhwmjBk1YqAMVMADU8EwKr2o3L7suEURxAKkXirUVqKv0OGUEEyx9CJp9IFWVA0kaJ8OEiiZ0GOYlTEsawzBsuniAytG1Z6D7GhcBh3E8To9DCCJhiqUZKuKbIBGmPwvcyH2GAWEZEkquxbb6SZ2idgpw/qSOBH6NoQ49sPbGjv29DmFO3cWT3VgUEStgkJqOA4qzWts/qopiuKEskJKC1wNLZvErgFqk9nVgQTAmCwRJR1IBTJH8C49OSSQNEkMxJGLCylJ0oyOBM0gzIki51OLFSdJUrhi0CSQuECPTi0rsrbPskBHPZ1yPNWryur87bdpm0K2E4VoWHRZJIqYaEDBGDGjpC4XALg8VSkQC2mVKoi1yuLaQkslDSzKroI6NU6r3TLhXayvBbKdR8ucV4vUfTEG/r/f%2ByBAHAGAaA8Bk1UDTQSJ%2BfwZhO5LRcg/V%2BCR/I7UYRtGaIAv4/0ilQuGXAdJcEsjQWgp1zqXTKo9W6X0lHPVeu9T6NNvqMN%2BgQf6gNWogzBhDKGWiYYs22DxfAnxkao21hA1QmNdhfVxvUVqhNia3TJpYxaFtqaSTpgzTATNYZGFZqAZyHMuYKF5vzQWjBhayHgflRBsgpalR4mguWbMjZWCVh41WQ8NZa04LrAg%2Bt/CG0VhYU2eDzaW0KYXBOyNnAQFcFnSqrsKihz0N7RoHT0iB0aKnJY8dehJ0zrHf2NsWlNGjiMz2GcBgDJzoMPOPSO5rA2CXTZ%2BMcFV04KQ8hf8AFw1oWAjQzd8BQJYR3Ra3dSC937qMIe%2BNV7rxAdPZIJ9kjJH8DPOeR9z42U4FfG%2BkS77wAft5bqvDuHEHftsL%2BMUWAKHRFCdEEiLgMgmCla56UYGFVFnlCQqSirIIyToAI1Var1RptglqF8OpPx6n1ZFw1UXooxFinFPIIBTQEcwua/h2G3y4fwzacKJWCPRWkNI3xMU6W%2BLywiZDtLHVkQkeRV0brPRUbql6b1bZfR%2BowPRAMgZWMwKDcGYhTGSXMWEnxpBrGRzsejRxyAsYuMEG4gmRMSYOm8RTPxX1AmZGCczMJEQInLT4NE2JAshZaLgWLFJRL0ky2pdQhWxt8kq3gOrTWORtYAHo9a5ryTUs2CRoFWyHhHWZ9tHb5GmV092ozBklByAMvpOQFnp0bY0ZOMdW3Z2acO%2BZ6y07Z0mWO8OU7ukzs2UXbZ%2BUGXArwYc9lrxOUYp5fqE8fKW43LmncrukSe59wHpQMu7ykggP8EEQI08pEaCfVpFSm62p2VsNfC9y15IgFHqA/wKlD7iRfcWcSWll7%2BEZSC39HCOzL2St%2By%2BAHZKkDplkZwkggA%3D%3D)

By turning `(...&&Pred_0<*>::value)` and `(...&&Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllDeceive<Pred_0, Args...> && AllDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllDeceive = (...&&(not Predicate<Elements::value>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbrv7h5gnbkxeRAB0jyfYANTIBgoKL8rEmPiiu1ILwIAE8UoxWJhHvdsPQ2IIFM8TBoAIJoBhbFIEF4o2i0AAitUweAAbpgXid8S8INDzP46RAGKhsT8/ngAVdTrC9owCAoQCASWIvJzsAKhd5MMtlicrKjkSiAPQAKlVavVGsVCpVapeABVMDMvuqtaidRqLarTSiFecDkwjqdbg8nsdsAqZsQvA5vr90AB9DQKkwAdjlKJekZeMwd7LeAhmmFUKWIL1iqE8LwlIopYaoYiUofxsuDIeLx3Dtr29sdNzuqFpbo9BC9PtZAa4pfDUejjUcyHjDETydT6cz2fJoYs%2BdohbLJfl84rwdRdsu12dqBeAEkkajPd7sQBZATMgQgrsKnsx/uD4cpl6brPCydh3dLysflcotcOzlnMEITYaEUWIYBESbVFfgARy8PBfi%2BXECSJUl/3bQMgVA8DG3dVF0XvUcM1oF4qC8BgIBlMNfgIDYGBIgtOSsed5VXat11OUFwWYYDHiwiDcNAzBYPgw0cTxQktlQ650I0TCwIUHCKTMellLE5DJLJaS/X9Lg5Ow10BPw3YRzTIiSLIiip2o2jgS9Rii2/G92X9JhPgSAhqDI64TyZIgGAvU5OybN0KJlZdUQ4VZaE4ABWXg/A4LRSFQTg3Gsaxo3WTZJzMY4eFIAhNEi1YAGsQBiyR7g0SQuBDY4NBijRlP8MwAA5Wv0ThJF4FgJA0WSEqSlKOF4flZMKxLItIOBYBgRAQHWAgUjuchKDQfY6ASKJIU4VRWv8ABafxJBeYBkAHKR7jMXg2SIYg8HQPR%2BEEEQxHYKQZEERQVHUSbSF0XSAHdiCYFJOB4KLYviorks4AB5O5luxVAqBePbDuO07zpeS6zGpDwNvoVNzDy5ZeAmrRVggJB1pSTayAoCBafpkBgCkZIaFoXZiH5CBYhh2IIiaEFwd4QXmGIEE4dibRagm/L1vhAg4YYWgRb%2BrBYi8YAbjxfluF4LAWEMYBxA1kS6jJfWkqTWo7m2fKIl2aK/toPBYhByWPCwGGWzwXqDdIMliHTJRCWNow3aMIrVioAxwIANTwTBAbhrjRc%2B4RRHED7nvkJQ1BhgH9BNlB0ssfR3f5SBVlQLEsn1g6ZnQSlTEsawzCG4P7qwauKM6boshcBh3E8No9DCeZykqPRCkyARJj8XS556QZp5GXSajqAQ%2BgmMe8k3ro5fqWY1%2BGRJN9mRe9BjZoz8WC/VgULKtgkSGODi0hBt4Ya0f2o6TpnQupVPGEBcCEBIEpUm5MY6rAQJgJgWBEj9zKpIY49xAjHBDJIaqZhJD%2BH6jFDoLtuqkF6nle4/guD%2BFaoEVq1CKpcBipg/wX8YbDVGiAcaMdppzWpgtRGK1GbMyJttNgnAmgsBJCGA6TA3gGCMDjQI9wuBVRuvgO6D0nqyFejnaQedvqFz%2BroZIwNQai3fp/b%2BsMOAIyWncF4KNHzECkTIuR7wTZKJUVVfGqBCYJCgSsGBk0qY0z8XTImq0mbhJZpI6RB0PFGC4IELgslObc15vzP64thYZxyZLaWssHAZ0VryFWasYaa21rrWcGcjYmzNklfAvxLaGhhrbZA9sM5Oy6DDN2Hthbe22ElP2Ad8rB1DpgcODSIigBCXweOCgk4pzTowDOeddHvX0bIQxv0komJLtHNuVgK79L7rXeuCZOBNwIC3Y4%2BJjkdy7gkHubSa4D2Ps4CArhr66UnmUc%2Bs90jz2yPvJeqRgWrynoCw%2Bg8d5XzBTfI%2B29ein2hQ/G%2BCLcjgtvnMAFGKuBPxfu9Sx0M/q/ziW4%2BRnjkneI0NScBd0oGEuCZTOBCCkGUHfqQ8hyjqohmYSGOqkg8HHV0tYjhtguEFR4TNeai0kZRJEVtHaHBJGYxYAoEkA4SS0suDMdRECe7aJetnLZmddlFxAMcUgZiwYG1JWw8l8NBHI1Ruqk6mrtVZj1X%2BGYvj/HE1yscMmMr5n8OVQzNaMSiaCmQCkFI/pdWBH9PqggLkXHHT4HQDJlAslJXyerfKhbClyxKX4pW5T1ZNMwFrHWYhamB3qZHYZhsLaOCtu01QdtdjdMEL0127tPYgiGb7e6YzeATPSFMvYMzo7zLjkwROydU7p0Dhss1EhtlfQLnsnQ1rDnGHLjYM58ALk9H1oqZuZd26WE7j/buD03n9y3j0Yeo9sUTxHvfGey9IVZF%2BRCooWQf0bw%2BSi3eLREWws%2Bai/ooGL5jH6IB3FCG35rA2K/QlnUP5kqGpwZxLANVap1b63Y/qwEaMgSTFlYa2WkHgYgkY/cSE9SSMo44xwYqNRqv1TjIYaFOvwyNKV3CQmlRAJIGKGCYqtWUoESQgQ6pYK4Dal2xw8M/04Ky4qOHrpCa0yJimung4ZGcJIIAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/all_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/all_deceive.test.hpp)
