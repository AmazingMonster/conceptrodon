<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Agent`

<p style='text-align: right;'><a href="../../../index.md#higher-order-modifications">To Index</a></p>

## Description

`Mouldivore::Agent` accepts an operation and returns a function.
When invoked by a packed container, the function extracts the list of elements from the packed container and instantiates the operation with the list.

<pre><code>   Operation
-> Container&lt;Elements...&gt;
-> Operation&lt;Elements...&gt;</code></pre>

## Type Signature

```Haskell
Agent ::   template<typename...> class...
        -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Capsule<int, int*, int**>`.

```C++
template<typename...>
struct Capsule;

template<typename...>
struct Operation;

template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

using SupposedResult = Operation<int, int*, int**>;

using Result = Metafunction<Capsule<int, int*, int**>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Agent` uses partial template specialization to extract elements from a packed container. Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxAGkAA6oCoRODB7evgnJqY4CoeFRLLHxXIF2mA7pQgRMxASZPn7ltpj2%2BQy19QSFkTFxCQp1DU3ZrcM9fcWlAQCUtqhexMjsHASYLIkGGyYAzG4bWzuY%2B4cAnomMrJgAdPf72ADUyAYKCk8A8lfETJ2PJg0AEFhsQvA4nkDgIwCICgSZ/FZgU8UU8jts/qcDgRLtc2ADkajQeCCE8ACKYOp0J4Iqz%2BMn7JHwwko9EnM5szEc3HMNj3W6PF5vD4eQRMMJxUhonk3fnYehsQQKAlA1FPYkQilU2hnUVU8LEM7yzYwhT8gF7bBwtW0p5eVJGaVXGl7MlfH5/dJGhWm82Wxk0%2BmMuHW1Gc3bYmV8%2B5Q4iYE1KlVq%2B1hYBPACynnQLrdWvFOoOsfjioIZoelpAIBxV2DwIRDL2TLhAHoAFTtjudrvNludp4AFUwww%2BnZ7wLbXcnHbHzPhZj2YVeXiwLrcXkctEI5xV5gXDCXK7OyGG6CwVB388X3kPBzQ%2B8wiVLO%2BB4axFyuvLu5atwI1pLcTCJAoXj0LWs6vtyH6yt%2BcJ/u6cSegIYFwhBkZQdGtxAsQwDKv6wIpo66aUkwVBePunQ5pC0KCGc3wIf8FYgJmtDoGcWE4X6VqNiG%2BEOmmQheIkuSYOgABKQ4gaS%2BxunRvwMW4YQEFKimtspgjthaTa8amTzicBtBSa6GbEaR5FegcAFASBb6KWpBCqU8KmthaXFaSCdSOMgAD6TDvHEBAQCelYKDcPm4W4emSVKAlCSkImRQZjxzIyHALLQnAAKy8H4HBaKQqCcG41jWOqSwrJgNLzjwpAEJoqULAA1iAGUAGy3AAHC1UgZf4LWSAAnHsvXzvonCSLwLASBoGikDleUFRwvAKCAM21blqWkHAsAwIgIBLAQiTruQlBoFsdBxBENycKonUALR9U8wDIMgTxSLcZi8CJhAkHg6B6PwggiGI7BSDIgiKCo6jraQuhcKQADuvyJJwPBpZl2V1flnCfOuh2kqgVBPDdLX3ZIj3Pa9kjvU8EAeGd9DEJVexcHMvBrVoCwQEgp2JOdZAUBAPN8yAwBSGYfB0BsxDLRA0SY9EYT1OcKO8ArzDEOcnzRNoVRrdVp0lp8DC0Mr0NYNEXjAABtC0Mt3C8FgLCGMA4hm3gcbVAAbkOmOYKoVTrms1WKe0mObtEvwax4WCYwQxB4JN9ukN7xDRHFFJO0Ym5GHVCxUAYOEAGp4Jg8N0Tl1UA8IojiKDVcQ2omOw/ozsoMVlj6Hg0TLZACyoI%2B6R27dJ7SaYljWGY80p/HWA9xACyVNUzgQK4YwtEEDDoNMAxlEkKRpAIa96LkB8MNvJSDHDi%2BdN0oyeM0ejXzUIy9BKMyX7YL9H1fL/n7MLOLGWKsCQaMOBZVmpjBaRM7oPSei9N6Zgaa4G%2BozXcLM2a5wWAgTATAsDxHnqQJqkg9i3EGv4SQGhJBmEkC1aarV%2BqjQ4ONUgk1ma3C6i1dq/V2pcBahlSQXAMqDRahA6GC0lorRqrnTaO0uZ7VxkdAWQsGaXTYJweoLBPb%2BFukwIUztXr9VuFwW4eUvpEBnv9WQQNa7SHrkoRu0NdDi0RoBFWoDwFzV4AtHGB11xPAJk8DRWidF6MdFwQxxiNA0zprzBmTMzCsyketTm3NUD00lEotJsTBhBO0a8Z24SuAzRoAZOIMs5bQzVkrFWpAqkay1jrBwNSDYwiNibTG5tLbW1tjUx2ztXZ5XwB7Rw3s7amP9sgQONSQ7pWhuHSO5xo5rDynHBONSU5pyUBnfpqZpH5yYEXEuZcPw1KrtYkGtjZANyhnlJxLcc5jysB3cOc8%2B4DwEEPEerpHkTynnEGePte5tA6OkFwm9v4by3m/Hex996dAhSfTof8P5PwELfRo99xjAt1s/KY0KL670mHfLI68iWvyKDCgBCgyrAIAbMjxkDOCBOIJo7Ruj8lhIiSYpB%2BBzFM3QUkjmWCcF4MoKA5hrDDGUP8EI/w/g9hUJoQI0R81OASNWtIrau19p42OoLLJfNVFrA0Q9FgChPYvU9uE24JxhifV5T9P6cMzk1wuWDeQ9ibk6BAHsBGSM3GMIZWI7GCj8aExNWTM1FqnhWsMba0ktMDVxN3HsRJ7MNpyOURkk6SbBgWqEl5WNXl40%2BRZX1CWpTpaUAqXlOpptqp1oabrZpaTDbG1NoMzAFsrZiB6UnPpWdlkO3dji0ZvsJlTKTjMsOXcFlLNjvHRO1UNnp02DsnOyS%2BAFwUMXUu5dTlWNdRIS54NPVNx9fc4w7cbAvPgG8zodtmxBR%2BZYSeXjp6/UBQQ1FfgV7gsxevEI%2BL/57zyOkBFcL0jIsJe0HFaKv4AcfrBpeXRf7AZRQhklj80MUoJSAwB5V8P0oxsGjgzKWCmvNZa618aeUoP5WmzBpBsG4MGAQ2ZEqQBmEMXsPYGUMqUKKRoXjvV2oqq8Wq2wkj01zEaiAYhRi9jtX4fOATLV5y9UYXsEjqrFqCvqowj64msZ6ZkwsFOqRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/agent.test.hpp)
