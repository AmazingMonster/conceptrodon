<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pursuit`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

## Description

`Pursuit` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Pursuit ::   template<template<template<template<template<typename...> class...> class...> class...> class...> class...
          -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Pursuit
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RESULT;
};
```

## Examples

- We will create a `Pursuit` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_3;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Operation;

using PackedPursuit = Pursuit
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

using Result = PackedPursuit::Glow<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Pursuit`.

```C++
static_assert(PackedPursuit::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Items>
struct Pursuit
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Tranquil>
    using Glow = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBoIAnqlGKxMAA6dE3Q77JgKBTo1GY7G4/GEgzEjEBbBYsl4ilUom01EASR%2BChuT3GxC8DkOynWCi8hCeJgA7FYHodJYdZo5kFiBONMKpUsRpXgAF6YAD6BDVmogSyeUuOYsOxEwBHWDD1mFQVHxEBZrwUhoCFhNABFhRKpWDgf9QbD/RDfsHA6HoX7I0HoxGA99Eci2CTKdScYzSemU/Sadm0%2BSCamGXmGYcACrEQwAR0FtHZPslnO5uo9FqYdBN7q8mSMhwIieOAQ95crDBrdC%2BTpYGcpJ3doq9bu992NUfja5DUPXMe3cc3cJhe4RSOYybp%2BZnOaz5%2BLN9zd%2BvhavBYr1dr9ZXUu74WAhwA4rQqAAO6DsOrbNBOpyvmOtbZiAID9kic7CiKi7io8DwAPQAFS4Xh%2BEEZhTw4Xh5bYEIZZCIc%2BFEVhBH0TRy47HsByYIOZwCJsqQEGys4PE8G7hlu%2B5hoewlCQeiFJmiD4FpmclFveT4XtmHIEFyPJTlqGjIfxDyCWJkk7iJsbiQmJ4oiWSnyZeKmyZeakabqWlcLpGHPMZEmiQZPmeeZ0lWY%2BNmBQpz4OQ8TaaT8WpmG5Al%2Bb5R6Gd5CWJqeMnKbemXWYpQW5aFjnNocWkBHF%2BkJRVSWJWZPlpZZ9khbZWXBQ1dKFTyADySKVg0ZX3CRuGHAAYngxDjIc2CqKw7xsYxen3N%2BvbKEwyAANaYOgfJjYKuonMOW0CkK/GnEaUpaRopDHA2xXRSkV2fpKWlmJdp2PdFpXHbcS7zYtv5CF4qRFBtABKmACrQu1DocXXxMC2TCid13nS9SO3SjD03a8MXo8aJUI196FPL9hyg%2BDkP7St62bfyO3wQBwFfDDPXw7O33uTKeDIFq6bxAQEAXPBCgotzvFuKTXgQ5d/2AxkINgxLBA3K6hN0aRQiYGgDDoBNU2/LNeG0ezzSyiLSitBAy1rRtB20yAmT6ksoF7YckjK08HArLQnAAKy8H4HBaKQqCcG41jWNKawbGxOw8KQBCaB7KyrSA3saKiZhmAAnAAHBomfe9niQBJIZgipIiT6Jwki8CwEgaBd/uB8HHC8AoIAXfHAce6QcCwDAiAgGsBCpF4BDkJQaBvHQ8SRCinCqIXAC0iSSIcwDIHKUjp7wG2ECQeDoHo/CCCIYjsFIMiCIoKjqF3pC6CkQGVqknA8J7Pt%2BwnQecB1o8j7qdpDgL0SMvVe69N6SHTocCAHgp70FVDHJYvBO5aBWBAJAk9UjTzIBQCAmDsEgGAFIZ6NAIbxDbhAGIX8YjhBaPCV%2BvAaHMGIPCDqMRtAa07rHSebBBAdQYLQehd8sAxC8MANwYhaBt24LwLALBDDAHEMI0anC8AADcwZfyVBrUeWxY7hBeF7O%2BtA8AxErCwjwWAv7qTwLXGRpANHEBiLLVs8ijAmKMAnFYVADDAAUAANTwJgICMN/ax2PsIUQ4gL4ROvmoL%2BD99AKJQGHSw%2BhTFt0gCsVA3FsjSMXhcPaphLDWDME3RxxAD6aKyd0VRzgICuCmH4FIoRwhDEqCMFIRQsgCCaXobpDR5jDASGMOodTGgTDaJ4Doeg7DjL6K0IZHSRm2EmX0sYkylmLC4CsBQkdNgSHfhwX2pBG68GbkApeK814b0OFvMw0DcB7wQWYAIOzkFeJWAgTATAsAJANKQZOgRUSZwCGXDQJdy7129okTOlcODV1ILXN5qJkiJGzjnLgiRvaSC4N7UFFcznfxbrYduccvE937ugwef9R7jzwagOBM854cBaCwNRIpF5MDTL2LgmdURcFRIHXeRBKmHxSBE0%2B0TpCxKUPEu%2BuhnpPyYC/GRRyTlEubr/Yeo9DiALZRyrlPLfx8oFUK6BsCsHwOOK8swSDyVdzQRgxlVr4j0vwfAkABrOXYiMHyrgF1SEvDGpQKhd8mF0IYaQCNLC2EcIcFGnhjACD8MEV/ERYiJG0CkVGuRCilGB3wOaBw6jNF320cgXRUaDF1C/iYsxdDLFbEDjYuxsdHHOKUK4/NP4KU%2BKYH4wJwTQlRslVE8%2BMrZBxNvoHRVSTPHFKsGk%2BtmSAU5IaPkwpQ5F2lPKfEMV1SAVzJLfUxp0z8gtK1lszpaQMg9JyOe5pt7ijZGvSs49DQFlTLyE%2Bj9vRNltIWDe2YkxH2zIA%2BUYZhzVjrAOTs%2BFGqv4XO9Ua31Jr%2BWCo0I8/AoqbVvPtSgxOpBvm/JGACoxiLkX8ohSKfFIoRTFzMOXXFpykOcFbmSwjaCqVICHv/d1LrsGzzYJwNl1zpxqLlGo01fxxg7xw/vcVl9IlnwkJOq%2BcqZ06BAEEZVqq34Ic/nfLVtKAFUEOGJ1eEmpMyf9ONGBgnrU7ACARil1KPVutwR5hIknAZamk5nLUsmCDc2ICwFefA6DBooWGwOMahGx3i3GzhibGW8JTQIoRhbMCiPEZI6Rsc83uObbIlRJaNHSOFaoHRLxq2CFrcY0x5j4RNusZUttvAO0uNeD2zxjq%2BC%2BICUEkJJ5R2yClRO5T06Ek6fncYVJNgV3wGybkhUnBMICx3ZYMp5yKlVNXbssZJ6/ANK1us4IV7ANQa6Xeho52Bmvqu8s2ZR3P1rLA6MnoAgv1vvA/0c7IGBhPe2bs/Z591VGabpwCzYXxMKEk4cALqJgvYeeXh95DrUFfJ%2BX8ygRzKMgCzqiAIARvap1xfXEnIp0WseM%2Bx0lHdPmAv8Py%2BjGg%2BUQq4AEbFIozA4vhQESH5z6dcaOWYIXxKPmOpWI4zIzhJBAA%3D)

## Links

- [source code](../../../conceptrodon/pursuit.hpp)
