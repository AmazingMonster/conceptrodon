<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferent`

## Description

`Typelivore::IsDifferent` accepts two elements and checks whether they are different.
The result is returned through member `value`.
<pre><code>Left, Right -> Left != Right ? true : false</code></pre>

## Type Signature

```Haskell
IsDifferent :: typename... -> auto
```

## Structure

```C++
template<typename...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};
```

## Examples

```C++
static_assert(IsDifferent<int, int*>::value);
static_assert(!IsDifferent<int, int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename LeftSide, typename RightSide>
struct IsDifferent
{ static constexpr bool value {true}; };

template<typename Element>
struct IsDifferent<Element, Element>
{ static constexpr bool value {false}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxAGkAA6oCoRODB7evgnJqY4CoeFRLLHxXIF2mA7pQgRMxASZPn7ltpj2%2BQy19QSFkTFxCQp1DU3ZrcM9fcWlAQCUtqhexMjsHASYLIkGGyYAzG4EAJ6JjKyYANTBmFTCeFikF8enzGwXAEp4wAh3WPvYJg0AEFhsQvA4LgBJBQAETwVCocUYBEBQJMAHYLBdJo5kBc0AxhphVIliBdoqhPBcAG5iLyXDEWAhgzAYmH7LFsjmo1EbLY7VkHZ5nN7YehsQT/VGg8EEKGw%2BGI4jI/ZuMWbZGPdUSlF7AHAxnYuq4/ECIkkskUqm07wMzFUMRKLl7Tno9kunnAgD0ACo/f6A17Ub6/QAVbBCUP%2BoPegNxn0xtEGsx7MLIbxYC6qgmrRIEBRSg3AnF4ZAAfSYCiUDQg0LhCKRkoOYQIjxbPv%2BIBANvpc25xeNpYrVbiBAgYDAdcVjd1bhbbab2C7PcwfZdHAWtE4AFZeH5uLxUJw3NZrNilisGSmeKQCJoNwsANYgbeSAB0GkkXHRew0240Zj%2BP4ZgABwgfonCSLwLASBoGikPuWikEeHC8AoIDwXeHBaAscCwDAiAgEsBCJF4rYUBAaBbHQcQROcnCqCB/gALT%2BJIFzAMgeJSG%2BZi8Jg%2BBEMQ9x6PwggiGI7BSDIgiKCo6jYToegAO7EEwiScDwm47nu97IZwADyZGkXKqBUBcjEsWxHFcRcPFmBcEAeNR9BkuYexcHMvBYThpAQEgVGJDRZAUYFwUgMAUhmHwdAbMQ6EQNEenRGE9RHJpvApcwxBHAZ0TaFUWE3lROoGQwtDpYppBYNEXjAG4Yi0OhB7VZshjAOIVX4Mq1TUpgzVIcSVRkWsN4tu0em0Hg0RqTlHhYHpzJ4DBLV9cQFJKDCbVGFNRj3gsVAGMACgAGp4JgykGS8GUycIojiNJYnyEoah6boXD6O1KCnpY%2BjTehkALKgebpM1zHDOg%2BwwqYljWGYSGoGtwlYADEALJU1TOBArhjC0QQMOg0wDGUSQpGkAi43ouTkwwRMlIMH0Y503SjJ4zR6EzNQjL0YT9PTJOTKzWR44LPNFMTEjoxeqySxBHC7ghekoRZTGsexnHce%2BDkQLghAkFm15ebe%2B0LAgmBMFg8Ro6Qz6SHsb4AJx7OikifmYkj%2BHB27%2BA7ctQaQMEeW%2B/jlCBDsgeUr5cNuTuBIhh6cGhGHG4puEEf5RHGWR5CUGFrl0WwnD1Cw1LosxTD4gYRh2Q7b5cB%2B/GCSQIkfU9EkPdIT1ya9VW6NFqnqRl2ny7pVUoUZJFkRcZkXMXpfl5X7U13XH6Oc5QWuQbexmEbPkbn5AWoC5cQ55RR8b4Mc9l%2Bm7VcA7XDwTQtBxQlSVVVlaU3R/OV5QVDg3SVZEZUKp6RqnVBqtAmo3SwCwdqnUkLdUKngPqA1%2BKqGGhsG640txVSmjNNK801hISWitG8a0NqYC2rAnaYRQCpz4EdU651LrXRam3e6UlO6yG7gpJCfdPp7RhlYX6eDUZAxBmaTg4MCCQz2NDH6Fh4aHiRvcfq8B0btCQVjHGbNxj40JrzGYDNSZ5HSJTD61NOh01mIzTRmMujc3MW0DoXMpiGIlozRxuiRbc2sQzKWywZaeTlgreO%2BkOCz2ICXMuFcb7VzvivDQjldZCS3p5byJtSBmwtoMa2OD/aB1rp%2BdEMd0Q/kkO7NiH0wkoSTphfafl05IGIiZU%2BedaL0Q4MXayLAFDUjxNSBJAphiNz1sjUSsh26cNujwt6IA9ikAHhpA8w9QlK0MlnUy5lunsV6f0mkQymAbGGGvc%2BwUt57F3g0jO7SQq5zOa5bsyBEiJDLIMh2ZZhkEArFEtiMVn5xFfslVKOUv4gtyvlQqACj6lXKpVBBmBar1Uas1G8MC4FEN4Ig3qaiqpDWQCNLBggJq4OmrNI4hDFrCVIbwchKRKHbQ6rQhph0mDHTOhdK6jAbrsMkhILhskXq8KUgsquxgFF/WiGI5CEjCScC9BDb6sNLBKOQiolG6jnFaL8NjAmTiQjuP5lTMmnQnGWPSH4gWdjmZeOFhza1riGiWo5ra9mni3HiyNcEhQ0spKrNHgjTgkSWA9L6QMw5xy5Q6ybm5Q2GTU6m3NpbSgw8CkgDMLXPYextz/i/HBLN6J/DgRqYnWwyc95zCfCASQ25HbbhAoBB2kgHY/mdlwUVnA9gBoTqhFOOFh58UVmPUtFaFhrVSM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_different.hpp)
- [unit test](../../../../tests/unit/typelivore/is_different.test.hpp)
