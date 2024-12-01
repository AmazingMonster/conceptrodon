<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsSnowful`

## Description

`Omennivore::IsSnowful` accepts a type.
It returns true if the type is a packed `Snow` and returns false if otherwise.

<pre><code>   Type
-> Type == Snow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsSnowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSnowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsSnowful_v {RESULT};
```

## Examples

```C++
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike;

template<template<template<typename...> class...> class...>
struct FlowLike_0;

template<template<template<typename...> class...> class...>
struct FlowLike_1;

static_assert(IsSnowful<SnowLike<FlowLike_0, FlowLike_1>>::value);
static_assert(! IsSnowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKQgyoAO5UXlod3uJkSFleM0cyFeaAYY0wqhSxFe0VQnleADcxF5MK9QRYqGIlKCACJHcGk8nA4HbXb7a4PI5uYGvVmvWl7JgHY4c%2BlM3lc648nac7knc6XNgAOhlNxhBgUChlUrlyAVStlh2w8qYiuVqvVryEdEYG1ILLZArFVqFJxFfJ5EuY0s12rVuo1Kq1Or1rp9nqEJGIf2pWuBTxeBA%2BXx%2B/0BTON9AYGwTQb%2B%2BrDYcZYIhTShMIE8MRyNR6Kx3lx%2BIIz2uiTJhwpdapjIeAHoAFSdrvdnut4EdruvAAqmDGCle3b7bZ7M8n1IeNv59sFS7pK%2BFa%2BtTquGbd6t3/oP7t9XtuDwjb2%2Bf1CAGshVYW/dFxvRbbn%2BKLs7MEf937j56bnDatI1eAAxWhrzwO8AH0NGbEEF2Xa0kLfFD%2BW3F1T0PP9f1PIDnjecDIJgrh4KArk8GQaCPTiAgIE%2BK84yBY5GNvW0iN%2BNjYNIMCIM4qDMGg0jM2wEAQHLHFFngyFKOoxVaIgMAwGjRiAWYtwwgIG4xIkzApIbDhlloTgAFZeD8DgtFIVBOGZSxrAhVZ1krMxDh4UgCE0QzlhvEATLMKVEjMSQAA4QpMjQAE5/I0AA2ELDn0ThJF4FgJA0QILKsmyOF4BQQECTzLMM0g4FgGBEBAVYCBSLwCHISg0F2E1iAiK5OFUELYoAWliyRXmAZBoSkKUzF4TB8CIYg8HQPR%2BEEEQxHYKQZEERQVHUYrSF0LhSF%2BYgmBSTgeCM0zzK86zOAAeTq2qo1QKhXk6nq%2BoGobXhGsxXggDxmvoZFzDcxZeCKrRlggJAmpSFqGogKGWpAYApDMPg6G2Yh8ogaILuiMJmlOY7eFx5hiFOK7om0TAHEJ0gmrYQQroYWgCa2rBoi8YA3DEWh8u4XgsBYQxgHEVm8GIKnHAxUcLoRKm6s2dzNNqC7aDwaIDtJjwsAu6s8DSvnSCl4hUSUEkdiF1WjC85YqAMYAFAANTwTBfiuz8afm4RRHEFbPfWtQLp2/QhZQaxrH0NX8sgZZUBSepee6sZ0COElTHsywzGyo3pqwKOIGWOwJayFwGHcTx2j0EIwkGCphl2wpMgESY/Hr9JG4YOYhniXbC4cHpxlacu8h72oi4EXoWk72vu9sAfm70GZJ%2Br%2BY64LpyNgkU6ODM0gst4HKnq63r%2BsG4bJFG77cEIEg8VcrhgY863lgQTAmCweJ89IXzJEOKVIsORIARJDBVihlEysVIpJQ4ClUgaU3JSlilweKkUQpIJMpILgJl/6xV3hdHKeUCqP2KuDCqEMqq3TqrDeG/02psE4M0FgGJEjdSYDqIwH1IpSi4FKKyE1r45zmrIRaPtpB%2ByUAHLaugUb7UOoTLeO896XQ4DdGqdVXgPVeAwphLC2HAA4Vwnh31frQ3%2BrfQ4ZgH6gxKmQ6hcQqGoD%2BsMLRzD3RGC4JFLggQaC0HRpjbGW1ib4xpoE0m5NKbUwNnTRgBBGbMwumzDmXNaA8xpgLC2mwrL4HFn3KWvNeGqDltsGmStjJbVVurfGWsMkg2mvrdyRsTaYDNoLIwltQDEL4HbR2ztXbuwNp7YRy1RGyH9ptKyUjg5WzTlYSwEdoh5xjnHLICck4p2mdYTO%2B9s4zWltHLoY8/AQFcPPXaVcyhdz0A3eoJzUht3qFPBYI9ujjznkPFu%2By%2B4vNmMvC5PdXm5HeYvfoPzp6bxWGsDe98oEKLwZwTRxBGHMNYa4vR7iDEaEvpNG%2BgN74gyfqQF%2Bb9hif1KTAuBnCNCSESFgxIiRDjAMkH1Xaij8G2EIVYkh8AyHVTuvYxxrV2ocAYa9FgCgMTQgxGi%2BkYxxpYoEbtAZ3shmrXkOIsZOgQCJRkUdPm8jzpbRyiou66jHrCv6qK8VmIpWCjGEYhxJi4hmMOJY62pVIb2phhQOGHr/riWQCkFI0FJWRWgtKgg1EEV9VRj4uIficZ41JsEhNZMKYSxplEhmTMWaZMwOzTm3NebuTSa06ppAslF1yTLApyB5bFMEMrMpasNanCqTrWpNMGnpCaebVpYR2lg06Uwe2TsXZu0YB7IRSqJDDLWmqwOmrJnGDDrM8pCzrJLMLJwVsSdQ7pwsJs6y2zc7wALqPT5hzjlvMrqXB5ddblFCyDcq5WRb0z17vUCeg8AULzPR%2Bger6F7/Irn8755zQVQoUOvZaercEGrhWa14FqJXWu2LaiAV8ppmNxUQsGz9X7v0oFvMlCROGHEOCZCKGCMpkcSPFWD2VOAEMKvi7%2BiRRrUq4FISKlLEj/y4MkUphx9UMdyjh7yUCxr0f3oxsTixlhGwyM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_snowful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_snowful.test.hpp)
