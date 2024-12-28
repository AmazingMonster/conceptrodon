<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyFalsify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-any-falsify">To Index</a></p>

## Description

`Pagelivore::AnyFalsify` accepts a class template predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||(not Pred&lt;Vs&gt;::value))</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AnyFalsify = REQUIREMENT;
```

## Examples

`AnyFalsify` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0<***>::value))` and `(...||(not Pred_0<***>::value)) && (...||(not Pred_1<***>::value))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<auto...Args>
requires (...||(not Pred_0<Args>::value))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0<Args>::value)) && (...||(not Pred_1<Args>::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMyJpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAggSYLKkGzyaJbkxeRAB0AM%2B2HuD3GxC8DmOpwuGhBJgA7FZHocUYdZo5kIc0AxxphVKliIcYqhPIcAG5iLyYQ4IixUMRKBEAEU%2BSIezNZcMeewOULO5y41wOd0ez1e70wn2%2Bv1QAL%2BQJBYIhBD5Fy4cMRINRaOaGKxAlx%2BMJxNJFO81Np9NojPhLMSbI59q5Dx5%2B0OADUmABPIX7EVPF5vJgfL4/IiHACSCseSshnq9GrZ2vReEx2MNBMOYdQ5MpFsRUdtnMejod3JuhyoXgYvtuILFQZD0v%2BAIexGACmjbcwAEcvHhTgpDhA5Qi3GOIAxUCqTvzYV82x2gSAQGaqUsliD088jUSSbRK9WIJvEacCOsa1bGU6iyXRYGJVLs3LF53EsDHqc%2BwPMEOR4D4XHQDJ2nVVLilV9l1XPMNxpMwADZzHg4dR0AicpxnaEBQg9s32wFc10wDctwNHdMxNA8qwYY9aTPC9DgIcFJRvFk7xdCsABVfxVG5/W2bZDmwYhiBIRVdVTc4mAUJRWmoaspXVd9j03e0OBWWhOACXg/A4LRSFQThx0saw0TWDYLTMRIeFIAhNDUlYAGsQACeC/gADngqQAnheDJAATkSHzLP0ThJF4FgJA0DRSB0vSDI4XgFBAaLbN0tTSDgWAYEQEA1gIVJfnISg0FeOh4kiVgtlUDyAFpfMOYBkExKQ/jMXgzkIEg8HQPR%2BEEEQxHYKQZEERQVHUNLSF0LhSAAd2IJhUk4Hh1M07S7P0zgAHlfgKlVUCoQ5qvgurJAaprDhasxhw8Ur6EJcwrKWXhUq0FYICQErUjKsgKAgL6fpAYApDMPg6GeYgkogGINpicIWi9ZbeDh5hiC9LaYm0TAHCR0gSrYQQtoYWhEcmrAYi8YBvloa1cawFhDGAcQyZ/Bw8DJX8NrxbHfi2azwmeDTJtoPAYgWtGPCwDbGLwCLuF4DniGJJQmReRmRaMOyVioAwO3dPBMFmrbUkYXG%2BuEURxGG82xrUDbpv0RmUGsax9FFpLIBWVBUgaJKOBq8Z0E%2BJlTGMywzDixXiG6znPe6bGGhcBh3E8Do9FCcIhkqEYZqKLIBCmPxc4yfOGHmYYEhmuwE96CY2lT/Iq7qGuBD6Vpy%2BzyvbDrwu9FmdvM4WHOVgUMzNgkVaOC0mKNvio7avqxrmskVrh1wTqHssrhnpsrWVgQTAmCwBJj1IJzJESP4AvhSQNEkMxJHgqKXL8kKODC0gIsSMw/kSeD4TcokNyAQAhcECn5NyM9JrxUSslXeaV3rZQ%2BrlXahU/oA3uhVNgnBjqnSxAYIwl0/J/C4H8PSHUiDRx6jNc2A0rbSBtkoO2k1dCg3motJGk9p6xV4PFHa%2BVfiHAOvPE69VkAEOAEQkhZCbqoDuvEOC38d6vXSsgjB8Qir/Tkd9e6KAJFcD8lwaKNBaAQyhjDSaKMEa4ysWjDGWMcbyzxnIgmBAiYkw2uTSm1NaZOPpurLYel8CnDZhzP25DVA82eLjAWdQNoizFgjSWgSXrRzltZRWytMCqwZkYDWoAEF8F1gofWhtjamycbQy2Q0GGyFthNPSrDHaa1DlYSwbsYge1Pt7X2nAA4ECDokEOLtw6R3iFQ2Op9q5s2cBAVwvcZoZ3KBXPQecGgLLSCXBoHdFhNx6K3HuDci7xxmY0OuOyc7d36Bs/uAxB4rO3qsdY49HlC24bPTgIi8HiMZlI0hVwIDr0oYo7eL096kAPkfEYp8nJGOikLD%2BX8Ah/H8gEPyZh0UITcmA3yUC4qcFgSlLWGUkFIDyntTR6jiBYK2C0Fg9UWAKDJJiMkBi/gSnGO1fAlDuq9VkHQmpI15BMIaToJIc0FpLXllw9a0DtqoP2odVQDKmUsrZRylUEBbo6IUY9RIyjiVqO0T9SlxrdHMtSKkc4rK/LnA1ecZVDDwbxHMbDeGaMbHuvRpjBOuN8aMDccTUmQTMAUypmIXx1l/F5JSaQYJNcwlc0icgXmMTBBxOFqLcWXpknSzSbjTJGRslqzyeEApb0ilMD1gbI2JsdLWSqYNCQtTRoivtuKiRzsw42ASV0r2Ptsh%2B22IHLtbSLAR14VHGOfaTmJzmcnDZSys67M2cUbIGy1nZAuV3aZDQ271zyMc3dtc5j3M7n3Q5h6L2nuWeex5o9nlDRlXi3hnzHWHEZcy8k6rgzcTXtykgIKDUIP3ofY%2BlBJ6IqSD/HFlkzDwa4G5DQ8E0Uvs2glWwcCVEbjPiAC%2BJCgEBHvokAIyHLI%2BTfokWV%2BKMPYcnm1NDMD4FvRWIrTIzhJBAA%3D%3D)

By turning `(...||(not Pred_0<***>::value))` and `(...||(not Pred_1<***>::value))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate<Variables>::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgkgDMpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJiSbhBYLemEhbiYXiIADo0ZDsDdkAYFAobspiJh8KIQaQbkjUWiAGotPBMGL0BQYoFoBibVIEG4XBgATwAYmJMlQeTdIQARG4QNEokwAdjccrcEAYqE5BKJeBJ8KhNOIdIZmCZSWwIBAADcxF5MEslpCrJcgT8/qdHYcbgAVQ0EPGfV3O30O75u9XoAD6Gg%2BLsuMKecIRFNQ0uZl3GxC8DnxhLDGiBcvtFxuhZus0cyCxAnGmFUqWINxiqE8Nwt3kwotlFiogvhsrFdtzPb7gauwazoa4kf2AJj4O1iORifRxqBqfTatHXH7%2BaLxeapfLDEr1dr9cbzatbY7XblvaS%2Bevg8BQduNJFAeBoNjEKhCfuyYuK4zF9NyBbcS01fdDxrcl5ybS1WzzO571vfsbzvJ99huKgvAYCddinD8Z3jedpQuYhgCNbAgUJABHLw8EJPFuX5QU8GFBEQ3DMlSPIpMl0uVlIOPBtaEw7CIFtdtCQIdYcM7WglD7Ach2nONv2ItFuIoqjMFo%2BjDS5XkBXk1ieXY0cNC4siFF4zFzAANnsgzmOMtioQ4rhLJ4xdKP4isQSPOthNEhhxLzKSZJuAg021KwlMfYdbk9cZcIBMDkFDJhcXiAhqGwhEN2NcTbVvDgVloTgAl4PwOC0UhUE4BVLGsYs1g2eCzCSHhSAITRSpWABrEAAjslEAA47KkAJZTsyQAE4kmmjr9E4SReBYCQNAs6ravqjheAUEALJ6mrStIOBYBgRAQDWAhUmRchKDQR46HiSJWC2VRxoAWhmm5gGQMspBRMxeA1Ig9XQPR%2BEEEQxHYKQZEERQVHUE7SF0DyAHdiCYVJOB4MqKqq3q6s4AB5ZE7s5VAqBuT67J%2ByQ/oBm4gbMSUPGe%2Bha3MTqll4Y6tBWCAkCe1IXrICgIDFiWQGAKQzD4OgQWIA6IBiEmYnCFoeXx3gteYYgeTJmJtEwBw9dIJ6XgIMmGFoXW0awGIvGARFaHky2sBYQxgHEJ29IcPAzUNEmq3N5Eti68IQXKtHaDwGIcaNjwsBJqK8HW7heBD4h6yUMVQV9hOjF6lYqAMciqTwTBMbJ1JGEt6HhFEcQEeb5G1BJjH9F9lBrGsfRE4OyAVlQDlsgOjgvvGdBxVMJrLDMHbc4h0PR%2B6c2GhcBh3E8Do9FCcIhkqEYPKKLIBCmPxz4yS%2BGHmYYEg8uwt96CY2n3/IX7qN%2BBD6Voj9T7P1sB/a%2BehZiAOPgsM%2BKwFCtU2BIQmHBKqkG2rwXadNvq/X%2BoDSQwNJS4EICQUUHUuD826mXFYCBMBMCwAkcSpBBrJBRPNWUkgNCSDMJIOym1hqzWWhwVapB1pJDMCiJIdlZSjSSKNAIAQuALVmqNNBJNdr7UOpQk6wtLoi2upTe6UsZbczemwTg9NGZYgMEYVms0URcBRLVMGJA8CQw8s3WGbdpAdyUF3NGuhFbY1xnrZBqD0Gkw4BTW6yIbg0ywQzX62Jfa2PsY4jmqAubxFIWIihgtTp6OMfEB60sMni25igax8tZpcAsjQWgKs1YazRgbHWlsWlGxNmbC22crYZJtnbB2JNnau3dp7Hp3ti5bFqvgQkQcQ5TycaoCOIJLYxzqCTBOScdapymQLPUWcuq53zpgQuPsjAl1ANovglcFDV1rvXRuPSPGt3ht42QndUa1QCb3UuC8rCWCHjEEejDx4NCnjPAgc8khij%2BdYZeGDV6uPXow1%2BQdnAQFcOAjyR9yhPz0BfBoWK0h3waEAxYP8ej/zAV/G%2Bm80WNA/mSs%2BoD%2BhEsgQMaBeLyGrHWIg7lccwlqM4PEyxSSbFcDsQ4iMEAiHg2yeQgWVDSA0LoSMRhg0akWTjsI0RAQURzQCLNMwRqzB2VGoomaqi0bqNsJovJOj4B6JulTYphTiCmK2C0Fgv0WAKDNGWM0EqUQznGKDfA4NXFQ1kJ415iN5C%2BM%2BToEAKQgl42zqE4m1ryYGOprTVQPq/UBqDSGzkEBOZlKybzJIuSy5nVFqUiWrqG3lP9akVIoZA2zVDCW0M%2BbvHK3iI0zW2sjZtJHcbU2W9LbW0YLbe2jtpmYBdm7MQYyuoTPObs0gMy37zLDks5AkdVmCHWfHROyceQ7PTvsy2RyMgnKLuc8IlyhbXKYFXGudcG7VS6s8uGEg3lIwTd3ZNPzjADwBZs4FY8J4Vk4NsWe/dF4WHhXVRFWBoN0u3hi3eRKcUn3JcS4o2QiUEuyEykBqKGgAM/nkWlVH35zE5cAiB1K6OsaY7ilj3L4G8vhhmq1O1hV9puL6/1TZi1wmSjK8NJDeYKq0ULahtD6GUGQTq5N4iLUdTMLprgo0NB2UNYJjBnANFHSVcwpI9jZEBC4UkAIhmOrTUEUkTNQm9qKb6oIkGJmImKu0SsXOmRnCSCAA%3D)

## Links

- [Example](../../../code/facilities/concepts/pagelivore/any_falsify/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/concepts/any_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/any_falsify.test.hpp)
