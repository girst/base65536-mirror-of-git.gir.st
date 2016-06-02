# base65536
Reimplementation of [ferno][1]'s [`base65536`][2] in C for UNIXoid shells. 

## Why
 * Why not?
 * beat [Twitter][3] and pack your tweet with 280 characters!
 * Annoy your friends!

## Building
To generate the binary, run `make`.    
If you want long options (e.g. --decode), enable `-DLONG_OPT`. 
To automatically run the included tests, run `make test`. (will rebuild)    
You can copy the resulting `base65536` file to a directory in your `$PATH`.

## Usage
`base65536` uses GNU's [`base64`][4] tool as a reference and therefore has the
same command line arguments. This means, you can either pipe data in or give a
file as an argument. 

### 'Hello World'-Example:

    echo -n "Hello World" | ./base65536

will output:

    驈ꍬ啯𒁗ꍲᕤ

## License
`base65536` is released under the GNU General Public License, version 3.    
See `LICENSE` for details.
&copy; 2016 Tobias Girstmair, [isticktoit.net][5]

## In other Languages
* [JavaScript](https://github.com/ferno/base65536)
* [Python](https://github.com/Parkayun/base65536)
* [Go](https://github.com/Nightbug/go-base65536)
* [Ruby](https://github.com/Nightbug/base65536-ruby)
* [PHP](https://github.com/hevertonfreitas/base65536)

[1]: https://github.com/ferno/
[2]: https://github.com/ferno/base65536
[3]: https://twitter.com/girstmair
[4]: http://linux.die.net/man/1/base64
[5]: http://isticktoit.net/
