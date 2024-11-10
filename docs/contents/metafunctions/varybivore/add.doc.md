<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Add`

## Description

`Varybivore::Add` accepts two variables and sums them up.
<pre><code>I, J -> I + J</code></pre>

## Type Signature

```Haskell
Add :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct Add
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Add_v
{RESULT};
```

## Examples

We will add up one and two.

```C++
static_assert(Add<1, 2>::value == 3);
```

## Implementation

Here's the entire implementation:

```C++
template<auto I, auto J>
struct Add
{ 
    static constexpr auto value 
    {I + J}; 
};

template<auto I, auto J>
constexpr auto Add_v 
{I + J};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAbKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8XaYDmlCBEzEBBk%2Bfly2mPZ5DDV1BAVhkdFxtrX1jVktCsM9wX3FA2UAlLaoXsTI7BwEmCwJBpsmAMxuTF5EANQAkqSnx2cAUgfYJhoAghPEXg6nz%2BjoT88mAHYLKc/qcwacJkxHMhTmgGBNMKoEsRridUKcAG5iLyYEEvcEgoHnEGWU73AEAEQOwL%2BgKp%2BysLz%2Bm22u0wByOaIuVxu6Pu%2B0eLzhCKRKN5Xx%2BAH0MXj/kSScDyfTGf8XgB6ABUWu1OrVf01WoAKtghIbtXr1TqrRqLarXrVoZKmAolPUIN9focWqczA8QCAsd5cQd6RTTvt5tSOItaJwAKy8PwcLSkVCcNzWawQ5arYNmfY8UgETTRxYAaxAcbMADoAWZJAAOBtxjQATirGliDf2%2Bk4kl4LAkGg0pCTKbTHF4ChAI%2BLyejpDgsBgiBAywICRO5EoaG2dGioVY61UDdiAFpYpJTsBkDCpNWzLxMPgiMQ8Og9PxBCIxOwpDJBEUFR1HnUhdBaAB3YgmASTgeBjeNExLVNOAAeROTcCFOVAqFOE9z0va9b1Oe8zFOCAPD3egUXMAt5l4OctEWCAkF3BJ9zICgIDYjiQGAKQzD4OhNmIacIAiZCImCOoAE84N4KTmGIGTUIibRKjnQtdzYQRUIYWg5NArAIi8YAjloWhp24XgsBYQxgHEIy8GIDS8AxTArJTRFKhOdZC2CTZY1A2g8AiaDlI8LBkIIN9B2s0h3OICJkkwCktnskKjBLRYqAMYAFAANTwTAINQhJGHkgDhFEcR/y/eQlDUZDwP0eyUEzSx9FC6dIEWVAEg6KyzwmT0KVMSxrDMcdErfLAeogRYKiqZwIFcUZmlIQJpiKEpsmSVIBHWvbcjSXodrmVp2mqSYjvGNpXIELp6jO/pSiGbpbve57tteiRFpzNY/t7DgE1HZCJzw08LyvG870kB9yNwQgSBJOiGOyxYEEwJgsBiBbSArSR9mrVt9gBSQNEketYmHONYlbYH%2B1IQcC2rWIygbVsGzKONJC4ONSfiMdeAnKcZyLbLFxXFi1wwrcuJ46jDzYTg6hYDEATPJhYQMIwSNbasuGrLyXxId9P1kH9aukeqgKa0DdEEqCYPkhCQaQ0CJ3QjcTmw3C1Y1rWdfs/XDeN8jKPY6jUbMeiJfnZjWNQKjom3bjk6jgYA815Bdf41suBHGhaBEsSJNAxTZMqyvlNU9SHEq7TGAIPSDOQ4zTPMyzKtsjL1hTfAXKqdzPKfVQfM2SqAraZCQrC2TIv7hjYsqxLkqUNK7KMTLQATvg8sK4rSvKpNC3qq2/xt2Q7ZAlNHdarLxqsTq5/mvqBrSIaRpDJ/Jum6JZoeXgIte6y0/CrQYO4TwTR/CQJerMN6OQDrpGgWMRI%2B0OjwN2ndK6j0bqoI2ktDoT0piFF%2BuMfBmRCGTCwXMf6KxAZcDdqDYWKEODXGIOrTW2tc4hy4AbI2GhEamxovmJh6ME6Y2xrjSgbsmYswNpTAEAsAQAn2FTSQl4WisNFrYcWjEFxLlXOuTCadFYHiPKrThhEWAKAxDCDE/DqxsgmE%2BER5sWjnxqpfKqN9mogB7M7WC1lmEe3HGhOWWEcIcJYDYuxDinEuKwhRDOHFUYRgkUxRcScU6cR3Kk6iAZkAJASNKfhkoklOmsTbYS0Qy6SWkspaujSVJqQ0o3ZOOkW76UMgPTAJkzJiG7vFXu28l6kEHq5EeyFvLIF8lPQQM9gqhXCjJRe0UV7xTXilTeGVgi7yyblJg%2BUiolTKhVeKXjfwSCvoBRqt8dABIfsYDqNhX7ANTB/AQVk1QjXahNSwU0RYzXfEA3ql0HrgLWgQ2B6BaGIIwWkT6SDME/QQXoIh10PowpwZCkh8KMWUJgRQ7oBKmFLAYX%2BUJYNPacBiXE%2BxmJElQg8skpGr5UbiPjkxKROMBj4yCvIkAZgDb7H2HGFsfNhxioBF2Gl4TJx6NnBjAmIBJAAgfMorgUhWxKNJlwAEwN9hhJFpwTJpZgaPnlaaxVBj5iLESikZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/add.hpp)
- [unit test](../../../../tests/unit/varybivore/add.test.hpp)
