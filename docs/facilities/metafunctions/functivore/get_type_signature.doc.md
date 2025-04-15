<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_type_signature">To Index</a></p>

## Description

`Functivore::GetTypeSignature` accepts a function-like type and returns its type signature.

## Type Signature

```Haskell
GetTypeSignature
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetTypeSignature = RESULT;
```

## Examples

We will extract the type signature from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);

/**** Tests ****/
static_assert(std::same_as<GetTypeSignature<decltype(fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<AbominableFun>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<decltype(FunAddr)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<decltype(&Tester::fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<FO>, SupposedTypeSignature>);
```

## Implementation

The implementation of `GetTypeSignature` relies on the metafunction `TypicalGetTypeSignature`, which is implemented by dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename...Args>
using GetTypeSignature = TypicalGetTypeSignature<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8dnuwuJ2YtAAngAvaKvHa/AiYFhJAxwi4mADMbgIoLuzDYaOw/2GxC8DiBIIh0WUxFQRExdxRAHYrPSrmirKd/nCEUjMCj0bTGKweQAlTAEUgXfk4zAAOllJ2IwAUeIJBCJJOBYnJxEp1OpWMwaLcIoIEHlitl0rmyvZjP%2BF3tFy8aSMEv1AH00sBmARljy0VcLsbTQqFBarai2X9maz/hz4YimMjDZLBYHReKU2wLWalaj8adCcSCKTNZDtVSafrDUGc2GLmgGMNrVHIw7Hc7gK67h68F7E77eQGayGwzGbSyI7HTpyE3Dk/qpRcAGIMZuF9VkssgC5JLwRWh4ZAlsFlnWVu6Gld4hlMieRuNcxMGvkL1NXvMqtXFjUn6KXhibM2267vuh7HlqZ56he6LvtgN4mNGk7stO8bcvO2KpgAsvCK4Zq%2BbAXHUX6%2BmuqpFuBZaGthLAroRZEOL6IAgIBH6nMBe4HkeP4QRWUHPm41GwfBiH3ihj5zi%2BGEEUuADyzbEJgACOXh4ApLwKcpqnPPBZgAGyyUxqB3MQiYkBA4a3p%2B5HcZRMFyaxJzsaBXGbn%2B6JYMgtD8hA5j6TJhnGaZxDmeGcEIZZSF/B8gIACpYoeYgAOKinFdxCL23oDm8D6zvxmY8rBVkkqlCW0MlBCpZg6V9j6Cmxoy7bBJ2/KDhRbluLBTH8j2NUkZOIlTgC3zDdl0WXAAkly8KMPUNTQtsvyfCNw2/DlaGSQKWZyiGzZOk1FzlZV1WZQprUlaIZUpfqx39nV6K1rKeJdVWkX/Ety2HG9gLYKorCIjyo1DR9C2DeYqLBJ5XhYLybgNqsSQELm%2BZRUDmwXFQXgMA4GQvIDwQHiEFzBMWGMMBAxPisTmxWg1Cm1QwFwaKyDIsshqMXEwESoCwwSc/Q6OY9jAi4zC/x7S6JxczzzD7pgS6Y61xPk4IlOCNT9bCwQY4o0tAtY3NKTE9EIsg6c%2BPBDyTBeEQy6Yyc6DoMQN4onppMs9rX2XIbghQjbbClFCpNC4282fQW9HFjFzxwsQ9Wtg65uE8TevK2KRNq3MGuNsW4UXHTywM0zEbu%2BOHtjdsevBxcqARNomAOCbYcnOuxayXHdoJ4I1eBUQwVzKnqsEOrDbDM7%2BfEIXzMIazUZ3oNutCF4SR5Jg6BHRlt0A6Lpzi52i/L6kq/r71p3%2BunJoU%2Bf1Nl%2BzUfDI3vyTI4yBukwChKI0EDDOgTEKIKr%2B5jcIda6G9ar8Q8l5fU1BMahXFPvFea8QEn2fNgCyKpEyHgAR/E039f7/zfoaYBaVQF9TcJLbmvNZby1XHmOBS8EHHxOigtB4cMEvzftgr%2BBAf4gD/mwABhCrrEOQYaCB3lqH20drAwi9DD6IOEUwvELDm6zUwRw6IODuF4P4QQ9ERCqokLum4MRUDfJ3xjkxUm0j4FyMYZvJR2sn5qPfhorhPC%2BGYAEXooRBiRF2TxHQg%2BSh5G%2BMUXmZRHAFi0E4PEXgfgOBaFIKgTgbhrDWAuAoJYKw/RmFRDwUgBBNCRIWAAaxAPEVE0p6TxHiPSLg8QzBcFiLELgXAzDSGiRwSQvAWASA0BoUg8TEnJI4LwBQIABmFISZE0gcBYAwEQCAJYBBdxigoBANACI6DRFCIKTgqhYi6QALS6UkBcYAyAjxSGlGYXgq9CAkDwD/No/BBAiDEOwKQMhBCKBUOoaZpBdBtAAO4mSSJwHgUSYlxKKUkzgMlrarOrlQC4BzjmnPOZci41yzAXAgB4LZ9AnZgy4HMXgUytALAgEgTZSRtlkHWbS%2BlIBgBSDMHwOgMdxkQAiLCiIvNiCgghbwflzBBUyVrvXKZ%2BTNlsEEDJBgYJYVYAiF4YAbgxC0HGdwXgWAWCGGAOIAF%2BAFLYwAG7PFhZgVQ9drZrHyUbTpiSDwRBMoKjwWBYWqjwL0nVpALXEC5koG4%2BqjAE1ANMhYVADCKgAGpPGBTJbEwrvnCAup86Qrz5BKDULCoF%2BgDUoDSZYfQeAIjjMgAsIyNRtVHO/v6UwlhrBmGGQG4gTzLWVvaFKjILgGDuE8C0fw/bpj9BiG0PI6QBBjFaMkVIU6GCjoDuO7twcuijEHeMVdNR109AtjMAYEwRhNE3bOyYjQl2zFJYsZYqwJBQo4LEwZsKRmosOScs5FyrmSBuXi3ADziW5NJeSopcwFgIEwEwLAMRzKkDKZISpABOVE9JJAaEkO03S/T4i6UQ/oTg3TSC9LydKXSXBdKxEQy03S8RJD1OQ7pZ9AKRljImQU0DsyFnUqWYi625BKBMqJbstgnAGgsDNfSI5TB6wGBdFwRD0ouDSkSfc3uTy9BZveeIL5Wbfm5oBbodloKmDgp1Q%2Bp9QzeAjIRSs62yK33orOZ5A12KFNKY0HigldKiUu1RGYMl7HI2zJpdzbz0R%2BMbNC8y5zRh5NcAGTQLyxtKC8oBaKhoQq/XpfFZKhwKbZUzQVUq41mBVXqs1dq/JeqDVGsSSantFrtUqZtcgO1KbHWwpdW60EHq1iJO9b6/JAag2YBDTVpqHHo1MDjQmpNjAU2afTRITNsg9P/MSYZgtRgi1NpLS6itsHq0404HW7hDbi0WBbVZttHaDsLDsD25wEBXAzuHegS9h6535AyK9id86agfZXQ9tdx7fvbs6MewHehz0nuyGeyH%2B6x33pvdk5HnSLMvs4A5j9MmXPycU8pv9%2BBe6%2BeA4Fyl4HIPQcoA%2BwjxGFPoeqYh%2Bk9JUQYckKctolm4WjNsGxilMy5mLOWasiLgmdl7I4GJjFLAFBmqPGa/H3Jhh3OJ4855qatMZtTWtvNIBUSkGM6ZyF%2BHH0wuY/C3jxZUAotUDLuXCuldPlHviqLPmwaogCwLqlIXCXhcZW7gY8vl5ukV4ht0yuCBujt5mzlyWeV8oFZl/J2XQQSrrnlv1BX5WKsy3V0raqNW0C1Sm6rYa%2Bu6q0uay1ALrW2rhO1n2TreBdYy71r17bBu8GG4fMbYaJtBamzNzAibk1%2BsWx85bOuc3rZ0PrrbxgLulvLfAKtCNjsbFwY2qwlgrtJJu1gO74OnsvdPW9qHf3vvTrP5fhdF/j%2B1FBzfh/u778w7BzDi/92sl3uvej83wyWOMeFwsu8uFwYe0okeROAGpOXuoGlOUGAwsGnSdOIAZgCmqIqINS6G8WGgmB9IFGTGgBvO4yky8BcGIAHONykgGGsQkg9ILSTSsQBBpuqIABVmnAIGkaD6tyRBHBvO3uCwAaaQzgkgQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_type_signature.test.hpp)
