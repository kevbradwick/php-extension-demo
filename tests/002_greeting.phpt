--TEST--
Output Hello World!
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php
echo greeting('World');
?>
--EXPECT--
Hello World!
