<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-among">To Index</a></p>

## Description

`Varybivore::Among` accepts a list of variables and returns a function.
When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Among
 :: typename...
 -> auto...
 -> auto
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto>
    alias Page
    {
        static constexpr auto value 
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Among<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the variable at the index is returned. Otherwise:
  1. Drop several variables from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQBAOykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgAzOFkN4sHcTOC3MhZugsFR4dhQaD/oCcYdgdi7gBJFgpehsQRMXrfI743F086Y64ETAkgzM%2BFuJheIgAOj5ADVmngmDF6Ap0aDZsQvA47lcWAJgHDElZEg94VZrqDmazKZgOVyiHcAGJ4YizCXXKUyghyhVGDmm80ES0glWgu6eu460l6jkZABemAA%2BrbCa6vXdrbLlMRUERlExgJhlar1eDNSDrpGfWz9QjAyGwxGvcRMABHLxmz53CDh8Hph4aFYer3R22x%2BOoRPJjn1jHZr0mFVRpqOZB3NAMWaYVQpYh3Q2oO4ANzEXhTw4sTotao1yvTmdbntzfoRS75PKuwDLLMYBHF4IHV0jXgyRjuPc3Dc/cYTSfzNxr1vckH0vCUM0xPdIK1JkWV9dlz25ZcdwIUhF2Qu4hDqAR0HQi8%2BQAeQIBB4kfZ92ztRVHTNWZ0Owqc8LuYjSPNcCnygzMc3gvN/TwINQyJEtPUozt/2TOFB09LdJJfSM2zHPAJynGc5wXJdV3XTcpPkrd5WohEWLI9jsBAEBT2ZX8uy/Ps7gAWjuMx0TMtdvH1aCuKHDzGTkk8eLPNxC0E/tjzuMtK2rL463hRtm1C0S/27AC%2B2E1NR0pJTJwEVT5wwo1XI3VNUOHQ8Dw1HzuN1RDAv4oshI4nTwqrMsovrRsuBbHSEus5KERCnSZNmDLlOy5k1Ly5cCs3FUGNwkr93mmCs1871/OqgirxvTA70EcjQrfcIlS/OEfzEpLewRYDttAhQTPKrVvNgm56R%2BLFjjubBVFYUkU1ev4XppHyhvHYMmAUJQWggfSHQRDR0K4dCzHQ8FnJAGyERRp8XK0k7GzucEWwzDg1loTh/F4PwOC0UhUE4NxrGsKMNi2TcIR4UgCE0Ym1gAawCSQeQ0AAOMwzAATjFrh/GFoWuESRJpFJjhJF4FgJA0OHKep2mOF4BQQDhzmqeJ0g4FgGBEBADYCBSblyEoNASToeJIlYHZVCFgA2OzPckO5gGQCcpB5MxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1GN0hdARgB3YgmBSTgeBJsmKa5mnOEI7lbdtVAqDuD3vd9/3A7uYOzFrDwnfoBdzHBDreCNrQ1ggJBHZSZ2yAoCBx8nkBgCkJGaFoZlzUoGJy5icJmgATyL3gt%2BYYgd8ImJtDqI32cd0DCIYWg98zrAYi8YBOVoWh9e4XgsBYQxgHER%2B1Z6grk%2BOXWcdRuQ7HZuEZkStqa0DwDEfOx8PBYHLgQKOasv6kBAcQGI6RMBPF/kYBBRguZrCoAYYACh%2BQfBzoRF4lN2Zx2EKIcQycWFpzUOXbO%2Bg/4oAZpYfQiD9aQDWKgFIvRP52WRDFUwlhrBmG1rgqOWBREQDWLUeozgICuCmH4BGoQFjlEqHoQomQBD6LMekCxDAhgmNGAjLRvR%2BiTE8O0PQziGhzHsSMBITi5hWICQMXxSx/GaOZtsCQJcODk1IFrXgOsG5ex9n7AOQcBYdwgLgQgJA4RsxWIPchaxSJMCwAkDRpA%2BaSHBDyMW4IFYaEkGYSQnsNb%2BE9mLfQnAVakDVv3HknsuCeyFmLWWnt/CSClvUz28Ty46z1gbDm5DTYW1Hlbaudtp6zx7q7NgnBmgsBXIkOyTBJwGA/FwMWPIuCCzDhHEg0dY6yATuw6QnClDcMzroJGecC77xiXEhJFcOBVxttyO4ddklNz9tCP%2Bbdrm3I0J3VA3d4j5PBGYQpyzjYjzHqiiePd7YzwJXPOFRgrlcDhsvVe%2BsIAb0zofXe%2B9SBMuPqfc%2BDgWXX3vLfe%2B5cn4vzfh/FlP8/4AOpvgMswDQGZ3AcgSBLKYHdHLggpBu9UE7GphgvAWD2a4PwUoIh4rDorMoUmGhdCGGMBZSw15Sd3myC4RnamPy%2BFkPkVYIRar1HiMkVkaRsiGyesUco%2BIqjQFiK6D0LILgGDuHcXkQx8bQmmIRuY3oQTUg2N6Kmxx0aL7eIGFmrxAhXHzDKH4zxgTE0GPGCE4xVaOrrE2FE5tSsgXzM4NC1J5z4VXJuYLWsOTI4YoHji4eJTMBlNGJUpWvT%2BnXKaYkfwYt5bgmaa0qZczM4LNsEsoeJszaW2tjXYlOyXZuwOcQFgzcWAKBXBOFcA68yzHubk1Rzz45sIdSneQnyXU6BAOCUgfzC5f0BWXXdldNm13rqoO9D6n0vr1LMFFaLe4QgJkU3Fpt8UYfPaSnuIBH0pBSMGZ9YtgyvoIMGBD7y6C0vXpvbex8WVspPmfC%2B3LUU3zvg/SVmBn6vzECK7BYqSFau/kAxwIDP7U3lYq7Byq4G8DVcgnemr0GYJZQaghxqSGmtw%2Ba6htDMD0MYbal5P6JCOtTgBnhwH3XGEETYH18A/VSM4LsZEAiFGWCUYklR0dI2VNLX4XR8as1GMrWE6xRQshZozVkPN/iC3aL6DW3IdbwvltS9W4ttaCstHy82hQkSk6QZ3drbt9G7j3sfauFDzI0PZIeZh/u2LD0rCnTOipMSF0gHFjycE4JAhNKpRoUbiQRnVcSZwRZhtilVJAJIfwdS5aJA1kLSQksuAizMLMpW4IoM1d1hO7m3SOChzmyCnDk6cFkVjZIIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/among.test.hpp)
