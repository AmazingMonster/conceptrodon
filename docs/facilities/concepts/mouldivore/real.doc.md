<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Real`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-real">To Index</a></p>

## Description

`Mouldivore::Real` accepts an element and a class template predicate.
It returns true if the predicate invoked by the element returns true and returns false if otherwise.

<pre><code>   E, Pred
-> Pred&lt;E&gt;::value</code></pre>

## Structure

```C++
template<typename, template<typename...> class>
concept Real = REQUIREMENT;
```

## Examples

`Real` turns a class template predicate into a concept so that it can be used for subsumption.

It accepts the element before the predicate so that the constraint can be applied to the terms inside the parameter list of an ordinary function.

## Implementation

```C++
template<typename Element, template<typename...> class Predicate>
concept Real = Predicate<Element>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCDSAA6oCoRODB7evnoJSY4CQSHhLFEx0naYDilCBEzEBGk%2Bfly2mPY5DJXVBHlhkdGxtlU1dRmNCgOdwd2FvZIAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYca6MyHiYCmfbB8enex87r0eHP2YAzMFkN4sGcTP83AQAJ43AD6BGITEICnB2F%2Bv3enyxm2%2BmLOAEkWHF6GxBExWs8trjsTT9r8CJgiQYGeDITDGKxMGdsCTGARSGcGUzyZhWdCbsw2AA6GWos7ApgKJ7KYiYfCiFn/NHHNAMZZxAhnABKmDEYP%2BFzOKrVeA1oohPMZfNRIBAADcxF57VZjhjaTi/ecACqPAhPF6B2nfemM4kisXsyWYGVS1G/UbELwOM5CTlHBT4wTogDsFjOo3JtvlAlGmFUcWIZwiqE8Zw93i5JlLVDESi7F3BZf7g/RxyFcc1bjTxwzWcNubY%2BcLBFZwRXWpLZYrjmQ1YYtfrjebrfbXrBpYRXuH/yHxYHN9H%2BYI6Fdl8w8PZZyoXgYEBNYlZBdMCXIstTOJgvCIGYRxnZ9XR7WglA/G4vx/CAIKgmCfjebYzhDUZKQDWDK2QWFFSUGoICwYFxUwag0K4GYZldU9MGgh9iJ3MilWiAgIDAMAzmo2haPo38uClRjmPdT02MHDg5loTgAFZeD8DgtFIVBOCnSxrHLBYlk7AEeFIAhNAUuYAGsQGUgA2KUAA47KkZTizsyQAE5/ncgF9E4SReBYCQNA0Uh1M07SOF4BQQDC8yNIU0g4FgGBEBABYCDiSDyEoNAiToaJQk5ThVGcgBaDyzmAZBdykKUzF4G0iGIPAX0afhBBEMR2CkGRBEUFR1ES0hdEaAB3RE4k4HhFJUtSLK0zgAHlIOyw1UCoM4yrsyrJGq2qznqswzggDwCvoRtzH%2BRjeASrQ5ggJB8riQqyAoCAXrekBgCkMw%2BDoBliFiiAIkWiJgmqKEZt4CHmGIKFloibQygS0z8tJAhloYWhoZGrAIi8YA3DERCYdILAWEMYBxHxvBVXKN1HkWusykglZTLXZpFtoPAIkRBGPCwRaETwYLuF4JniGbJQripoxeaMCy5ioAxgAUAA1B5xuWiVyc64RRHEPqDcGtRFrG/RqZQaxrH0PnYsgOZUANFJYo4crRnQcELlMPTLDMSKpdarBHYgOZSnKZwIFcIYGlIQIJgKIpMkSZIBDj1PshSLpk96EZmlRioxkzguWmLjpc56GIRhLzx6j0CsairqYa4jwzlgkOaOFU8LFqi7aKqqmq6skBrTtwQgSDBEyZju5W5gQU0sBicPSBsyR/ilbzi0kDRJDMSQ7NC%2BzPP8jhAtIYL/jMKV/js4tHP%2BRzlOUrgfM8xy%2B5GqKYriszlbJTSk9DKa0cofS%2BpdYqbBSpD32gqIwR1PKSSlJpZqJA2p6ANt1Y20hTZKHNiNXQ/1JpMGmhLbuvcIq8CiqtLKkEzibUHrtKqCDgBIJQRoU651XqXRnjfOeADEqPWeqgC60RcqfTEbw3obCuCeS4GFGgIloggzBiNOGUNyaaIRkjFGDhyYYz5NjXGi0CZExJrQMmEsKaMmprTTS%2BAGaOCZu7NBqg2YMnJlzJSI1eb8yhkLFYmlRbi1MlLGWmA5b2OCKAYRfA1aa21rrRg%2BtZA4N6ng2QZthqaWIVbJWfsrCWHthEMOztXY1k4J7Z8PsinWEDjQ4ObVmZOyaOXaOsd67DATgwdALcU6NCyOnVI3T47DNaAM/O7Si4CHaIMMZjdC5RzaGMKZNd%2BgdFLps5uSdq5d3mIsTujFz5UP7pwZhe15QGEQfIzhE98AtX4bdIRD1F7L16GvGyiiwq%2BMvtfZSUovLKU8mYUFZg7KOXfh5b%2BkVOB/3ioAlK6VMrrUkZAoqJUODVBYFVFgCg3S7jdHc5koYmqPIwe1fqhseoSCyQNAhuSdAgH%2BKQUh5DZqnIWj/FaYCNpbVUHiglRKSUigImdaRb1%2BH/EEfdJKICMXvTypKy67pkBxDiLCYlnlYSktGLCQVeDAaqMoOozSOi8amQtXo1GhixGYxMXjRxmBCbE1Ju7UylN7HBN4E4ouriWYeOQOzbxghuZ%2BL5gLKEQSRatTCZLaIkTokK1iYA1WTB1Za0wDrPWNjsFG0ydSnJFsWUFOMLbEp/jylaUqfuTgqwvY239hYRpWlmmh3gBHZZrQXB9O2YnfI%2Byhlp1aNsiZOc9mtyWR01ZWzFll1mbO3Zg6p21znekeOTdxgrsGe3I5vVKHcrhRwbaQrCVtlFQycVk8nnXReXKpipAl5MBXpQbu/yWW32hQCMwv6uCOQ0HZEFsKaHwtsP/B91lYhb3fi/A%2B/xlKAYBO5c%2B/wj2geiq8yy59GogaWphyDpApZJGcJIIAA%3D)

## Links

- [Example](../../../code/facilities/concepts/mouldivore/real/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/concepts/real.hpp)
- [Unit test](../../../../tests/unit/concepts/mouldivore/real.test.hpp)
