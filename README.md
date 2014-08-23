RES
---

```sh-session
$ make
  clang res.c -Wall -framework ApplicationServices -o res
$ ./res
    0: 2560 x 1600
    1: 1280 x  800
    2: 2048 x 1280
  * 3: 1650 x 1050
    4: 1440 x  900
    5: 1152 x  720
    6:  840 x  524
    7: 1024 x  768
    8:  800 x  600
    9:  640 x  480
$ ./res 0
  2560x1600
$ 
```
