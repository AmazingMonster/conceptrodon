<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pursuit`

<p style='text-align: right;'><a href="../utilities.md#pursuit">To Index</a></p>

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
Pursuit
 :: template<template<template<template<template<typename...> class...> class...> class...> class...> class...
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
/**** Items ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPursuit = Pursuit
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedPursuit::Glow<Operation>;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXDeSzuSLBWKeQBPZ7MNgAOiVqNukKYCgUSoVKrVGq1OoMeuVAWwqsNmuNpt1FoV%2BI5ClRIImxC8Dluyg2Ci8hHRiSsV1ugduc0cyFVAgmmFUaWIwbwAC9MAB9AhxxMQZYgoMwv23YiYAgbBhpzCoKhaiB2pkKTMBCw5%2B70y7Z0X8iWc4XsyVtrsd8W9oX91ud4dD2WMViYfUms3qm0GufTq3mpezo3amfW1fW24AFWIhgAjt7aI6A0Hna7U48WnQc/WvFkjLcCOOYQF7nuDwxj3Q2VWWHnE1YXrExEkbOsmxbbsRxgoc4IFPtEMHZCpXbFCRXHeUp0tNcgOXRdcK3IiVxIwiNwI9d9yPE8z2bINH3CYBbgAcVoVAAHd30/G8mD/OFqJ/E8lxAEBX2eEDfQg/1gV%2BWksWpO4ADE8GICZbmwVRWGJTBKRxDF5IBIF0TBCEoV0tk0AYLY0gIB1gKuAy7gAz5vhBUdUJ7Dz0LQgdfPEidFTI9cFxCzdSIovClydAgXTdACkw0STHIZBCfK8tK/IypDMLlSdtwi0L8Ki4L8JiuLUwSrhktky5vKy2Ccoa%2BCmoC7CCvIoqOrCyiyquS94o5JMzBq9zMvqibxvGrD8tK7riuIyLFrogbKqGgJRrku4AHlngPCk3NS1qpuO06MOamU8qCpbCvCzq7p6kqbvutF%2Btiq9bl2%2BJyRyTbriOd0mGQABrTB0FuAA1D47D0ukrkY59lCB0H0A9NTvVTWFPzRr0fUcuEsyDBKNFIGFz0DKrScJimhrMKnyYJdb0WAyCUv%2Bu4hC8NJijBgAlD4vFoVNDsuBHmM57nMj5gWhe4z69p%2BgRmbcanGaZRL6fomn1a4TXswSumya1tWWCTDb8bRVnarxfmvVlkWxduW3Bcxj9AZBsGcYx0S2M4tkvv236WZkpyDj3D5hapGKfuQJM53iAgIERUSFEnOP7LcZ2hdJiWefQLOCFRWsQ62wzTkUsOhEwKzwc07T6Fhiuy8BJsQzwWP47aCAkY91HPW9kAsnTZZuKx25JGLjhVloThkl4PwOC0UhUE4FXLGsYN1k2CywR4UgCE0KfVmBkBkkkBUNAADjMMwAE5b64ZIr8vrhEkSaQZ44SReBYCQNBJheS8V4cF4AoEAJMD6LynqQOAsAYCIBAOsAgaQvAEHIJQNARI6DxEiJOTgqhL4ADYAC0hDJC3GAMgMMUgFRmF4GDQgJA8DoD0PwQQIgxDsCkDIQQigVDqCgaQXQusOIHjSJwHg09Z7z0PsvTg21UEoNTGWW4BCSFkIoVQ24NCzC3AgB4LB9BYzmACFwZYvBIFaFWBAJAmC0jYLIBQCAdiHEgGAFIOmNAhbxDARAGIsiYjhFaNKCRvBAnMGINKbaMRtDV0gXvTBpICDbQYLQEJgisAxC8MANwYhaBgO4LwLALBDDAHEBk1ScS8AADcPiyKjNXVB2w97hEZJ/JetA8AxAPJEjwWBZGxTwL/QppBanEBiFLR4JSjCdKMIfVYVADDAAUBDd4HEvoLz3mw4QohxDcO2XwtQsjhH6FKSgaw1h9BdLAZAVYqBbI5AKcQxEWNTDr0sGYIBYziDMLqbcnoVTnAQFcNMPwutQjhGGFUUYutijZAEKCvQcLGgLBGAkXWdhAVNEmO0TwnQ9CYocH0HFqLoXotsDixFGKSWQsWDC1YCgt5bAkFIjgc9SCAN4MA1RRDSHkModQ8%2BuiIC4EYcY3e5j97zNWAgTATAsAJAzKQE%2BgQFS3wCO/DQkgzCSEIf/ZIhDb76E4N/Ugv9TEKkIVwQhl9b4v0IWfR%2B6rCEctkcA0B4CpVQOsfAmxiDFGoPQc41AhicF4I4K0Fg1TEjEKYLOZ8XBb4Ki4Bfeh%2BAiA/JYbrbZHC9nSAOUoI5gjdB01EUwcRhTWXss5XIjgCjkGoNuCotRfL43MUTcmi%2BeiDH2KMTCMEZhJWWOgX6lxRig1jtGGqIwiauAky8YyNSlB/GCPCcE0JpA12ROibEhwG7EmMGSak9JS9MnZNybQfJG7imlPKaeypRLakFKXg05ATSN2tPqLIzp3Tgl9O2EvQZwy95jImUoKZt6mLzL4EslZayNkbpzbsrh%2BbZCHIEUvEtpy5lvKsJYK5MQblKvuY0J5LyPy4esJ8rl3zflEYZfULFLgGDuDxQUcFLHSVLFhZkeFuQ2NgvSLxlFtK0UEsY0SgQ/QpgCfE70KTNKKhiepQMKlFL5iibJSytYGxmVmONWymRgjuUto0dO9tSaU0aD0aKjN/bTFDulaQWV8rRhKs/qa81SatUpFvm/AI2rdWSF1jW91thPXDp9fAP1SClETpDb2sNbBOCRo0YBapYZqkdrFBMNNYrmGsNkLmlDPD5CFowzoEAQQy0VskQZ6tbr5EBuUVQVRaWFAZduFlpNOXUz6ISw4%2BzARHPepgbYgb46nGToSBl7mSZutJl60mVQZC%2BB0EXb4ldS8t3pL3jtndcT90hqSSktJsiz05LyQUveN6ZkAaKQ%2BxwT76mqEaYyD9ggv2CJ/T06U/6Bk/OA7wUDkymSQbmaNxZTBlmrMwOsuUiGivIYkKh3h5XjlVew8YC5%2BGf30eXg8iMnAdjJ0ox8r58RM1/KVYSxozHWP5EExCpTWmeMlByGp5FOQuMwoBZJ7FqnZMYok40aTgxNPcfUzJxnBLFNQu4wyplXCq1GaAZwNr5D0uZey1ydSIr00kHs2YixTmXMKsoKyzzIA74KgCAEZIT9gv/zt4kG1rrjOcA9RApzKrkhqtfokf%2Bl9JAPy4NfMwLrP4BFV1yz3XqrGsroe7tXID49H1GT4nI/ggA%3D%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/pursuit/implementation.hpp)
- [Source code](../../../conceptrodon/pursuit.hpp)
