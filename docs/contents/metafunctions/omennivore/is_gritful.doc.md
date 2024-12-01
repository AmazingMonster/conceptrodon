<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGritful`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-1">To Index</a></p>

## Description

`Omennivore::IsGritful` accepts a type.
It returns true if the type is a packed `Grit` and returns false if otherwise.

<pre><code>   Type
-> Type == Grit&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGritful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGritful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGritful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_1;

static_assert(IsGritful<GritLike<CoolLike_0, CoolLike_1>>::value);
static_assert(! IsGritful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGritful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct IsGritful<Sunshine<Consistency...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAOLEhFRetDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXiCLFQxEoQQARI5gklkoFA7a7fbXB5HNxA14s140vZMA7Hdl0xk8znXbk7Dlck7C3lC2kCvnnS5sAB0ipu0IMCgUivlyuQqvVSsO2BVTDVGq1OpN%2BsNxr1Bu1RoUryEXlhCDCmFIzNZ/NFXsFYql3vF0slIt9ZwuzAV1stus1FttVtjNrNUfjMdNdo1HlheDhDGQpyp%2BqBTxeBA%2B31%2BBH%2BgOOjudrsZWYyufz5tuRYZoPBTUh0IEcIRSJRaMx3hxeIIz2uiVJh3JM8pDIeAHoAFTrjebrfLoFrjevAAqmDG9s3O5XW8vZ6pDx9fMDAf9oYfz6f97f3NlEcwbejv9T/7Jomf4pkBNzFpOpavD8hChAA1oKVhLvcd7BhKfohu%2BmFoUGJxflcgEZqBRHAQBxEJuBDwlm8HiePBmAAPoaIuwK3i%2BWHoahGGcexn7hgR5FpnGYHCSR6YUR2jyQTRqK0PRDFcCxEGcngyAMXacQEBAnwwVWAKMrp9GNrJ8mBK8tFyXgCEKeB%2BogCAo7YosLEQqp6lqppEBgGA5a6dWjJhAQNz2Y5mDOXOHDLLQnAAKy8H4HBaKQqCcEyljWOCqzrOOZiHDwpAEJokXLHBIAxWY8qJGYkgABw1TFGgAJzlRoABsNWHPonCSLwLASBogQJUlKUcLwCggIEhWJZFpBwLAMCICAqwECkXgEOQlBoLsdBxBEVycKoNWtQAtK1kivMAyBQlI8pmLwmD4EQvzoHo/CCCIYjsFIMiCIoKjqNNpC6FwpAAO7EEwKScDwUWxfFRXJZwADya2rWWqBUK8h0nWdF1Xa8N1mK8EAeNt9BIuYeWLLwU1aMsEBIFtKQ7WQFAQEzLMgMAUhmHwdDbMQ40QNECPRGEzSnNDvBi8wxCnEj0TaJgDhS6QW1sIISMMLQkuA1g0ReMAbhiLQ43cLwWAsIYwDiHreDEMrjjoseCPwsra2bPlgW1AjtB4NEENyx4WAI5OeB9ebpDO8QKJKMSOzW37RhFcsVAGMACgAGp4JgoNI%2BGqtvcIojiN9Rd/WoCPA/o1soNY1j6P742QMsqApPUZvHWM6BHMSpjpZYZjDdHz0uy3XSO1kLgMO4njtHoISuvMwwg4UmQCJMfir%2Bk68MHMQzxCDdiTwIvQTHPeRH7UJ8NOM/RLwfegzOfuRb7Yd/7xUK/LAoWUbBIsMOBxVIENXgI0sZHVOudS611JC3WJrgQgJBcS5S4NTAqKdlgIEwEwLA8QIAlX8IceUjVDiJACJIaqrUBoxVao1LqHAeqkD6nleUrUuDtUajVDhMVJBcBiqQ1qICEYjTGhNDB016YLQZktVGa0Nrs1QGTXa%2B0ODNBYOiRIx0mCGiMATRq8ouDyiSg9JBz1XqyA%2BqXaQ5clCV0BroXm4NIZS0AcA0BiMOAoxWmtV4GNXjqM0do3RwB9GGOMcTUmzNyYoMOGYdBtMZoyI5uTBRKThiBK0baIwXBGpcECDQWgAshYi0BjLCWqtylywVkrFWkd1aMAIFrHWCN9aG2NrQU2qtLaJ02ElfADsHB4GdmbExqh3bbFVt7aKgM/YBwlsHPpNNfgR3ytHWOmB45WyMEnUAki%2BDpyzjnPOBdI5FysV9GxsgK4AySo4muyd%2B5WEsI3aIzcCHJXblkTu3de5POsEPMBI88BYHeT/a%2BQznAQFcJvBeM9P4LG3kULIsKkW7wRSvCekLb59FRVi%2BoZ975lEfkfO%2BeLn5EsGF/Q%2BP8/5fTcfDQG4DMnBOyaE3J4SNAIMesgymaCaaYNINg3BwwPkzKYSwgxGhJCJAEYkRIhxKGSDOiDDxojbDiMSVI%2BAMjlpozSUo6JKi2CcHUbjFgCh0RQnRByukYx7o8vMSDc5JdLk/XkHY25OgQCdWcVDc2DLhFMuRnI9GmMzXnQtVajEtqBRjEiYalmsTDgJJTrNRmibUls3SfEK1KQUgMRtY1BidqCDqWICwM6fMilxBKaLcWctKkNvlorR2qsGma21rrfpmADZGxNmbfKPSdlLNIAMyeIzXbjOQB7KZggfazP9oHU4izQ4rNVus9ImyE47LCHsumBymAZ2zrnfOjBC6WNdRIK5v1PVVx9Q84w9cXlzLBZ8junBlzdzrgPCwgLkrAtBfAcF3QoUwovm/RexLqV6DXvUPFcGsgYsPvinoZKINPwhQSj%2BD8YOktxRh/DLRkMAJWGsf%2BaCGHuJEZwAJFbzWWutbG7Y8aICIKerE/lEi6ZYJwXgyggCJUJAMYcQ4MUGp8IGqJxI7Ug3DU4GIyagrSoyturKrgUhGrSsSKQrgyQZmHEZfJ0a3HioMLunJsBCnTOLGWNHDIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_gritful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_gritful.test.hpp)
