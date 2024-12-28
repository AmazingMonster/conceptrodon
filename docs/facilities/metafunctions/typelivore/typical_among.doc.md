<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalAmong`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-among">To Index</a></p>

## Description

`Typelivore::TypicalAmong` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
TypicalAmong
 :: typename...
 -> auto...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalAmong
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = TypicalAmong<int, int*, int**, int***>::Page<3>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalAmong` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the element at the index is returned. Otherwise:
  1. Drop several elements from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `TypicalAmong` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<typename...Elements>
struct TypicalAmong {};

template<typename First>
struct TypicalAmong<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct TypicalAmong<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { using type = TypicalAmong<Others...>::template ProtoPage<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhugsFRIdh/v9Pt80dtfqiLgBJFhJehsQRMGqvHaY9EUw7Ij67C4AFQAnkk8KJaCcWAJgKSMf8CJg8QY%2BZC3AQmYxWJgAHTS7AExgEBSI/7DYheBz0pkssTszkQgDsVj1V0hVlOvP5%2BOJmGForuzDYFwAYnhiMMlacVWqCBrmaydUZhc7XQR3X8Df8LpGLnyBVbhWkAF6YAD63uxoajF096uUxFQRGUTGAmH1huNgNNf1OmZjlqFUMTKbTGajxEwAEcvC7nhcIOnAeWrho5hGo9nvbn86hC8Xhf2kdWoyYDRcvGkjNGxRCB06XW6K/ry5XR5Ha4LrVCmF4iNLJSdgG3%2BfLFYCFydM2vglyZyXIVcLpOBZFhebj3o%2BhIKreiIgCAtoXseRomtSJxnnGUJwfaJZBsMpCbnaEoXEImBoAw6C4RhEq3gA8gQCDRC%2Bb7jj6WpshyAZQthBC4URJFkRcNF0a6UGvsi4aLqeFrnvGeBJqmOItpGTGAdOwEQuJparuuXJwdu/6Mr62pscAwoCfRwnYDBqF8gBeZAbOULYhcAC0FxmNBsFiiah5IWa6lWSBjZyfOJ4XG2nbdi8fZ/n%2Bw4hUptkqfZbjBepy4WJpX54b%2BO6cV5y5HshNaSWhbiBc2InqWFXZtpF/aDlwI7qfFU4/nOCkaZ%2BG46X%2BhHEQI6B5YhFaFVG/nCleN7SmBmBPoIDEhZ136qT1ymtVC02zZB0pKsNZpDceNKUmSKK0tgqisPiJZvCdR08r5ALAgwoJeOCwokasSQKqGN3bIRXhJHkmDoAASs8Xi0N612nItf0A6kQOgwo4Pej1wQEDsPlVmctKI8j3JUtDWkXLjEO6cxfpGcKaO4Wjmw04I2z0%2Bj2zuWtbiAu5cGYz9mz0s8kPHR69SOMgyZMAoSiNBAsIwQoEpiy%2Bbgk1xsOAyDYMQ4iI67ScHALLQnDxLwfgcFopCoJwbjWNYWZLCsv5AjwpAEJoesLAA1iA8SSJKGgABxmGYACcQdcPE/t%2B1wep6tIBscJIvAsBIGgaKQJtmxbHC8AoICpy7pt66QcCwDAiAgEsBBJNe5CUGgeJ0NEoQSpwqh%2B7ETmxJIFzAMgyAXFIkpmLwQOECQeDoHo/CCCIYjsFIMiCIoKjqAXpC6G0ADuxBMEknA8PrhvG675ucFR15V96qBUBcrft533e9/3PtmL2Hj1/QxAQo7cy8PnWgLBAJAddmQfxrhAYBDcYjACkGYPgdA%2BSukoBEY%2BERggNAZHvXgqDmDEAZFRCI2hiL5ydnXCCVEGC0AwavLAEQvDADcGIWgOduC8CwCwQwwBxDUO7A4PAAA3Z4x9MCqGIteNYTs0ZVGPrQPAERt64I8FgY%2BBBiB4CTiw0gAjiARHhjcdhRgZFGFdgsKgBhgAKAAGpPA3lRO0mCF7CFZHPaQU95BKDUMfde%2BgOEoGtpYfQsic6QAWKgT6GRmFOVhH%2BUwlhrBmAzlo1RWAgkQAWHYIhGQXCkTGK0UggRgh9FKAMNoeR0gCBybkVIZSGDTH6DECYVQMkCC6KMTwLQ9DpN4c0kYPQCkzGKbYHpFSJg9NqUU%2BpaS7arAkAfDgRs07H0zjfNuHcu49z7gPF%2BEBcCj0/uYQEDVf7GIWHRJgWAYipNIJ7SQgJJRB0BDHDQkgzCSFiCneIsQg76E4AnUgScDmSliFwWIfsg6RwSJIMO9zYgLNXpnbOudnbGKLqXQB5dz7VwoOA1A79G7Nw4A0FgfC9ROSYBcUEHD%2B5B0lFwX2w98BECSZPWQM9xDz1cUvDxq9dCwK3jvTBsz5np14JnM%2BldrwXCvssu%2BXcKUbi4NS2lGhX44pAdEL%2BgIzA/yRQXABQDVWQLARAj%2BKADBGAVVwVONAIb0SQSgtBuD7HYPQfgwhDh7GkPlOQyhx8aF0IYbQJh9i2EcK4WbfAbZeECOYWbYRoi%2BT2MkXHM2Mi5HoMUWsM2Ki1H2K0TopQejQ1fmRaYosljrG2MYPY1xrLnEOM5SvM2PLvFGJiVYfxqaUkhLCQICJUSBxtriQk6ISTBHBPaE0vwEBXDDLyaRMZswSlVJqLO0pNQF0DM6TUFpTQ2njAnV02ooy%2Bl1I6UMvduTJiNA3RMxYyxpkNW%2BXMo%2BcLODStWeSs1XIFU0t9r2HZjKNWHJ1f/E5mAzkDEuXHX5/zqVPL1PEIO0dATPNeZC2FGdOAIrzsi4uZcK4XyNQaj%2BTc2CcEJffFgCg%2BF9z4T%2B88wx6W7PHsy6eTiJAuNkA2zxIBASkD5bvFhgqX2YY4GKi%2Bkrr6qEo9R2j9GrTDBVbivZQJATar/oXNFxrohEeUyAGjANkx0aDsmBjBBkzSZcfA21EBkGr2dY6jRDm8EEKIR6nFZCKFUPDZgWh9DGHMKdiGgxmbWE8McNGoRIjkBiMTYIKRq9U3yIZBm5Rqj1FOzzbo/kRajG6r4GY8tmAbF2I0TW9j7KuPuMbToXjLbjB%2BJsJ2%2BA3aajMPWDLQdlh4kisSePMdlyt2ZOndki9/h50nvGZU/IGRV3LoyDejpjTD07tnUN7pUxJuLsGd0Nbx7iinsfQoKZc9hMYZFW%2ByzFwqM0YuMZyUZn/0MpIEB9TxzSCnPOZQWZMGQDB0lICQE8Rw6QpToDvUILzsnyzrYRFGm5gexAJIeIdyo56hTn7SQocuABzMDCuOgIRMXZh/D2ZQ8ofwpA27TR9FMmSCAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_among/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_among.test.hpp)
