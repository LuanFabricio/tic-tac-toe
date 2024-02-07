# Dependencies
| Name   | Version |
|:------:|:-------:|
|`Raylib`| `5.0`   |
|`clang` | `16.0`  |
|`lld`   | `16.0`  |
|`gcc`   | `13.2`  |

# How can I compile?
Just make sure you have all dependencies installed and run the build script in the terminal.
```terminal
$ ./build.sh
```

# How can I run?
First, compile the game.
## Web
Just start an HTTP server on web folder.
```terminal
$ cd web
$ python -m http.server 3000
```

## Linux
Just run the game on linux folder.
```terminal
$ ./linux/main.out
```
