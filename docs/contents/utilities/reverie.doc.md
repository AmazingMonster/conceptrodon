<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Reverie`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

## Description

`Reverie` accepts a list of warehouses and returns a function.
When invoked by an operation, the function instantiates the operation with the warehouses.

<pre><code>   Warehouses...
-> Operation
-> Operation&lt;Warehouses...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the warehouses.

<pre><code>size() -> sizeof...(Warehouses)</code></pre>

## Type Signature

```Haskell
Reverie ::   template<template<typename...> class...> class...
          -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Reverie
{
    static constexpr auto size() -> size_t;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;

    template<template<template<template<typename...> class...> class...> class>
    using UniSnow = RESULT;
};
```

## Examples

- We will create a `Reverie` with warehouses `Warehouse_0, Warehouse_1, Warehouse_2, Warehouse_3`.
Then, we will transport the warehouses to `Operation`.

```C++
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<template<typename...> class...>
struct Warehouse_3;

template<template<template<typename...> class...> class...>
struct Operation;

using PackedReverie = Reverie
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

using SupposedResult = Operation
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

using Result = PackedReverie::Snow<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Reverie`.

```C++
static_assert(PackedReverie::size() == 4);
```

## Implementation

```C++
template<template<template<typename...> class...> class...Warehouses>
struct Reverie
{
    static constexpr size_t size()
    { return sizeof...(Warehouses); }

    template<template<template<template<typename...> class...> class...> class Sorrow>
    struct Detail { using type = Sorrow<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = Detail<Sorrow...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2BpwIAE9UoxWJgAHRwm6HfZMBQKOEwhFIlFogDqLUwCDWSgUNye42IXgchwASpgAG7xPD/B4mADsVgeh05h1mjmQiIE40wqlSxG5eAAXpgAPoEMWSiBLJ5c45sw7ETAEdYMOWYVBUNEQXHqgleImKgIWFUAESeSq5gL%2BANeQJB32djtB7uB/1BEKhbDRGIMWPhAWwiODqND4cxCkOQhIxFQAHcSRyuWSKbKrRqmHQVZbTeFgIdwZDjgErfHEymvkb8YTMFH0WGTpbWTaLbb05yHd6nb9%2B57B66%2B6O/cwA9GI8jm0HZ4GwzOQzCE8Qk6nWz3DkWjPGGCmK1Wc806F81xvF9gQCAyz72Y8WZ2H08APQAKk/X%2B/P9fb%2B/hwACrYEIgFCIc35/g8H4/rBX5QY8zJmLsDD7F4RxfGgqGYKkBDEluiHPF6o7ET63wTtCV7LnOBGZpS9YmkoUoaG23ZESOZFjpxFFTi2MaRlepIEOS9F4ox0pcKxzIPFxA4utxkKTrC06xoJDx0bKDGNlKZhSYRsnDvJAI8cpfHUWp9waYcWmmtKAR6U8BluhxckeuRimUSpAleQu0ZCSJsoAPKQsQwLZA50EAQAYngxDjIc2CqKw7yYBB8FsbuJbKEwyAANaYOgNL0sQjJHtSdIMkyjynHanI2UxGikMc271RJTW1dZYnaWY7UtV1tlSvZzKtl20n3Jl8ZeKkRQFTSCheLQsonFWwXxGFAi2jVfXGtpjXNfcyqtVKKT7Yd/VMT1p1ckdQ3Vbco2ERNc0LUtlaHNleWzRVJXsCAQgHpubiraFDQkg9QlhcgUqzvEBAQBcN4KNC0P4W4z2LU1QhTTNhVNi9Nzmi%2BkVfvGmBYegCVJb8qWQWxPJ4FDMOtBAH35bjxWMojEqYAqR7LYckiE08HArLQnAAKy8H4HBaKQqCcG41jWNyawbKlOw8KQBCaCLKy5SA4saDCZhmAAnAAHBopvi%2BbiQBJIZgspIiT6Jwki8CwEgaI10uy/LHC8AoICNdrMsi6QcCwDAiAgGsBCpF4BDkJQaBvHQ8SRNCnCqLbAC0iSSIcwDIHyUjG7wBWECQeDoHo/CCCIYjsFIMiCIoKjqGHpC6CkyahaknA8KLEtSzrcucIFicJ7KeqHDniT54Xxel5IxuHBAHhp/Qooa0svCh1oKwQEgqepOnZAUBAp/nyAwBSD1NCLfEQcQDEY8xOELRgoPvAf8wxBgkCjEbQZNQ6a1TmwQQgUGC0G/l3LAMQvDADcGIWgQduC8CwCwQwwBxDwNiqAvA9J0GyyFGTROWxNbhBeGLLutA8AxFCgAjwWAx7CTwJ7DBpBioxAyJgHM2CjD0KMDrFYVADDAAUAANUZMmVa0tNb12EKIcQLclHtzUGPHu%2BgcEoCVpYfQDCg6QBWKgXC2R0G5wuMtUwlhrBmD9sVEqWBjEKm6IQ5wEBXBTD8CkUI4QhiVBGCkIoWQBA%2BL0KEho8xhgJDGHUDxjQJhtE8B0PQdhEl9FaDEoJcTbDJIiWMZJOTFhcBWAoVWmwJDDw4JLUgvteD%2BznnnAuRcS6HDLmYdeuAq472QmU/eoiVgIEwEwLACQ3H60CDCU2AQnYaAds7b24tEim1dhwd2pBPYBC4DCZIiRzYWy4IkcWkguDi1mS7Bp48A62GDlrUREdo7H1jlPROycr6oC3hnLOHAWgsFpCyXOTAZx7i4KbGEuzSH4CIM4uushG6qOkOopQmiu66B6n3JgA8ME1Lqdc/2k946J0OLPf5gLgWgpLOCyFMINDr03mfbexxkJmD3g8sOR8T5fKZfED519t4gHJUCpERhwVcEao/F4cVKBvy7n/L%2BP9SAKoAUAkBDglUQMYAQaBsCx4IKQSg2gaClVYJwXg2W%2BB1QOCIU2MeZDkAUKVdQuoY96GMK/iwrYst2GcM1jwvhAjzXFkeeIpgkiZGYDkYpJVSjEXN2RbIDRndZYYp0SI2xVgDHutcaY8xApOBWIIOgGx%2BiLAOMaU4mudqTHuJtZ47xqT8h%2BIYOgEpwS0gZDCTkJtvjO3FGyO2vJGT61JP6IUutDQskDACQsDtsxJi9vScU2dsTqmrHWFUsp6z8VjyacKylorqUQqhd0mFJAWU7PZQfXWpARljJGG42hmztkQoWSyC5LIWT2zMM7M59S92cEDvcm9R9nlIDjtPflPLz6ZzYJwf5rSWAKFpHyWkNK/jjArueuFKQ40qITa3eQqKU06BAEELFOKh47tHl3QlbyZ5UEOIhwuyHUOHHQxCzDsoN4weZTsAI17HkvIFXyy%2BomEioemlKTjUpuPQ2ICwAufA6DSpfnK2WKq4Gay02q0BmqvmQJ1TAuBlrMCIOQag9BmszVCO9ZgghNriH2tUOQl4zrBCuroQwphYIvVsJKn63gAalBBqESGzlfAJHSNkfI2NCKCMSETW3EjWjyPpuMGWwxMRc1y3zQwdBr4EaZvsY4%2BIzia1uJHQ0FwraJ3%2BPKGukJXaGgTqiYO1duT0kJNHdOid1Xegrsa11op46l2jeyZ10p5TKnNzxbRv2nBmOKaQyhtDGHvTxQgD02Fl6BkcsPsM0Z4zKA1JfSAM2MIAgBHFobM53trssgOQBujQG7khyGaQKZEKv0aHBQsrgAQTksjMKc9ZAQFuNLe6BmpZhIc3MGZylYxVMjOEkEAA)

## Links

- [source code](../../../conceptrodon/reverie.hpp)
