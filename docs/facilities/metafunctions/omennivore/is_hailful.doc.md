<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsHailful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-hailful">To Index</a></p>

## Description

`Omennivore::IsHailful` accepts a type.
It returns true if the type is a packed `Hail` and returns false if otherwise.

<pre><code>   Type
-> Type == Hail&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsHailful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsHailful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsHailful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike;

/**** Items ****/
template<template<template<auto...> class...> class...>
struct SailLike_0;

template<template<template<auto...> class...> class...>
struct SailLike_1;

/**** Tests ****/
static_assert(IsHailful<HailLike<SailLike_0, SailLike_1>>::value);
static_assert(! IsHailful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsHailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct IsHailful<Tranquil<Melancholy...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFAAJJh0KheWgAkwAdgsV2mjmQVzQDFGmFUyWIV2iqE8VwAbmIvJgrsSLFQxEpiQARcGk4WiwnnIEgl4I87gtwAq7Kq7Sh6yhVq0EIiFajW64HqsEQpheIgAOktiKpBgUCkt5utyFt9qtCWwNqYdodTpdVwAKsRDABHLx0UhKlV642Qw3azVx/VuU0Wt0e51e12O92e71p3NZgCyNUMyAQnihhPdyIIqPRNyxONoeIJEMDIbDrbcxYMDDLFZ91er8pJZMaFKpAlp9MZzNZHO83N5ta54oSYqJIvXkouP2%2Bfy%2B2yu2FUrAe3PeAMPe%2BOO8PVwAapg7TU3repYmY9GdbGZV/Pz%2BKaoIO6YuiBBbgRmebZki5womiBBXNidChAA1jqVjyp8%2By3NKChvrsfzfgmf4/sRJpmsB%2BZQVmvqZiBNZ1ohQhNmhmAAPoaBKWGAgBJFGmRfEUamMEQdRYFpoxCFXCxKF4Oh7FcNx/zYdc/rPgQ%2BGXnB454Mg7GZnEBAQA2yHNviCpmWxCqybQbGcaQMmsfJHFKUO2AgCAC5cgsynknpBkvs0EBgGAGJmS2CphAQiKed5mC%2BeuHBLLQnAAKy8H4HBaKQqCcIqljWGSKxrEuZgJDwpAEJoyVLKhIBpZI5oaAAHGYZgAJwdVwaWtS1XBEkS0ipRwki8CwEgaIEWU5XlHC8AoICBNV2XJaQcCwDAiAgCsBDJGa5CUGg9x0HEETwpwqgtQAbAAtNdkhXMAyCUlI5pmLwmD4EQxB4Ogej8IIIhiOwUgyIIigqOoq2kLoXCkAA7kGyScDwKXpZlNW5ZwADyZr7YhqBUFcV13Q9T0vVcb1mFcEAeCd9CMuYFULLwK1aEsEBIMdySnWQFAQDzfMgMAUhmHwdBAsQi0QNEWPRGETRQqjvAK8wxBQjj0TaJgDgq6Qx1PAQOMMLQysw1g0ReMAya0LQi3cLwWAsIYwDiBbeDELrjhss%2BWN0rrZobJV0U1FjtB4NEQYax4WBY7WeATY7pC%2B8QzJKEKwKuxHRg1UsVAGMACgPngmAIzjsJZZVgPCKI4hgzXkNqFjcP6K7KDWNY%2BiR4tkBLKgyR1A7t2jOg4JCqYhWWGYs2p79WC9xASx2N7mQuAw7ieG0eghGEAzlEM8MFBkAgTH4R9pCfDCzIM8TwyvDjdGMLRb7k981KvAg9M0N8H3ftjPzPnoaYP895zEPsvEq6wJDow4BlUgM1eBzRJjde6j1nqvSajTCAuBCAkB5OVLgrMqp5yWAgTATAsDxCXqQeqkgEjmg6gkIaGhJBmEkNdKaaVrodX0JwMapAJoVXNNdLg10WodX6tdRqPUmHXQQVjOaC0lokNWpzLaXMdr4wOgLIWjNzpsE4E0FgbIiS3SYJ6IwVMOrmi4M1T630SB/QBrIYG9dpCNyUM3GGuhxZIyYCjR2sD4GIOxhwPGe0zRXCJigsmj0MxWK4DYuxGhab015ozAhCQzDEPZmtTRei4iHUFqgBmQwEmi26oEGgtApYyzljDNWSt9ZNI1lrHWetk6G0YMbU25scqW2trbe2%2BtnbZw2AMz2q9fYOxygHZAQd9ahxGjlCOUclaxwmWzX6SdKqp3TpgTOLsjA51AGovghdi6l3LpXfWNc3Ggw8bIJu0Mcq%2BLbrnSeVhLDd2iIvfug9MjD1HuPL51gZ5ILnn9P2fdOifz8BAVwQD4a71KLfPQx86jItIJizIv95jvy6F/QBr9z5wsfsSmYYD0X3xJTkMlIC%2BjUr/jA5YqxoFEL4XAzGMNkGkzQZY4A1jbHNVprgn6WSiFs1IaQchlChg0JGgIoRNjWFEjSh1QaSR2EPXhqEpRtgVF5PUfATRu0CbFMKcQAxGxjHkxYAoNklI2RJPNNqUYDi8HzxcUDOujzwbyC8a8nQiREbIxVsEnls1cbaMJsTVQ9rHXOtde6xCdNSkZLiFkhIuS87rW5hmvmlrC2My8sgZIyR2Iuo6uxVN7EE0eMlnEep8tFYaxaW2zW2tvb626YIE2ZssaDJtmIEZycxknK2aQfAXtH4zP9qoQOQIlmCDDjDNZ0coSbPjjs/W%2By0iHKzicsIZyOYXKYEXEuZcK6MDua4v1EgnkQyDS3UNvZjCdx%2BWs/5uVAVTk4JsUeHcp4WAhblKFC94DLw/hShFSLSU7w3viw%2BOLL5YoQxfQoeLmUEvJXUb%2BL96XAJg/h5%2ByH/6MuxYy8jrKFBQNBpGhRvLOAk0TU69kKbZSjDFY4pmhDc1qLIRQqhlBYHKpAJ1c0CQEhpV6pILgU1pNEnEUx6N81DXLRlXQtKjCBpEimi1SQ3UuBtTMPIkaCQo1IM4NKwTXKPqqes%2Bp41SxU7pGcJIIAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/omennivore/is_hailful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_hailful.test.hpp)
