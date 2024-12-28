<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsUnequal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-unequal">To Index</a></p>

## Description

`Varybivore::IsUnequal` accepts a target and a list of variables.
It returns true if all variables are unequal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

## Type Signature

```Haskell
IsUnequal
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsUnequal
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsUnequal_v
{RESULT};
```

## Examples

```C++
static_assert(! IsUnequal<1, 1.0, 2, 3>::value);
static_assert(IsUnequal<1, 2, 2, 3>::value);
```

## Implementation

We will implement `IsUnequal` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsUnequal
{
    static constexpr auto value
    { (...&&(Target < Variables || Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsUnequal_v
{ (...&&(Target < Variables || Variables < Target)) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCspK4AMngMmAByPgBGmMQgZlykAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3EwvERrgAVZrATAEUjXGFEAB02IAas08EwYvQFJDsICxsQvA47go5BEAI5eMSAkwAdisF2uXOuM0cyGuaAYY0wqhSxHRsNQ1wAbmIvJhAdzrmyLNcINjMeYAGzaiCI4jIgjKqHXPHEAlEzAKZWstxstym/GE4nGh36w2LRY2gAikI5ANZvoh/sBwNBrwVUIxUvdKLR0Y1ZotxNJgMFwtF4piqE8NLpmEZYgA%2BtKWey1RrtbrY0bIQ6k86rTa7bbHebG9a6wikSjPT6/Syvr8fv9vjtrthVKxHph3idAWPh/OLuSmnyi0wFEoWhAwGA8wymbQ68lrlxMRo0WY0RDSSAQLLvJhFgOLry8MgN1v4gQILdaYezJQqe17XKBt4Qtg96PvKL7Bhwyy0JwAS8H4HBaKQqCcHaljWDyqzrLO5gQjwpAEJoCHLAA1iAASSBeAAcZhmAAnCxXABBoDEMVwrKstISEcJIvAsBIGiXmhGFYRwvAKCAl7kehCGkHAsAwIgICrAQKSwuQlBoA8dDxJErCbKoDFagAtFqkjXMAyD8lImJmLwmD4EQ5roHo/CCCIYjsFIMiCIoKjqEppC6MkADuxBMCknA8IhyGoRRmGcAA8rCOlGqgVDXOZVk2XZDlnvRZhqh4hn0OKxFcIsvCKVoywQEgBkpEZZAUBAbUdSAwBSNeNC0MCxByRAMSpTE4TNAAnglvBTcwxAzelMTaJgDjzaQBnPAQ6UMLQc3hVgMReMA0K0LQcncLwWAsIYwDiMdeDEBtjjSlaqUihtsKbKR4TAoJGG0HgMSxctHhYKlBDmqJN2kB9xDZko3ogg9INGBRyxUAYwAKDieCYFF6UpIwW0%2BcIojiIFFMhWoqWRfoD0oNY1j6KDcmQMsqApPU12WWM6CQt6pi4ZYZhSYjnmfVzXRvVkLgMO4njtHooThIMFTDMkhSZAIkx%2BDr6R6wwcxDAkoy1PLAi9BMKt5Jb3Q2%2BM/Qa/M2u2C7Bt6DMLRm1rFvLAoBEbBISUcChpCSbw0n5RZ1m2fZjllWquCECQypmCR9VkVjywIJgTBYAkEDUf4EKYixEL8RokhmJIWriQEWosfonDCaQokkZiWpcFqDEsTxWp0RxVdalHqXSbJ8m50pzXqS1mlZbpXU9dVJlsJwzQsNKrKWUwAoGEYZ4sZi54YW56eed5sh%2BdT0i00o9Phbo14xXF83h5H0dpRwmXabCa4uU46FVssgI%2BwAT5nwvBVVAVV4iZwhGYHOjVlKLzXvEPS3U4HtWqigCBXB2KXiGiNMaE1wqLVmltShy1VrrU2vDHajA9oHSOhhE6Z0LpXS2nddGmx2EvXlh9a6F9VA/WBFtAGtRUogzBrNSG/CGqwy2ojZGmBUb3SMBjUAc8%2BC43xoTYmpM0KkQpnfAKD9ZB0zChhV%2BTNMaiysJYdmMROal0wrzLI/NBbC0cdYCWMcpZ4CwG4oOVsHAKwgK4b2yR1ZlHNnoXW9QYmpGNvUf2CxHbWwaF7e2hs5YROdrMN2CTRi5NyPk32rt4kBzDisNYoc6ptwjilcKscCoJ0Pg9KB59U7uQzrVFBedSAFyLsMdxgkO5d1PrXVkAQWJ8QhHXBukhkg/ynrYGeqD57wEXlpbKWCMHEA3psbeRUWAKGlPyaUhDMRgitAQVy/Tr7JDMVTCxQV5BPxsToEAEJSDv3ijdL%2BrSpIZWXjlPKqhzmXOubc%2B5YxYHwJqlnCEQzdHoJwR1Q5WK8FXJSCkEshCiwIoIEWaFD86CkMoOQjCNCjqkXpXQt6W0mGCH2odVKHDzpiG4fDXhWjFGkHwK9CJwivpiOQL9SRghpHhVkeDGaCjobKPhqo9I6i0ZaPCDopqeimB4wJkTEmZN4ZvP8hISxwVvkMz%2BfY4wrNnGyNCR4vmnAtiCxZmLCwATMJBJCfAMJTs/BRKVikuJmtMmpKKFkFJSSsgZI9nYbJttWh5J9uE%2BoqbE0W09n0FJVSc11ODg0gKIKJ5tM4PlGFVyZTwojIiiAacPKILqg1YZozi6UHDlMxIp8IQQgCJxVZ4kB2sn7hWsFMlNkKWGTRQIldeKsnEgxSQ7EuBMTMOPQSEJQUx04O2ue4cXKTv3dO7ZyxEYZGcJIIAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_unequal/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_unequal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_unequal.test.hpp)
