<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoLess`

## Description

`Varybivore::IsNoLess` accepts a target and a list of variables.
It returns true if the target is greater or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &ge; V<sub>0</sub>) && (Target &ge; V<sub>1</sub>) && ... && (Target &ge; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoLess ::   auto...
           -> auto...
           -> auto
```

## Structure

```C++
template<auto>
struct IsNoLess
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
static_assert(IsNoLess<5, 4, 3, 2>::value);
static_assert(! IsNoLess<4, 5, 3, 4>::value);
```

## Implementation

We will implement `IsNoLess` using only `<`, meaning <code>Target &ge; Variable</code> is expressed as:

```C++
not (Target < Variable)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsNoLess
{
    static constexpr bool value
    { (...&&(not (Target < Variables))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoLess_v
{ (...&&(not (Target < Variables))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG5MXkQA1AAqzcCYBKRXF0QAdB8Aas14TDH0ClO2BMGgAgrNiF4HFcAJIKSKoEKYBSAsEmRJWMFXbFXWZMRzIK5oBizTCqFLEK4xVCeK4ANzEXkwINBOKu6IsVwgHze5gCfIgDFQBC5d2IDxFpzcV2%2BxF%2B/2RKyV7MSABFTpjQej1SdNSy9gcjsyzq9ULd7o9nqaebL5QCgSziaTyZTqbS4QikSiAPp0lkcrk8vkCoUiiBiiXss4yn5/AFKlYqnV6sEAegAVJms9nUyyM5mbtghDcs7m09mK%2Bmy1qwXiCd6mCj4gQIB7EcjAWcAKzPaRXE7PMxAkAgBneTArDUsut4ZANpstCBgMCw%2BHtlFSvs9/u94ejxkTjUcNa0Thd3h%2BDhaUioThuazWXEbLaYdlmE48UgETTHtYAaxALszDeRIzEkAAOcCuw0ABOICNACcCB1PDhJF4FgJA0DRSEva9bw4XgFBAbDvyvY9SDgWAYEQEANgIFJLnISg0AOOh4kiVgdlUcCAgAWgCSQrmAZBCSkN4zF4TB8CIOV0D0fhBBEMR2CkGRBEUFR1DI0hdC4UgAHdiCYFJOB4E8zwvH8b04AB5S4GJFVAqCubi%2BIEoSRKuMSzC5DxWPoSlzA/FZeFIrQ1ggJAWJSNiyAoCBotikBgCkMw%2BDoPZiCIiAYismJwmaABPUzeHy5hiEKmyYm0OpSM/Fi2EEGyGFoYrtKwGIvGAc5aFoIjuF4LAWEMYBxHavBiFqvA6WRKyyTqS4dk/cI9hQ69aDwGIjIqjwsCsgg5QwgbSBm4hqSUVV9hGjajB/NYqAMYAFE%2BPBMH0myUkYEq1OEURxFUhT5CUNQrN0/QRpQB9LH0TaiMgNZUBSXp%2Bt42Z0FOVVTEsawzDw07ZNm%2BGuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/D0xneiGOnlmJqaBH6SZKbyPTanqPm5k5kYqnGAYWb0PEWglpYqjWBRn22CRzI4c8cKs/CXJ4/jBOE0TJHErlcEIEg32C0K7rWBBMCYLAEggf9/BON4YJORJJA0SQwICLCuwCGD9E4NDSAwj83gCLhEJg8C467SQuC7L2glw3h8MI4ivzuijqMi2j7MY%2BLEoCji2E4ZoWDpRJeKYIkDCMLyYLeLg3mvKTLdk%2BTZCU/7pEBjSQe03Q0sM4ySs17XM%2Bsjg7Poy4ricl5iFr%2BvG%2BQZvgFb9vO981B/Pia2zBCvOyIiqKj5igKmISm%2BkpruveO3kauBgrhsJoWhMuy3LtJlSKt9IBFUqo1QcN9BqjACDNValZDqXUep9W%2BkNa6Oxrz4EmvUGa/Uu6qAWnsb6K1uhWQ2ltIqu0MGhUOt9U651MCXWGkYG6oBL58Ees9V671PqXk/IDAeKkh6yBHlpa849wa3SxlYaG5C4auxvEjLIKM0YY2kTjPG8QCbyJVt0XmfgICuFlnpGmZRJYM3SEzbIgtWapEsRzWm5jhZ6NFn0OYxieauP5vMMxSs5buJsf4gYit6ZcBVmrFSM9LLaT1s/TeTcRp7w7hoc20krZBTCbbS%2B9tHbO0oJrCOUc25%2B0SGnRIiQTj%2B0CCnHWMTOA5xIvnSiNE6IOXvuXdinFq7r3ciwBQdJCR0g/m8I0sxJJpN7npARf0hE/VEaDEAA5J4mQGlE2peFbIl0cs5GuvT%2BmDOGaMsMflb4nyCicc%2BYVyJFw6XFZij8AqjmQCkFIvoP7eiOQ2HpQ8MrxH/nlAqFUQGAsqtVWqUCj6NVgS1NqmDMCdW6mIFBx00EsOoaQLBU1cFzQIcgRaxDBCkO0uQ7ahUqH7Vocdeh6RGFXRYeENh4UOFMCei9N6H0vrHWmcpCQwj1LAzEToRZkjjBQxsHI%2BACMlECH6qmNGkNsaWFxlnfGeAsA6M8b0MmFNci2NMYsUJdiihZA8ezLIITuYi16N4jxVqGji0cX44WATdVBIVo60J4TNjqzCWHLW0SNkcDXiwPZAz6SHPxMiMMFsZLW0yRfcKOSnajAUShQpIAzBtxOCcLs0EU5YWzYkRC6ys71NsLnK5SpSAAUkIkcSpSuBSBgiUr21Q/UnADaWgiCbfx%2BokiW%2BeWTE0nT%2BaTSQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_no_less.hpp)

- [unit test](../../../../tests/unit/varybivore/is_no_less.test.hpp)
