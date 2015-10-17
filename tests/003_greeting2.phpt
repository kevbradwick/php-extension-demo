--TEST--
Check default prefix is Hello
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php
echo demo_ext_greeting2('World');
?>
--EXPECT--
Hello World!
