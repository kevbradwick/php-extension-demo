--TEST--
Check default prefix is Hello
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php echo greeting_alt('World'); ?>
--EXPECT--
Hello World!
