<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoLess`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-no-less">To Index</a></p>

## Description

`Varybivore::IsNoLess` accepts a target and a list of variables.
It returns true if the target is greater or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &ge; V<sub>0</sub>) && (Target &ge; V<sub>1</sub>) && ... && (Target &ge; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoLess
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsNoLess
{
    static constexpr bool value
    {RESULT};
};
    
template<auto...>
constexpr bool IsNoLess_v
{RESULT};
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQgZlykAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3EwvERrgAVZrATAEUjXGFEAB02IAas08EwYvQFJDsICxsQvA47gpIqgQpgFCSLiYAOxWC7XLnXGaOZDXNAMMaYVQpYjXGKoTzXABuYi8mEB3OubIs1wg2Mx5gC2ogDFQBHViOIyMNkLc1zxxAJRMZi3tKtZABFIRyAc7XYDAcDQa9FVCMagEUiUWjA5qrTbiaTAYLhaLxZLpbdafTGQoAPoyr3s9Wa7W6/WGiDG00qqGW/GE4n2xaOl0Qt2A76/Q7/FvXbCqViPTDvE7N1t/L0XXl4ZAZphM%2BIECApukMpnmgCsaOk1whaLMpJAIDl3kwi09o6afMn05aEDAYBpC/T5vXq43a53e/lh9dHGWtE4y94fg4LRSFQTg3GsaweVWdY%2B3MCEeFIAhNC/ZYAGsQGXSRMQ0AAOMwzAATnwrhlxw7CuFZVlpB/DhJF4FgJA0DRSAAoCQI4XgFBAJjEMAr9SDgWAYEQEBVgIFJYXISg0AeOh4kiVhNlUbCAgAWgCSRrmAZB%2BSkTEzF4TB8CIa10D0fhBBEMR2CkGRBEUFR1F40hdGSAB3YgmBSTgeG/X9/yQ4DOAAeVhcTDVQKhriU1T1M07Trl0sx1Q8GT6HFWCuEWXgeK0ZYICQaSUlksgKAgQripAYApDMPg6GBYhOIgGIApicJmgAT283hWuYYh2qCmJtEwBwutIaTngIIKGFoTqnKwGIvGAaFaFoTjuF4LAWEMYBxDmvBiGGxwZUZAKRWG2FNng8JgWooDaDwGIPL6jwsACghrXo9bSGO4hJSUJ0QW2%2B6jCQ5YqAMYAFBxPBMFcoKUkYUbzOEURxBs5H7LUAKXP0baUHAyx9AezjIGWVAUnqNaVLGdBISdUxLGsMxWJ%2BkyTtJrpDqyFwGHcTx2j0UJwkGCphmSQpMgESY/HF9JJYYOYhgSUZai5gRegmfm8hV7p1fGfphfmMXbH16W9BmFpFdF5XlgUKCNgkXyOD/ZiArYqLlLUjStJ0zCkogXBCBIFUzDgrKENB5YEEwJgsASCBUP8CFMXwiFKI0SQzECRjlwCfD9E4WjSHouDMQCLgAmw/CyICDDiNToIWN4NiOK4iPeLyoT8pE0KJNK8q0vkthOGaFgZVZFSmAFAwjAS/DMS4LCDKMkg8FM5JkcstHpAxpQsac3Qavczyuqdl2m8CjgQrE2Frgij2Yo05AZ%2BAOeF6w5LUFS%2BIQ4hMxw5ynxbuA94iSTKl/IqaUUAvy4ERJiNBaD1Uas1JyPUOqjTQX1AaQ0RpfXGowSa01ZpAXmotZaq1RqbSBpsEh%2B0ubHTWkBM6yALqjWurUAK91HodRejQ7KH1Ro/T%2BpgAGW0jDA1AB3PgEMoYwzhgjAC8FN6o2sjvWQmNHJAUPrjEGDMrCEy4STBOwEKZZCpjTOmeimYs3iGzIxttVYOG5hAVwZtkhCzKErPQEt6huNSHLeoVsFg6zVg0U2WsZacycXrWYhsvGjHCbkSJFsDaeOto7FYawHaZQLs7fyTl3bRS9tPbab9F4aHVIHYyv9MrZUjqQaOsdhjGOokXEu88M6smXPhCiEJM6BEkMkC%2BLdbBt0AZ3eA3dRJhTASA4gQ9Nij1iiwBQMp%2BQylgZiMEjICDLyDiZMysgt6qNsvIPemidAgE3MfLy60z75NYsFXu4VIqqGWas9ZmztljE/t/dKocIQANBvxAqEDiqzLBVAtZKQUhZlgRmb5BAMxvJ3nVeIyCWptT6hgrF/VBqHVGvgwQU0ZoBVIUtMQFCvpUPEXw0g%2BADpOIYadVQ51gRsMEBwpyXCnrtV4W9ARX0hHpBEYDcR4RJG5WkUwSG0NYbw0Rl9ZRVkJBqLsuc7GVydHGAJjYQx8AyamIEGtLYNN8aM0sMzZurM17s2MXYUJPM%2BZJMFrzIJxsfFZD8Z6kocT0khOiWEvofiHWBo1qkkWwSTbBoiebfW7qbaZOghk6i583acCiu8tZsovl%2Bh%2BQHFe/yw51I7lHGOcdKBOzaYkeeEIITLhIoMxidbWSV1dgUzgrduL1LQpIZcKdyKskYthSQREuC4TMEEaiEIHnN07e3XKTt9LtseexBdyFvrou5pIIAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_no_less/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_no_less.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_no_less.test.hpp)
