# synchead
Sync C header files with their source

This program is meant to synchronize the header file with its implementation. All the function declarations in the header file may be overridden. The name must include the file name ending (e.g. `asdasd.h` is ok while `asdasd` is not). The source file must have the same name but with ending with `.c`.

## Usage

```
synchead NAME
```

Where:
 - `NAME` is the header file name

## License

![CC0 icon](https://mirrors.creativecommons.org/presskit/buttons/88x31/svg/cc-zero.svg)

This whole repository is licensed using the Creative Commons Zero v1.0 license. For more information, check out the [official web page](https://creativecommons.org/publicdomain/zero/1.0/) and/or the [Wikipedia page](https://en.wikipedia.org/wiki/Creative_Commons_license#Zero_/_public_domain).

[LICENSE file](LICENSE)
