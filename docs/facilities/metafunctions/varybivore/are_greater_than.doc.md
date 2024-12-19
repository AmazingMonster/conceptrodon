<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreGreaterThan`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-examinations">To Index</a></p>

## Description

`Varybivore::AreGreaterThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are greater than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &gt; Target) && (V<sub>1</sub> &gt; Target) && ... && (V<sub>n</sub> &gt; Target)</code></pre>

## Type Signature

```Haskell
AreGreaterThan ::   auto...
                 -> auto...
                 -> auto
```

## Structure

```C++
template<auto>
struct AreGreaterThan
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
template<auto...Args>
using Metafunction
= AreGreaterThan<1>
::Page<Args...>;

static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3>::value);
```

## Implementation

We will implement `AreGreaterThan` using only `<`, meaning <code>Variable > Target</code> is expressed as:

```C++
Target < Variable
```

Here's the entire implementation:

```C++
template<auto Target>
struct AreGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Target < Variables)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Target < Variables)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIA7KQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7BwEmCzJBpsm/m5MXkQA1AAqjcCYBPvYJhoAggoExF4OJw/EmADiX0ybxDOCEM9weJgSVkeJ2hJ02212mH2h2OqAAdOiAGqNPBMaL0BS3UEwk7PV7vZTEVBEZRMK5EmHgyEPYnE57/PDIE5oBjPTCqZLEE7RVCeE4ANzEXkRUJZ0MZJwg6NR5gAbKqIBdiFcCCckScscQcXjMAp5vNdQkACL7JnE8HW/xM%2BnQuE7f6Ig5HIhKh7AL5bRgEAn%2BO4y6FedJGE40q66/yW6OU6m0j1uX3%2BtiCBRKwmO0HO2FbN17T0opUGo34wlhkkNRyc7m8/mC4WimOYAD6YoL8sV6NV6s12rjbn12Nx%2BLNFodTqtNvzjwA9AAqVdr9eL0Er1dnbBCM5rzdL9cn5dHsGPV0IpFetHoz7AYOhh4RsLAE4AWWuTCoXgYnQYfN4w%2BL5fkwd1AWBQCDi4asHhAEB2yRB9s37EN50eUE2XrDsmAUJQmggL8Gl/f9HAEJEzFIE5AhOSRbgQiVvEweYMKeOsOVw/C4gICAwDAT9v1IgCkS4aiqJohiQCYqVWMdDhFloTgAFZeD8DgtFIVBODcaxrBJZZVkwXUzH8HhSAITQFMWABrEBlLMVEEjMSQAA5XOUjQAE4HI0FVXMCJSOEkXgWAkDQNFIdTNO0jheAUEBIssjSFNIOBYBgRAQGWAhkmOchKDQbY6DiCJWHWVRXJVABaFVJBOYBkE5KRUTMXhMHwIhDXQPR%2BEEEQxHYKQZEERQVHUFLSF0MSAHdiCYZJOB4RSVLUqytM4AB5Y48p1VAqBOSqarqhqmpOFqzAVDxivoQVzDM%2BZeGSrRFggJAiuSEqyAoCAPq%2BkBgCkKiaFoAEEogaJ1uiMJGgATyW3hoeYYhYc26JtBqZLzKKzMCE2hhaHhyasGiLxgEOWhaAS7heCwFhDGAcRibwL5ajFE11r5GpjnWcywk2ILNNoPBonmlGPCwdaXjwMKadIdniGFJRLS2BnhaMKzFioAxHwxPBMBmzbkkYBGRuEURxGGvr5CUNR1um/QGZQPTLH0EWEsgRZUGScieU4arnnQfZLVMSxrDMGKFe6jnPdsTB7F9lwGHcTxWj0EJplKco9FSdJfbGPwxNzwoGD6LO5jjhO6kmAu9A6X3uiaMuBgqYYelrsS2SbzOW4kRYFEMtY%2B/0VaovW2LDqq2r6sa5rJFahVcEIEgTIep7NcWBBwKweIIFskBJH8VEvP8BJJA0SQXJVCLlJVLyR%2BC0KAi4VEVS4fyvNc9/lMkLhlJPlUY9JqxXiolCyms0qZTetlHa%2BUfp/VumVNgnBGgsDFAkaqTAuQGCjFwLyqIX6aQ6svbqvVZADUttIa2Y07aTV0FROaC0EYrQ4KpIBMUtqwL2gdVB6DMHYIZudfBhCrqoBunEVeZhHrgJSq9d6YjPq3QKr9BR/1eEYOQDgwGXkuCRRBmDSgkNJpIzhqbExKM0YYwcKbHGgZ8aE3WiTMmFMqamzpmrdYml8Cs0cOzamRDVDc02Kbfm8d1rC1FnDCWninqGlluZBWStMAq3pkYdWoBZF8B1goPWBsjYmzltbChQ0qGyBoRNTS9DHYa1DlYV2ESPZ7y0j7TI1MA4ECDvGWp4dI5xGjo0/u8dMaZCTinHIhcgjJ2brMVuxd86p1yEXAovtpnZ07kMgCjdmgLImfXauPRVkVy7ts8ZddJiHIqP3QeQ0WFsOirwCe6j%2BGaMEXgghqINCL06ive6XBpHPWsqQLeTAd6UBYSFUgYV/D4Ivgkf%2BCQEj%2BEvpIOqYl7kbTirYMBALXpQKQDlXayiEGlXKig4gLATosAUGKTkYo3kImeO1b5pCxJFItiUs25T7Z5EYYtGmty1rAM4blY4Jx9onFQZS6ltL6XumeKI8Rd1TL%2BH%2BRA6BxLvqFVUbdaSyBkjJC7HgjsDKCC4XJXVPgdADEQyhjDFGZi7Wo3RpjGxYjcb2KJl4zApNyZiFcXLdxaSYmkG8cMvxnNAnIB5iEwQYTJoRLFrDaJUs4mm0SWkZJqs0lvggdrWkOT9aG2NupcybLBoSFKaNW2FSdB5C0c7MO9T3bwC9i0gQ1NFyBwbXUiwEcHlRzwFgAZldhnOAgK4Dukz0AXJzsszIk65mZBnesquXQa47Lrhshu5ye4zLOe3Ddncd0lF7n8pYKwh5nqCnc8enAJXmvqlSml4pZWbHlRAJeXVV5/PXrIze29BhNKChCsKZh8H%2BH8MpTyv8IoQYSP5dhDzOCgKShvUgdlJAJFanCrgUgvKwpPpUB%2B/hBUcMxTilhbVEMYt/S9RYCt0jOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_greater_than.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_greater_than.test.hpp)
