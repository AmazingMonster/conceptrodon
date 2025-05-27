<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::InvokeResultIn`

<p style='text-align: right;'><a href="../../concepts.md#functivore-invoke-result-in">To Index</a></p>

## Description

`Functivore::InvokeResultIn` accepts a function-like type, a possible return type, and a list of argument type.
It returns true if the function-like type invoked by the argument types returns the possible return type.
If the function-like type is a pointer to a member function, then the first argument shall be the corresponding object type.

## Structure

```C++
template<typename>
concept InvokeResultIn = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Mouldivore::Confess<std::is_invocable_r, Result, Fun, Args...>;
```

Note that since `std::is_invocable_r` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
struct FO;

// This will fail.
static_assert(std::is_invocable_r_v<void, void(FO::*) () volatile &, FO>);
```

The following code will not compile:

```C++
static_assert(InvokeResultIn<void(FO::*) () volatile &, void, FO>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAHKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIJBBEwLDSBgJcIRhOJTFJ8KRz2YbAAdEycbcoUwFJ9lMRMPhRATSLdaYxWJgmQzsPQ2IJsWDcVc0AwtmkCLcPAwqB9PnD7rcuTy8HzMGSJYTGAQFGKcSAQAA3MReI1gqxXEF/AHug5At23ACSRMlZqpOS%2Bhy9HvDZzxVwJ/qpjoRyOFbFuADEvAwBUL6ZhbgAlD5eWgETOJ7Niy7EYAyuWXBVKlU%2Bhg21AAa0w%2BYUhYIjbxYJ1ao1HLJE3Q1rwChREWboli9BRZDzBaLArTGduFarltlcOdwN%2BEc9rqOtwAKh9zSHD/uD0CQRNiF4HKmAPI7qPXHanhDj24AdzotC3FQmK0Ayd4tI4yAouyShtBAI5jhOU6oDOc7ECiNpks2eDoAK2HoBAKbPtaezLLcEBkc2JJ0Dm5j%2BCur6yssb6/J%2BJ7fp8/60IBwF0Lc7J/vUoHgUGUEwQkBAQI2zZth2XY9vC%2BGEcRICkeRlGeEG9CwmY9G3PhDE4sxTocKstCcAArLwfgcFopCoJwbjWNYtwKOsmy0eCPCkAQmimasLYgJIgQMmCACcYXJGCgRRWYgQWZIYLSOZHCSLwLASBoGikDZdkORwvAKCA2W%2BbZpmkHAsAwIgIDrAQaReMWFAQGgRI0cQUQipwqiBP4AC0/iSLcwDIMgtxSAyZi8PqRDEDhej8IIIhiOwUgyIIigqOoZWkLoXCkL%2BGJpJwPBmZZ1l%2BfZnDPo1DUqqgVC3D1/WDcNo3jZIk3kR4bX0MQOlglwyy8KVWirBASCtWk7XkJQUPtSAwBSGYfB0ASxBFRAsSXbEEStIiJ28LjzDEIiz6xNomAOITpCtVKBDPgwtAEztWCxF4wBuGItBFdwvBYCwhjAOIrN4NyDh4DaHyXZgqhU412zeREBIpXZtB4LEGKkx4WCXeieAZXzpBS8QsSZJgjyC0Y6tGH5qxUAYVYAGrvL%2Bz50jTi3CKI4hrV7m1qJde36ELKDOZY%2Bga0VkCrKgyo5LzfUjtqpiWNYZh5Sbc1YNHFE9FTjQuAw7ieJ0ehhBEwxVKM%2B3FNkAjTH4teZPXDALCMiT7XYBd9JM7SlwUXf1D3Aj9G07fV53th943ehzOPleLDXqxuRsWwSGdHBWTll35U9vUDUNI1jRNZjkbghAkADQMg3bqwIJgTBYIkeeBYlDJhWCySSBokhmJI/gsoWX8GFfQnA0qkAyoDBk/guBBDCoEOBCUuAWU/vRXKvB8qFWKj5O2FVqoQ1qrdRqsMWqoF%2BgkTqbBOCtBYDaZIfUmCsgMEYcaYUGRcAZHZGaJB5r7S9stX20h/ZKEDjtXQKNDpMGOnzTe28MFXQ4DdeqjVbgPX3i9IabJWFcHYZwjQ31yHQz%2BgDMwwNcFlXBpDIxMNmrwz%2BigFhSMwpcGyjQIsCRMbYx2sTfGNNfGk3JpTamRs6ZmkZszS6bMOZc24rzbyAshYizsvgcWjgpa824XLZACsabK3qJddWmt8Y622HZfWhtvImzNkoS2SSIigEsXwR2CgXaYDdh7I2AifarWEbIAO207ISJDrbVOVgI5FNzrHeOAhE7Jz7GM9OmcEjZ2ljHfOEtnAQFcLPfaFcKgdz0HXRouz0gt0aBPJYQ9eijxngPJuGzGhj0GIvQ5Xc7n5AefPF5BzJ4bzWGvVaciLo7T3s9Q%2BzChZsI4Vw8%2B%2BBZrX3MaDfypAH5P1GHnFKECoHsN/skVByQop/wAZIfaCisG2Bwci8GBCkB1TuqQ%2BxlCuocFoa9FgCgbRjRtLohkJJzzTXhbw0c/DZCCN6eteQojBk6BAGCA6R1CbAp3qC66xD7qPVUOyzl3LeX8omIYih/1zBgjBEivBhCmVkDsTYhxXK0hpAwrolE%2BqCAoi1cItGnjKDeLsgElm3l/VBILjTMJggIksxSZgdmnNubxP5oSJJZT%2BZix7hkmW2TclG3yarXgRStaIlKXrOalTeDVPNnU62DS8EOyYM7V27tGCezFT0iQfSNrSqDnKkZxhw42EmfAaZjReY7AQosywGdMFZxwmsvO3dNl%2BG2cXU5%2Byq5XLOSUHIpzjk5EuTXR5vcBinPnU8vue6p7fOPWe15fygYAo8v8lK8jd6cCetqrl%2Bk9VxgNRAC%2BCKTU3wsWDe%2Bj9n6UE3tipI7DTUWQsr/VxGhTXJG6OSzg2CSp31IIFCynDAEaF0lwXSyQpDANg2AjgYIQV5TQ0BlFKUpoquowVWjyxVgmyyM4SQQA)

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/invoke_result_in.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/invoke_result_in.test.hpp)
