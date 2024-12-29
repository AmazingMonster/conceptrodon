<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Send`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-send">To Index</a></p>

## Description

`Omennivore::Send` accepts a packed vessel and returns a function.
When invoked with an operation, the function extracts the list of items from the vessel and instantiates the operation with the result.

<pre><code>   PackedVessel
-> Oper
-> Oper&lt;(unpack)PackedVessel&gt;</code></pre>

## Type Signature

```Haskell
Send
 :: typename...
 -> template<template<typename...> class...>

Send
 :: typename...
 -> template<template<auto...> class...>

Send
 :: typename...
 -> template<template<template<typename...> class...> class...>

Send
 :: typename...
 -> template<template<template<auto...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

Send
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct Send
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;
    
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
    
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
    
    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;
    
    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RESULT;
    
    template<template<template<template<template<typename...> class...> class...> class...> class>
    alias Cool = RESULT;
    
    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RESULT;
    
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class>
    alias Grit = RESULT;
    
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class>
    alias Will = RESULT;
    
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class>
    alias Glow = RESULT;
    
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RESULT;
}
```

## Examples

We will send `Capsule<int, int*, int**, int***>` to `Operation`:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation {};

template<>
struct Operation<int, int*, int**, int***>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Send<Args...>::template Road<Operation>;

/**** Test ****/
static_assert(Metafunction<Capsule<int, int*, int**, int***>>::value);
```

## Implementation

`Omennivore::Send` uses partial template specialization to extract items from a packed vessel. We will showcase a simplified version that handles `Mold`.

```C++
/**** Primary template ****/
template<typename PackedVessel>
struct Send {};

/**** Partial template specialization ****/
// We extract `Elements...` from a `PackedVessel`.
template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOxcpK4AMngMmAByPgBGmMQgktIADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJSbaY9kUMQgRMxATZPn6B1bWZDU0EJVGx8YnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enF32V2UxDwLCaAE8rgRMPcDDC3scATC4S9MCYAMxuAgQ5KMViYYFMZAAa0w6AAapgFHZMdgAaNiF4HFchK4riZ/FZ/AARTFWc4Ar7bInNPBiaGwh5oq4KPHIcW0PAALxemURuz%2Bm02VwA6oTMKoCMRiQQOQA2DTYR6MAgKAB0jpMlquVGIqBYVyYFo0ymJZMp1NplvtyKl8PRWJR0phmOxuPxbEdoYx2CuyAMNKuHme4XipGhCeYScd1thtoUdIZxuZZrZDHQcZzjTzxDjZaeduTVdTAM5ArOVyHktRsaj4bRcZxeOLmG7qfTmYUVwA8niTXUq%2Bdh7KayyeZgW7QATvtbcGAA3VBkn1r%2BJqgTOjRXADuhAQ0IQhKfHYr3ZDJ7Dv2VxeOkRiFniHIYjyq7rg%2BDDtjaggOk6vYYhYHK8vyfbbsO0YRlOE5jvGM4EvOaYZkwNLJmcwDEJg5bIVug7DqB4TAFcABKqBMOgUEwQeR5xrR9GMV2qHYCAIDTpGA6cny6E4YCPy/EKQLYKorAPIS7xqSphx/HpuzZkwyQKF49Aatsfz4ZOUZFmREnVkyLJuKZ5n0NhgqfECd4buqunnLZxEybO5HObWsH3q8/byV5/xBURkZuMxjKRX58FxuEBAFtl2y5YIuwFQQezMcB0yOMg6YCKMhrJMQVwxKgnhXBeYheN%2BXI1uiWHoZhClyT51wALKHkwVBeAwDgBUiiWjsloWOfaZzEMAla9ucbHgaNjQTVNMXQayrjCatKEppJ0lJVxPGNliGWbmhg3KcZAAq1JmoFZwVXgyAAPpUUozQQDt42TdNj5Ym5ZkWcl2XFflVx5QjSPbD2F1td4mALPyHBLLQnAAKy8H4HBaKQqCcClljWLKKxrN%2BZgYjwpAEJouNLCSIAE5I9oaAAHGYZgAJxC1wBP83zXD%2BP40j4xwki8CwEgaBopAk2TFMcLwCggKrrOk7jpBwLAMCICAKwEMkXg5RQEBoPcdDxJEBKcKofPmgAtOakhXMAyBVVI9pmLw5KECQeDoHo/CCCIYjsFIMiCIoKjqAbpC6EEL4msknA8HjhPE2z5OcCu1tW2aqBUFcbue97vv%2B1cgdmFcEAeA79ANeYTMLLw%2BtaEsEBIPbySO2QtvD6PIDAFIZh8HQMLEDrEAxEXMThJCue8GvzDEBCK4xNomAOJvpD252K4MLQEJF1gMReMAbm0LQOvcLwWDgkY4hp/g9HTRe1JF0NEfa2GxmbZRqEXJUMQTS7w8FgIuxowQn3/sQJqSgDwf2AEqIwbMlhUAMGtCkeBMAvjvCTZm0dhCiHEAnShyc1BFwzvoQwxhrDWH0HgGIOtIBLFQMkOoL8PajFujyUw1NLBmA1ig0EWBuEQCWHYI%2BdQXANgmH4IIoQ8xzCGPkNIGQBBqL0AUfRDBZiDASEERR4N6hjBaJ4NoegrF1B6M0Mx5QdG2FsYYyxti3HzC4Aoum6wJD5w4ETNWRdNbV3dl7H2fsA482bhAXAYdO6MwCb3XBSwvy8SGPI0gnNJAYntELDEMsNCSDMJIS0GgCbmiFvoTgCtSBKyZvac0XBzR8yFpLc03MxalPNBEtOmtta6xZrgo2ptB7mzLtbcglAJ4d2dmwTgTQWAXn8B7b0lFwJcCFvaLgvMQ74CIDIqOshY40OkHQpQDC066FnlnUym9QnhPVrwTWpdLbWyuJXaJtcfa7I4vsw5vMW5txHh3DkjMzA9wmQbAeQ8PRQvzOPFFk9gX7K4KrGgtAF5LxXmnbeG9X6kBJbvfeh9j5krPraC%2BV8b6YDvg/MQz8T7vxYV/MmP8lF4H/i/MmQDkAgJPuAuWZMoEwIhHAjYZNEFKzJSgtBmAMFcvYpM/BTBCHENITOE%2BlCrnxxubIehqcyaPOYTgsRVhLAcK4fAXh/DMiCOEZiURbCJFSPiDIgBPDOh8ucBAVw3jggNj8R44xdRQ1RsyBGixAbrEuLsTkdRibnG%2BK0eYxxXj7G5B8TMLN7iLGBNWMEgJjSwmFxGZwAFsTFwsMbgco5z5kmnJIDC7umTEXZMwLkhI%2BS5bNNaQcip/gCZC2lhiSp1TJBBA%2BcXLWthxl90NsbM2Fty4LLthi5ZLsODrLriwBQF4qoXlBRGUYJzUkRwuTHahxrE7yDueanQIAMSkGeTnV%2Bbzq0axLnMiuVdVBHpPWei9aJRgQt3fETtGJ4WrqRSgGDY9FkoZAKe5IyRfrnqFr9S9BBfogZufPeIhLV7r13ifCle8D5KJPnSwQDLr7f2ZffR%2B7KyWcs/nKt%2BeBf6OAFYA1QwCYRisEBAtOUrISyoQaCRVzNlVpFVbCdVODEV8AIQoIhJCyEGsuQ%2BiQJqk4vsYe%2Bq1rDxE2CgXIp1AjOCbGESgT1FhJGfOkRHP1%2BSnGZBUe4PNabNGlGzbowomQY16LqPGxxNRA02N6KGnzAhk3RYLeMALObC3BeLSE5YZb46/uGf%2Bjg1dQOntahBmEUG22pM7RkhF/de39soKE4dIBhb2gxBiAm4s50qy6/4LpRXPmcDGXrLJBTEgExKVLfwKs%2BaSFFlwAWZghlywxH%2BkbS7EOhODsNxd3bGukBQekZwkggA)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/send/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/send.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/send.test.hpp)
