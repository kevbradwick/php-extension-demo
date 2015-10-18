PHP Extension Example
=====================

This is an example project demonstrating how to create a custom extension in
PHP.

Prerequisites
-------------

You must have the `phpize` and `php-config` installed. If you are using a
package manager for your linux distro, then search for -dev package e.g.

    apt-get install php5-dev

Building this extension
-----------------------

From the root extension source directory, use the phpize tool.

    cd php-extension-demo
    phpize

This will generate a number of file in the directory. You can now configure
the extension;

    ./configure --enable-demo_ex --with-php-config=/path/to/php-config

And finally build the shared module;

    make

Inside the `modules` directory you will find the shared module. Move this to
the modules directory of your php installation and enable the extension by
modifying your php.ini file.

Using the Extension
-------------------

A quick way of running the extension is by including the extension using the `-d`
flag of the interpreter, for example;

    php -dextension=/path/to/demo_ext.so -r 'echo greeting("World");'
