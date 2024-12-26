<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Diversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-diversity">To Index</a></p>

## Description

`Typelivore::Diversity` accepts a set of nonrepetitive elements and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every element from the previously provided set and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside a `Capsule`.

<pre><code>   Es...
-> Args...
-> Capsule&lt;(make set)&lt;Es..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
Diversity
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct Diversity
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will use `Diversity` to append `int, int*, int**` to `int*, void`:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Diversity<int*, void>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int*, void, int, int**>;

/**** Result ****/
using Result = Metafunction<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Diversity` is implemented as a shortcut to `TypicaDiversity<*>::type`:

```C++
template<typename...Elements>
struct Diversity
{
    template<typename...Agreements>
    using Mold = TypicalDiversity<Elements...>
    ::template ProtoMold<Agreements...>
    ::type;
};
```

[*Run this snippet on GodBolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAc0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcBAAnk8APoEYhMQgKGHYYHA367G5uJipBReeifA6AgiYFipAxUmFwxGMViYAB07KxwPGxC8DgJRJJ9BhVkuwKpNLpmAZCKezDY7NZAEkGAong5MOhsPQ2IJMYFsZdubyCDcACqIvCiWh3PAANwSxXhIBuqS8sVolpu43QIBAMswSLwWEEhHhDOVqsw6s12sYBD12AVOIA7CKgT9tjcAEpR9aZe38pQgYE3Us3cW0pj02H%2BuWYG4RtWOIxa6lx0jlpl1hU58atnXxzmXMte1HGm7KYioIgAWU86BLZZMqcXI9LXkyRk7T2hgTuo59KAE%2BAaYlXa4Z57XZe9vrwCiRsSYSiRqCol%2BH16/pdvfqZgeDRwEXDFUmwiYB%2BzjLFSCvb8y3NVJLTEG17WIR1YOvLFfVtMQvEwDsMLXBCkOtO0HVDAjPzgs0LStFDyOA2FGyjKkYzbXUFQ7ZiHHAyDBCHC5vywv8nl9CtJQnKdZ3nBlewIPj4yTfUxKZYVz2XO41NFDMbgsZ960JItz3EqspRrLsWQbUCWN42N%2BP1c8jT5Sdp1QOdaAXJjrJ4ls7IIASR2XNNvw3cDt3rGF91/NAGBPbIzyoi9YUIkdf3vR99Nfd9ksS6ifwIQ9/QAuNQxAyMfIgvzoJSr9iLosi0NK3Kv2EnDvHw6FmuvQliVJMy3G41iFIUJTsEowS8p6wV%2BsGjVhs4qzyubSr2P8hyut3bAVKeLSJtLDTduM6lK2rRlZRZBVhoCstQq3dz0F3fcXOkjyGXmjkHMCNMDq%2BnEfn%2BAGAVxQ4GwlVaq2ycl9kBPFAf%2BQExWOyVpQs%2BV2Su9aLick16Ma4DRRXRKTNO2sLvZC5gGITBVoTc9buAG57semjEPq1D0Nhd7WWu0sxKR0zJNc%2B6GQpqmadG89trM77k0037tKuOGgf%2B25sFUVhaXrL5gaVik/pBMEGAhLwoQZGLNlSQdMZ1/Z%2BV6sltcuYn%2BtJtHucx7G7emw6VdtmdMGaKgvCNhoodORGJVMlHzrdi5iGAWnLnpxmA6YIOQ8hyL7gajm3AiAhdg7W1UCDATfWF2E44TiX5fTRXbiELxUiKDVe1JE1HYuZPG%2BbjJW/edvmamvqGXzwubmLoMO3z6fBH2Tla5t/E29oDu9aTzcGZXk0s/9wPg54gRR8EWeC9P%2BfPu%2B338VNd41%2BhrlmkcZAkWfJRWggX8FBZV%2B9TcbeOw9xbugbeWIljCg4CsWgnB/C8D8BwLQpBUCcDcNYawXo1gbAiqCHgpACCaEgSsAA1gESQrINBJDMGYAAnNQrg/gKFJC4MmZM0hoEcEkLwFgEgNAaFIPAxByCOC8AUCAPh%2BCEGQNIHAWAMBEAgDWAQV0BByCUDQDSOgCQogsk4KoJIAA2AAtPoyQNxgDIGQDcKQrIzC8A1IQEgQY9D8EECIMQ7ApAyEEIoFQ6hJGkF0FwUgAB3NEqROA8CgTAuBBCkGcAAPJeCUUkm4b4bh6KMSYsxFirFkLMDcCAHgNH0GINCHBSxeASK0CsCASB1GIRKaoiA9TNGJGAFIMwfA6BUjQpQWIsTYgRBaE6bgvBBnMGIPCeJsRtAsQibwdRA54kMFoCMxBWBYheGAISWgtBRGjNIFgFghhgDiH8fgKmPF7T7MQZgVQuYqTzPIIIOosSPSxDRJMjwWBYmojwNwg5qFYh9weMcowHojAEJWFQAwCcABqbxgnxNlE8lxwgrQeOkGinxahYmBP0CclAaDLD6DwLEURkAVioEttkfZhjvSRVMJYawZhBGoWIEGd48AVh2Bss4CArgph%2BCCWECIQxKgjCCUULIAghV6GlQ0eYwxEhBN5YfRoEw2ieA6HoNVDQ%2BitCVRKlVthNVytVZqo1iwuA8swZsCQUSOCwP4bEoR6SDHGNMeYyx1j8kQFwA40p5hAg2sqVClYCBMBMCwIkCAxCQCSECKyahgRWEaEkGYSQ%2BjeH%2BH0dQ/QnBOGkG4SG1k%2BiuD6KSNQph%2Bj/CSHoSm/RLr/FCJEWIvBULpFyNqQopJyimktJKdotgnAWgsFtMmQxTAbgQhOVY6hrIuDkLsSeRxPoglorceITx2KlC4v8boTpoSiTzMdc6gRvAhGJOSSaNJGTPUzoMFuLgC6l0aAKUUhpCQymBDMBUjtkial1NQMUhIA6QNfsSLOowL6uB8JoKvB0fSBlDMmU88ZwzpmzIcE8xZcZlmrNiRsrZOy9lPKOScs56y8CXMcNc2JdyHlbFwfnV5/j3mfPhN8rYiC/kAtwUCkF1JKPgU7TCpg8LEXIsYKi2QW7MVePkHuvxiDD0EshUyqwJL3kUrjUgmlAg6UMr3JpllbKEgcqwLpnldQ%2BV%2BAFbFc1IRYpWslaQBV2QnMedKGKhYbm9W9DNdq/IqrbPqoNQMXzyrdVBbyMK01cwovGodasdY9qbUFqdTEltnB3WZNMdBhmL7F3kIKQGogQbylhsAxGqNMbKCOqLSWhd6bkz%2BGoSwwIGas31ubYIzgbbxGdpkfIxR/aKDNIg604dWwx1ZJYAoW0ljbTFclOMFdganEbrkxiiQWLZA4pUzoEAwRj3hNGWe7L/WODXuUakqg6T5uLeW6t0y4wP1TZKT%2BwI/6qlSJ7YOsDE3AeJCW83JEK3qFIjWwQJEqgTFdMQ70iA/T/EYbQwc9HUyZlzIOXhwQBG1m8GI9ssQZGDkUfBTx4nNGbL0f8Yx5ASTmO8FY%2BwxBHHhncd%2BRy/jvBBNKFBSJyFgG%2BCwoUAizASKUUHM3btndB3lN4pO%2Bp4wxKbA6e5fpho%2Bzti3lM5YVll72Wcus90OzLhHPBfi6K8o0WpUZBlTka38rHeKqS9a834XYs6tCz0AQEXXMmtmJMF3FrEt2%2BSxlhQdqPGXb65e3L8PTELaWxPV7VJ3v%2BtXZVkNv3w2kEjdGkYen2FNZADQ1kgRAj%2BAYfW3h1fkyVoT3E4Rth21/aWPGyQ/hk3MOTLwlIdCuCULME29hgQruJ7b53x1tiW%2BtoA9UlY7NsgJqAA)$Done$

## Links

- [source code](../../../../conceptrodon/descend/typelivore/diversity.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/diversity.test.hpp)
