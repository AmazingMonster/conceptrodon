<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Maximum`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-maximum">To Index</a></p>

## Description

`Varybivore::Maximum` accepts a list of variables and returns the maximum.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (max) V<sub>0</sub>, V<sub>1</sub>, ...,V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Maximum
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Maximum
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
static constexpr auto Maximum_v
{RESULT};
```

## Examples

```C++
static_assert(Maximum<1, 2, 3>::value == 3);
static_assert(Maximum<1.0, 2.5, 3.5>::value == 3.5);
```

## Implementation

We will implement `Maximum` using `std::ranges::max`.

Note that we are not instantiating `std::array` directly. Instead, we let 'Class template argument deduction(CTAD)' decide the correct type for `array`. [Check out this test to see CTAD in action.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r4BwemZjgLhkTEs8YkpdpgO2UIETMQEuT5%2BQbaY9iUMjc0EZdFxCcm2TS1t%2BZ0KE4MRw5WjSQCUtqhexMjsHOYAzBHI3lgA1CZ7bs3ETACe59gmGgCCj0%2Bz6CAgV7cnTGcA7BYuKQTmYTP8ACLnKzPV6zJiOZAAfSYCiULQg70%2BClYmBRCnObiwRwIN1SmAgTDWJyxX2I1zuFwiBBBYL2D3ZK2hrzhBA%2BdIZJ1iAKBADoNKzxSC9uLwVC9jCXs94Yj8eiCJi%2BdjcfjCcTaKTyRBYtTad9GUSNrF6NL7vcuQqOGtaJxArw/BwtKRUJw3NZrDSNltMGczHseKQCJonWsANYgQJmUX/MySAAcacCGiSiY0/jTe30nEkvBYEg0Eo9Xp9HF4ChAEqjnqdpDgsBgiBAGwIqS8LIoEDQLFSdASUVxnFUaf8AFp/JITsBkMgTlJRWZeJh8ERiHgPsD%2BIIRGJ2FIZIJFCp1M3SLpgQB3a6pTg8Z2u93R72cADyfd7BBOVAqBOKdZ3nRdl1XSR1xOCAPGHUdiFDcMVl4JstDWCAkCHEd6DIAccMQkBgCkMw%2BDoAgEnrY1P1iCJmhuF9eDo5hiBub9Ym0OomwjIc2EEb8GFoRibywWIvGAS5aFoetuF4LAWEMYBxFEvBiG4vAADdMFkr1MFUOo%2Bx2CNmW6T9aDwWJrjYjwsE/AhdzLOTSG04hYgyTAIUwRSjAsoxozWKgDGABQADU8Ewe9v3JD0I0PYRRHEM94svNRPzvfQlJQf1LH0Sz60gNZUFSXpZJnd5zghUxLGsMxq1c3csAKiA1lqepnAgVwpj8YEwgWCoqj0IosgEbqhoyEaGCGAbRmBNren6SZPHaPR5oaOZppGRI5rmMadoGTalm21qg22CQ3w4N1SCrXgaxA6c5wXJcVzXMxYNwQgSGQrhUMjAK1gQTAmCwRIWtIeNJBlJI9n%2BSQNEkVN/ArQJ/BSF0OBLUgy3DUV/C4fMkjTfHAkkLhAmh/xrs/Gs6wbP7m0wjssK7P8%2B3IShCLw8c2E4ZoWE0/4Zz%2BI4lNXJJRS4cVN23Eg9z0eLjyS6QUqUNKb10MjHyYZ85Iuq6bq/Dhfx7PtAOAvmBaFk4RaMMWJfFWD4NwhJkLMX70JbZnOYSdnB1QBC8LpfnBZtkiki4CUaANKjKFiWj6LYpjSBYhiOK4hwk74xgCEE4TPzEiSpJkpOFKUlSvXwdT6m03TNwM5AjKT0z0a9CyrIY2ydi9By8CciNXPcpQvJ85SIlABm%2BGCsKIqimKk4VxLT2V2RUuvL0Ncy/zqqsXK2%2BaoqSuyMqKr2KqcosOrboavcdPgVrug0jquuW/JeoYdBDsG4Fht6Pa0gm3on9ZpdB6OtAYf81oCEWvMcoW1Vq7Rfj1cYB1%2BpwJ%2BusTYZ10Ho31tTTgvxiDBytqHO2ksNDvRlkhfYP00L/VIIDYGowwbo0xtjcW8N/jk3%2BP8PYCNJDzmBAbGmtg6Ye0ZvAZm3Z/y%2B29sQbmOw%2BbgRYAoTSK5NJcHFgYSisxpafUavLWQisl7nnkKrNeOgQCFi1jrV8RZLofhvDWY2/4zYEJYEolRaiNGii0TpACcF/bOyoWGPY7sAqtmwoExCMiomB1UakVISJ1FJCRL42YKJCHznItHYg1E443hTonZyhT2KcW4pnf2/Ec5CREhXTA4lJJiGLs5Uuvku7yTUhpGun59KGUok3QQZkbxt2sjcTu9lHJJwHh5YeZcx7hKCkwEK4VIrRUYPPQxi8JDLwvGY9KljN7GHPnlWI%2B9vSHwELJAA9FibetV6oJEarfQqIDH5%2BE6u/P%2BfVYFHXGsUbIf8f7ZCAdtV57U%2BgILyEgyBEKUE/K/sgpaUL4FwsWF/E6mDTx6wcdWfBiiFzKNUScZJPiER%2BIoXo76YSGYAyBiDSgF1WEgDMOLPYexAhZlJhWNl/x8xU0cZwWmjY6EQ3%2BOuThXApBJA4dDLg/w7F7BxbdQV9MMIXQ3Py3FtZVUxhclRbIIBJBAA%3D%3D%3D)$Done$

```C++
template<auto...Variables>
struct Maximum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::max(array);
        }()
    }; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEapAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcYmAJEICBYMOwwPMYIYEK8UJhcOIxCYAE9Ueifv8KQDgb9djcAJIsVL0NiCJgNT4HQE0yn/QHAgiYRkGAV4pheIgAOilADUWngmLF6ApSZdxsQvA4bgBZJiqPAsHzogDsFmhlxuFpus0cyBuaAY40wqlSxBuYqINwAbmIvJgzRdLdCTcDA4GTP4rP47hAliHQxaTMHzfHQ%2BN0CAQC1CUS3QTiUGLLLiPLFe8pRLE3cYVZkynLcRMAR1gwrQR0yBCUZ3hmWLqIFnibHAjWAynKzG4wmjVXh/7K9WyVceVTybdsKpWEy/V9qcud5dgda8MgAPpMBRKVoQHV6g0o2FcUg3MxPwKojPe7x%2BmEzu43QJDiOR6nuel4ENeur6oaD4Sikz4Sv4r4Ie%2BICfr60KBL%2B/4IYBHArLQnD%2BLwfgcFopCoJwbjWNYVprBs36gjwpAEJoeErAA1gEkiwQAHGYZgAJwCVw/gaDxPFcEaRrSARHCSLwLASBoKQkWRFEcLwCggCkLGkXhpBwLAMCICAawEKk4rkJQaCMnQCRRKwWyqDxABsAC0LmSDcwDILaUgSmYvCYPgRDFumj78IIIhiOwUgyIIigqOoemkLoj4AO6EqknA8PhhHEax5GcAA8uKFkEDcqBUDcznuZ53m%2BTc/lmDcEAeLZ9CuhiXBLLwulaCsEBIDZqR2WQFAQCNY0gMAUgvjQtACsQWkQLEhWxBELREjlvAbcwxBEsVsTaJgDg7aQNksgQxUMLQ20pVgsReMAcK0LQWncLwWC9kY4gPXgDYOHgnrdilTqneKWxMREAqyWRtB4LEhIHR4WCFQQxaKZ9pAg8QsQZJgDw/cACNGKxKxUAYwAKNKbzpcVTwkUxkXCKI4hxSziVqIVaX6IYxjUZY%2BiI1pkArKgqQNB9blpj%2BpiWNYZhqbjYXdmL3SnQ0LgMO4ngdHoYQREMlQjI%2BRRZAIUx%2BGbGQWww8zDIkj52JrvQTG0ev5M7dSuwIfStA7JtO7Y7tW3oswB0bCymysCh0ZsEh5RwRGkKpvDqTVrkeV5Pl%2BdxLUQLghAkNCjG9cx5MrAgmBMFgiQxqQnGSIEEoCYE0kaJIZiSC5yn%2BC5An6Jw8mkIpgRcBKLlcC5PECRJLn%2BJIIlty5qeFepmnaRXemDcZQ2mWVlkTVNnUOWwnAtCwnpGm5TB2gYRhNQJEoT2RwXF2Fegs9F7PSJzSjcxSroF8mUmDZU%2BknFOaciocFKuZcUlVqq1WzvffmT8X6wVau1UanVS6BDMOXfq%2Bl94nwSFZSaqAOojAhPzLgwkUgLSWitNaKU9pbXOmwg6R0TpnWxpdRg11br3TIo9Z6r13rnW%2BvzP6IiAauxBh9N%2BqgIYCnOjDOohUEZIy2qjLYZEMb6nOrjfGSgibSIiKAHefAqY0zpgzRg51v5s1in/WQXNkpkWAXzMm8srBCy0aLBuEspacBlm2OWgsLBK3TirPAWBAmxx9kDZwEBXBh0fIbcojs9DmwaOktItsGiB0WN7HoftQ6e2thrZJjR3bFNNiHfo%2BSI4DCjtknqqx1gJw6bJKB69OCZzql5Ghj86EYI0K1IuoU8E9T6pXUg1da4jAbrJEeY9n6dyNP4ASUlAhdx7kvNeKUN62C3kQ3e8B95mXKuQ0hxAz5bEvvVFgChPS2k9GM4U7wCBBRCoicK8VWYxQkK4hKACPE6CSKQUB4DcpD2TgVY5JVD4VSqjVZ5rz3mfLZN8rBlCcEJDwQBOZViSH4rGrc8lnVULIFSKkE8HyBIni%2BeME8qhPJ8DoEwygLCyKcPukxfl3DNbnX4YIG6d1CqiJemICR2MpG/T0V9ORQMFGFXBsgSGajBAaJSlo5GRJdHo0xkYhIJjCaCnMWTKxlMmDU1ppgemjNHGyB/i4wF7ieZQofgLBW/iRbwHFpLbIH1thphQJE6J5FYnxMDdUrWqSdb5MycbEpBTijZHybk7I9Tg4uxqf7D2eQqn5oaIW3N4cKnFsrXMNpQdE6dPog23piK1IDPZV5F5byvTYoFOMSZfyuplxJQNKuNc66UCTmskAgkJSBECP4USS9lLzqNDPI5baNKnJ0vMpu/hW6SSNMpHikhhJcD4mYVeslAitvTpwEdbF4WBQ3Xerd5yVi40yM4SQQA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/maximum/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/maximum.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/maximum.test.hpp)
