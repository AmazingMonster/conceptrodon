<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Boolean`

## Description

`Varybivore::Boolean` accepts a variable and casts it into a boolean.
<pre><code>I -> bool(I)</code></pre>

## Type Signature

```Haskell
Boolean :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Boolean
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Boolean_v
{RESULT};
```

## Examples

We will cast 10 into boolean.

```C++
static_assert(Boolean<10>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto I>
struct Boolean
{
    static constexpr bool value
    { static_cast<bool>(I) };
};

template<auto I>
constexpr bool Boolean_v
{ static_cast<bool>(I) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwBspK4AMngMmAByPgBGmMQSZqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwc5gDM4cjeWADUJrtuyDPoWFRn2CYaAIIPjwSYLMkGb2duTF5ExwAkncXjNiF4HMcLKhPJhDC8TAB2KxPY5o44zJiOZDHNAMGaYVTJYjHGIw2jHABuYi8mBe6NOyIxjWxAH1RDMfmTPHcIIDloyACJnFHPRHC3ail5vD5fOnnP4A4G7e5PPEEokk7kU6GwwysykIpmYtkcghc8m8/lCkUIp4AegAVM6Xa77S8nc6ACrYIRel3uh2u4OOwPPJ57A5HTCnc54rbJAgKEERp4mvDIVlMBRKZoQXX0eHnLgaO4gEDU7yYZa2p4cVa0TgAVl4fg4WlIqE4bms1gx602Mb2PFIBE09dWAGsQE3JAA6DSSLiI3YaJsaQIBMwADm3%2Bk4kl4LAkGg0pDbHa7HF4ChAZ7H7frpDgsBgiBA6wIyX%2B5EoaA%2BdDxJErDbKo24BAAtAEkjHMAyA4lIc5mLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOoj6kLoXCkAA7sQTDJJwPANs2rbjp2nAAPL/N%2BBDHKgVDHGBkHQbB8HHIhZjHBAHgAfQJLDssvAPloqwQEg/7JIBZAUBAGlaSAwBSEkNC0G8xC3hAMRsTE4RNAAnoxvA2cwxB2RxMTaLUD4jv%2BbCCBxDC0A55FYDEXjAL8tC0Le3C8FgLCGMA4ghXgxBeXglKYDFHaErU/zbCO4RvI25G0HgMR0a5HhYGxBAYcesWkJlxBkkogrvIlZVGOOqxUAYwAKAAangmDURxySMI5RHCKI4iETh8hKGobGUfoiUoL2lj6OVt6QKsqCJpkMUQVcZyCqYljWGYl7NRhWC7RAqw1HUzgQK4kx%2BFRoTzGUFR6AUGQCB9/1pIDDCDL9SydN09SzMDVHPT0fTNBDwyVGM/TwxjKM/WjEhPQOWz4/uHAtuebFXoJ4FQTBcEIfOkkQLghAkKcZi7Fwimjj1qwIHCWAJI9pDTpIuxzgAnLsiKSIuZiSAEp5NgE4sk4epDHhzc4BFwATbuL2467OXBNpLQQXrwV43ne3OPqpb5qR%2B3E/jpelycBbCcE0LCUoiEFMLiBhGOJ4tzlwC4oWhJCYdhsh4XN0gLSRy3kboSS0fRjnMaTrHkVeXFfv8fECV7Pt%2BwHiXB6HC5STJmlyWzuxmFzylPg7rvxL%2BumoLJIwl77hyJVw4slnwdBmRZVnkc59lTdPrnuZ5DhTb5jAEAFQVsaF4WRdFU3xZ12wdvgaV1Jl2UoaoeVvFNRVdGxZUVfZ1WH0p9VTc1rWYO1CVGF1oC23wfqQ0RpjQmm2EcC044EQTrIJOZEOypzWt1C6VgtoPwevtQ6AhjqnV2OdTaFhroW1uphLK8AnpdHSq9d6ng2h6G%2BqUPGVEAY9CxiwzIqNFjo0RrDTGtDcgI0oS9XosxOF/QRnDfhn1sZzEYVw4mChCYESzmTc27EODHD7mXAeQch5Vw0FJZm6EG6cyUjzUgfMmAC0oFnNWGsQ6LkRCbREK5JBy2glRNRltbDWxbnbeADtPw8U7u3Yg7tthexEiwBQlIcSUj0XKGYEcWZ3RjrhWa0DppwJWiAXYNE6IMViionOl5OJO14vxTRxAWBRJiXEhJWIsq8Wkt3Ou8QG67Gbj1Z86lWlaRCX0uSFZkDJGSAaIerJEkECzNU6Co9TLxAntZWyrlZ4rLch5Lyy9u5%2BTXoFYKR9MBhQimIXejV96/xfqQY%2B6Uz5sVysgfKN9BB31KuVSqdln61Tfo1D%2BaQv4dV/uEf%2BKlAFMAGsNUa41JqNUgRkiQMDiJLXgToXJSDjAEO2jEDBnYsH4k4PaK4G1LqWCIZ2Eh91yHQyoX4N6DB3BSPofSsRUN2FA0Zcw0GPQWXcKEUjSRORpE8IEMjWRCxxEyKxpiHGcjxEEw2ETTmJNVEU04FUmpMFomxKpA0t4MxDGR3kuzUxNsVK835iMIWJU7H%2BBDrsXYTZ1xLlPPaxEutya504Fbe85iRZNglk2bcgRxaSHFiuKWXA8klV2CUi2XrTUThJshD1pTrwJuWKsZq6RnCSCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/boolean.hpp)
- [unit test](../../../../tests/unit/varybivore/boolean.test.hpp)
