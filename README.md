# c-fun (working title)
A immutuable-first language compiling to C++

## FAQ (not really, but to prevent those question)

### Why a new language?

WebAssembly is at the horizon and will only support C and C++ in the beginning. As those languages are not "functional" enough for me, I decided to design my own language and then compile down to C++. Plus I want to learn about designing a language and have fun :)

### Why C++ as target and not C?

Currently C does not support closures besides an non-standard extension made by Apple. C++11 does.

### I don't like the syntax, how can I change that?

Open an issue! Mention why you don't like a particular part and how you would change it. Then we can discuss it.

### Will this language have a standard library?

Yes. As soon as the compiler is built, the standard library will be written. Currently there are a few features planned:

- Observables (Streams)
- Immutuable data structures
