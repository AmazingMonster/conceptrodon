<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::MakeSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-make-set">To Index</a></p>

## Description

`Varybivore::MakeSet` accepts a list of variables and returns a set that:

- contains every variable in the list;
- doesn't contain repetitive variables;
- preserves the relative order of the list.

The result will be stored in a `Shuttle`.

<pre><code>   Args...
-> Shuttle&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
MakeSet
 :: template<auto...>
```

## Structure

```C++
template<auto...>
alias MakeSet = Result;
```

## Examples

We will turn `0, 1, 2, 2` into a set.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, 1, 2>;

/**** Result ****/
using Result = MakeSet<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Varybivore::TypicalDiversity`:

```C++
template<auto...Variables>
using MakeSet = TypicalDiversity<>
::ProtoPage<Variables...>
::type;
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADs0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcBAAnk8APoEYhMQgKGHYYHA367G5CBBeAgEeifA6AgiYFipAxUmFuJjE1AAOjZWOB42IXgcBKJJPoMKsl1xhxuADUmPDyftKdTaUx6bCmUQJS08ExYoLAtjLlyeQQ1fCcUkLDdZo5kDc0AxxphVKliDcVagbgA3MReTDQ02S4garWYExJO5Cn2hwLCoE/MUAFUReFEtDueDdCUI0q%2BwKpNLpQeVzLZLIAkrang5MOg/QH6JidZzUQabvHUomxCm08RivCQDdUl4tYmjQzSwpy1Sq%2BrNbWsUWTVHttsbgAlTDIdaZNM3RlKEDAm4Hm45hVKxnMm6j8cRYDV6eYUjOwts1fjW%2BBuu6i6H82N3nKYioEQyhMMAQaXN%2BwZRt%2B35eJkRhHoi3owncP7oCAKACPgDRiPu0EHgyuF4d%2B4xoSAeAKEisRMEoSKoFQDKSsasKXmujhGG%2B2rYA%2BLZtsmqYJN2WLoR63j3tC4FEd%2BPFJh2AkZg%2BhGSc2CYyfxXYZiOZasZWHHvEWD4sQ4166RyEl4UJIAIk86HHnmNz/oBqDAaBDIvgQukKHOOo2YhQqKcGEZRriS4WNR3o7uwim2Yq%2BZnqqhlsTeU6BqZX6Hvqf4AUBIGxQlxnJZx/mmopMFwcACFPNCgQoSR6E2lh2Q4WZ0EEc1km1WRFFUTRdEMVKmljqx%2BX%2BneWLcSp7ZqYJ3kgCJXoKW1RGEsSpK5VpFaTiN75eVx4lpUpfIrdqbgJTpBV6WyBnrYlJn1ot%2BEzVZ%2BZQYeAV%2BSKzXRaeLpFh5qWlde9k5VVKEOdlLmwh5O3vUCIYw6K/yI1mMa3MWubUowzQNDKpwI0jSOAtm8p5gyP1sn9d0XLBgMALJMAA1pgQiYIayHKa2qmdtNbipehYNOTlfVbbW0OXD5Tzwyj%2BMUnj%2BLYKorC0t6yNXNLKs4qC4KQkhsI2psqQEB%2BOJS/iy0CsrMuXF9sVkyyqUZYaZurZLqu3EIXipEUlYvl4tCGir1Pwe7nsZN77y%2B6z1WHebDIaA%2BXAPmYHKRsbrv7Cu4d%2BzjgKB%2BVPtZ2zdOM8zBCx/HieJ8nQUm827z%2B5bFwWomSLUUorQQB1CisJgLd1m4%2BcEA%2Bwde%2BgA9YksQocCstCcP4vB%2BBwWikKgnA85Y1jmmsGxIaCPCkAQmhTys9MBJILIaAAHGYZgAJw31w/iXxfXBJDUM8cJIvAsBIGhxwvS8rw4LwBQIA44H0XlPUgcBYAwEQCANYBB%2ByDwoBANANI6AJCiN3TgqgL4ADYAC0eDJA3GAMgK0UgWRmF4JWQgJA8BoQTvwQQIgxDsCkDIQQigVDqAgaQXQCcADuaJUicB4NPWe89D7L04AAeWJEgm4dEbi4MIcQ0h5CbiULMDcCAHh0H0CdOYQIXAli8HAVoFYEAkBoNbIY8glBbEYMSMAKQZg%2BB0CpF2SgsRpGxAiC0Hs3BeD%2BOYMQeEsjYjaFYmI3gaC2CCFkQwWgQSl5YFiF4YAjJaC0BAcE0gWAWCGGAOIPh%2BBiBDTTHkpe9o1zEi2HvCIVJ35L1oHgWIaJwkeCwNI1EeBv75M7LEUODwilGDaUYQ%2BKwqAGGAAocUbxBGyKeAvPezDhBJnYdIdZ3C1DSIEfoYpKBrDWH0O0kBkAVioANtkPJBCSLIVMOvSwZgAGdn9FgC5EAVh2CGs4CArgph%2BATmECIQxKgjATkULIAggV6GhQ0eYwxEgJ1%2BUZAQfRJieA6HoNFDRMUDDBQsSFtgJhtGxfkVFZKkUQpRT8remwJASI4HPUg/9eCAJUfgohJCyEULPjoiAuA6FGN3mY/eUyVgIEwEwLAiRvmkBPpIQILIb6BBSBoSQZhJB4N/v4PBN99CcE/qQb%2BJiWR4K4Hgi%2BN9n54P8JIB%2Baq8FsukYA4BoCJUQKsbA6x8CFHEgcag1ABjMHYI4C0FgbokgEKYNaAw8EuA3xZFwc%2BNCsL0MYZwjZbCJDbNkLs3hS9dDuOEUwURwTmWsvZTIjg8jEHEiUVQLlaiSEQmKVo5NqaNC6P0XYhI0JQRmHFRYyBfqnH2JQROkY7ajBJq4HHGgfsBI%2BL8QE8JsTSChMCZE6JDhN3xMxkklJ0j0mZOybkzdhTimlLSXgCpRkqnSNqeuKkm6ml1GkW0jpgTulbCXn0gZe8hkjOpDe68Uy%2BCzPmYs5ZjBN3rNYeIDhOylB7L4SWw5kynlWEsGc2IXyrk3IEHch51UcPWFeRy95DD3jwB%2BXUP5fgAUMHcBS4FIRWM0sWFCjIMKcjsfhXxxFRLkW4sY%2BixoZK4Wook/i6lonaW4uk4JqlcxFM8fpesRlpijUsqkXwzlqieXxo7UmlN59dHCqIKKkxI7JWkGlbKkYCr34mrNcmzVSR/A31foELVOrHWusM5wD1YDIPQLgQgpBQbp3ECwWwTgkb1EsAUG6K0bpzN5nGOmkVDC9CIc2Xm7Nhb9kgGCGWit4i9PVrdXIgNhplGqBS2ljLWWYrjF7SG/ttnAj2e9VAmx3XnGxeG4Y2ayBPZIkyzfJE2WCBIma9szxK6IC%2BL4dujd%2BTNsRKiTE/Jh7EnJNSbwM9WSxCXvyde8Z/7Tv3sqXRvhL76nvsEJ%2Bvh37Onwj/b0/0QHeAgaUKM8DkyBszJAjBzASyVkIdkEhrZJW0NFp0OVrDxgTl4e/YR5exHbScG2LVCjLy3kJA%2BXRy53QmMuFYzJzj6BuMkoRdkWnTPSgaZJXi3oKm8gcc5xihT5QxNqaxTz5T6nBdKd0woBl7Cq0GYAZwFRLX0vuna1STrQqM22dMeYhzTm5WUGZe5kAt8WSBECP4R%2Bjrf7m6SNa4LCugG2E9aOpYx8QCSH8Kql%2BSRf4X0kPfLgV8zAuvfoEeXHLQtesscy6hDvI9O9dysLm2QPdAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/make_set/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/varybivore/make_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/make_set.test.hpp)
