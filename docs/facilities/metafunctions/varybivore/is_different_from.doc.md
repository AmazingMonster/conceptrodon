<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different-from">To Index</a></p>

## Description

`Varybivore::IsDifferentFrom` accepts a variable and returns a function.
When invoked by an argument, the function returns true if the argument differs from the variable and returns false if otherwise.

<pre><code>Target -> Variable -> Variable different from Target ? true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom ::   auto...
                  -> auto...
                  -> auto
```

## Structure

```C++
template<auto>
struct IsDifferentFrom
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
template<auto...Args>
using Metafunction = IsDifferentFrom<1>
::Page<Args...>;

static_assert(Metafunction<1.0>::value);
static_assert(Metafunction<0>::value);
static_assert(! Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsDifferentFrom
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {false}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5glhyN5YANQmCW4EAJ7JmAD6BMRMhApH2CYaAILPLwSYLMkGn0duTC8RH2ABUmsBMARHu9RsQvA59gBJBQAETwVCocUYBAAYsRUCx3iYAOxWV77Cn7T7fX6Yf6A4EANSaeCY0Xo0PJlNh8II%2B2U%2BKIyiYEPelMOpP200cyH2aAYo0wqmSxH20VQnn2ADcxF5MBKLDc9SSUUcLBLTQkyW8uRSAPR20EIPAKfbJXqs2hSi7IT14ABeTDq%2BwA7nQvbE5Qg0owxZSHft0YcAGwaZnEVnsumpxOurDoeGYdD7JiukypsHECFQ1MAOjjFOpPyDdOOnJe4p5CIFqCFItbbkr1fb4pJ5uleFl8sVytV6s1Ou8%2BrHVDEShNZotZqJtqpX2bf2ODNQtdPL2AxEwX2xDwST13XnSRn5/cOCRR/MFqGFouO58v16CAop71ne26vA2e40i29JAieZ5Vre94dtyjQynKAgziqJZwS%2BEKXFqhy7mOPZ9r%2BbgvIhIGPCAICLsaxKWtaG5WjuLx2gAVFx3E8Xa7ycVxILYEIILcXxrwCTxvFsU2tKwUQIGUcASHvI%2BYTAPsACykJMFQXgMA4mRvh%2ByJohiWKCHiBL/Fw7a0T%2BA5KcBp7QqxEGvBOyCXKWSjNBA2mNHpBl1DZtYaDRdG6pgCzgS8nneQovkEP5OlBYZAj/OFd60fR0WxfFPlxMlYBgFpqX6elDA2RFuUxVaHBLLQnAAKy8H4HBaKQqCcG41jWFKKxrMuZgJDwpAEJoDVLAA1iAzWSGFATEgkGjNRoZjJsmZgABzbfonCSLwLASBoGikO1nXdRwvAKCAZ0TR1DWkHAsAwIgIArAQyRAuQlBoN8dBxBErAbKo23JgAtMmkj7MAyCylItZmLwRaECQeDoHo/CCCIYjsFIMiCIoKjqI9pC6IEIa3MknA8I1LVtZNXWcAA8kC318qgVD7GDkPQ7D8P7IjZj7BAHgA/QqpbFwCy8A9WhLBASD/ckgNkBQEAq2rIDAFIZh8HQnzELdEDREz0RhE0py07wFvMMQpws9E2iYA4NukP9bCCCzDC0NbZNYNEXjAACtC0Ld3C8FgLCGMA4gB3gl6GVqmAR51Squ0CGxjWEnxNWTtB4NEtwOx4WBMzceDHZHpAp8Q6pKCiXyx4XRiTUsVAGMpjJ4JgIYsxc7VjdjwiiOIBMj8TahMxT%2BixygfWWPoRe3ZASyoMkdQRxDozoEcKKmJY1hmJddcZlgq8QEsdiu3ULgMO4nhtHoIRhAM5RDPkaQZAIEx%2BF/hRMizEGPEQIN9Ko9HGE/XIYCai326GMPob85if1sIgv%2BehpjNGAR/UB19BrrAkPTDgrVzpMyujzcGUMYZwwRgtEWEBcBoyliNGWct25LAQJgJgWB4hX1ILNSQCRawAE4EjEkkBoSQZhJCplWsmER%2B0OCHVIMdUatZkxcGTNtER20tHzS4M1MRyYyFkyujdO64127PTekrD67Mfoay1pLYGbBOBNBYFqYkEMmBygMM%2BLgIjaxcDCijfARBz5Y1kLjce0hJ5KGnmTXQ%2BsqZMBppHYhpCLq8CumzL6QJ9hcxLMQTx3jfG7FjkLIJISNCi3FqrSWhwRpmFllYx6itlYEgaXEX6msunaw8V4iGFSjCBK4GdGgtAjYmzNmTO2Vt3bzIdk7F2bsa6e2xD7P2TNA7B1DuHd20cW4bE6vgJOjgU5pxRqoTOnx3a5xqEzQuxcrZlxOXLDM1cxp1wbpgJuMcjCt1AO0vgXcFA9z7gPRg7sR4xPxnE2QU9SadWSXPNuh8rBL2eZfdem9Mjb13vvDFx9T5xHPqneA184GVXvo/HI/8ggPxwfMABP8sjQIZQUNlzLUHgLqJAloHLMHUv5YgnloC0G9AwWAsVyCQFEOWKsQhMslFZPIZwYppSfF%2BMqYE4JYVRZMIiU00arT5ZTVIFwnhQx%2BH5xUWooJUjiRGOJMtaRsiOjZOZtdWwljzWK1sUgT6HNenOKBiDdxJT%2BYsAUFqWUWo9W0lGGE5hGMok4zHvCwm8gEnIp0IkUgqT0l01VYzMxrMHGc25h46Nsb42JpbKMOp/TGlbASGa6xdiw3qz%2Bi2oYcbkjJAIoEy4SaCDeSjXEw2cQZnm0tg7RZ87HbO1vu7DZ3tfb%2B1OZgIOIcxAHJrkcwF7zSBnPgZcpmGdkBZ3uYIR5Bci4l1OG8iunz3Y/JjP8lu6lrGdxFOC3u/dB4wuiZmiQCKia5pngW/xxhF42GxZSrqeLMKcDtLvBeR9LAnxyWfDGFK16dHgc4CArhpWMvQOKvQXK6jkZo0AuVuDhVdAEAK8jfKEEzEYyyyVUD6WYNlaUeVKqFAEPxpkstl0NU1phjGuN2oG2fCbYw8JJATVsLaQrTh3DeGUGIfakAZggkJASM1NaARTomeJNo0xUmfW3XuhwgR/hmqiOattDaIjJAiOWuIrgCQlEJEkzkzg7D2nEORrZkLPr/VLDrukZwkggA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_different_from.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_different_from.test.hpp)
