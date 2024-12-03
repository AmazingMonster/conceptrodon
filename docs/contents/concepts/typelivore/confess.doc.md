<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Confess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::Confess` accepts a callable type predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns true and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> Predicate{}(Elements::value...)</code></pre>

## Structure

```C++
template<typename, typename...>
concept Confess = REQUIREMENT;
```

## Examples

`Confess` turns a callable type predicate into a concept so that it can be used for subsumption.

The following code will fail since `(Pred_0{}(*))` and `(Pred_0{}(*)) && (Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (Pred_0{}(Args::value...))
constexpr bool fun(){return false;}

template<typename...Args>
requires (Pred_0{}(Args::value...)) && (Pred_1{}(Args::value...))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxemUYA1MrEmOgA%2BhqHJv4AIodYyLQEAJ6pmBAmgVaBtxBMXiIADoQasTAB2CynAhbBiHAjELyYG5WcG3MH%2BKwaACCJhx%2BwiwGOpwuXGudwe9Webw%2BXx%2BfwBwNBEKhmBhxDhCKRKIh6J5OLx2IImBYqQMwpubkZqEOAEkbthBXNEQ5DgBZASoIgMF6ClmCw6Gw5zJiOZCHNAMOaYVSpYiHaWHABuYiR10h8rR/NxXsxepxwtF4uR/jcr3ezDYIKB2OIwAUCsFpwAjl48KcFIcICczpd9WiILH4yAQC7vJho6swTjLdbbfbYqhPIcqF4GBAwZDobCW2IlDyvQKAyKxaaQ2GaZGKyCiwn/IqcSm0xmszmLhp839ZyWy0jK6trmYAGzmI%2BrknnLibwtxhQ713ToFVwW14X1w6N5ut9ud1nszmIiGqK3P62Imma5xMAoSitNQbaShqDBagIuqhle84Kh2GIWBw6y0JwgS8H4HBaKQqCcG41jWMamzbJgh7%2BDwpAEJouHrAA1iAgRHkCAAcR5SIE4JHpIST%2BMJZj%2BPonCSLwLASBoGikMRpHkRwvB3kpLEkbhpBwLAMCICAmwEKkgLkJQaCinQCRRKwuyqPxAC0ImHMAyDmlIQJmLwZyECQeDoHo/CCCIYjsFIMiCIoKjqDppC6FwpAAO7EEwqScDweEEURrFkZwADygJmQQhyoFQhyOUeLmSG5HmHF5ZhZh41n0Pa5iMasvDaVo6wQEgVmpDZZAUBAg3DSAwBSGYfB0MKxB3hAsR5bEEQtC8mW8KtzDEC8BWxNo9TaUxVlsIIBUMLQG3xVgsReMAUq0LQd7cLwWAsIYwDiDd6ZHXgTqYC9pE2vUgK7ExETCvh8W0HgsRpbtHhYHlCJ4PJr2kADxCNkotwip9sNGKx6xUAY8YAGp4JgyUFRGm1RcIojiJFIXyEoah5Yl%2BifSgVGWPocN3pA6yoKkfQvU5czoDctymJY1hmKpWPEIFgPwOsdQNM4ECuNMfhJWEiwVFUehFFkAh66bGTmwwwzGys3S9I08yW0lmt9AMrR26M1QTIMrt%2B17Rs%2BxIGu0TsofSRwhHKXlamVc5rnuZ5kjeVmuD%2Be1klcF1zHE%2BsCCYEwWCJB2pCcZI/hAmJ4KSBokhmJIR6KdxKTQ7JpDyYxQICUevFJLxXBHoEkhcIEYlHrH8VqRpIBacTemGf1xnFeZo3jW1dlsJwLQsE64JOUwFoGEcNRAlwQLA/gRAq0FSWs2FzPSKzMUc/Fugzal6Wbdl0e5dPhVV6lXKg6Yge8D5HyeJ9BqSRz6X2aqgVqCQGJmFzj1XSy8N4JAsmNRBQ02ogF3vvJyUCjA1C4EpGgzwEiLWWvFba616YMN2vtQ6Dh6anUYAQC6V08q3Xuo9Z69N3oE12KRfApwGgAyBr5VQoNhT00hj0PKsN4brSRmI7qKt0ZMSxjjTAeMPpGEJqAHSJMyYKEptTWmjB6YPyZhFZ%2BshX5xVIh/bmRM5ZWH5qooWZdRbi04JLAg0s7heIVkrBIt81bC0dn9bWutPAdD0IbcoIckpmz6AHTJ2RvbLF9u7Z2/skn5Ddj0eJ/R5h5JNm7F2JT9aBwWGk/JkcFDhwir/GOKleDxyIRA4%2B0Cz4XyuBADON8GI526vnUghdi5jDLu3OSARYH13BOPcE4J/ANybqPKeqlOCz3nmYxe8Bl4mRKjgrBxAt67F3q5FgCgnTmidGfYMcxfLXwCnfBmj9HEMxcZzAIKU0oZVep0/%2B%2ByOBFVMoCMqFU7m1QeU850ryxxzAQUgrO/h/BoIXpgvBw1LkEoIU81IqRzgvKSOcN5BBIJgJErNahC1KB0NIsw66TF2WsKOhwxBZ1uGXWuuIzAd0HpiCERjERxjNGkAkX9aReUQbIDBoowQyiYZwwRi8DRKNtH0z0RkAx%2BNjGEgXqTJgFMqY0zphjex4UJBOOiuzVxOggUn2MHzGwvj1ZkTFtkF6AB6KWvN5aWEVj05Wqs/Ea3KVrPwOsGDuHqSkxN1SHY5ItsmjJ1s%2BhpoKbGj2dS8gNMKQIT2TSlg1MaQHE0Qdmk1LDlsCOOco5dLjpwUBLB7mPOeai4U6LRmfKxZMvOZiC5FxLpQX%2BHd5JmFgdiwIgR64UI0Ni4SvE9k9IObYOeo7eocRAJXc%2B/heIj0kkuo8klhJR38BCrd6k91sSjj5Td%2BUH3oKrJjGh2RD1AA)

By turning `(Pred_0{}(*))` and `(Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Confess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Confess<Pred_0, Args...> && Confess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept Confess = Predicate{}(Elements::value...);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgZqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJSXaYDplCBEzEBNk%2BfoG2mPZFDPWNBCVRsfGJtg1NLbntCmP94YPlw2YAlLaoXsTI7BwEmCzJBjsmAMxuBACeyYysmADUysSY%2BKI7pDfnl8xsAHQ/2PRsggUx2wJg0AEE0AxNskCDcPAwqJgFAobscACJ3B5PJiHADsVlxaIgf12jAIChAIAAbmIvJgfl8lscrODQWCAPQAKm5PN5fPZbK5PJuABUkeSbryBeChXy5dzpWC2V50kZMY8APoaVFHDFYZC0d6YCAmfxWfxEpheIgMpn4h4EdYMN7EOnMkyEplHFlK8Eq8LAdXoDVcHV6mqGi7G03my3W1C2j0WB1Ol1u70etFen1snZ7A6YY5uK1EG4ASWBbOmrocNwAsgJUEQGGc2Um2TdOzdpji8MgbpDpphVMliDcS6gbjTvLckxXCe7WQuM6zwXn9jjCycjZ96T8wcRgECjiDwQ8AI5ePAPFHwxHIov3TUaV4Ho8Myvgwc7EdjmKoTwbioLwGAgO1k0wR1iGdKgxCUd0F1XMF1wLIsd2uBk32PU8D0wS9ryROEBHvY83CfYMXxuLCPxPVEzAANnMeiiIRJFSPIkNX0PBQaJw79h1HG5/0A4DQPAlNoLTLcCTRNtwR7RxkA1JhkXiAhqBAosGwYJsBFbE4uErE8wOzDgVloTh/F4PwOC0UhUE4NxrGsbs1g2WczCOHhSAITQzJWABrAJJC%2BDRJC4XEjg0fwNAY%2BizAADgS/ROEkXgWAkDQXxsuyHI4XgKRfXzbLM0g4FgGBEBANYCGSa1yEoNA9joeJImuThVAS%2BiAFp6MkG5gGQfspC%2BMxeEeQgSDwdA9H4QQRDEdgpBkQRFBUdQStIXQggAd2IJhkk4HhzMs6y/PszgAHlrTq2FUCoG5Op6vqBqGm4RrMG4IA8Zr6DHcwvKWXhiq0FYICQJrkhasgKAgSHoZAYApCSGhDXiCkIBic6YnCRoziO3gceYYgzkumJtBqYrvKagECEuhhaHxzasBiLxgGLWhaApbheCwFhDGAcRmYI2oqSRc7hxqa0tm88IdgszbaDwGJ9pJjwsHOghiDwDKedIMXiH/JQ0V2AWlaMPyVioAwjwANTwTAdsuj4CZW4RRHEZa5vkJQ1HO7b9AFlBnMsfRlYpSAVlQGFMm57rpnQdFTEsawzFyg3tawCOwI6LpMhcBh3E8Vo9FCOYygqPQCgyAQJj8fI0hrhgBgr4YgmqWoBF6cZi9ydvOkpuoZhboYEnbmY670HsmhHhYx5WBQ3M2CQTo4KzSBy3g8serrev6wbhpCz7iXwIh/s8rggZ8y2VgQTAmCwBIc6CyQji%2BABOI5cUkMKzEkeisr%2BHou/FKHA0qkAyl5L49EuD0QSu/BKsD/DhX8J/eiG9zp5QKiAIqlsyqVXBtVG69VYbwz%2Bm1NgnBGgsCpLibqTABwGDVFwd%2BXwuChXGqfKaM0gjewWp7aQ3s1p%2B02roJIe0DoE1XuvTeF0ODXVqtaG491xzEBoXQhhBoBbvVYew7U31UC/XiHRI4yxgZ4MIWQ%2BIDU4aGKhn9EA1DaHdS0UYFhXAXyox2MQDGWNNpEzxq7AJJMyYUwcK7GmZJ6aM3OizNmHMuauz5mbLYdl8APFFuLTaktkDS1dnLTo50lYqzxurVJwNta628gbI2mATb8yMObUAJUrY2wUPbR2ztGCuz4R7JagjZDCI2nZMRgcLbJysKHYp2co4xwEHHBOScQ4WDTlvDO01xaR1zoPZwEBXCTyCGXUoo8q6N26AclIZzMiz0rv3POXcJ693rtszuPRh7lxOePPoFzp6zGOXPFeqx1jL0vqAmRmDOCqPUfQxh2iWFsNCl9XAk1z6A3MS02%2B99H6UFXuAyBrCwq4lQbiSKkg/59SCLIrBtgcHXxafg%2BAhCaq3RsVY4gFCtjUJeiwBQVJ%2BxUnhQWaYnCUXTVmrIfh/S3ZDP9iAI4pAJGHR5tIs6m08oKNusoh6XL%2Bo8r5VOQVm5phfR%2BvY4xAMjhXxBqVSxdjoasrtQ4vlyRkgagFe/DUQqCDKTUX1PgdBvG%2BOxrjEmQSQ2k3JpTCJhjabRKZmkzArN2ZiESXrZJjTymkHSYPMW3M7I5LyXrApCs7LFNVmcMpmtKmuxqWkOpptGkBjwdbJgdsHZOxdnrXpi0JADNWr7YZOg5VjOMMssOMQZn2TmQwbm7IE7BxTpYVZ9l1lZ3gAvAeryC5FxyM8o58xbmXMKJkC51dug3Lbi87o3dmhPKnpu697z/mHt%2BT8p9B624LyXktFVGC1WQp1TcPV/LDU7GNSfFFJjL7otBpih%2Bwwc4KzxYkVhRwjj%2BBiuFLKaHcRwL/blTg2DcEYtIC/fwH9/AJQYu/SQ79Ipfy4PKhWRxVUEfynS2DoCxr4a3oRjj/l9bo3zpIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/confess.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/confess.test.hpp)
