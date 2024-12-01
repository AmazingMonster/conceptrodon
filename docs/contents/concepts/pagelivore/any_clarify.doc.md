<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AnyClarify`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::AnyClarify` accepts a class template predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...||Predicate&lt;Variables&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AnyClarify = REQUIREMENT;
```

## Examples

`AnyClarify` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0<*>::value)` and `(...||Pred_0<*>::value) && (...||Pred_1<*>::value)` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<auto...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BXKQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRAB01yfYJhoAgjPEXg4A1MrEmOgA%2Bhr3DxMAHYrI83uC3jMmI5kG80AwZphVMliG8YqhPG8AG5iLyYN7AiwEF6YYEAEROoMBQIpxypAN2%2B0OpNO5yuN2Od0ez1eBA%2BX1%2BXABhIBEMhjRhcIEiORqPRmJx3nxhOJePJlOFNI1jwZewO0JZZwuqGulwexGACluAK%2BAEcvHgvgo3hBTcC3O7Pt8/ic3ObLbcQCBFXjlgD4TKUWiMbQ3lQvAwIGGQV8CBsGHGxEoNVqdY9Gfqjqzjab/VbOTbMPbHZhna6bkCPY2vb9/qcy4Hg7jMMsCWYAGzmfsut2Nz0Cn5C9sW8vYIMhnvh6W7WXRzHxxPJiyp9NvVUsqy5wHciV4ZA/JgKJTNagJ31T7BJsN0jirWicAK8PwcLSkVCcD1LGsSF1k2ZUzGOHhSAITRX1WABrEAAn7S4AA5%2BykAIgX7SQAE5jmwiD9E4SReBYCQNA0Uhv1/f8OF4BQQComCf1fUg4FgGBEBAdYCGSC5yEoNB9joeJIlYbZVHQgBaHC3mAZBYSkS4zF4b5CBIPB0D0fhBBEMR2CkGRBEUFR1FY0hdCSAB3YgmGSTgeDfD8v1gv9OAAeQufi%2BVQKg3ik/tZMkeTFLeZSzBdDwRPoVFzEg5ZeBYrRVggJBhOSUSyAoCAMqykBgCkMw%2BDoXZiEYiAYjcmJwiaABPRzeBq5hiDqjyYm0WoWKg4S2EEDyGFoBqLKwGIvGAM5aFoRjuF4LAWEMYBxBGms6ixWs3KRWoLm2KDwl2d8LNoPAYjs1qPCwNziTwcjZtIdbiHRJQyT2RbjqMWDVioAxLQANTwTBrI85JGEa4zhFEcQjN0%2BQlDUNyrP0RaUGsax9BOxjIFWVBkh6GbpJmdATjJUwgMsMxaIe4gtI2rHOm6TIXAYdxPDaPRQnmMoKj0AoMgESY/CSXmekGLmRmqLouvqWYBb0Go6gEPpmlF4YEmqGXWdydX%2BhVxY1dWBRQK2CRnI4T9qLcuiApkuSFKUyQVJdXANLiiCuES6DPtWBBMCYLAEiTUhEMkY5LnwoFJA0SQzEkftKOQ3DiI4UjSHIyDLgw/tUNw1CuH7AJJC4AJ8P7C2LLohimM91jUq4tKeO8gScry2LxLYTgmhYLEgWkpg4QMIxwtwy4uEuX91KIantKSGH9Kh6QYdM%2BGLN0YrbPsxrTfNmjeDory%2BIuN4/LeTvu97/vFqHkex6i1AYviPtjjMD3krY%2BuW/iQTcrvzLYpAU%2Be7IAHoVXCXAqI0FoGVCqVULLNXqmDOBrV2qdQcGDXqjACADSGm5Ua41JrTTBvNN62xfz4C%2BGtDaFktrIB2mDfaXQ3LHVOvVC6JCkrU1ulBB6T1MAvQWkYd6oAa58B%2Bgof6gNgagzurPSGhkF6yCXuZX8q8kYfVJlYSw6MYiY0DjjPGnACYECJscEmqNyaU3iFPWmgd5Y9CZizHIgtgjM11tzIWaQ%2BZZE1k44WmRXHi3plLRWGtHFy0lgrXosx/FqzGP0WW2tlac1VibNYGxjbuyTtvS2nAT7EC7j3PuQDL5cGHqPDQTt8CT0fu7JKXtSA%2Bz9iMQOh0U5p2HlHIExcgRAmONHWOhcy60U4JXZin12J1yQLxHyX8P7EDbtsTuckWAKCxLCLEJTLjMhmGpSpmlp7gznnI8GiiEYgGOKQdeDlZpb1cuXTyjdfL%2BUWSFZZqzsQbK2XyCA0Vf4P3iscF%2BYz34/yyjMkFf9VnJGSD8dZuEfifIvHknCJVIHxGgdVWqrUEGYrah1LqaC759UwYNYapDMBjQmmIAhd0iECLYaQMhUt1ozXHqobauw6GCAYUdE6Z06qsKuhwsG3C0i8NegI8IQiUoiKYH9AGQMQbfigjIgyEh5EmThkonQZzVHGDMTYJhOjsa40yDNAA9ITFGZMLAU13lTGmRrAkRPsfE5x6Bok8w8T0V1vjihJL1mEhmwS4neMDUEyJOt/VuNiRMUNCS5ilGSRkw2aTDI3MGbvHJzy3ivLWR8g0MwKku2qYCmu3tfb%2B0oKbVp/hh7HGOAEAIUcwEaHrdhVCGb3L0VsFXV%2BywEIgBDiPY4qEC4QSbf2CC2Ek7HFuUM7tfbTaqU7RXauKVVgPXSM4SQQA%3D)

By turning `(...||Pred_0<*>::value)` and `(...||Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AnyClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyClarify<Pred_0, Args...> && AnyClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AnyClarify = (...||Predicate<Variables>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbrv7h5gnbkxeRAB0jyfYANTIBgoKL8rEmPiiu1IL1uD0eADUmngmLF6ApniYNABBNAMLYpAgvREMACebgMxDwVGxLxOABEXhBHvcTIE3DS3D8/ngAVdThCCdDYc8QCAAG5iLyYZYnKxIhGIgD0ACoZbK5fKJeLpbKXgAVTAzL5yxVI5Xy/UynWI8XnA5MI6nEGoKnwpEzYheBzfX7oAD6GnFNNFiJevpeM3NzLeAhmmFUKWIL1iqE8L353kwJMCFgIDqugVJIs9GazYqRpsu1ytNuO2HF9sdGMZbq42e9fv9jUcyGDDFD4cj0dj8cFSZTaZpmeO3sHueN%2Bb2ZotNzu1seiOIwDhpfFvwAjl48L8vljcfjCdjrtX3UCF0uS2WkSj2xGozHaC8qF4GBBhcnfgQNgxH2IlFmc3miIFuarIzqC9xnsul4LpgG5bhqmI4nikJEkeLonpii4KBeJJmAAbOYeGIXuKGHqcx5cKeWEXuK167B2d6xk%2BL5vhYH5fi8qaCv%2BmaAQGzaukwnwJAQ1DPtctalq%2BwrDhwqy0Jw/i8H4HBaKQqCcHSljWP66ybIm5jHDwpAEJocmrAA1gEkj3BokhcIExwaP4Gj4XhZgABwefonCSLwLASBoGikCpakaRwvAKCAwWmapcmkHAsAwIgIDrAQKR3OQlBoPsdAJFErDbKoHl4QAtHhkgvMAyAtlI9xmLwTJEAS6B6PwggiGI7BSDIgiKCo6hxaQuiUQA7sQTApJwPDyYpylmepnAAPJ3BlGKoFQLzFWVFVVTVLx1WYFIeLl9CRoZXDLLwsVaKsEBIDlKR5WQFAQI9z0gMAUjJDQtC7MQUUQLEC2xBETTYtNvCg8wxDYktsTaLUsXGTlbCCEtDC0BDQ1YLEXjADctC0FF3C8FgLCGMA4g4/BdS8hqC1hrUdzbMZES7ApQ20HgsQTbDHhYAtqZ4AFpOkPTxDRkopJ7JT3NGGZqxUAYS5gngmCjUtKSMJDvXCKI4g9e18hKGoC0jfolMoNY1j6DzUWQKsqDolkJOlTM6BkqY2mWGYYUSy1DOO503RZC4DDuJ4bR6GE8zlJUeiFJkAiTH4lFJz0gzxyMlE1HUAh9BMUd5LnXRI/UsxZ8MiS57Mqd6AGzRV4sNerAoelbBIs0cEpIULeFW0leVlXVbVNlHRAuCECQuFGVdJmK6sCCYEwWCJK%2BpBWZIxz3AAnMcgSSHZZiSHhQX%2BHhu8%2BRwfmkAFRn3HhXB4R5u8ec//j2f4%2B94X3Q3hZFaKC84p3WSvdVKq1MqvXemdAqbBOBNBYLyQIpUmBvAMEYA6u97hcFso1fAzU8CtUosbTqhtpDG36mbIauhkjjUmpDbuvdQq8HCitdKdwXgbWBMQJBKC0HvEplgnBtljqoFOgkWeKxrqKwSg9cRT0zpZTegoj6iDkGlUEUYLgu8uDBV%2Bv9QGwMhrQ3BrrUxsN4aIwcLrVGjACAYyxgtXG%2BNCbE11uTOW2w1L4F%2BHTBmQ0mbIBZrrdmXQFrc15uDAW3jroElFsZCWUtMAywpkYeWoAQF8BVgoNWGstY6zFqQg23UKGyCoYNNStDLYK29lYSwdtYgOw3s7HobsPZextr7f2CRA7NLbmXfOfgICuHrpRWOZRq6J3SMnbIxc06pBmZnOOUzS6hwLnXeZDdBk9ELnMSZLcG6bNyAsxu%2ByFgJ0umsDYncrmc2Yf3TgPC%2BGoPQUInRIiNAUins1Wel0ZEgKXivNelBu633vtguygRv6BEcpIE%2BFVKIsMWhFWwQCbrxUSilNKa1lEwPyoVBBvDdosAULyFsvIPmXBmPg6eLU2qyDIaUvWFTzYgGOKQehU1SZMPmv/ZakD1qbUQSSslFKqUgRmGIiR50zDHGOPPDFd15Eyrxaos6fJkApBSK6Slu9XTUoIIJYlFC6CGMoMYtSFjsbGWtVYpGtjxFowcZjbGPjMB4wJmIdxYtPHpNiaQXx5d6YkzUkEkJYswmczUpEvmuIMABuFgk3gST0gpNlukiImTbrZKYKrdWmttYqWMsUrqEgyl9VNpUnQ7KanGC6TYSJ/T1IuxDJwCUHtrY%2BwsH7VhAciFBw3nnHo4dI4nJjhHZulzFlFCyGMmdsyp05xDuXDZ/R53Dorv0JdNcxjrq2bXbdKzDlXPbjc7qvK/5hSeSKyqpLyVxglbsKVk8CEzwuoqxepBl6rxGBvTm4KkjYPlf4Fy9kgrysCC/K9rDOCAJil%2Bre/g97%2BA8vhXekhd6OQPlwDlnNjh8uvaipV3cGowZRQC26qwJYZGcJIIAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/any_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/any_clarify.test.hpp)
