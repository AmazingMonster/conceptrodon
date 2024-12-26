<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Pop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-pop">To Index</a></p>

## Description

`Typelivore::Pop` accepts a list of elements and pops the last one. The result is stored in `Capsule`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>, E<sub>n</sub>
-> Capsule&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Pop
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias Pop = RESULT;
```

## Examples

We will pop the last element from `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = Pop<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pop` is implemented as a shortcut to `TypicalPop<*>::type`:

```C++
template<typename...Elements>
using Pop = TypicalPop<Elements...>::type;
```

[*Run this snippet on GodBolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADsGqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOt2wqgIrgAYsRZF9DkCdjtbgB1TC3ADudFoty8SluBAQeE%2BVC8DAcOUJqBByNuaApTChzChhIQGLSxA%2BCQAbph0LdDAKucgNkoBWkBgoAHQgqEsNIGKEmQJuAgAT2ezDYKuwIImxC8DnBkJhcMEtxMSSsSXuKqsVzlmAVSswKrVzsVTLdqo1WtYmGlQd19IMCk%2BHkETAiCVIhM1jADQel2HobEECl1%2BoIhuNEOZ6FhsndkZaMeI7tTzsYBBlwcCeobIKtDsut3bhM9rvdfsTbGTFkwwAiDAiwEzTauHbxWSMtwAsp4BSr7rdS9HIhXVYPhwxR0Y69K41X07Xk1nAq2rXbL83fmC3Ew0govPQEQcgfKvcrfQntYH6z1K4DSNAg1yfF96HtO9QTuAAVTU8FEWhlFQNJ3zOJ0XW9Hs/yTQDs1zMCELSJCxFQ9CW2vaDHSuL9u1/f02FuaE8GICYs2AnNQNuEiyJQtD3VY9iCE44FrRBad8THeNnktQJV0fZ9Xx9NwLyvW0aOBOiuxwxi%2BwxYSJjjXt/1uIRMAZdAxJA40%2BOQiihLY4zzMsgRrMncTWyk2dgFkjEV3A5SoNVIzRKbW9HU0yLtMuei9LVPDmLCkykoxCyrNSpiAOlAB5IkEgnIDLls4jEIcwTQucgg4wy9y43y9l2PPTyqKnDtpLnXtJI7QL8zNYt9LM%2BzyMqtxGsKlrsBAEBus86cZvi1lF1oDy3BS1yrPU5toqve8AQO75aTBABJF1qyjRoMKRQ7bsw2i4t0n9Euy5MTxrIqQU6vyKPk1cRoEtJKzTD6psWhMtOOu7EShg4TVYRUMSO/bofu2LzECCJkG8LB5LcBktjSWsxNhvYgsgpGYZ07DntM/DZU80ryZUyGUbJoQvDSYp%2BQAJQ%2BV8wORy5vvMznufQPnILAwKlIp90Ihq24Fb2ONlb2baHr%2BMnJYF66vt824ddoaWFNuRzVQV1XBBVpXrZttWNdirXeI%2BQWqZKlpHGQAB9JhwwSAgIAmdAZoUANfYnNwjcVjmucyXn%2BeN3VlntDhVloTh/F4PwOC0UhUE4NTLGsW4FHWTYArMQIeFIAhNDT1YAGsAkkaUNAADjMMwAE5u64fwO/brgkiSaQM44SReBYCQNFSHO84LjheAUEBUjr3O09IOBYBgRAQHWAg0i8GqKAgNAFToBIogDThVHbgA2ABae/JFuYBkGQW4pGlMxeH5QgSB4BDlwGQggRBiHYFIUB8glBqHrqQXQIDMTECfJwHg6dM7Z3gYvXKx8j5gVQFQW4d8n4vzfh/L%2BrczC3AgB4C%2B9BiCWirlwZYvB15aFWBAJA59SIMPIJQHhl9EjACkGYPgdAoTsUoLEeBsQIitHVGg3gcjmDEHVLlWI2hLLrxrufU8uUGC0EURvUgWBYheGAI%2BWgtAV7cF4FgFghhgDiBMfgEUjg%2BS2LzpgVQllj7bBrgreo8DaB4FiCgtRHgsDwJzHgaedjSB8mILEeOjxHFGFCUYeuqwqAGHHAANXeJiXKWolHQPAeIKB/BBCKBUOoExiD9BOJQNYaw%2Bgwkr0gKsNCjRbGP2DiuUwxdLBmAXkk4gQCPjwFWHYbROQXAMHcJ4ToegwgxkWKMEBxRsgCGmH4LZmQdkMAWCMRIIDZmUgEP0KYyyCjnPqHMq5kxBjrNOXoOYNz8j7NsM8k5VRNkzPLlsCQGCOBZ1IPPXgi9iEP2fq/d%2Bn9v7UIgLgABjCMYsLYdk1Y7ImBYESBAJuIBJCBGlN3QIo8NCSDMJIe%2Bs9/D327voTgk9SDT2rtKe%2BXB77t27kPe%2B/hJD93JffCF2DODL1XrXbJW9d5cP3ng4%2B/Cz6oHoVfG%2BHBWgsB5EkR%2BTBQxOK/t3aUXA25/3wEQCZwDynIUgdIapMC6nwN0GI5BqC7GgvBZC/OnBcGH2PrcQhMLSGv2xoargxrTUaBoXQ3hCQmGBDMKw6VG9OHcNVXGsgp9BEMJQAYIwEauCpBoMbQq0jZHyLUWUlRCiNFaIcGUvRNYDFGPgWYixVibFlIcU4lxec3FzM8fAnxfioRlKCePPOoTwkKKidsPOsT4k1ySSkpQaTe1jhlbkpgBSiklMYGUh1FS7XQNqXAhpIAxH5uMK0yw7TYidMJfnImOQ%2BkDIUkMqwIyxkJCtVMrpPRHl%2BAgK4PZqzFl/KWAckoOQwPQaOZBzZgHLlNGeXB5DjRrkvIqG885aHbnfI%2Bdh4Y/yzmAo2MClhzKwVYJMdCkhcKDVzgjSatuNDUWWoTZilNHCcWYDxaMJ949WXsuNVSpI/hu4j0CNS2lQqxV0YlbYKV7DN7bz3gffByqc3qrYJwLVZCWAKB5J/HkLHXQTHNWioBegj22okPa2QZ76l510MEN1aQlGetowvX1iqCFENUIZ4zpnzPegmDGjNQiE2BGTaptNKAot8OzUl0YJmubezM93b2FmCDeyC/aiRZaIAyJMTWqtCTyvqM0doxtqr9GGOMf2zA5jLFiC7QkntGT532LYoOqZJiR2ijHQkidISwkRPVHOmJEyl28BXak50G6smpr4HkhQhTMDFNKQkuzECHOntgS5nQIBgjXpacMmw07H3dJfQIWxOxg4Xa/RYUZULxmTJuxh%2BZIHFnobWTh0jehtmNHQyDnIiGznfaeQMdDFzMO/NeUDvDsOCPvMR4DqD5GK4guo168VHBiHBZM7cLL0pcvsYtSQLjcXsWkFxfiygoKROXuNYEQI/gB5CtnuzpIPKFO%2BaXsptedPm6SH8GS4eKQO6SD7lwTuZhRXj0CD5qFSn4ugt/gLtXQuNeJMKvMyQQA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/pop.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/pop.test.hpp)
